#include "raylib.h"
#include <vector>
#include <array>
#include <cmath>

struct Vec3f { float x, y, z; };

// ---- PID ----
struct PID {
    float kp, ki, kd, prevErr = 0, integral = 0;
    float update(float target, float actual, float dt) {
        float err = target - actual;
        integral += err * dt;
        float deriv = (err - prevErr) / dt;
        prevErr = err;
        return kp * err + ki * integral + kd * deriv;
    }
};

// ---- Drone physics ----
struct Drone {
    Vec3f pos{0,0,0}, vel{0,0,0};
    float mass = 1.0f, gravity = 9.81f, drag = 0.4f;
    void applyForce(Vec3f force, float dt) {
        vel.x += (force.x / mass - drag * vel.x) * dt;
        vel.y += (force.y / mass - drag * vel.y) * dt;
        vel.z += (force.z / mass - drag * vel.z) * dt;
        pos.x += vel.x * dt;
        pos.y += vel.y * dt;
        pos.z += vel.z * dt;
        if (pos.y < 0) { pos.y = 0; vel.y = 0; }
    }
};

// ---- Mission (autopilot mode) ----
struct Waypoint { Vec3f pos; float holdTime; };
enum class MState { TAKEOFF, ENROUTE, HOVER, LANDING, DONE };

struct Mission {
    std::vector<Waypoint> waypoints;
    size_t idx = 0;
    MState state = MState::TAKEOFF;
    float timer = 0;

    Vec3f currentTarget(Vec3f pos) {
        if (state == MState::TAKEOFF) return { pos.x, 5.0f, pos.z };
        if (idx < waypoints.size()) return waypoints[idx].pos;
        return pos;
    }

    void tick(Vec3f pos, float dt) {
        switch (state) {
            case MState::TAKEOFF:
                if (pos.y >= 4.8f) state = MState::ENROUTE;
                break;
            case MState::ENROUTE: {
                if (idx >= waypoints.size()) { state = MState::LANDING; break; }
                Vec3f t = waypoints[idx].pos;
                float d = std::sqrt(std::pow(t.x-pos.x,2)+std::pow(t.y-pos.y,2)+std::pow(t.z-pos.z,2));
                if (d < 0.3f) { state = MState::HOVER; timer = 0; }
                break;
            }
            case MState::HOVER:
                timer += dt;
                if (timer >= waypoints[idx].holdTime) { idx++; state = MState::ENROUTE; }
                break;
            case MState::LANDING:
                if (pos.y <= 0.05f) state = MState::DONE;
                break;
            case MState::DONE:
                break;
        }
    }
};

// ---- Motor mixer ----
struct MotorMixer {
    std::array<float,4> mix(float thrust, float roll, float pitch, float yaw) {
        std::array<float,4> m;
        m[0] = thrust - roll + pitch + yaw;
        m[1] = thrust + roll + pitch - yaw;
        m[2] = thrust - roll - pitch - yaw;
        m[3] = thrust + roll - pitch + yaw;
        for (auto& v : m) v = fmaxf(1000, fminf(2000, v));
        return m;
    }
};

// deadzone helper, PS4 sticks rest around 0 but drift a little
float deadzone(float v, float dz = 0.12f) {
    if (fabsf(v) < dz) return 0.0f;
    return v;
}

int main() {
    InitWindow(1000, 700, "Drone Sim");
    SetTargetFPS(60);

    Camera3D camera = { 0 };
    camera.position = { 15, 12, 15 };
    camera.target = { 0, 3, 0 };
    camera.up = { 0, 1, 0 };
    camera.fovy = 50;
    camera.projection = CAMERA_PERSPECTIVE;

    Drone drone;
    Mission mission;
    mission.waypoints = { {{5,5,5}, 1.5f}, {{5,5,-5}, 1.5f}, {{-5,5,-5}, 1.5f}, {{0,5,0}, 1.0f} };
    MotorMixer mixer;

    PID pidX{1.5f, 0.02f, 1.0f};
    PID pidY{4.0f, 0.3f, 2.0f};
    PID pidZ{1.5f, 0.02f, 1.0f};

    std::vector<Vec3f> trail;
    bool manualMode = true;
    int gamepad = 0;

    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        if (dt > 0.05f) dt = 0.05f;

        if (IsKeyPressed(KEY_M)) manualMode = !manualMode;

        float fx = 0, fy = 0, fz = 0;
        std::array<float,4> motors{1500,1500,1500,1500};
        bool padOK = IsGamepadAvailable(gamepad);

        if (manualMode && padOK) {
            // PS4 layout: left stick = throttle/yaw, right stick = pitch/roll
            float throttle = -deadzone(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_Y));
            float yaw      =  deadzone(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_LEFT_X));
            float roll     =  deadzone(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_X));
            float pitch    = -deadzone(GetGamepadAxisMovement(gamepad, GAMEPAD_AXIS_RIGHT_Y));

            fx = roll * 6.0f;
            fz = -pitch * 6.0f;
            fy = drone.mass * drone.gravity + throttle * 15.0f;

            motors = mixer.mix(fy, fx, fz, yaw * 4.0f);
            drone.applyForce({ fx, fy - drone.mass * drone.gravity, fz }, dt);
        } else if (manualMode && !padOK) {
            // fallback: WASD + space/shift if controller isn't detected
            float throttle = (IsKeyDown(KEY_SPACE) ? 1.0f : 0.0f) - (IsKeyDown(KEY_LEFT_SHIFT) ? 1.0f : 0.0f);
            fx = (IsKeyDown(KEY_D) ? 1.0f : 0.0f) - (IsKeyDown(KEY_A) ? 1.0f : 0.0f);
            fz = (IsKeyDown(KEY_S) ? 1.0f : 0.0f) - (IsKeyDown(KEY_W) ? 1.0f : 0.0f);
            fx *= 6.0f; fz *= 6.0f;
            fy = drone.mass * drone.gravity + throttle * 15.0f;
            drone.applyForce({ fx, fy - drone.mass * drone.gravity, fz }, dt);
            motors = mixer.mix(fy, fx, fz, 0);
        } else {
            // autopilot mode (mission)
            mission.tick(drone.pos, dt);
            Vec3f target = mission.currentTarget(drone.pos);
            fx = pidX.update(target.x, drone.pos.x, dt);
            fy = pidY.update(target.y, drone.pos.y, dt) + drone.mass * drone.gravity;
            fz = pidZ.update(target.z, drone.pos.z, dt);
            motors = mixer.mix(fy, fx, fz, 0);
            float totalLift = (motors[0]+motors[1]+motors[2]+motors[3] - 4000) * 0.02f;
            drone.applyForce({ fx, totalLift, fz }, dt);
        }

        trail.push_back(drone.pos);
        if (trail.size() > 300) trail.erase(trail.begin());

        UpdateCamera(&camera, CAMERA_ORBITAL);

        BeginDrawing();
        ClearBackground(RAYWHITE);
        BeginMode3D(camera);

        DrawGrid(20, 1.0f);
        Vector3 dp = { drone.pos.x, drone.pos.y, drone.pos.z };
        DrawCube(dp, 0.6f, 0.15f, 0.6f, RED);
        DrawCubeWires(dp, 0.6f, 0.15f, 0.6f, MAROON);

        if (!manualMode) {
            for (auto& w : mission.waypoints)
                DrawSphereWires({w.pos.x, w.pos.y, w.pos.z}, 0.3f, 6, 6, BLUE);
        }

        for (size_t i = 1; i < trail.size(); i++) {
            Vector3 a = { trail[i-1].x, trail[i-1].y, trail[i-1].z };
            Vector3 b = { trail[i].x, trail[i].y, trail[i].z };
            DrawLine3D(a, b, GREEN);
        }

        EndMode3D();

        DrawText(TextFormat("mode: %s  (press M to toggle)", manualMode ? "MANUAL" : "AUTOPILOT"), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("gamepad: %s", padOK ? GetGamepadName(gamepad) : "not detected (using WASD fallback)"), 10, 35, 20, DARKGRAY);
        DrawText(TextFormat("pos: %.2f %.2f %.2f", drone.pos.x, drone.pos.y, drone.pos.z), 10, 60, 20, DARKGRAY);
        DrawText(TextFormat("motors: %.0f %.0f %.0f %.0f", motors[0], motors[1], motors[2], motors[3]), 10, 85, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}