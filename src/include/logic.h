#ifndef _LOGIC_
#define _LOGIC_

#include "struct.h"

void init_plateau(Board *p);
void cut_image(MLV_Image *image, Board *p);
void shuffle(Board *p);
void swap(int x1, int y1, int x2, int y2, Board *p);
Square get_position_square_click(int x, int y, Board *p);
void chek_if_square_click_is_around_black_square_and_swap(Square square_click, Board *p);
void move_case(int x, int y, Board *p);
int check_if_victory(Board *p);

#endif