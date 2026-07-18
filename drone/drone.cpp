#include <iostream>
#include <cmath>

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

struct Drone {
    float altitude = 0, velocity = 0, mass = 1.0f, gravity = 9.81f;
    void applyThrust(float thrust, float dt) {
        float accel = (thrust - mass * gravity) / mass;
        velocity += accel * dt;
        altitude += velocity * dt;
    }
};

int main() {
    Drone drone;
    PID altPID{2.0f, 0.1f, 1.0f};
    float target = 10.0f;
    float dt = 0.1f;

    for (int i = 0; i < 100; i++) {
        float thrust = altPID.update(target, drone.altitude, dt) + drone.mass * drone.gravity;
        drone.applyThrust(thrust, dt);
        std::cout << "t=" << i * dt << " alt=" << drone.altitude << "\n";
    }
    return 0;
}