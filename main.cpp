#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <GLES2/gl2ext.h>
#include <cstdio>
#include <cstring>
#include <emscripten/html5_webgl.h>

int main() {
    auto glPolygonOffsetClampEXT = (PFNGLPOLYGONOFFSETCLAMPEXTPROC)eglGetProcAddress("glPolygonOffsetClampEXT");

    EmscriptenWebGLContextAttributes attrs;
    emscripten_webgl_init_context_attributes(&attrs);
    attrs.majorVersion = 2;
    EMSCRIPTEN_WEBGL_CONTEXT_HANDLE context = emscripten_webgl_create_context("#canvas", &attrs);
    emscripten_webgl_make_context_current(context);

    const char* extensions = (const char*) glGetString(GL_EXTENSIONS);
    printf("GL_EXTENSIONS: %s\n", extensions);
    printf("GL_EXTENSIONS[]:\n");
    GLint count = 0;
    glGetIntegerv(GL_NUM_EXTENSIONS, &count);
    bool found_EXT_polygon_offset_clamp = false;
    for (GLint i = 0; i < count; ++i) {
        const char* extension = (const char*) glGetStringi(GL_EXTENSIONS, i);
        printf("  - %s\n", extension);
        if (strcmp(extension, "EXT_polygon_offset_clamp") == 0) {
            found_EXT_polygon_offset_clamp = true;
        }
    }

    printf("found_EXT_polygon_offset_clamp = %s\n", found_EXT_polygon_offset_clamp ? "true" : "false");
    printf("glPolygonOffsetClampEXT = %p\n", glPolygonOffsetClampEXT);
    if (found_EXT_polygon_offset_clamp) {
        printf("EXT_polygon_offset_clamp was available, calling glPolygonOffsetClampEXT...\n");
        glPolygonOffsetClampEXT(0, 0, 0); // crash if function pointer is null
        printf("Success!\n");
    }
}
