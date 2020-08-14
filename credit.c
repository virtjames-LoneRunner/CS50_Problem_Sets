#include <stdio.h>
#include <cs50.h>

int card[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

int odd_count = 0;
int odd[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int odd_total = 0;

int even_count = 0;
int even[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int even_total = 0;

int odd_double = 0;
int total = 0;

bool confirm;

int check_validity(int digits[]);

int main(void)
{
    int card_type;
    // Get user input
    int card[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    long int card_number = get_long("Number : ");


    // Separate user input into individual digits
    for (int i=0; i <= 15; i+=1)
    {
        card[i] = card_number % 10;
        card_number /= 10;
    }


    // Determine possible card_type
    /*
        0 == Invalid
        1 == visa 13
        2 == Visa 16
        3 == American Express
        4 == Mastercard
    */

   // If card has 13 digits, check if it is visa 13.
    if (card[15] == 0)
    {
        if (card[14] == 0)
        {
            if (card[13] == 0)
            {
                if (card[12] == 4)
                {
                    card_type = 1;
                }
                else
                {
                    card_type = 0;
                }

            }
            else if (card[13] > 0)
            {
                card_type = 0;
            }
        }

        // If card has 15 digits, check if it is American Express.
        else if (card[14] == 3)
        {
            if (card[13] == 4 || card[13] == 7)
            {
                card_type = 3;
            }
            else
            {
                card_type = 0;
            }

        }
        else
        {
            card_type = 0;
        }

    }

    // If card has 16 digits, check if it is Visa 16 or Mastercard.
    else if ((card[15] > 0) && (card[15] == 5 || card[15] == 4))
    {
        if (card[15] == 4)
        {
            card_type = 2;
        }
        else if (card[15] == 5)
        {
            if (0 < card[14] < 6)
            {
                card_type = 4;
            }
            else
            {
                card_type = 0;
            }

        }
    }
    else
    {
        card_type = 0;
    }


    // Check validity

    // Visa-13
    if (card_type == 1)
    {
        confirm = check_validity(card);
        if (confirm == true)
        {
            printf("VISA\n");
        }
        else if (confirm == false)
        {
            printf("INVALID\n");
        }
    }

    // Visa-16
    else if (card_type == 2)
    {
        confirm = check_validity(card);
        if (confirm == true)
        {
            printf("VISA\n");
        }
        else if (confirm == false)
        {
            printf("INVALID\n");
        }


    }

    // American Express
    else if (card_type == 3)
    {
        confirm = check_validity(card);
        if (confirm == true)
        {
            printf("AMERICAN EXPRESS\n");
        }
        else if (confirm == false)
        {
            printf("INVALID\n");
        }
    }

    // Mastercard
    else if (card_type == 4)
    {
        confirm = check_validity(card);
        if (confirm == true)
        {
            printf("MASTERCARD\n");
        }
        else if (confirm == false)
        {
            printf("INVALID\n");
        }
    }
    else if (card_type == 0)
    {
        printf("INVALID\n");
    }

}

// If card passes initial test, check with Luhn's Algorithm.
int check_validity(int digits[])
{
    for (int j = 1; j <= 15; j += 2)
        {
            odd[odd_count] = digits[j];
            odd_count += 1;
        }
        for (int c = 0; c <= odd_count; c++ )
        {
            int odd_double = 0;
            odd_double = odd[c] * 2;
            if (odd_double > 9)                 // If the product has two digits, separate the digits.
            {
                int first = odd_double % 10;
                int second = odd_double /= 10;
                odd[c] = first + second;        // Add the two digits.
            }
            else if (odd_double < 10)
            {
                odd[c] = odd_double;
            }
            odd_total += odd[c];
        }
        for (int m = 0; m <= 14; m += 2)
        {
            even[even_count] = digits[m];
            even_total += even[even_count];
            even_count += 1;
        }
        int total;
        total = odd_total + even_total;

        // Check if the card is valid.
        if (total % 10 == 0)
        {
            return true;
        }
        else if (total % 10 != 0)
        {
            return false;
        }

}