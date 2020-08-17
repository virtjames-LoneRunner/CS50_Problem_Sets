#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

int encrypt(int input, string argument);

int main(int argc, string argv[])
{
    int successful = 0;
    // Check if there is an argument
    if (argc == 2)
    {
        int argv_length = strlen(argv[1]);
        char character_test[argv_length];
        int good_input = 0;

        // Check if argument is valid/an integer
        for (int i = 0; i < argv_length; i++)
        {
            character_test[i] = argv[1][i];
            if (isdigit(character_test[i]))
            {
                good_input += 0;
            }
            else
            {
                good_input +=1;
            }
        }

        // Encryption function
        // Returns 1 if one or more requirement/s is/are not met
        successful = encrypt(good_input, argv[1]);
    }

    else if(argc != 2)
    {
        printf("Usage: ./ceasar key \n");
        return 1;
    }

    // Checks to see if encryption was successful
    // If not, main function will return 1 or an error
    if (successful == 1)
    {
        return 1;
    }

    printf("\n");

    return 0;
}



int encrypt(int input, string argument)
{
    if (input == 0)
    {
        int key = atoi(argument); // Convert string to integer

        // Other Variables
        string message = get_string("plaintext: ");
        int length = strlen(message);
        printf("ciphertext: ");

        // Encrypts message using Caesar's cipher
        for (int i = 0; i < length; i++)
        {
            if (message[i] >= 'a' && message[i] <= 'z')
            {
                char new_char = (((message[i] - 'a') + key) % 26) + 'a';
                printf("%c", new_char);
            }

            else if (message[i] >= 'A' && message[i] <= 'Z')
            {
                char new_char = (((message[i] - 'A') + key) % 26) + 'A';
                printf("%c", new_char);
            }

            else if (isspace(message[i]) || ispunct(message[i]))
            {
                char new_char = message[i];
                printf("%c", new_char);
            }
        }

    }

    else if (input != 0)
    {
        printf("Usage: ./ceasar key \n");
        return 1;
    }

    return 0;
}
