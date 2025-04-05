# Orin
orin is a game framework built for those seeking a new game development experience, for experienced and amateur developers.
it's made for people to turn ideas into games without requiring extensive knowledge of game development but also have low level
and advanced features built in to it.

this library is still being developed, expect significant changes over the year.

# Features
- display handling
- textures
- key/mouse input
- vectors and matrices
- _audio will be coming soon_

# Basic display
```c
/**
 * Orin Framework, 2025
 * Basic window example
 *
 * This program demonstrates on how to:
 * - Create a window
 * - Set up a camera and shader
 * - Render a rectangle centered in the center of the screen
 */

#include <orin.h>

int main() {
    // DisplayMode contains the width and the height of the screen
    DisplayMode displayMode = { 800, 600 };

    /**
     * CreateDisplay(DisplayMode, title, args)
     * Here, we are creating a 800 by 600 pixels display
     * called "Game", this window will be using OpenGL 3.3,
     * OpenGL 2.1 and 4.6 are also supported.
     */
    Display *display = CreateDisplay(displayMode, "Game", OPENGL_33);

    /**
     * This is a shader, the base of how rendering works in modern OpenGL
     * CreateDefaultShader() returns a basic shader with the intention of being
     * used for simple or prototype games, you can write your own shaders and
     * load them here using CreateShader(vertexFile, fragmentFile)
     *
     * IMPORTANT: The default shader does NOT work with any other OpenGL version
     * that is not 3.3!
     */
    Shader *shader = CreateDefaultShader();

    /**
     * This is the camera, the essential component to follow the player and etc.
     * Contains basic properties for now since I haven't added 3D OpenGL yet.
     */
    Camera2D camera;
    camera.position = (Vector2f) { 0, 0 }; // Base (x: 0, y: 0) position
    camera.zoom = 1; // Zoom set to 1 (default)

    // Game loop, while the display shouldn't close
    while (!DisplayShouldClose(display)) {
        // Clear the background buffer with red
        ClearBackground(RED);

        /**
         * BeginDrawing(Shader, Camera2D)
         * Needs a shader and a camera to properly work.
         */
        BeginDrawing(shader, camera);

        /**
         * Vector2f is a struct with two values
         * x: float
         * y: float
         */
        Vector2f size = { 64, 64 }; // Size is 64x64

        // Making the position centered on the display
        Vector2f position = { (displayMode.width - size.x) / 2, (displayMode.height - size.y) / 2 };

        /**
         * DrawRectangle(Vector2f position, Vector2 size, Color color)
         * Draws the rectangle to the specified position and size
         * The transformation and color is later processed inside the shaders
         */
        DrawRectangle(position, size, WHITE);

        EndDrawing(); // End the drawing context

        // Swap the buffers and poll event the GLFW display
        UpdateDisplay(display);
    }

    // Clean up display resources and close the window
    DestroyDisplay(display);

    return 0;
}
```
