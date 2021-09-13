/* nuklear - 1.32.0 - public domain */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <time.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "libs/nuklear.h"
#include "libs/nuklear_glfw_gl3.h"
#include "libs/stb_image.h"
#include "ui.h"

#include "libs/utilities.c"

#include "style.c"
#include "ui.c"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

int main(void)
{
    /* Platform */
    static GLFWwindow *rex_glfw_window;
    int width = 0, height = 0;
    struct nk_context *ctx;
    struct nk_colorf bg;

    /* GLFW */
    glfwSetErrorCallback(error_callback);
    if (!glfwInit())
    {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    rex_glfw_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rex", NULL, NULL);
    glfwMakeContextCurrent(rex_glfw_window);
    glfwGetWindowSize(rex_glfw_window, &width, &height);

    /* OpenGL */
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }

    ctx = nk_glfw3_init(&glfw, rex_glfw_window, NK_GLFW3_INSTALL_CALLBACKS);

    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;
    ui_init(ctx); /* initialize, must be set here */
    while (!glfwWindowShouldClose(rex_glfw_window))
    {
        /* Input */
        glfwPollEvents();
        nk_glfw3_new_frame(&glfw);

        glfwGetWindowSize(rex_glfw_window, &width, &height);
        /* GUI */
        ui_run(ctx, (float)width, (float)height);

        /* Draw */
        glfwGetWindowSize(rex_glfw_window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(bg.r, bg.g, bg.b, bg.a);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);
        glfwSwapBuffers(rex_glfw_window);
    }
    nk_glfw3_shutdown(&glfw);
    glfwTerminate();
    return 0;
}
