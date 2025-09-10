#include <stdio.h>
int main() {
    int d, i1, i2, i3, i4, i5, j1, j2, j3, j4, j5, first_sum, second_sum, total;
    printf("Enter the first 11 digits of a UPC: ");
    scanf("%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d%1d", &d, &i1, &i2, &i3, &i4, &i5, &j1, &j2, &j3, &j4, &j5);
    first_sum = d + i2 + i4 + j1 + j3 + j5;
    printf("First sum: %d \n", first_sum);
    second_sum = i1 + i3 + i5 + j2 + j4;
    printf("Second sum: %d \n", second_sum);

    second_sum += first_sum * 3;
    printf("Total sum:{1} %d \n", second_sum);
    second_sum -= 1;
    printf("Total sum:{2} %d \n", second_sum);
    second_sum = second_sum % 10;
    printf("Total sum:{3} %d \n", second_sum);
    total = 9 - second_sum;

    printf("Check digit: %d", total);

    return 0;
}
