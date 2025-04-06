#include <stdio.h>
#include <string.h>

//map each morse symbol to a character
struct entry {
    char *morse;
    char letter;
};

//lookup table for a-z and 0-9 in morse
struct entry table[] = {
    {".-", 'a'}, {"-...", 'b'}, {"-.-.", 'c'}, {"-..", 'd'}, {".", 'e'},
    {"..-.", 'f'}, {"--.", 'g'}, {"....", 'h'}, {"..", 'i'}, {".---", 'j'},
    {"-.-", 'k'}, {".-..", 'l'}, {"--", 'm'}, {"-.", 'n'}, {"---", 'o'},
    {".--.", 'p'}, {"--.-", 'q'}, {".-.", 'r'}, {"...", 's'}, {"-", 't'},
    {"..-", 'u'}, {"...-", 'v'}, {".--", 'w'}, {"-..-", 'x'}, {"-.--", 'y'},
    {"--..", 'z'}, {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'},
    {"....-", '4'}, {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'},
    {"----.", '9'}
};

//function that checks what letter a morse symbol stands for
char decode_one(char *code) 
{
    for (int i = 0; i < sizeof(table)/sizeof(table[0]); i++) 
    {
        if (strcmp(code, table[i].morse) == 0) 
        {
            return table[i].letter;
        }
    }
    return '?'; //if the morse code doesn’t match anything
}

int main() 
{
    char line[1000];

    //ask the user to type in a morse code message
    printf("enter morse code message:\n");
    fgets(line, sizeof(line), stdin); //get full line of input

    //split the input into each morse code symbol
    //symbols are separated by spaces
    //words are separated by '/'
    char *part = strtok(line, " \n");

    //go through each symbol one by one
    while (part != NULL) 
    {
        if (strcmp(part, "/") == 0) 
        {
            printf(" "); //if we hit a slash, print a space (word separator)
        } 
        else 
        {
            char decoded = decode_one(part); //convert morse to letter
            printf("%c", decoded); //print the letter
        }
        part = strtok(NULL, " \n"); //move to next symbol
    }

    printf("\n"); //new line at the end
    return 0;
}