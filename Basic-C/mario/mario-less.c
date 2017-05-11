#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int r, c, num, sp;//declares integers r=rows, c=column, sp= space, 
    do
    {
        printf("height: ");//print the work (height) on the screen
        num  = GetInt();//call for an integer input from a user
        if (num == 0)//checks if num is equal to 0
        {
            return 0;
        }
    }
    while(num < 1 || num > 23);
    
    for(r = 1; num >= r; r++)
    {
        for(sp = num - r; sp >= 1; sp--)
            printf(" ");
        for(c = 1; c <= r+1; c++)
            printf("#");
        printf("\n");
    }
    return 0;
}