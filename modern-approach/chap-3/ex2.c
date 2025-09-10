/*
Write a program that formats product information entered by the user.
*/

#include <stdio.h>
int main(void) {
    int item_number = 0;
    float unit_price = 0.0;
    char purchase_date[] = "";

    printf("Enter item number: ");
    scanf("%d", &item_number);

    printf("Enter unit price: ");
    scanf("%f", &unit_price);

    // printf("Enter purchase date (mm/dd/yyyy):");
    // scanf("%s", purchase_date);

    printf("Item \t Unit Price \t Purchase Date \n");
    // TO-DO why is it failing when uncomment LN 17-18 out?
    printf("%d \t %.2f \t %s", item_number, unit_price, purchase_date);

    return 0;
}
