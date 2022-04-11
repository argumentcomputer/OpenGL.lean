#include <lean/lean.h>

#include <GLES3/gl32.h>
#include <GLES2/gl2ext.h>
#include <GLES3/gl3platform.h>

/**
 * Unwrap an Option of an external object as data for some
 * or NULL for none. Unsafe.
 */
static inline void *lean_option_unwrap(b_lean_obj_arg a) {
  if (lean_is_scalar(a)) {
    return NULL;
  } else {
    lean_object *some_val = lean_ctor_get(a, 0);
    return lean_get_external_data(some_val);      
  }
}

/**
 * Option.some a
 */
static inline lean_object * lean_mk_option_some(lean_object * a) {
  lean_object* tuple = lean_alloc_ctor(1, 1, 0);
  lean_ctor_set(tuple, 0, a);
  return tuple;
}

/**
 * Option.none.
 * Note that this is the same value for Unit and other constant constructors of inductives.
 */
static inline lean_object * lean_mk_option_none() {
  return lean_box(0);
}

static inline lean_object * lean_mk_tuple2(lean_object * a, lean_object * b) {
  lean_object* tuple = lean_alloc_ctor(0, 2, 0);
  lean_ctor_set(tuple, 0, a);
  lean_ctor_set(tuple, 1, b);
  return tuple;
}

GL_APICALL void GL_APIENTRY glBlendBarrier (void);
GL_APICALL void GL_APIENTRY glCopyImageSubData (GLuint srcName, GLenum srcTarget, GLint srcLevel, GLint srcX, GLint srcY, GLint srcZ, GLuint dstName, GLenum dstTarget, GLint dstLevel, GLint dstX, GLint dstY, GLint dstZ, GLsizei srcWidth, GLsizei srcHeight, GLsizei srcDepth);
GL_APICALL void GL_APIENTRY glDebugMessageControl (GLenum source, GLenum type, GLenum severity, GLsizei count, const GLuint *ids, GLboolean enabled);
GL_APICALL void GL_APIENTRY glDebugMessageInsert (GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar *buf);
GL_APICALL void GL_APIENTRY glDebugMessageCallback (GLDEBUGPROC callback, const void *userParam);
GL_APICALL GLuint GL_APIENTRY glGetDebugMessageLog (GLuint count, GLsizei bufSize, GLenum *sources, GLenum *types, GLuint *ids, GLenum *severities, GLsizei *lengths, GLchar *messageLog);
GL_APICALL void GL_APIENTRY glPushDebugGroup (GLenum source, GLuint id, GLsizei length, const GLchar *message);
GL_APICALL void GL_APIENTRY glPopDebugGroup (void);
GL_APICALL void GL_APIENTRY glObjectLabel (GLenum identifier, GLuint name, GLsizei length, const GLchar *label);
GL_APICALL void GL_APIENTRY glGetObjectLabel (GLenum identifier, GLuint name, GLsizei bufSize, GLsizei *length, GLchar *label);
GL_APICALL void GL_APIENTRY glObjectPtrLabel (const void *ptr, GLsizei length, const GLchar *label);
GL_APICALL void GL_APIENTRY glGetObjectPtrLabel (const void *ptr, GLsizei bufSize, GLsizei *length, GLchar *label);
GL_APICALL void GL_APIENTRY glGetPointerv (GLenum pname, void **params);
GL_APICALL void GL_APIENTRY glEnablei (GLenum target, GLuint index);
GL_APICALL void GL_APIENTRY glDisablei (GLenum target, GLuint index);
GL_APICALL void GL_APIENTRY glBlendEquationi (GLuint buf, GLenum mode);
GL_APICALL void GL_APIENTRY glBlendEquationSeparatei (GLuint buf, GLenum modeRGB, GLenum modeAlpha);
GL_APICALL void GL_APIENTRY glBlendFunci (GLuint buf, GLenum src, GLenum dst);
GL_APICALL void GL_APIENTRY glBlendFuncSeparatei (GLuint buf, GLenum srcRGB, GLenum dstRGB, GLenum srcAlpha, GLenum dstAlpha);
GL_APICALL void GL_APIENTRY glColorMaski (GLuint index, GLboolean r, GLboolean g, GLboolean b, GLboolean a);
GL_APICALL GLboolean GL_APIENTRY glIsEnabledi (GLenum target, GLuint index);
GL_APICALL void GL_APIENTRY glDrawElementsBaseVertex (GLenum mode, GLsizei count, GLenum type, const void *indices, GLint basevertex);
GL_APICALL void GL_APIENTRY glDrawRangeElementsBaseVertex (GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const void *indices, GLint basevertex);
GL_APICALL void GL_APIENTRY glDrawElementsInstancedBaseVertex (GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei instancecount, GLint basevertex);
GL_APICALL void GL_APIENTRY glFramebufferTexture (GLenum target, GLenum attachment, GLuint texture, GLint level);
GL_APICALL void GL_APIENTRY glPrimitiveBoundingBox (GLfloat minX, GLfloat minY, GLfloat minZ, GLfloat minW, GLfloat maxX, GLfloat maxY, GLfloat maxZ, GLfloat maxW);
GL_APICALL GLenum GL_APIENTRY glGetGraphicsResetStatus (void);
GL_APICALL void GL_APIENTRY glReadnPixels (GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLsizei bufSize, void *data);
GL_APICALL void GL_APIENTRY glGetnUniformfv (GLuint program, GLint location, GLsizei bufSize, GLfloat *params);
GL_APICALL void GL_APIENTRY glGetnUniformiv (GLuint program, GLint location, GLsizei bufSize, GLint *params);
GL_APICALL void GL_APIENTRY glGetnUniformuiv (GLuint program, GLint location, GLsizei bufSize, GLuint *params);
GL_APICALL void GL_APIENTRY glMinSampleShading (GLfloat value);
GL_APICALL void GL_APIENTRY glPatchParameteri (GLenum pname, GLint value);
GL_APICALL void GL_APIENTRY glTexParameterIiv (GLenum target, GLenum pname, const GLint *params);
GL_APICALL void GL_APIENTRY glTexParameterIuiv (GLenum target, GLenum pname, const GLuint *params);
GL_APICALL void GL_APIENTRY glGetTexParameterIiv (GLenum target, GLenum pname, GLint *params);
GL_APICALL void GL_APIENTRY glGetTexParameterIuiv (GLenum target, GLenum pname, GLuint *params);
GL_APICALL void GL_APIENTRY glSamplerParameterIiv (GLuint sampler, GLenum pname, const GLint *param);
GL_APICALL void GL_APIENTRY glSamplerParameterIuiv (GLuint sampler, GLenum pname, const GLuint *param);
GL_APICALL void GL_APIENTRY glGetSamplerParameterIiv (GLuint sampler, GLenum pname, GLint *params);
GL_APICALL void GL_APIENTRY glGetSamplerParameterIuiv (GLuint sampler, GLenum pname, GLuint *params);
GL_APICALL void GL_APIENTRY glTexBuffer (GLenum target, GLenum internalformat, GLuint buffer);
GL_APICALL void GL_APIENTRY glTexBufferRange (GLenum target, GLenum internalformat, GLuint buffer, GLintptr offset, GLsizeiptr size);
GL_APICALL void GL_APIENTRY glTexStorage3DMultisample (GLenum target, GLsizei samples, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLboolean fixedsamplelocations);
// ucx

static inline lean_obj_res lean_exclusive_or_copy(lean_obj_arg a, lean_obj_res (*copy_fun)(lean_obj_arg)) {
  if (lean_is_exclusive(a))
    return a;
  return copy_fun(a);
}

inline static void noop_foreach(void *mod, b_lean_obj_arg fn) {}


static lean_external_class *g_gl_platform_class = NULL;

static void gl_platform_finalizer(void *ptr) { 
  drop(ptr);
}

static lean_external_class *get_gl_platform_class() {
  if (g_gl_platform_class == NULL) {
    g_gl_platform_class = lean_register_external_class(
        &gl_platform_finalizer, &noop_foreach);
  }
  return g_gl_platform_class;
}

/**
 * gl
 */
lean_obj_res lean_gl_create_program(uint32_t objectId) {
  uint32_t i = glCreateProgram();
  return lean_io_result_mk_ok(lean_box(i));
}


