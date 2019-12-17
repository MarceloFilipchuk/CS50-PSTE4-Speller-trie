#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cs50.h>

unsigned int hash (char word[], int counter);

int main (void)
{
   int *x = malloc(sizeof(int));
   if (x == NULL)
   {
        return 1;
   }
   *x = 4;
   int *y = x;
   if (*y < 5)
   {
       printf("Y es menor que 5\n");
   }
   printf("X= %i Y= %i .\n", *x, *y);
}
