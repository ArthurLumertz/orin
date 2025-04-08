#ifndef ORIN_H
#define ORIN_H

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 201112L)
    #if !defined(_MSC_VER) || (_MSC_VER < 1900)
        #error "C11 or newer is required to compile this project."
    #endif
#endif

#ifndef ORAPI
    #ifdef _WIN32
        #ifdef ORAPI_EXPORTS
            #define ORAPI __declspec(dllexport)
        #else
            #define ORAPI __declspec(dllimport)
        #endif
    #else
        #define ORAPI
    #endif
#endif


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdbool.h>

#define RESIZABLE   (1 << 0)
#define VSYNC       (1 << 1)
#define FULLSCREEN  (1 << 2)
#define OPENGL_46   (1 << 3)
#define OPENGL_33   (1 << 4)
#define OPENGL_21   (1 << 5)

#define DEFAULT_DISPLAY 0

#define NEAREST GL_NEAREST
#define LINEAR  GL_LINEAR

typedef enum {
    KEY_UNKNOWN = -1,
    KEY_SPACE = 32,
    KEY_APOSTROPHE = 39,
    KEY_COMMA = 44,
    KEY_MINUS = 45,
    KEY_PERIOD = 46,
    KEY_SLASH = 47,
    KEY_0 = 48,
    KEY_1 = 49,
    KEY_2 = 50,
    KEY_3 = 51,
    KEY_4 = 52,
    KEY_5 = 53,
    KEY_6 = 54,
    KEY_7 = 55,
    KEY_8 = 56,
    KEY_9 = 57,
    KEY_SEMICOLON = 59,
    KEY_EQUAL = 61,
    KEY_A = 65,
    KEY_B = 66,
    KEY_C = 67,
    KEY_D = 68,
    KEY_E = 69,
    KEY_F = 70,
    KEY_G = 71,
    KEY_H = 72,
    KEY_I = 73,
    KEY_J = 74,
    KEY_K = 75,
    KEY_L = 76,
    KEY_M = 77,
    KEY_N = 78,
    KEY_O = 79,
    KEY_P = 80,
    KEY_Q = 81,
    KEY_R = 82,
    KEY_S = 83,
    KEY_T = 84,
    KEY_U = 85,
    KEY_V = 86,
    KEY_W = 87,
    KEY_X = 88,
    KEY_Y = 89,
    KEY_Z = 90,
    KEY_LEFT_BRACKET = 91,
    KEY_BACKSLASH = 92,
    KEY_RIGHT_BRACKET = 93,
    KEY_GRAVE = 96,
    KEY_ESCAPE = 256,
    KEY_ENTER = 257,
    KEY_TAB = 258,
    KEY_BACKSPACE = 259,
    KEY_INSERT = 260,
    KEY_DELETE = 261,
    KEY_RIGHT = 262,
    KEY_LEFT = 263,
    KEY_DOWN = 264,
    KEY_UP = 265,
    KEY_PAGE_UP = 266,
    KEY_PAGE_DOWN = 267,
    KEY_HOME = 268,
    KEY_END = 269,
    KEY_CAPS_LOCK = 280,
    KEY_SCROLL_LOCK = 281,
    KEY_NUM_LOCK = 282,
    KEY_PRINT_SCREEN = 283,
    KEY_PAUSE = 284,
    KEY_F1 = 290,
    KEY_F2 = 291,
    KEY_F3 = 292,
    KEY_F4 = 293,
    KEY_F5 = 294,
    KEY_F6 = 295,
    KEY_F7 = 296,
    KEY_F8 = 297,
    KEY_F9 = 298,
    KEY_F10 = 299,
    KEY_F11 = 300,
    KEY_F12 = 301,
    KEY_F13 = 302,
    KEY_F14 = 303,
    KEY_F15 = 304,
    KEY_F16 = 305,
    KEY_F17 = 306,
    KEY_F18 = 307,
    KEY_F19 = 308,
    KEY_F20 = 309,
    KEY_F21 = 310,
    KEY_F22 = 311,
    KEY_F23 = 312,
    KEY_F24 = 313,
    KEY_F25 = 314,
    KEY_KP_0 = 320,
    KEY_KP_1 = 321,
    KEY_KP_2 = 322,
    KEY_KP_3 = 323,
    KEY_KP_4 = 324,
    KEY_KP_5 = 325,
    KEY_KP_6 = 326,
    KEY_KP_7 = 327,
    KEY_KP_8 = 328,
    KEY_KP_9 = 329,
    KEY_KP_DECIMAL = 330,
    KEY_KP_DIVIDE = 331,
    KEY_KP_MULTIPLY = 332,
    KEY_KP_SUBTRACT = 333,
    KEY_KP_ADD = 334,
    KEY_KP_ENTER = 335,
    KEY_KP_EQUAL = 336,
    KEY_LEFT_SHIFT = 340,
    KEY_LEFT_CONTROL = 341,
    KEY_LEFT_ALT = 342,
    KEY_LEFT_SUPER = 343,
    KEY_RIGHT_SHIFT = 344,
    KEY_RIGHT_CONTROL = 345,
    KEY_RIGHT_ALT = 346,
    KEY_RIGHT_SUPER = 347,
    KEY_MENU = 348,
    KEY_LAST = KEY_MENU
} Key;

typedef enum {
    BUTTON_1 = 0,
    BUTTON_2 = 1,
    BUTTON_3 = 2,
    BUTTON_4 = 3,
    BUTTON_5 = 4,
    BUTTON_6 = 5,
    BUTTON_7 = 6,
    BUTTON_8 = 7,
    BUTTON_LAST = 7,
    BUTTON_LEFT = BUTTON_1,
    BUTTON_RIGHT = BUTTON_2,
    BUTTON_MIDDLE = BUTTON_3
} Button;

typedef struct {
    unsigned int width;
    unsigned int height;
} DisplayMode;

typedef struct {
    GLFWwindow* handler;
    DisplayMode displayMode;
} Display;

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

#ifndef ORIN_VEC2
    #define ORIN_VEC2
    typedef struct {
        float x;
        float y;
    } Vector2f;

    typedef struct {
        int x;
        int y;
    } Vector2i;
#endif

#ifndef ORIN_VEC3
    #define ORIN_VEC3
    typedef struct {
        float x;
        float y;
        float z;
    } Vector3f;

    typedef struct {
        int x;
        int y;
        int z;
    } Vector3i;
#endif

#ifndef ORIN_VEC4
    #define ORIN_VEC4
    typedef struct {
        float x;
        float y;
        float z;
        float w;
    } Vector4f;

    typedef struct {
        int x;
        int y;
        int z;
        int w;
    } Vector4i;
#endif

#ifndef ORIN_MAT4
    #define ORIN_MAT4
    typedef struct Matrix4f {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    } Matrix4f;
#endif

typedef struct {
    Vector2f position;
    float zoom;
} Camera2D;

typedef struct {
    unsigned int id;
    int width;
    int height;
    int channels;
} Texture;

typedef struct {
    unsigned int id;
} Shader;

typedef struct {
    Vector2f position;
    Vector2f uv;
    Vector2f normals;
    Color color;
} Vertex;

typedef struct {
    unsigned int vao;
    unsigned int vbo;
    unsigned int ebo;
    Vertex *vertices;
    unsigned int *indices;
    size_t vertexCount;
    size_t indexCount;
} Model;

typedef struct {
    float x;
    float y;
    float width;
    float height;
} Rectangle;

typedef struct {
    int x;
    int y;
    int width;
    int height;
} RectangleI;

typedef struct {
    Vector3f min;
    Vector3f max;
} BoundingBox;

typedef struct {
    Vector3i min;
    Vector3i max;
} BoundingBoxI;

#define WHITE           ((Color){255, 255, 255, 255})
#define BLACK           ((Color){0, 0, 0, 255})
#define GRAY            ((Color){169, 169, 169, 255})
#define LIGHT_GRAY      ((Color){211, 211, 211, 255})
#define DARK_GRAY       ((Color){105, 105, 105, 255})
#define RED             ((Color){255, 0, 0, 255})
#define GREEN           ((Color){0, 255, 0, 255})
#define BLUE            ((Color){0, 0, 255, 255})
#define YELLOW          ((Color){255, 255, 0, 255})
#define CYAN            ((Color){0, 255, 255, 255})
#define MAGENTA         ((Color){255, 0, 255, 255})
#define ORANGE          ((Color){255, 165, 0, 255})
#define PURPLE          ((Color){128, 0, 128, 255})
#define BROWN           ((Color){139, 69, 19, 255})
#define NAVY            ((Color){0, 0, 128, 255})
#define TEAL            ((Color){0, 128, 128, 255})
#define DARK_BLUE       ((Color){0, 0, 139, 255})
#define DARK_GREEN      ((Color){0, 100, 0, 255})
#define DARK_RED        ((Color){139, 0, 0, 255})
#define SKY_BLUE        ((Color){135, 206, 235, 255})
#define LIGHT_BLUE      ((Color){173, 216, 230, 255})
#define GOLD            ((Color){255, 215, 0, 255})
#define SILVER          ((Color){192, 192, 192, 255})
#define PINK            ((Color){255, 192, 203, 255})
#define HOT_PINK        ((Color){255, 105, 180, 255})
#define CORAL           ((Color){255, 127, 80, 255})
#define SALMON          ((Color){250, 128, 114, 255})
#define LAVENDER        ((Color){230, 230, 250, 255})
#define INDIGO          ((Color){75, 0, 130, 255})
#define TURQUOISE       ((Color){64, 224, 208, 255})
#define BEIGE           ((Color){245, 245, 220, 255})
#define VIOLET          ((Color){238, 130, 238, 255})
#define TRANSPARENT     ((Color){0, 0, 0, 0})

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

typedef enum {
    UNIFORM_FLOAT,
    UNIFORM_INT,
    UNIFORM_VEC2,
    UNIFORM_VEC2I,
    UNIFORM_VEC3,
    UNIFORM_VEC3I,
    UNIFORM_VEC4,
    UNIFORM_VEC4I,
    UNIFORM_MAT4,
} UniformType;

#ifdef __cplusplus
extern "C" {
#endif

// Display
ORAPI Display *CreateDisplay(int width, int height, const char *title, int args);
ORAPI int DisplayShouldClose(Display *display);
ORAPI void DestroyDisplay(Display *display);
ORAPI void SetDisplaySize(Display *display, int width, int height);
ORAPI void SetDisplayTitle(Display *display, const char *title);
ORAPI void UseVSync(bool sync);
ORAPI void SetDisplayIcon(Display *display, const char *fileName);

// Mouse functions
ORAPI void HideMouse(Display *display, bool hidden);
ORAPI bool IsMouseHidden(Display *display);
ORAPI void DisableMouse(Display *display, bool disabled);
ORAPI bool IsMouseDisabled(Display *display);

// Drawing functions
ORAPI void ClearBackground(Color color);
ORAPI void BeginDrawing(Shader *shader, Camera2D camera);
ORAPI void BeginDrawing2D(Camera2D camera);
ORAPI void EndDrawing();
ORAPI void DrawTexture(Texture *texture, float x, float y, float width, float height, Color tint);
ORAPI void DrawTextureV(Texture *texture, Vector2f position, Vector2f size, Color tint);
ORAPI void DrawRectangle(float x, float y, float width, float height, Color tint);
ORAPI void DrawRectangleV(Vector2f position, Vector2f size, Color tint);

// Texture loading and unloading
ORAPI Texture *LoadTexture(const char *filename, int filter);
ORAPI void DestroyTexture(Texture *texture);

// Shader
ORAPI Shader *CreateShader(const char *vertexFile, const char *fragmentFile);
ORAPI Shader *CreateDefaultShader();
ORAPI void DestroyShader(Shader *shader);
ORAPI int GetShaderLocation(Shader *shader, const char *uniformName);
ORAPI void SetShaderValue(Shader *shader, int location, const void *value, UniformType type);

// Model
ORAPI Model *CreateModel(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indexCount);
ORAPI void DestroyModel(Model *model);
ORAPI void DrawModel(Model *model, Vector3f position, Vector3f scale, Color tint);

// Keyboard and Mouse input
ORAPI bool IsKeyDown(Key key);
ORAPI bool IsKeyReleased(Key key);
ORAPI bool IsButtonDown(Button button);
ORAPI bool IsButtonReleased(Button button);
ORAPI Vector2f GetMousePosition();
ORAPI Vector2f GetMouseDelta();

// Math functions
ORAPI bool RectIntersects(Rectangle a, Rectangle b);
ORAPI bool RectContains(Rectangle a, Rectangle b);
ORAPI bool PointInRect(Rectangle a, Vector2f point);

ORAPI bool RectIIntersects(RectangleI a, RectangleI b);
ORAPI bool RectIContains(RectangleI a, RectangleI b);
ORAPI bool PointInRectI(RectangleI a, Vector2i point);

ORAPI bool BBoxIntersects(BoundingBox a, BoundingBox b);
ORAPI bool BBoxContains(BoundingBox a, BoundingBox b);

ORAPI bool BBoxIIntersects(BoundingBoxI a, BoundingBoxI b);
ORAPI bool BBoxIContains(BoundingBoxI a, BoundingBoxI b);

ORAPI Rectangle GetCameraViewport(Camera2D camera);

// Utility functions
ORAPI int GetRandomValue(int min, int max);

#ifdef __cplusplus
}
#endif

#endif
