/* Computes the Volumen of a sphere */

#include<stdio.h>
#include<math.h>
# define TWENTY_BILL 20
# define TEN_BILL 10
# define FIVE_BILL 5
# define ONE_BILL 1


int main(void) {
    int amount = 0;
    int twenties_count, tenties_count, fivies_count, ones_count;

    printf("Enter a dollar amount: ");
    scanf("%d", &amount);

    printf("------------ \n");
    printf("Amount is %d \n", amount);
    
    twenties_count = amount / TWENTY_BILL;
    amount = amount % TWENTY_BILL;
    printf("$20 bills: %d \n", twenties_count);
    // printf("Remaining is: %d \n", amount);

    tenties_count = amount / TEN_BILL;
    amount = amount % TEN_BILL;
    printf("$10 bills: %d \n", tenties_count);
    // printf("Remaining is: %d \n", amount);

    fivies_count = amount / FIVE_BILL;
    amount = amount % FIVE_BILL;
    printf("$5 bills: %d \n", fivies_count);
    // printf("Remaining is: %d \n", amount);

    ones_count = amount / ONE_BILL;
    amount = amount % FIVE_BILL;
    printf("$1 bills: %d \n", ones_count);
    // printf("Remaining is: %d \n", amount);


    return 0;
}
