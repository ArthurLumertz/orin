import ctypes
import os
import platform

# Window flags (bitmasks)
RESIZABLE   = 1 << 0
VSYNC       = 1 << 1
FULLSCREEN  = 1 << 2
OPENGL_46   = 1 << 3
OPENGL_33   = 1 << 4
OPENGL_21   = 1 << 5

# Display
DEFAULT_DISPLAY = 0

NEAREST = 0x2600
LINEAR  = 0x2601

# Keyboard keys
KEY_UNKNOWN            = -1
KEY_SPACE              = 32
KEY_APOSTROPHE         = 39
KEY_COMMA              = 44
KEY_MINUS              = 45
KEY_PERIOD             = 46
KEY_SLASH              = 47
KEY_0                  = 48
KEY_1                  = 49
KEY_2                  = 50
KEY_3                  = 51
KEY_4                  = 52
KEY_5                  = 53
KEY_6                  = 54
KEY_7                  = 55
KEY_8                  = 56
KEY_9                  = 57
KEY_SEMICOLON          = 59
KEY_EQUAL              = 61
KEY_A                  = 65
KEY_B                  = 66
KEY_C                  = 67
KEY_D                  = 68
KEY_E                  = 69
KEY_F                  = 70
KEY_G                  = 71
KEY_H                  = 72
KEY_I                  = 73
KEY_J                  = 74
KEY_K                  = 75
KEY_L                  = 76
KEY_M                  = 77
KEY_N                  = 78
KEY_O                  = 79
KEY_P                  = 80
KEY_Q                  = 81
KEY_R                  = 82
KEY_S                  = 83
KEY_T                  = 84
KEY_U                  = 85
KEY_V                  = 86
KEY_W                  = 87
KEY_X                  = 88
KEY_Y                  = 89
KEY_Z                  = 90
KEY_LEFT_BRACKET       = 91
KEY_BACKSLASH          = 92
KEY_RIGHT_BRACKET      = 93
KEY_GRAVE_ACCENT       = 96
KEY_WORLD_1            = 161
KEY_WORLD_2            = 162
KEY_ESCAPE             = 256
KEY_ENTER              = 257
KEY_TAB                = 258
KEY_BACKSPACE          = 259
KEY_INSERT             = 260
KEY_DELETE             = 261
KEY_RIGHT              = 262
KEY_LEFT               = 263
KEY_DOWN               = 264
KEY_UP                 = 265
KEY_PAGE_UP            = 266
KEY_PAGE_DOWN          = 267
KEY_HOME               = 268
KEY_END                = 269
KEY_CAPS_LOCK          = 280
KEY_SCROLL_LOCK        = 281
KEY_NUM_LOCK           = 282
KEY_PRINT_SCREEN       = 283
KEY_PAUSE              = 284
KEY_F1                 = 290
KEY_F2                 = 291
KEY_F3                 = 292
KEY_F4                 = 293
KEY_F5                 = 294
KEY_F6                 = 295
KEY_F7                 = 296
KEY_F8                 = 297
KEY_F9                 = 298
KEY_F10                = 299
KEY_F11                = 300
KEY_F12                = 301
KEY_F13                = 302
KEY_F14                = 303
KEY_F15                = 304
KEY_F16                = 305
KEY_F17                = 306
KEY_F18                = 307
KEY_F19                = 308
KEY_F20                = 309
KEY_F21                = 310
KEY_F22                = 311
KEY_F23                = 312
KEY_F24                = 313
KEY_F25                = 314
KEY_KP_0               = 320
KEY_KP_1               = 321
KEY_KP_2               = 322
KEY_KP_3               = 323
KEY_KP_4               = 324
KEY_KP_5               = 325
KEY_KP_6               = 326
KEY_KP_7               = 327
KEY_KP_8               = 328
KEY_KP_9               = 329
KEY_KP_DECIMAL         = 330
KEY_KP_DIVIDE          = 331
KEY_KP_MULTIPLY        = 332
KEY_KP_SUBTRACT        = 333
KEY_KP_ADD             = 334
KEY_KP_ENTER           = 335
KEY_KP_EQUAL           = 336
KEY_LEFT_SHIFT         = 340
KEY_LEFT_CONTROL       = 341
KEY_LEFT_ALT           = 342
KEY_LEFT_SUPER         = 343
KEY_RIGHT_SHIFT        = 344
KEY_RIGHT_CONTROL      = 345
KEY_RIGHT_ALT          = 346
KEY_RIGHT_SUPER        = 347
KEY_MENU               = 348
KEY_LAST               = KEY_MENU

# Mouse buttons
MOUSE_BUTTON_1         = 0
MOUSE_BUTTON_2         = 1
MOUSE_BUTTON_3         = 2
MOUSE_BUTTON_4         = 3
MOUSE_BUTTON_5         = 4
MOUSE_BUTTON_6         = 5
MOUSE_BUTTON_7         = 6
MOUSE_BUTTON_8         = 7
MOUSE_BUTTON_LAST      = MOUSE_BUTTON_8
MOUSE_BUTTON_LEFT      = MOUSE_BUTTON_1
MOUSE_BUTTON_RIGHT     = MOUSE_BUTTON_2
MOUSE_BUTTON_MIDDLE    = MOUSE_BUTTON_3

class DisplayMode(ctypes.Structure):
    _fields_ = [
        ("width", ctypes.c_uint),
        ("height", ctypes.c_uint),
        ("refreshRate", ctypes.c_uint),
    ]

class Display(ctypes.Structure):
    _fields_ = [
        ("handler", ctypes.c_void_p),
        ("displayMode", DisplayMode)
    ]

class Vector2f(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_float),
        ("y", ctypes.c_float),
    ]

class Vector2i(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_int),
        ("y", ctypes.c_int),
    ]

class Vector2d(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_double),
        ("y", ctypes.c_double),
    ]

class Vector3f(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_float),
        ("y", ctypes.c_float),
        ("z", ctypes.c_float),
    ]

class Vector3i(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_int),
        ("y", ctypes.c_int),
        ("z", ctypes.c_int),
    ]

class Vector3d(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_double),
        ("y", ctypes.c_double),
        ("z", ctypes.c_double),
    ]

class Vector4f(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_float),
        ("y", ctypes.c_float),
        ("z", ctypes.c_float),
        ("w", ctypes.c_float),
    ]

class Vector4i(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_int),
        ("y", ctypes.c_int),
        ("z", ctypes.c_int),
        ("w", ctypes.c_int),
    ]

class Vector4d(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_double),
        ("y", ctypes.c_double),
        ("z", ctypes.c_double),
        ("w", ctypes.c_double),
    ]

class Color(ctypes.Structure):
    _fields_ = [
        ("r", ctypes.c_ubyte),
        ("g", ctypes.c_ubyte),
        ("b", ctypes.c_ubyte),
        ("a", ctypes.c_ubyte),
    ]

class Camera2D(ctypes.Structure):
    _fields_ = [
        ("position", Vector2f),
        ("zoom", ctypes.c_float)
    ]

class Texture(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_uint),
        ("width", ctypes.c_int),
        ("height", ctypes.c_int),
        ("channels", ctypes.c_int),
    ]

class Shader(ctypes.Structure):
    _fields_ = [
        ("id", ctypes.c_uint)
    ]

class Vertex(ctypes.Structure):
    _fields_ = [
        ("position", Vector2f),
        ("uv", Vector2f),
        ("normals", Vector2f),
        ("color", Color),
    ]

class Model(ctypes.Structure):
    _fields_ = [
        ("vao", ctypes.c_uint),
        ("vbo", ctypes.c_uint),
        ("ebo", ctypes.c_uint),
        ("vertices", ctypes.POINTER(Vertex)),
        ("indices", ctypes.POINTER(ctypes.c_uint)),
        ("vertexCount", ctypes.c_size_t),
        ("indexCount", ctypes.c_size_t)
    ]

class MatrixFields(ctypes.Structure):
    _fields_ = [
        ("m00", ctypes.c_float), ("m01", ctypes.c_float), ("m02", ctypes.c_float), ("m03", ctypes.c_float),
        ("m10", ctypes.c_float), ("m11", ctypes.c_float), ("m12", ctypes.c_float), ("m13", ctypes.c_float),
        ("m20", ctypes.c_float), ("m21", ctypes.c_float), ("m22", ctypes.c_float), ("m23", ctypes.c_float),
        ("m30", ctypes.c_float), ("m31", ctypes.c_float), ("m32", ctypes.c_float), ("m33", ctypes.c_float),
    ]

class MatrixUnion(ctypes.Union):
    _fields_ = [
        ("fields", MatrixFields),
        ("data", ctypes.c_float * 16)
    ]

class Matrix4f(ctypes.Structure):
    _anonymous_ = ("union",)
    _fields_ = [
        ("union", MatrixUnion),
    ]

class Rectangle(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_float),
        ("y", ctypes.c_float),
        ("width", ctypes.c_float),
        ("height", ctypes.c_float),
    ]

class RectangleI(ctypes.Structure):
    _fields_ = [
        ("x", ctypes.c_int),
        ("y", ctypes.c_int),
        ("width", ctypes.c_int),
        ("height", ctypes.c_int),
    ]

WHITE = Color(255, 255, 255, 255)
BLACK = Color(0, 0, 0, 255)
RED = Color(255, 0, 0, 255)
GREEN = Color(0, 255, 0, 255)
BLUE = Color(0, 0, 255, 255)
YELLOW = Color(255, 255, 0, 255)
CYAN = Color(0, 255, 255, 255)
MAGENTA = Color(255, 0, 255, 255)
GREY = Color(169, 169, 169, 255)
TRANSPARENT = Color(0, 0, 0, 0)

system_platform = platform.system()

if system_platform == "Darwin":
    liborin = ctypes.CDLL("orin.dylib")
elif system_platform == "Linux":
    liborin = ctypes.CDLL("orin.so")
elif system_platform == "Windows":
    liborin = ctypes.CDLL("orin.dll")
else:
    raise RuntimeError(f"Unsupported OS: {system_platform}")

liborin.CreateDisplay.argtypes = [DisplayMode, ctypes.c_char_p, ctypes.c_int]
liborin.CreateDisplay.restype = ctypes.POINTER(Display)
def CreateDisplay(mode: DisplayMode, title: str, args: int):
    title_bytes = title.encode("utf-8")
    return liborin.CreateDisplay(mode, title_bytes, args)

liborin.DisplayShouldClose.argtypes = [ctypes.POINTER(Display)]
liborin.DisplayShouldClose.restype = ctypes.c_int
def DisplayShouldClose(display: Display) -> int:
    return liborin.DisplayShouldClose(display)

liborin.UpdateDisplay.argtypes = [ctypes.POINTER(Display)]
liborin.UpdateDisplay.restype = None
def UpdateDisplay(display: Display):
    liborin.UpdateDisplay(display)

liborin.DestroyDisplay.argtypes = [ctypes.POINTER(Display)]
liborin.DestroyDisplay.restype = None

def DestroyDisplay(display: Display):
    liborin.DestroyDisplay(display)

liborin.SetDisplaySize.argtypes = [ctypes.POINTER(Display), ctypes.c_int, ctypes.c_int]
liborin.SetDisplaySize.restype = None

def SetDisplaySize(display: Display, width: int, height: int):
    liborin.SetDisplaySize(display, width, height)

liborin.SetDisplayTitle.argtypes = [ctypes.POINTER(Display), ctypes.c_char_p]
liborin.SetDisplayTitle.restype = None
def SetDisplayTitle(display: Display, title: str):
    title_bytes = title.encode("utf-8")
    liborin.SetDisplayTitle(display, title_bytes)

liborin.UseVSync.argtypes = [ctypes.c_int]
liborin.UseVSync.restype = None
def UseVSync(sync: bool):
    liborin.UseVSync(1 if sync else 0)

liborin.ClearBackground.argtypes = [Color]
liborin.ClearBackground.restype = None
def ClearBackground(color: Color):
    liborin.ClearBackground(color)

liborin.BeginDrawing.argtypes = [ctypes.POINTER(Shader), Camera2D]
liborin.BeginDrawing.restype = None
def BeginDrawing(shader: Shader, camera: Camera2D):
    liborin.BeginDrawing(shader, camera)

liborin.EndDrawing.argtypes = None
liborin.EndDrawing.restype = None
def EndDrawing():
    liborin.EndDrawing()

liborin.DrawTexture.argtypes = [ctypes.POINTER(Texture), Vector2f, Vector2f, Color]
liborin.DrawTexture.restype = None
def DrawTexture(texture: Texture, position: Vector2f, size: Vector2f, color: Color):
    liborin.DrawTexture(texture, position, size, color)

liborin.DrawRectangle.argtypes = [Vector2f, Vector2f, Color]
liborin.DrawRectangle.restype = None
def DrawRectangle(position: Vector2f, size: Vector2f, color: Color):
    liborin.DrawRectangle(position, size, color)

liborin.LoadTexture.argtypes = [ctypes.c_char_p, ctypes.c_int]
liborin.LoadTexture.restype = ctypes.POINTER(Texture)
def LoadTexture(filename: str, filter: int):
    current_directory = os.path.dirname(os.path.abspath(__file__))
    full_path = os.path.join(current_directory, filename)
    str_bytes = full_path.encode("utf-8")
    return liborin.LoadTexture(str_bytes, filter)

liborin.DestroyTexture.argtypes = [ctypes.POINTER(Texture)]
liborin.DestroyTexture.restype = None
def DestroyTexture(texture: Texture):
    liborin.DestroyTexture(texture)

liborin.CreateShader.argtypes = [ctypes.c_char_p, ctypes.c_char_p]
liborin.CreateShader.restype = ctypes.POINTER(Shader)
def CreateShader(vertex_file: str, fragment_file: str):
    current_directory = os.path.dirname(os.path.abspath(__file__))
    
    vertex_file_path = os.path.join(current_directory, vertex_file)
    fragment_file_path = os.path.join(current_directory, fragment_file)

    vertex_file_bytes = vertex_file_path.encode("utf-8")
    fragment_file_bytes = fragment_file_path.encode("utf-8")
    
    return liborin.CreateShader(vertex_file_bytes, fragment_file_bytes)

liborin.CreateDefaultShader.argtypes = None
liborin.CreateDefaultShader.restype = ctypes.POINTER(Shader)
def CreateDefaultShader():
    return liborin.CreateDefaultShader()

liborin.DestroyShader.argtypes = [ctypes.POINTER(Shader)]
liborin.DestroyShader.restype = None
def DestroyShader(shader: Shader):
    liborin.DestroyShader(shader)

liborin.CreateModel.argtypes = [
    ctypes.POINTER(Vertex),
    ctypes.c_size_t,
    ctypes.POINTER(ctypes.c_uint),
    ctypes.c_size_t
]
liborin.CreateModel.restype = ctypes.POINTER(Model)
def CreateModel(vertices: list, indices: list):
    vertex_array = (Vertex * len(vertices))(*vertices)
    index_array = (ctypes.c_uint * len(indices))(*indices)

    return liborin.CreateModel(vertex_array, len(vertices), index_array, len(indices))

liborin.DestroyModel.argtypes = [ctypes.POINTER(Model)]
liborin.DestroyModel.restype = None
def DestroyModel(model: Model):
    liborin.DestroyModel(model)

liborin.SetColor.argtypes = [Color]
liborin.SetColor.restype = None
def SetColor(color: Color):
    liborin.SetColor(color)

liborin.DrawModel.argtypes = [ctypes.POINTER(Model), ctypes.POINTER(Matrix4f)]
liborin.DrawModel.restype = None
def DrawModel(model: Model, transform: Matrix4f):
    liborin.DrawModel(model, transform)

liborin.SetUniform1f.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, ctypes.c_float]
liborin.SetUniform1f.restype = None
def SetUniform1f(shader: Shader, uniform_name: str, value: float):
    liborin.SetUniform1f(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform2f.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, Vector2f]
liborin.SetUniform2f.restype = None
def SetUniform2f(shader: Shader, uniform_name: str, value: Vector2f):
    liborin.SetUniform2f(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform3f.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, Vector3f]
liborin.SetUniform3f.restype = None
def SetUniform3f(shader: Shader, uniform_name: str, value: Vector3f):
    liborin.SetUniform3f(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform4f.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, Vector4f]
liborin.SetUniform4f.restype = None
def SetUniform4f(shader: Shader, uniform_name: str, value: Vector4f):
    liborin.SetUniform4f(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform1i.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, ctypes.c_int]
liborin.SetUniform1i.restype = None
def SetUniform1i(shader: Shader, uniform_name: str, value: int):
    liborin.SetUniform1i(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform2i.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, Vector2i]
liborin.SetUniform2i.restype = None
def SetUniform2i(shader: Shader, uniform_name: str, value: Vector2i):
    liborin.SetUniform2i(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform3i.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, Vector3i]
liborin.SetUniform3i.restype = None
def SetUniform3i(shader: Shader, uniform_name: str, value: Vector3i):
    liborin.SetUniform3i(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniform4i.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, Vector4i]
liborin.SetUniform4i.restype = None
def SetUniform4i(shader: Shader, uniform_name: str, value: Vector4i):
    liborin.SetUniform4i(shader, uniform_name.encode("utf-8"), value)

liborin.SetUniformMatrix4f.argtypes = [ctypes.POINTER(Shader), ctypes.c_char_p, ctypes.POINTER(Shader)]
liborin.SetUniformMatrix4f.restype = None
def SetUniformMatrix4f(shader: Shader, uniform_name: str, value: Matrix4f):
    liborin.SetUniformMatrix4f(shader, uniform_name.encode("utf-8"), value)

liborin.IsKeyDown.argtypes = [ctypes.c_int]
liborin.IsKeyDown.restype = ctypes.c_int
def IsKeyDown(key: int):
    return liborin.IsKeyDown(key)

liborin.IsKeyReleased.argtypes = [ctypes.c_int]
liborin.IsKeyReleased.restype = ctypes.c_int
def IsKeyReleased(key: int):
    return liborin.IsKeyReleased(key)

liborin.IsButtonDown.argtypes = [ctypes.c_int]
liborin.IsButtonDown.restype = ctypes.c_int
def IsButtonDown(button: int):
    return liborin.IsButtonDown(button)

liborin.IsButtonReleased.argtypes = [ctypes.c_int]
liborin.IsButtonReleased.restype = ctypes.c_int
def IsButtonReleased(button: int):
    return liborin.IsButtonReleased(button)

liborin.GetMousePosition.argtypes = None
liborin.GetMousePosition.restype = Vector2f
def GetMousePosition() -> Vector2f:
    return liborin.GetMousePosition()

liborin.GetMouseDelta.argtypes = None
liborin.GetMouseDelta.restype = Vector2f
def GetMouseDelta() -> Vector2f:
    return liborin.GetMouseDelta()

liborin.IdentityMatrix4f.argtypes = None
liborin.IdentityMatrix4f.restype = Matrix4f
def IdentityMatrix4f():
    return liborin.IdentityMatrix4f()
