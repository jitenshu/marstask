#include <stdio.h>
#include <ctype.h> //new to me
#include <string.h>

//this function undoes the shift for a single character
char reverse_shift(char ch, int pos) 
{
    //if the character is lowercase, convert to uppercase
    if (ch >= 'a' && ch <= 'z')
    {
        ch = ch - 'a' + 'A';
    }

    //calculate how much to shift back
    int shift = pos + 1;

    //shift the character backward
    ch = ch - shift;

    //if it goes before 'A', wrap it around the alphabet
    if (ch < 'A') 
    {
        ch = ch + 26;
    }

    return ch;
}

int main() 
{
    char input[100];

    //ask the user to enter the encrypted message
    printf("enter the encrypted message:\n");
    fgets(input, sizeof(input), stdin);

    //figure out the length (excluding newline)
    int len = strlen(input);
    if (input[len - 1] == '\n') 
    {
        input[len - 1] = '\0'; //remove newline
        len--;
    }

    //print decoded message
    printf("decoded message:\n");

    //loop through each character
    for (int i = 0; i < len; i++) 
    {
        //apply reverse shift using position
        char decoded = reverse_shift(input[i], i);

        //print the decoded letter
        printf("%c", decoded);
    }

    //print newline at the end
    printf("\n");

    return 0;
}