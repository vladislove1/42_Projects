#ifndef GUI_H
# define GUI_H

#ifdef __cplusplus
extern "C" {
#endif

# include "rt.h"

bool init_gui(t_sdl *sdl);
void process_gui_event(SDL_Event* event);
void render_gui(t_app *app);

GLuint gl_compile_shader(const char *str, GLuint type);
GLuint gl_compile_program(const char *vertex, const char *fragment);

#ifdef __cplusplus
}
#endif

#endif
