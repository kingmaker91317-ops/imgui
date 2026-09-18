#ifndef LION_CHAMS
#define LION_CHAMS

#include <GLES2/gl2.h>
#include <dlfcn.h>
#include <string>

static void *handle = nullptr;

// ===== Flags =====
bool def = false;
bool shading = false;
bool wireframe = false;
bool outline = false;
bool outline2 = false;


static const char* shaderName = "_AlphaMask";
int w = 2;

void setShader(const char* s) { shaderName = s; }
const char* getShader() { return shaderName; }
void setChamsColor(float r, float g, float b, float a) {
    ChamsColor = ImVec4(r, g, b, a);
}

using glGetUniformLocation_t = GLint (*)(GLuint, const GLchar *);
using glDrawElements_t = void (*)(GLenum, GLsizei, GLenum, const void *);

glGetUniformLocation_t old_glGetUniformLocation = nullptr;
glDrawElements_t old_glDrawElements = nullptr;

// ===== FIX: Guard — jangan render kalo hook belum ready =====
static bool chams_ready = false;

GLint new_glGetUniformLocation(GLuint program, const GLchar *name) {
    return old_glGetUniformLocation(program, name);
}

void new_glDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices) {

    // ===== FIX: Early exit kalo hook chain belum complete =====
    if (!chams_ready || !old_glDrawElements || !old_glGetUniformLocation) {
        if (old_glDrawElements) old_glDrawElements(mode, count, type, indices);
        return;
    }

    if (mode != GL_TRIANGLES || count < 2000) {
        old_glDrawElements(mode, count, type, indices);
        return;
    }

    GLint currProgram = 0;
    glGetIntegerv(GL_CURRENT_PROGRAM, &currProgram);

    // ===== FIX: Program 0 = no shader bound = skip =====
    if (currProgram == 0) {
        old_glDrawElements(mode, count, type, indices);
        return;
    }

    if (old_glGetUniformLocation(currProgram, shaderName) == -1) {
        old_glDrawElements(mode, count, type, indices);
        return;
    }

    if (outline) {
        glEnable(GL_BLEND);
        glDepthRangef(0.0f, 0.5f);
        glDepthFunc(GL_ALWAYS);
        glLineWidth((float)w);
        glBlendColor(ChamsColor.x, ChamsColor.y, ChamsColor.z, ChamsColor.w);
        glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
        old_glDrawElements(GL_LINES, count, type, indices);
        glBlendColor(ChamsColor.x, ChamsColor.y, ChamsColor.z, ChamsColor.w);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        old_glDrawElements(GL_TRIANGLES, count, type, indices);
        glDepthFunc(GL_LESS);
        glDepthRangef(0.5f, 1.0f);
        glDisable(GL_BLEND);
    }
    else if (def) {
        glDepthRangef(1.0f, 0.5f);
        old_glDrawElements(mode, count, type, indices);
    }
    else if (shading) {
        old_glDrawElements(mode, count, type, indices);
        glDepthRangef(1.0f, 0.5f);
        glBlendColor(ChamsColor.x, ChamsColor.y, ChamsColor.z, ChamsColor.w);
        glEnable(GL_BLEND);
        glBlendFunc(GL_ONE, GL_CONSTANT_COLOR);
        old_glDrawElements(mode, count, type, indices);
    }
    else if (wireframe) {
        old_glDrawElements(mode, count, type, indices);
        glDepthRangef(1.0f, 0.5f);
        glBlendColor(ChamsColor.x, ChamsColor.y, ChamsColor.z, ChamsColor.w);
        glEnable(GL_BLEND);
        glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
        glLineWidth(1.0f);
        old_glDrawElements(GL_LINES, count, type, indices);
        glDisable(GL_BLEND);
    }
    else if (outline2) {
        glDepthRangef(1.0f, 0.5f);
        old_glDrawElements(mode, count, type, indices);
        glDepthRangef(1.0f, 0.0f);
        glLineWidth(10.0f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_CONSTANT_COLOR, GL_CONSTANT_ALPHA);
        glBlendColor(0.0f, 0.0f, 0.0f, 1.0f);
        old_glDrawElements(mode, count, type, indices);
        glDepthRangef(1.0f, 0.5f);
        glBlendColor(ChamsColor.x, ChamsColor.y, ChamsColor.z, ChamsColor.w);
        old_glDrawElements(GL_LINES, count, type, indices);
    }
    else {
        old_glDrawElements(mode, count, type, indices);
    }

    // ===== Reset state =====
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0f);
    glBlendColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDepthRangef(0.0f, 1.0f);
}

bool mlovinit() {
    handle = dlopen("libGLESv2.so", RTLD_LAZY);
    return handle != nullptr;
}

void LogShaders() {
    auto p_glGetUniformLocation =
        (glGetUniformLocation_t)dlsym(handle, "glGetUniformLocation");
    if (p_glGetUniformLocation) {
#if defined(__aarch64__)
        A64HookFunction((void*)p_glGetUniformLocation,
            (void*)new_glGetUniformLocation,
            (void**)&old_glGetUniformLocation);
#else
        MSHookFunction((void*)p_glGetUniformLocation,
            (void*)new_glGetUniformLocation,
            (void**)&old_glGetUniformLocation);
#endif
    }
}

void WallhackChams() {
    auto p_glDrawElements =
        (glDrawElements_t)dlsym(handle, "glDrawElements");
    if (p_glDrawElements) {
#if defined(__aarch64__)
        A64HookFunction((void*)p_glDrawElements,
            (void*)new_glDrawElements,
            (void**)&old_glDrawElements);
#else
        MSHookFunction((void*)p_glDrawElements,
            (void*)new_glDrawElements,
            (void**)&old_glDrawElements);
#endif
        // ===== FIX: Set ready SETELAH kedua hook terpasang =====
        
    }
}

#endif
