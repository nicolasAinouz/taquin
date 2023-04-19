/**
 * @file logic.c
 * @author Nicolas Ainouz
 * @brief Partie logique du jeu.
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "include/struct.h"
#include "include/frame.h"
#include "include/logic.h"

/**
 * @brief Initialise le plateau de jeu.
 * @param p plateau de jeu
 *
 */
void init_plateau(Board *p)
{
    int i, j;

    for (i = 0; i < NB_LIG; i++)
    {
        for (j = 0; j < NB_COL; j++)
        {
            if (!(i == 3 && j == 3))
            {
                (p->bloc)[i][j].line = i;
                (p->bloc)[i][j].column = j;
                (p->bloc)[i][j].img = NULL;
            }
            else
            {
                (p->bloc)[i][j].line = -1;
                (p->bloc)[i][j].column = -1;
                (p->bloc)[i][j].img = NULL;
            }
        }
    }
}

/**
 * @brief Coupe l'image en 16 morceaux et l'assigne à chaque case du plateau.
 * @param image
 * @param p plateau de jeu
 *
 */
void cut_image(MLV_Image *image, Board *p)
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
 * @param p plateau de jeu
 *
 */
void shuffle(Board *p)
{
    int x, y;
    for (int i = 0; i < 1000; i++)
    {
        x = rand() % 4;
        y = rand() % 4;

        chek_if_square_click_is_around_black_square_and_swap(p->bloc[x][y], p);
    }
}

/**
 * @brief Echange deux cases du plateau.
 * @param x1 Coordonnée x de la première case.
 * @param y1 Coordonnée y de la première case.
 * @param x2 Coordonnée x de la seconde case.
 * @param y2 Coordonnée y de la seconde case.
 * @param p plateau de jeu
 *
 */
void swap(int x1, int y1, int x2, int y2, Board *p)
{
    Square temp = p->bloc[y1][x1];
    p->bloc[y1][x1] = p->bloc[y2][x2];
    p->bloc[y2][x2] = temp;
}

/**
 * @brief Récupère la case sur laquelle l'utilisateur a cliqué.
 * @param x Coordonnée x de la case.
 * @param y Coordonnée y de la case.
 * @param p Plateau de jeu.
 * @return Case sur laquelle l'utilisateur a cliqué.
 *
 */
Square get_position_square_click(int x, int y, Board *p)
{
    x = x / (SIZE_CASE + SPACE_BETWEEN_CASE);
    y = y / (SIZE_CASE + SPACE_BETWEEN_CASE);

    return p->bloc[y][x];
}

/**
 * @brief Vérifie si la case sur laquelle l'utilisateur a cliqué est autour de la case vide.
 * 
 * @param square_click Case sur laquelle l'utilisateur a cliqué.
 * @param p Plateau de jeu.
 */
void chek_if_square_click_is_around_black_square_and_swap(Square square_click, Board *p)
{
    for (int i = 0; i < NB_LIG; i++)
    {

        for (int j = 0; j < NB_COL; j++)
        {
            if (p->bloc[j][i].line == square_click.line && p->bloc[j][i].column == square_click.column)
            {

                if (p->bloc[j][i + 1].line == -1)
                {
                    swap(i, j, i + 1, j, p);
                }
                else if (p->bloc[j][i - 1].line == -1)
                {

                    swap(i, j, i - 1, j, p);
                }
                else if (p->bloc[j + 1][i].line == -1)
                {

                    swap(i, j, i, j + 1, p);
                }
                else if (p->bloc[j - 1][i].line == -1)
                {

                    swap(i, j, i, j - 1, p);
                }

                return;
            }
        }
    }
}

/**
 * @brief Déplace la case sur laquelle l'utilisateur a cliqué.
 * 
 * @param x Coordonnée x de la souris.
 * @param y Coordonnée y de la souris.
 * @param p Plateau de jeu.
 */
void move_case(int x, int y, Board *p)
{
    Square square_click = get_position_square_click(x, y, p);
    chek_if_square_click_is_around_black_square_and_swap(square_click, p);

    MLV_clear_window(MLV_COLOR_BLACK);
    draw_image(p);
}

/**
 * @brief Vérifie si le joueur a gagné.
 * @param p Plateau de jeu.
 * 
 * @return 1 si le joueur a gagné, 0 sinon.
 */
int check_if_victory(Board *p)
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
