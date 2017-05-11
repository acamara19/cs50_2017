 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Caesar                                 *
 * Description:                                    *
 * Implement a program that encrypts messages      *
 * using Caesar’s cipher, per the below.           *
 * ************************************************/
 
 #include <stdio.h>
 #include <cs50.h>
 #include <string.h>
 #include <ctype.h>

int main(int argc, string argv[])//command line argument
{
    if (argc != 2)//check if argument counter is not equal to 2
    {
        printf("Usage: ./caesar k\n");//print line on screen
        return 1;//quit the program
    }
    int key = atoi(argv[1]);//convert ASCII string to integer and assign to key
    
    printf("plaintext: ");//print line on screen
    string ptext = get_string();//Get user input and assign it to ptext
    
    for(int ch = 0, length = strlen(ptext); ch < length; ch++)//loop through the string one character at a time
    {
        if(isalpha(ptext[ch]))//checks if character is an alphabetic letter
        {
            for(int i = 0; i < key; i++)
            {
                if(ptext[ch] == 'z')//if the current charactere is lower 'z'
                ptext[ch] = 'a';//wrap around to the next charactere 'a' 
                
                else if(ptext[ch] == 'Z')//if the current charactere upper 'Z'
                ptext[ch] = 'A';//wrap around to the next charactere 'A' 
                
                else
                ptext[ch]++;//if the charactere is not 'z' or 'Z', increement 
            }
        }
    }
    printf("ciphertext: %s\n", ptext);//print the string of ciphertext on the screen
    return 0;
}

    
   

