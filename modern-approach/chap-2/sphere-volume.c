/* Computes the Volumen of a sphere */

#include<stdio.h>
#include<math.h>
# define PI_VALUE 3.1416;

int main(void) {
    float radius = 0;
    printf("Enter sphere radius in meters: ");
    scanf("%f", &radius);

    float cubic_radius = pow(radius, 3);
    printf("------------ \n");
    printf("cubic radius is %.2f \n", cubic_radius);

    float volume = 4.0f/3.0f * cubic_radius * PI_VALUE;
    printf("The volume is %.2f \n", volume);
    return 0;
}
