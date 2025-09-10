/*
Write a program that accepts a date from
the user in form mm/dd/yyyy and
then displays it in the form yyyymmdd
*/
#include<stdio.h>

int main(void) {
    int month = 0;
    int day = 0;
    int year = 0;
    printf("Enter a date (mm/dd/yyyy): ");
    scanf("%d/%d/%d", &month, &day, &year);
    printf("%d%d%d", year, month, day);
    return 0;
}
