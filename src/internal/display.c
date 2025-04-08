#include "display.h"
#include <stdio.h>
#include <stdlib.h>
#include <stb_image.h>
#include "input.h"

Display* Internal_CreateDisplay(int width, int height, const char *title, int args) {
    if (!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW!\n");
        return NULL;
    }

    glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
    glfwWindowHint(GLFW_RESIZABLE, (args & RESIZABLE) ? GLFW_TRUE : GLFW_FALSE);

    int contextVersionMajor = 2;
    int contextVersionMinor = 1;
    int modernOpenGL = 0;

    if (args & OPENGL_46) {
        contextVersionMajor = 4;
        contextVersionMinor = 6;
        modernOpenGL = 1;
    } else if (args & OPENGL_33) {
        contextVersionMajor = 3;
        contextVersionMinor = 3;
        modernOpenGL = 1;
    } else if (args & OPENGL_21) {
        contextVersionMajor = 2;
        contextVersionMinor = 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, contextVersionMajor);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, contextVersionMinor);

    if (modernOpenGL) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        #endif
    }

    GLFWwindow *window = glfwCreateWindow(width, height, title, (args & FULLSCREEN) ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (window == NULL) {
        fprintf(stderr, "Failed to create GLFW window!\n");
        glfwTerminate();
        return NULL;
    }

    glfwSetCursorPosCallback(window, Internal_CursorPosCallback);
    glfwSetMouseButtonCallback(window, Internal_MouseButtonCallback);
    glfwSetKeyCallback(window, Internal_KeyCallback);

    const GLFWvidmode *vidmode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    glfwSetWindowPos(window, (vidmode->width - width) / 2, (vidmode->height - height) / 2);

    glfwMakeContextCurrent(window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        fprintf(stderr, "Failed to initialize GLAD!\n");
        glfwTerminate();
        return NULL;
    }

    glfwSwapInterval(args & VSYNC);
    glfwShowWindow(window);

    Display *display = (Display*)malloc(sizeof(Display));
    if (display == NULL) {
        fprintf(stderr, "Failed to allocate memory for Display!\n");
        glfwDestroyWindow(window);
        glfwTerminate();
        return NULL;
    }

    display->handler = window;
    display->displayMode = (DisplayMode){ width, height };

    if (args & OPENGL_21) {
        glEnable(GL_TEXTURE_2D);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }
    return display;
}

int Internal_DisplayShouldClose(Display* display) {
    if (display == NULL) {
        return 0;
    }
    return glfwWindowShouldClose(display->handler);
}

void Internal_UpdateDisplay(Display* display) {
    if (display == NULL) {
        return;
    }
    glfwSwapBuffers(display->handler);
    glfwPollEvents();
}

void Internal_DestroyDisplay(Display* display) {
    if (display == NULL) {
        return;
    }

    glfwDestroyWindow(display->handler);
    free(display);
    glfwTerminate();
}

void Internal_SetDisplaySize(Display* display, int width, int height) {
    if (display == NULL) {
        return;
    }
    display->displayMode.width = width;
    display->displayMode.height = height;
    glfwSetWindowSize(display->handler, width, height);
}

void Internal_SetDisplayTitle(Display* display, const char *title) {
    if (display == NULL) {
        return;
    }
    glfwSetWindowTitle(display->handler, title);
}

void Internal_UseVSync(bool sync) {
    glfwSwapInterval(sync ? 1 : 0);
}

void Internal_SetDisplayIcon(Display *display, const char *fileName) {
    int width;
    int height;
    int channels;
    unsigned char *pixels = stbi_load(fileName, &width, &height, &channels, 4);
    if (pixels == NULL) {
        fprintf(stderr, "Failed to load display icon: %s\n", fileName);
        return;
    }

    GLFWimage image;
    image.width = width;
    image.height = height;
    image.pixels = pixels;
    glfwSetWindowIcon(display->handler, 1, &image);
    stbi_image_free(pixels);
}

void Internal_HideMouse(Display *display, bool hidden) {
    glfwSetInputMode(display->handler, GLFW_CURSOR, (hidden ? GLFW_CURSOR_HIDDEN : GLFW_CURSOR_NORMAL));
}

bool Internal_IsMouseHidden(Display *display) {
    return glfwGetInputMode(display->handler, GLFW_CURSOR) == GLFW_CURSOR_HIDDEN;
}

void Internal_DisableMouse(Display *display, bool disabled) {
    glfwSetInputMode(display->handler, GLFW_CURSOR, (disabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL));
}

bool Internal_IsMouseDisabled(Display *display) {
    return glfwGetInputMode(display->handler, GLFW_CURSOR) == GLFW_CURSOR_DISABLED;
}