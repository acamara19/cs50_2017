 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Initials                               *
 * Description:                                    *
 * Implement a program that, given a person’s name,*
 * prints a person’s initials.                     *
 * ************************************************/

#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

void print_initials(char *name);//function declaration

int main(void)
{
    string n = get_string();//gets user input

    print_initials(n);//function to print initials from user input
    return 0;
}

//function to get the initials of any give name and print them in upper case letters
void print_initials(char *name)
{
    if(name == NULL)//check to see if user input is valid
    {
        return;
    }

    if(name[0] != ' ' && name[0] != '\0')//check the string validity
    {
        printf("%c", toupper(name[0]));//prints the first charater in upper case letter
    }
    for(int i = 0, length = strlen(name); i < length; i++)//loops over the string char by char
    {
        if(name[i] == ' ')//checks if the current char is whitespace
        {
            if(i + 1 < length && name[i + 1] != ' ')//check for extra char and whitespace
            {
                printf("%c", toupper(name[i + 1]));//print the char in upper case letter
            }
        }
    }
    printf("\n");//prints new line
}


