#include <stdio.h>

int main(int arg_counter, char arg_vect[]) {
    int i = 0;
    if (arg_counter == 1) {
        printf("You only have argument, You suck");
    }
    if (arg_counter > 1 && arg_counter < 4) {
        printf("Here's your arguments:\n");
        for(int i = 0; i < arg_counter; i++) {
            printf("%s", arg_vect[i]);
        }
        printf("\n");
    }
    return 0;
}