#include <stdio.h>

int main() {
    int first_dig, second_dig, third_dig;
    printf("Enter a three-digit number: ");
    scanf("%1d%1d%1d", &first_dig, &second_dig, &third_dig);

    printf("The reversal is: %d \n", (third_dig * 10 * 10) + (second_dig * 10) + first_dig);
    return 0;
}
