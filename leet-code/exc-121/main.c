#include<stdio.h>

int maxProfit(int* prices, int priceSize) {
    int highest = 0;
    
    if(priceSize < 1) return highest;

    int lowest = prices[0];

    for(int i = 0; i < priceSize; i++) {
        int current = prices[i];
        
        if(current < lowest) {
            lowest = current;
        }
        
        int profit = current - lowest;
        
        if(profit > highest) {
            highest = profit;
        }
    }

    return highest;
}

int main() {
    int prices[] = {7,6,4,3,1};

    int profit = maxProfit(prices, 5);

    printf("profit is %d", profit);

    return 0;
}
