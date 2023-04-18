#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "include/struct.h"
#include "include/frame.h"
#include "include/logic.h"

/**
 * @brief Initialise le plateau de jeu.
 * @return Board
 *
 */
Board *init_plateau()
{
    int i, j;

    p = malloc(sizeof(Board));

    for (i = 0; i < NB_LIG; i++)
    {
        for (j = 0; j < NB_COL; j++)
        {
            if (!(i == 3 && j == 3))
            {
                (p->bloc[i][j]).line = i;
                (p->bloc[i][j]).column = j;
                (p->bloc[i][j]).img = NULL;
            }
            else
            {
                (p->bloc[i][j]).line = -1;
                (p->bloc[i][j]).column = -1;
                (p->bloc[i][j]).img = NULL;
            }
        }
    }
    return p;
}

/**
 * @brief Coupe l'image en 16 morceaux et l'assigne à chaque case du plateau.
 * @param image
 *
 */
void cut_image(MLV_Image *image)
{
    for (int i = 0; i < NB_LIG; i++)
    {
        for (int j = 0; j < NB_COL; j++)
        {
            ((p->bloc)[i][j]).img = MLV_copy_partial_image(image, j * SIZE_CASE, i * SIZE_CASE, SIZE_CASE, SIZE_CASE);
        }
    }
}

/**
 * @brief Mélange le plateau de jeu.
 *
 */
void shuffle()
{
    int x, y;
    for (int i = 0; i < 1000; i++)
    {
        x = rand() % 4;
        y = rand() % 4;

        chek_if_square_click_is_around_black_square_and_swap(p->bloc[x][y]);
    }
}

/**
 * @brief Echange deux cases du plateau.
 *
 */
void swap(int x1, int y1, int x2, int y2)
{
    Square temp = p->bloc[y1][x1];
    p->bloc[y1][x1] = p->bloc[y2][x2];
    p->bloc[y2][x2] = temp;
}

/**
 * @brief Retourne la case du plateau sur laquelle l'utilisateur a cliqué en fonction des coordonnées du clic.
 *
 */
Square get_position_square_click(int x, int y)
{
    x = x / (SIZE_CASE + SPACE_BETWEEN_CASE);
    y = y / (SIZE_CASE + SPACE_BETWEEN_CASE);

    return p->bloc[y][x];
}

/**
 * @brief Vérifie si la case sur laquelle l'utilisateur a cliqué est à côté de la case vide et l'échange si c'est le cas.
 *
 */
void chek_if_square_click_is_around_black_square_and_swap(Square square_click)
{
    for (int i = 0; i < NB_LIG; i++)
    {

        for (int j = 0; j < NB_COL; j++)
        {
            if (p->bloc[j][i].line == square_click.line && p->bloc[j][i].column == square_click.column)
            {

                if (p->bloc[j][i + 1].line == -1)
                {
                    swap(i, j, i + 1, j);
                }
                else if (p->bloc[j][i - 1].line == -1)
                {

                    swap(i, j, i - 1, j);
                }
                else if (p->bloc[j + 1][i].line == -1)
                {

                    swap(i, j, i, j + 1);
                }
                else if (p->bloc[j - 1][i].line == -1)
                {

                    swap(i, j, i, j - 1);
                }

                return;
            }
        }
    }
}

/**
 * @brief Gère le déplacement des cases du plateau.
 *
 */
void move_case(int x, int y)
{
    Square square_click = get_position_square_click(x, y);

    chek_if_square_click_is_around_black_square_and_swap(square_click);

    MLV_clear_window(MLV_COLOR_BLACK);
    draw_image();
}

/**
 * @brief Vérifie si le joueur a gagné.
 *
 */
int check_if_victory()
{
    int victory = 1;
    for (int i = 0; i < NB_LIG; i++)
    {
        for (int j = 0; j < NB_COL; j++)
        {
            if (!(j == 3 && i == 3))
            {

                if (p->bloc[i][j].line != i || p->bloc[i][j].column != j)
                {
                    victory = 0;
                }
            }
        }
    }
    return victory;
}
