 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Greedy                                  *
 * Description:                                    *
 * Implement a program that calculates the minimum *
 * number of coins required to give a user change  *
 * ************************************************/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

//Declares Global variables
int quarter = 25;
int dime = 10;
int nickel = 5;

int main(void)
{
    //Declares and set local variables
    float change = 0;
    int change_in_cents = 0;
    int q_change = 0;
    int d_change = 0;
    int n_change = 0;
    int cents_left = 0;
    int total_change = 0;
    
    
    do
    {
    printf("O hai! How much change is owed? ");//prints line on the screen
    change = GetFloat();//ask for user input
    if (change <= 0)//checks the user input 
    printf("Change should be non-negative and greater than zero!\n");
    }
    while(change <= 0);
    
    //converts dollars to cents
    change_in_cents = (int)round(change * 100);
    
    //determines quarter count
    q_change = change_in_cents / quarter;
    cents_left = change_in_cents % quarter;
    
    //determines dime count
    d_change = cents_left / dime;
    cents_left = cents_left % dime;
    
    //determines nickel count
    n_change = cents_left / nickel;
    cents_left = cents_left % nickel;
    
    //determines how much coins should be given
    total_change = q_change + d_change + n_change + cents_left;
    
    //prints the number of total change
    printf("%d\n", total_change);
    
    return 0;
}