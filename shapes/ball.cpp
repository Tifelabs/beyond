#include <iostream>
#include <fstream>
#include <cmath>

// Image dimensions
const int WIDTH = 640;
const int HEIGHT = 480;

// Ball properties
const float BALL_RADIUS = 2.0f;
const float BALL_Y_POS = 1.0f; // Initial Y position of the ball
const float BALL_BOUNCE_HEIGHT = 5.0f; // Maximum height of the bounce
const float GRAVITY = 9.81f; // Gravity constant

// Light position
const float LIGHT_X = 5.0f;
const float LIGHT_Y = 10.0f;
const float LIGHT_Z = 5.0f;

// Function to compute the Y position of the ball at a given time
float computeBallY(float time) {
    // Simulate a bouncing motion using a parabolic trajectory
    float t = fmod(time, 2.0f * sqrt(2.0f * BALL_BOUNCE_HEIGHT / GRAVITY));
    float y = BALL_BOUNCE_HEIGHT - 0.5f * GRAVITY * t * t;
    return (y < BALL_Y_POS) ? BALL_Y_POS : y; // Ensure the ball doesn't go below the ground
}

// Function to check if a ray intersects the ball
bool intersectBall(float rayOriginX, float rayOriginY, float rayOriginZ,
                   float rayDirX, float rayDirY, float rayDirZ,
                   float ballX, float ballY, float ballZ, float radius) {
    // Vector from ray origin to ball center
    float ocX = rayOriginX - ballX;
    float ocY = rayOriginY - ballY;
    float ocZ = rayOriginZ - ballZ;

    // Coefficients for the quadratic equation
    float a = rayDirX * rayDirX + rayDirY * rayDirY + rayDirZ * rayDirZ;
    float b = 2.0f * (ocX * rayDirX + ocY * rayDirY + ocZ * rayDirZ);
    float c = ocX * ocX + ocY * ocY + ocZ * ocZ - radius * radius;

    // Discriminant
    float discriminant = b * b - 4 * a * c;

    // If discriminant is positive, the ray intersects the ball
    return (discriminant >= 0);
}

// Function to render the scene
void renderScene(float time, const std::string& filename) {
    // Create a PPM image file
    std::ofstream image(filename);
    image << "P3\n" << WIDTH << " " << HEIGHT << "\n255\n"; // PPM header

    // Camera position
    float cameraX = 0.0f;
    float cameraY = 0.0f;
    float cameraZ = 10.0f;

    // Ball position
    float ballX = 0.0f;
    float ballY = computeBallY(time);
    float ballZ = 0.0f;

    // Ray tracing loop
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            // Normalize pixel coordinates to [-1, 1]
            float pixelX = (2.0f * x / WIDTH - 1.0f) * (WIDTH / (float)HEIGHT);
            float pixelY = 1.0f - 2.0f * y / HEIGHT;

            // Ray direction
            float rayDirX = pixelX - cameraX;
            float rayDirY = pixelY - cameraY;
            float rayDirZ = -1.0f; // Camera looks along the negative Z-axis

            // Normalize ray direction
            float length = sqrt(rayDirX * rayDirX + rayDirY * rayDirY + rayDirZ * rayDirZ);
            rayDirX /= length;
            rayDirY /= length;
            rayDirZ /= length;

            // Check if the ray intersects the ball
            bool hitBall = intersectBall(cameraX, cameraY, cameraZ,
                                         rayDirX, rayDirY, rayDirZ,
                                         ballX, ballY, ballZ, BALL_RADIUS);

            // Shadow ray
            bool inShadow = false;
            if (hitBall) {
                // Point of intersection
                float hitX = cameraX + rayDirX * length;
                float hitY = cameraY + rayDirY * length;
                float hitZ = cameraZ + rayDirZ * length;

                // Shadow ray direction (from hit point to light)
                float shadowDirX = LIGHT_X - hitX;
                float shadowDirY = LIGHT_Y - hitY;
                float shadowDirZ = LIGHT_Z - hitZ;

                // Normalize shadow ray direction
                length = sqrt(shadowDirX * shadowDirX + shadowDirY * shadowDirY + shadowDirZ * shadowDirZ);
                shadowDirX /= length;
                shadowDirY /= length;
                shadowDirZ /= length;

                // Check if the shadow ray intersects the ball
                inShadow = intersectBall(hitX, hitY, hitZ,
                                         shadowDirX, shadowDirY, shadowDirZ,
                                         ballX, ballY, ballZ, BALL_RADIUS);
            }

            // Set pixel color
            if (hitBall) {
                if (inShadow) {
                    image << "100 100 100 "; // Shadow color (gray)
                } else {
                    image << "255 0 0 "; // Ball color (red)
                }
            } else {
                image << "0 0 0 "; // Background color (black)
            }
        }
        image << "\n";
    }

    image.close();
}

int main() {
    float time = 0.0f; 
    renderScene(time, "ball.ppm"); 
    std::cout << "Rendered bouncing_ball.ppm" << std::endl;
    return 0;
}