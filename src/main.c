/**
 * @file main.c
 * @author  Nicolas Ainouz
 * @brief Fichier de lancement du jeu.
 * @version 0.1
 * @date 2023-04-19
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include <MLV/MLV_all.h>
#include "include/struct.h"

#include "include/logic.h"
#include "include/frame.h"

/**
 * @brief 
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char const *argv[])
{
    Board p;

    init_plateau(&p);
    create_window(&p);

    MLV_actualise_window();

    int clic_x = 0;
    int clic_y = 0;
    int quit = 0;

    while (quit == 0)
    {
        MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &clic_x, &clic_y);

        move_case(clic_x, clic_y, &p);

        MLV_actualise_window();

        quit = check_if_victory(&p);
    }

    print_victory(&p);

    return 0;
}
