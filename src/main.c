#include <stdio.h>
#include <MLV/MLV_all.h>
#include "include/struct.h"

#include "include/logic.h"
#include "include/frame.h"

/**
 * @brief Fonction principale.
 *
 */
int main(int argc, char const *argv[])
{
    create_window();
    MLV_actualise_window();
    int clic_x = 0;
    int clic_y = 0;
    int quit = 0;

    while (quit == 0)
    {
        MLV_wait_keyboard_or_mouse(NULL, NULL, NULL, &clic_x, &clic_y);

        move_case(clic_x, clic_y);

        MLV_actualise_window();

        quit = check_if_victory();
    }

    print_victory();

    return 0;
}
