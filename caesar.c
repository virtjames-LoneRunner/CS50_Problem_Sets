#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, string argv[])
{

    if(argc != 2 || isalpha(*argv[1]))
    {
        printf("Usage: ./ceasar key \n");
        return 1;
    }
    if (argc >= 2 && isdigit(*argv[1]))
    {
        int key = atoi(argv[1]);
        printf("Cipher key: %i\n", key);

        string message = get_string("plaintext: ");
        int length = strlen(message);
        printf("ciphertext: ");

        for (int i = 0; i < length; i++)
        {
            if (message[i] >= 'a' && message[i] <= 'z')
            {
                char new_char = (((message[i] - 'a') + key) % 26) + 'a';
                printf("%c", new_char);
            }
            if (message[i] >= 'A' && message[i] <= 'Z')
            {
                char new_char = (((message[i] - 'A') + key) % 26) + 'A';
                printf("%c", new_char);
            }
            if (isspace(message[i]) || ispunct(message[i]))
            {
                char new_char = message[i];
                printf("%c", new_char);
            }

        }
        printf("\n");
    }
    else
    {
        printf("Usage: ./ceasar key \n");
        return 1;
    }




}