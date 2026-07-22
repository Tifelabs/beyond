#include "raylib.h"

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "SONIC DRONES");

    SetTargetFPS(60);

    while(!WindowShouldClose()){

        BeginDrawing();
        ClearBackground(RAYWHITE);
        
        DrawText("Initializing Drone Configs!", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
}