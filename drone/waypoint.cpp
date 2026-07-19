#include <iostream>
#include <vector>
#include <cmath>

struct Vec3 { float x, y, z; };

enum class State { IDLE, TAKEOFF, ENROUTE, HOVER, LANDING };

struct Waypoint { Vec3 pos; float holdTime; };

class Mission {
    std::vector<Waypoint> waypoints;
    size_t idx = 0;
    State state = State::IDLE;
    Vec3 pos{0,0,0};
    float timer = 0;

    float dist(const Vec3& a, const Vec3& b) {
        return std::sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
    }

public:
    void addWaypoint(Vec3 p, float hold) { waypoints.push_back({p, hold}); }

    void tick(float dt) {
        switch (state) {
            case State::IDLE:
                state = State::TAKEOFF;
                break;
            case State::TAKEOFF:
                pos.z += 1.0f * dt;
                if (pos.z >= 5.0f) state = State::ENROUTE;
                break;
            case State::ENROUTE: {
                if (idx >= waypoints.size()) { state = State::LANDING; break; }
                Vec3& target = waypoints[idx].pos;
                Vec3 dir{target.x-pos.x, target.y-pos.y, target.z-pos.z};
                float d = dist(pos, target);
                if (d < 0.2f) { state = State::HOVER; timer = 0; break; }
                float speed = 2.0f;
                pos.x += (dir.x/d) * speed * dt;
                pos.y += (dir.y/d) * speed * dt;
                pos.z += (dir.z/d) * speed * dt;
                break;
            }
            case State::HOVER:
                timer += dt;
                if (timer >= waypoints[idx].holdTime) {
                    idx++;
                    state = State::ENROUTE;
                }
                break;
            case State::LANDING:
                pos.z -= 1.0f * dt;
                if (pos.z <= 0) pos.z = 0;
                break;
        }
    }

    Vec3 position() const { return pos; }
    State currentState() const { return state; }
};

int main() {
    Mission m;
    m.addWaypoint({10, 0, 5}, 2.0f);
    m.addWaypoint({10, 10, 5}, 2.0f);
    m.addWaypoint({0, 0, 5}, 1.0f);

    float dt = 0.1f;
    for (int i = 0; i < 400; i++) {
        m.tick(dt);
        Vec3 p = m.position();
        std::cout << "t=" << i*dt << " pos=(" << p.x << "," << p.y << "," << p.z << ")\n";
    }
    return 0;
}