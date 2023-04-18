#ifndef _LOGIC_
#define _LOGIC_

#include "struct.h"

Board *init_plateau();
void cut_image(MLV_Image *image);
void shuffle();
void swap(int x1, int y1, int x2, int y2);
Square get_position_square_click(int x, int y);
void chek_if_square_click_is_around_black_square_and_swap(Square square_click);
void move_case(int x, int y);
int check_if_victory();

#endif