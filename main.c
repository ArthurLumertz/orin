// import x

#include <stdio.h>

#include <orin.h>
#include <orinmath.h>

// import orin

void main() {

    DisplayMode display_mode;
    display_mode.width = 800;
    display_mode.height = 600;

    Display *display = CreateDisplay(display_mode, "Game", OPENGL_33);

    Shader *shader = CreateDefaultShader();

    Camera2D camera;
    camera.position = (Vector2f) { 0, 0 };
    camera.zoom = 1;

    while (!DisplayShouldClose(display)) {
        ClearBackground(BLACK);

        BeginDrawing(shader, camera);
        DrawRectangle((Vector2f){0, 0}, (Vector2f){48,48}, RED);
        EndDrawing();

        UpdateDisplay(display);
    }

    DestroyDisplay(display);

}