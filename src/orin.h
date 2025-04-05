#ifndef ORIN_H
#define ORIN_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TRUE    0
#define FALSE   1

#define RESIZABLE   (1 << 0)
#define VSYNC       (1 << 1)
#define FULLSCREEN  (1 << 2)
#define OPENGL_46   (1 << 3)
#define OPENGL_33   (1 << 4)
#define OPENGL_21   (1 << 5)

#define DEFAULT_DISPLAY 0

#define NEAREST GL_NEAREST
#define LINEAR  GL_LINEAR

#define KEY_UNKNOWN            -1
#define KEY_SPACE              32
#define KEY_APOSTROPHE         39
#define KEY_COMMA              44
#define KEY_MINUS              45
#define KEY_PERIOD             46
#define KEY_SLASH              47
#define KEY_0                  48
#define KEY_1                  49
#define KEY_2                  50
#define KEY_3                  51
#define KEY_4                  52
#define KEY_5                  53
#define KEY_6                  54
#define KEY_7                  55
#define KEY_8                  56
#define KEY_9                  57
#define KEY_SEMICOLON          59
#define KEY_EQUAL              61
#define KEY_A                  65
#define KEY_B                  66
#define KEY_C                  67
#define KEY_D                  68
#define KEY_E                  69
#define KEY_F                  70
#define KEY_G                  71
#define KEY_H                  72
#define KEY_I                  73
#define KEY_J                  74
#define KEY_K                  75
#define KEY_L                  76
#define KEY_M                  77
#define KEY_N                  78
#define KEY_O                  79
#define KEY_P                  80
#define KEY_Q                  81
#define KEY_R                  82
#define KEY_S                  83
#define KEY_T                  84
#define KEY_U                  85
#define KEY_V                  86
#define KEY_W                  87
#define KEY_X                  88
#define KEY_Y                  89
#define KEY_Z                  90
#define KEY_LEFT_BRACKET       91
#define KEY_BACKSLASH          92
#define KEY_RIGHT_BRACKET      93
#define KEY_GRAVE_ACCENT       96
#define KEY_WORLD_1            161
#define KEY_WORLD_2            162
#define KEY_ESCAPE             256
#define KEY_ENTER              257
#define KEY_TAB                258
#define KEY_BACKSPACE          259
#define KEY_INSERT             260
#define KEY_DELETE             261
#define KEY_RIGHT              262
#define KEY_LEFT               263
#define KEY_DOWN               264
#define KEY_UP                 265
#define KEY_PAGE_UP            266
#define KEY_PAGE_DOWN          267
#define KEY_HOME               268
#define KEY_END                269
#define KEY_CAPS_LOCK          280
#define KEY_SCROLL_LOCK        281
#define KEY_NUM_LOCK           282
#define KEY_PRINT_SCREEN       283
#define KEY_PAUSE              284
#define KEY_F1                 290
#define KEY_F2                 291
#define KEY_F3                 292
#define KEY_F4                 293
#define KEY_F5                 294
#define KEY_F6                 295
#define KEY_F7                 296
#define KEY_F8                 297
#define KEY_F9                 298
#define KEY_F10                299
#define KEY_F11                300
#define KEY_F12                301
#define KEY_F13                302
#define KEY_F14                303
#define KEY_F15                304
#define KEY_F16                305
#define KEY_F17                306
#define KEY_F18                307
#define KEY_F19                308
#define KEY_F20                309
#define KEY_F21                310
#define KEY_F22                311
#define KEY_F23                312
#define KEY_F24                313
#define KEY_F25                314
#define KEY_KP_0               320
#define KEY_KP_1               321
#define KEY_KP_2               322
#define KEY_KP_3               323
#define KEY_KP_4               324
#define KEY_KP_5               325
#define KEY_KP_6               326
#define KEY_KP_7               327
#define KEY_KP_8               328
#define KEY_KP_9               329
#define KEY_KP_DECIMAL         330
#define KEY_KP_DIVIDE          331
#define KEY_KP_MULTIPLY        332
#define KEY_KP_SUBTRACT        333
#define KEY_KP_ADD             334
#define KEY_KP_ENTER           335
#define KEY_KP_EQUAL           336
#define KEY_LEFT_SHIFT         340
#define KEY_LEFT_CONTROL       341
#define KEY_LEFT_ALT           342
#define KEY_LEFT_SUPER         343
#define KEY_RIGHT_SHIFT        344
#define KEY_RIGHT_CONTROL      345
#define KEY_RIGHT_ALT          346
#define KEY_RIGHT_SUPER        347
#define KEY_MENU               348
#define KEY_LAST               KEY_MENU

#define MOUSE_BUTTON_1         0
#define MOUSE_BUTTON_2         1
#define MOUSE_BUTTON_3         2
#define MOUSE_BUTTON_4         3
#define MOUSE_BUTTON_5         4
#define MOUSE_BUTTON_6         5
#define MOUSE_BUTTON_7         6
#define MOUSE_BUTTON_8         7
#define MOUSE_BUTTON_LAST      MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT      MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    MOUSE_BUTTON_3

typedef struct {
    unsigned int width;
    unsigned int height;
    unsigned int refreshRate;
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

typedef struct {
    float x;
    float y;
} Vector2f;

typedef struct {
    float x;
    float y;
    float z;
} Vector3f;

typedef struct {
    float x;
    float y;
    float z;
    float w;
} Vector4f;

typedef struct {
    double x;
    double y;
} Vector2d;

typedef struct {
    double x;
    double y;
    double z;
} Vector3d;

typedef struct {
    double x;
    double y;
    double z;
    double w;
} Vector4d;

typedef struct {
    int x;
    int y;
} Vector2i;

typedef struct {
    int x;
    int y;
    int z;
} Vector3i;

typedef struct {
    int x;
    int y;
    int z;
    int w;
} Vector4i;

typedef struct {
    union {
        struct {
            float m00, m01, m02, m03;
            float m10, m11, m12, m13;
            float m20, m21, m22, m23;
            float m30, m31, m32, m33;
        };
        float data[16];
    };
} Matrix4f;

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

#define WHITE ((Color){255, 255, 255, 255})
#define BLACK ((Color){0, 0, 0, 255})
#define RED ((Color){255, 0, 0, 255})
#define GREEN ((Color){0, 255, 0, 255})
#define BLUE ((Color){0, 0, 255, 255})
#define YELLOW ((Color){255, 255, 0, 255})
#define CYAN ((Color){0, 255, 255, 255})
#define MAGENTA ((Color){255, 0, 255, 255})
#define GREY ((Color){169, 169, 169, 255})
#define TRANSPARENT ((Color){0, 0, 0, 0})

#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))

#ifdef __cplusplus
extern "C" {
#endif

Display* CreateDisplay(DisplayMode displayMode, const char *title, int args);
int DisplayShouldClose(Display* display);
void UpdateDisplay(Display* display);
void DestroyDisplay(Display* display);
void SetDisplaySize(Display* display, int width, int height);
void SetDisplayTitle(Display* display, const char *title);

void UseVSync(int sync);

void ClearBackground(Color color);

void BeginDrawing(Shader *shader, Camera2D camera);
void EndDrawing();

void DrawTexture(Texture *texture, Vector2f position, Vector2f size, Color color);

void DrawRectangle(Vector2f position, Vector2f size, Color color);

Texture *LoadTexture(const char *filename, int filter);
void DestroyTexture(Texture *texture);

Shader *CreateShader(const char *vertexFile, const char *fragmentFile);
Shader *CreateDefaultShader();
void DestroyShader(Shader *shader);

Model *CreateModel(Vertex vertices[], size_t vertexCount, unsigned int indices[], size_t indexCount);
void DestroyModel(Model *model);

void SetColor(Color color);
void DrawModel(Model *model, Matrix4f transform);

void SetUniform1f(Shader *shader, const char *name, float value);
void SetUniform2f(Shader *shader, const char *name, Vector2f value);
void SetUniform3f(Shader *shader, const char *name, Vector3f value);
void SetUniform4f(Shader *shader, const char *name, Vector4f value);

void SetUniform1i(Shader *shader, const char *name, int value);
void SetUniform2i(Shader *shader, const char *name, Vector2i value);
void SetUniform3i(Shader *shader, const char *name, Vector3i value);
void SetUniform4i(Shader *shader, const char *name, Vector4i value);

void SetUniformMatrix4f(Shader *shader, const char *name, Matrix4f *value);

int IsKeyDown(int key);
int IsKeyReleased(int key);
int IsButtonDown(int button);
int IsButtonReleased(int button);

Vector2f GetMousePosition();
Vector2f GetMouseDelta();

#ifdef __cplusplus
}
#endif

#endif
