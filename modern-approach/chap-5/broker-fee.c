#include<stdio.h>

int main() {
    int trade_value;
    float commission;

    printf("Enter value of trade: ");
    scanf("%d", &trade_value);

    if(trade_value < 39) {
        printf("error: minimum charge is 39");
        return 1;
    }
    printf("\n Trade Value: %d", trade_value);
    if (trade_value < 2500) {
        printf("\n Under $2,500");
        commission = trade_value * .017 + 30;
    } else if (trade_value < 6250) {
        printf("\n Between $2,500 and $6,250");
        commission = trade_value * .0066 + 56;
    } else if (trade_value < 20000) {
        printf("\n Between $6,250 and $20,000");
        commission = trade_value * .0034 + 76;
    } else if (trade_value < 50000) {
        printf("\n Between $20,000 and $50,000");
        commission = trade_value * .0022 + 100;
    } else {
        printf("\n Over $50,000");
        commission = trade_value * .0009 + 255;
    }

    printf("\n Commission: $%.2f ", commission);

    return 0;
}