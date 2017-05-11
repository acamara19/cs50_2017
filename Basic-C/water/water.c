/**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Water                                  *
 * Description:                                    *
 * Implement a program that reports a user’s water * 
 * usage, converting minutes spent in the shower to* 
 * bottles of drinking water.                      *
 * ************************************************/

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    printf("minutes: ");
    int x = GetInt();
    int y = (x * 12);
    printf("bottles: %d\n", y);
}