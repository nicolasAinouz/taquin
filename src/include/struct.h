#ifndef __STRUCT__
#define __STRUCT__

#include <MLV/MLV_all.h>

#define NB_COL 4
#define NB_LIG 4
#define WIDTH 512
#define HEIGHT 512
#define SIZE_CASE 128
#define SPACE_BETWEEN_CASE 2

typedef struct square
{
    int line;
    int column;
    MLV_Image *img;
} Square;

typedef struct board
{
    Square bloc[NB_LIG][NB_COL];

} Board;

#endif