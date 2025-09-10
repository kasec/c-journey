#include <stdio.h>

int main() {
    int number, first, second, third, fourth, fifth;
    printf("Enter a number between 0 and 32767: ");
    scanf("%d", &number);

    first = number % 8;
    number = number / 8;
    second = number % 8;
    number = number / 8;
    third = number % 8;
    number = number / 8;
    fourth = number % 8;
    number = number / 8;
    fifth = number % 8;

    printf("Remaining: %d \n", number);
    printf("In octal your number is: %d%d%d%d%d \n", fifth, fourth, third, second, first);
    return 0;
}
