#include <stdio.h>

int main() {
    int number, first_number, second_number;
    printf("Enter a two-digit number: ");
    scanf("%d", &number);
    // divition with int values is always an integer
    first_number = number / 10;
    second_number = number % 10;

    printf("The reversal is: %d \n", second_number * 10 + first_number);
    return 0;
}
