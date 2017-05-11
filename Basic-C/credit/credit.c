 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Credit                                  *
 * Description:                                    *
 * Implement a program that determines whether a   *
 * provided credit card number is valid according  *
 * to Luhn’s algorithm                             *
 * ************************************************/
 
 /* Amex uses 15 digit numbers starting with 34 or 37
    Mastercard Uses 16 digit numbers starting 51, 52, 53, 54, or 55
    Visa Uses 13 and 16 digit numbers starting 4
 */
 
 #include <stdio.h>
 #include <cs50.h>
 #include <math.h>
 
 int main(void)
 {
  long long card_number;
  
  do
  {
   printf("Number: ");
   card_number = GetLongLong();
  }
  while(card_number < 0);
  
  long long rev = 0;
  long long rem = 0;
  
  while(card_number > 0)
  {
   rem = card_number%10;
   rev = rev*10+rem;
   card_number /= 10;
  }
  printf("%lld\n", rev);
  
  
  //return 0;
 }