#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



int main(int argc, string argv[])
{

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



        // If argument is valid, proceed
        if (good_input == 0)
        {
            int key = atoi(argv[1]); // Convert string to integer

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

        }

    // If one or more of the requirement/s is/are not met
        else
        {
            printf("Usage: ./ceasar key \n");
            return 1;
        }
        //printf("\n");
    }
    else if(argc != 2)
    {
        printf("Usage: ./ceasar key \n");
        return 1;
    }

    printf("\n");

    return 0;



}