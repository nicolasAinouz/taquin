#ifndef _FRAME_
#define _FRAME_

#include "struct.h"

void draw_image_cut(int i, int j, Square c);
void draw_image(Board *p);
void create_window(Board *p);
void print_victory(Board *p);

#endif