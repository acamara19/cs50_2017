 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Vigenere                               *
 * Description:                                    *
 * Implement a program that encrypts messages using*
 * Vigenère’s cipher                               *
 * ************************************************/
 
 #include <cs50.h>
 #include <stdio.h>
 #include <ctype.h>
 #include <string.h>
 
 int main(int argc, string argv[])
 {
     //check to see that user has correct the correct argument input
     if(argc != 2)
     {
         //print the line to screen
         printf("Usage: ./vigenere k\n");
         //exit the program
         return 1;
     }
     //assign the second argument to a string key
     string key = argv[1];
     
     //loop to check and make sure that each charactere in argv[1]
     //or key is an alphanumeric charactere. If not, exit the program
     for(int i = 0, n = strlen(key); i < n; i++)
     {
        //check if each letter in key are alphanumeric
        if(!isalpha(key[i]))
        {
            //print the line to screen
            printf("Usage: ./vigenere k\n");
            //exit the program
            return 1;
        }
     }
     //get a plaintext input from the user
     printf("plaintext: ");
     string p_text = get_string();
     //declare an int and assign its length to keylen
     int keylen = strlen(key);
     //declare a character pointer 'cipher' and assign the value of user input
     char* cipher = p_text;
     //loop through the plaintext one character at a time
     for(int ch = 0, j = 0, length = strlen(p_text); ch < length; ch++)
     {
        //check if each character in plaintext are alphanumeric  
        if(isalpha(p_text[ch]))
        {
            //determine the key position, then wrap around if they end is reached
            char charletter = (isupper(key[j % keylen])) ? 'A' : 'a';
            //determine the letters in plaintext wheather they're lower or upper 
            char shift = (isupper(p_text[ch])) ? 'A' : 'a';
            //encrypt users plaintext with the formula: ci = (pi + kj) mod 26
            cipher[ch] = ((p_text[ch] - shift + (key[(j % keylen)] - charletter)) % 26) + shift;
            //increament the key position for next letter
            j++;
        }
        else
        {
            //print all non-alphabetical charaters as they are
            cipher[ch] = p_text[ch];
        }
     }
     //print the ciphertext to screen
     printf("ciphertext: %s\n", p_text);
     //return 0 on success
     return 0;
 }