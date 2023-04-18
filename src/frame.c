#include <stdio.h>
#include <stdlib.h>
#include <MLV/MLV_all.h>

#include "include/struct.h"
#include "include/logic.h"

/**
 * @brief Dessine l'image sur le plateau sauf celle de la case vide.
 *
 */
void draw_image_cut(int i, int j, Square c)
{
    MLV_draw_image(c.img, j * (SIZE_CASE + SPACE_BETWEEN_CASE), i * (SIZE_CASE + SPACE_BETWEEN_CASE));
}

/**
 * @brief Dessine contenu dans chaque case du plateau.
 *
 */
void draw_image()
{
    MLV_draw_filled_rectangle(0, 0, WIDTH, WIDTH, MLV_COLOR_BLACK);
    for (int i = 0; i < NB_LIG; i++)
    {
        for (int j = 0; j < NB_COL; j++)
        {
            if (p->bloc[i][j].line != -1)
                draw_image_cut(i, j, p->bloc[i][j]);
        }
    }
}

/**
 * @brief Créer la fenêtre et initialise le plateau de jeu.
 *
 */
void create_window()
{

    MLV_create_window("Taquin", "Taquin", WIDTH, HEIGHT);

    MLV_Image *image = MLV_load_image("src/res/cat.jpg");
    MLV_resize_image(image, 512, 512);

    p = init_plateau();
    cut_image(image);
    shuffle();

    MLV_free_image(image);

    draw_image();
}

/**
 * @brief Affiche la fin de partie et libère la mémoire.
 *
 */
void print_victory()
{
    MLV_draw_text(200, 200, "Victory", MLV_COLOR_RED);
    draw_image_cut(3, 3, p->bloc[3][3]);
    MLV_actualise_window();
    MLV_wait_seconds(15);

    for (int i = 0; i < NB_LIG; i++)
    {
        for (int j = 0; j < NB_COL; j++)
        {
            MLV_free_image((p->bloc)[i][j].img);
        }
    }
    free(p);

    MLV_free_window();
}