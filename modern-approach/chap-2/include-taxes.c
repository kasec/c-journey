/* Computes the Volumen of a sphere */

#include<stdio.h>
#include<math.h>
# define TAX_VALUE .05;

int main(void) {
    float amount = 0;
    printf("Enter dollar and cents amount: ");
    scanf("%f", &amount);

    float taxes = amount * TAX_VALUE;
    printf("------------ \n");
    printf("Taxes of amount %.2f is: %.2f\n", amount, taxes);

    printf("The total is %.2f \n", amount + taxes);
    return 0;
}
