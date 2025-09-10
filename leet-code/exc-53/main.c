
#include<stdio.h>

int maxProfit(int* prices, int priceSize) {
    int largest_sum = 0;
    
    if(priceSize < 1) return largest_sum;

    largest_sum = prices[0];

    for(int i = 0; i < priceSize; i++) {
        int current = prices[i];
        int next = i+1 < priceSize ? prices[i+1] : 0;

        printf("current is %d\n", current);
        printf("next is %d\n", next);

        int sum = current + next;
        int largest_plus = largest_sum + next;
        int temp_largest = sum < largest_plus ? largest_plus : sum;

        printf("largest_sum is %d\n", largest_sum);
        printf("sum is %d\n", sum);
        printf("largest_plus is %d\n", largest_plus);
        printf("temp_largest is %d\n", temp_largest);
        printf("-----\n");
        printf("\n");

        if(largest_sum < temp_largest) {
            largest_sum = temp_largest;
        }
        
    }

    return largest_sum;
}

int main() {
    int prices[] = {5,4,-1,7,8};

    int profit = maxProfit(prices, 5);

    printf("profit is %d", profit);

    return 0;
}

/*
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
  ^

current => [-2]
next => [-1]
     
largest_sum => [-2] => -2
largest+next => [-2, 1] => -1
current_sum => [-2, 1] => -1

largest_sum => [-2, 1] => -1
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
     ^

current => [1]
next => [-3]

largest_sum= [-2, 1] => -1
largest+next => [-2, 1, -3] => -4
current_sum => [1, -3] => -2

largest_sum => [1, -3] => -2
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
        ^

current => [-3]
next => [4]

largest_sum => [1, -3] => -2
largest+next => [1, -3, 4] => 2
current_sum => [-3, 4] => 1

largest_sum => [1, -3, 4] => 2
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
            ^

current => [4]
next => [-1]

largest_sum => [1, -3, 4] => 2
largest+next => [1, -3, 4, -1] => 1
current_sum => [4, -1] => 3

largest_sum => [4, -1] => 3
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
                ^

current => [-1]
next => [2]

largest_sum => [4, -1] => 3
largest+next => [4, -1, 2] => 5
current_sum => [-1, 2] => 1

largest_sum => [4, -1, 2] => 5
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
                   ^

current => [2]
next => [1]

largest_sum => [4, -1, 2] => 5
largest+next => [4, -1, 2, 1] => 6
current_sum => [2, 1] => 3

largest_sum => [4, -1, 2, 1] => 6
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
                      ^

current => [1]
next => [-5]

largest_sum => [4, -1, 2, 1] => 6
largest+next => [4, -1, 2, 1, -5] => 1
current_sum => [1, -5] => 4

largest_sum => [4, -1, 2, 1] => 6
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
                          ^

current => [-5]
next => [4]

largest_sum => [4, -1, 2, 1] => 6
~ largest+next => [4, -1, 2, 1, -5] => 1 ~ continuity lost
current_sum => [-5, 4] => -1

largest_sum => [4, -1, 2, 1] => 6
---
---
[-2, 1, -3, 4, -1, 2, 1, -5, 4]
                             ^

current => [4]
next => [0]

largest_sum => [4, -1, 2, 1] => 6
~ largest+next => [4, -1, 2, 1, -5] => 1 ~ continuity lost
~ current_sum => [4] => 4 ~ ommited as next values doesn't exist

largest_sum => [4, -1, 2, 1] => 6
---
*/
