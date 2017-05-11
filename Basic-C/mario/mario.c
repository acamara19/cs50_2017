 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Mario                                  *
 * Description:                                    *
 * Implement a program that prints                 *
 * out a double half-pyramid of a specified height *
 * ************************************************/
 
#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int r, h, num, sp; //Declare variables
    
    do
    {
        printf("height: "); //Print screen
        num = GetInt(); // Get user input
        if(num == 0) // Check if statement is true
        {
            return 0; // return a value of zero
        }
    }
    while(num < 1 || num > 23); 
    
    for(r = 0; num > r; r++) // Print rows 
    {
        for(sp = num - r; sp > 1; sp--) // Prints Spaces
            printf("%s", " ");
        for(h = 0; h < r + 1; h++) // Prints heights
            printf("#"); // Prints hashes
            printf("  "); // Prints spaces between pyramids 
        for(h = 0; h < r + 1; h++) // Prints heights
            printf("#"); 
        printf("\n"); // Move to next line
    }
    return 0;
}