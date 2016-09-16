/*Taylor Posey
CS50x 2016
Problem Set 2
This file encodes a given phrase using a keyword of the user's choice via vigenere encryption.
Expects an alphabetical keyword as an arguement, and a phrase to encode as user input.*/
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <unistd.h>

/*Returns 1 if string is all alphabetical characters*/
int allAlpha(string s);
/*Prints the cipher char based on given plain char and key char*/
void convertToCipher(int c, int k);
/*Returns a string with all lowercase characters. Assumes alpha only string*/
string allLower(string s);

int main(int argc, string argv[])
{
    /*If there isn't one argument that is all alphabetical, throw an error*/
    if (argc != 2 || !allAlpha(argv[1]))
    {
        printf("Please give a single keyword, all alphabetical characters.\n");
        return 1;
    }
    string key = allLower(argv[1]);
    string text = GetString();
    int index = 0; /*place in key word*/
    for (int i = 0; i < strlen(text); i++)
    {
        if(isalpha(text[i])) {
            convertToCipher(text[i], key[index % strlen(key)]);
            index++;
        } else { /*not an alphabetical*/
            printf("%c", text[i]);
        }
    }
    printf("\n");
    return 0;
}

void convertToCipher(int c, int k)
{
    k -= 97; /*0-index the ascii mapping*/
    if (c > 64 && c < 91) /*Capitol letters*/
    {
        printf("%c", (((c-65) + k) % 26) + 65);
    }
    else /*Lowercase letters*/
    {
        printf("%c", (((c-97) + k) % 26) + 97);
    }
}

string allLower(string s)
{
    for(int i = 0; i < strlen(s); i++) {
        s[i] = tolower(s[i]);
    }
    return s;
}

int allAlpha(string s)
{
    for (int i = 0; i < strlen(s); i++)
    {
        if (!isalpha(s[i])) {
            return 0;
        }
    }
    return 1;
}