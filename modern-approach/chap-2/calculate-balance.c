#include<stdio.h>


int main(void) {
    float loan_amount = 0;
    float interest_rate = 0;
    float monthly_payment = 0;

    printf("Enter amount of loan: ");
    scanf("%f", &loan_amount);
    printf("Enter interest rate: ");
    scanf("%f", &interest_rate);
    printf("Monthly payment: ");
    scanf("%f", &monthly_payment);

    printf("------------ \n");

    float monthly_interest = ((interest_rate * loan_amount) / 100) / 12;
    printf("Monthly interest rate is: %.2f \n", monthly_interest);

    loan_amount = loan_amount - monthly_payment + monthly_interest;
    printf("Balance remaining after first payment: %.2f \n", loan_amount);
    monthly_interest = ((interest_rate * loan_amount) / 100) / 12;
    loan_amount = loan_amount - monthly_payment + monthly_interest;
    printf("Balance remaining after second payment: %.2f \n", loan_amount);
    monthly_interest = ((interest_rate * loan_amount) / 100) / 12;
    loan_amount = loan_amount - monthly_payment + monthly_interest;
    printf("Balance remaining after third payment: %.2f \n", loan_amount);
    
    return 0;
}
