#include <iostream>
#include <array>
#include <cmath>

// Quadcopter X-frame motor mixer: takes thrust/roll/pitch/yaw -> 4 motor PWM values
struct MotorMixer {
    float minPWM = 1000, maxPWM = 2000;

    std::array<float,4> mix(float thrust, float roll, float pitch, float yaw) {
        // motor order: 0=FL, 1=FR, 2=RL, 3=RR
        std::array<float,4> m;
        m[0] = thrust - roll + pitch + yaw;
        m[1] = thrust + roll + pitch - yaw;
        m[2] = thrust - roll - pitch - yaw;
        m[3] = thrust + roll - pitch + yaw;
        for (auto& v : m) v = clamp(v);
        return m;
    }

    float clamp(float v) {
        if (v < minPWM) return minPWM;
        if (v > maxPWM) return maxPWM;
        return v;
    }
};

// Simple IMU sim: adds noise to true attitude to mimic sensor readings
struct IMU {
    float noiseLevel = 0.02f;

    float readRoll(float trueRoll) { return trueRoll + noise(); }
    float readPitch(float truePitch) { return truePitch + noise(); }
    float readYaw(float trueYaw) { return trueYaw + noise(); }

private:
    float noise() {
        return ((rand() % 1000) / 1000.0f - 0.5f) * noiseLevel;
    }
};

// Telemetry logger: batches and prints state at intervals
struct Telemetry {
    float logInterval = 0.5f;
    float timer = 0;

    void update(float dt, float alt, float roll, float pitch, float yaw) {
        timer += dt;
        if (timer >= logInterval) {
            std::cout << "[TELEM] alt=" << alt
                      << " roll=" << roll
                      << " pitch=" << pitch
                      << " yaw=" << yaw << "\n";
            timer = 0;
        }
    }
};

int main() {
    MotorMixer mixer;
    IMU imu;
    Telemetry telem;

    float trueRoll = 0.1f, truePitch = -0.05f, trueYaw = 0.0f, alt = 5.0f;
    float dt = 0.1f;

    for (int i = 0; i < 50; i++) {
        float roll = imu.readRoll(trueRoll);
        float pitch = imu.readPitch(truePitch);
        float yaw = imu.readYaw(trueYaw);

        auto motors = mixer.mix(1500, roll * 100, pitch * 100, yaw * 100);

        std::cout << "t=" << i*dt << " motors: "
                  << motors[0] << " " << motors[1] << " "
                  << motors[2] << " " << motors[3] << "\n";

        telem.update(dt, alt, roll, pitch, yaw);
    }
    return 0;
}