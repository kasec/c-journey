/* Computes the Volumen of a sphere */

#include<stdio.h>
#include<math.h>
# define TAX_VALUE .05;

int main(void) {
    float x = 0;
    printf("Enter value of X: ");
    scanf("%f", &x);

    // float result = (3 * pow(x, 5)) + (2 * pow(x, 4)) - (5 * pow(x, 3)) - (pow(x, 2)) + (7 * x) - 6;
    float result = (((((3 * pow(x, 5)) +  2) * pow(x, 4) - 5) * pow(x, 3) - 1) * pow(x, 2) + 7) * x - 6;
    printf("------------ \n");
    printf("Polynomial result is %.2f", result);

    return 0;
}
