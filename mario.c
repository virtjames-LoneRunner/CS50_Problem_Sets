#include <stdio.h>
#include <cs50.h>

int get_rows(void);
void print_pyramid(int rows);


int main(void)
{
    // Prompt user for pyramid height
    int rows = get_rows();
    print_pyramid(rows);

}


int get_rows(void)
{
    int number_of_rows;
    do
    {
        number_of_rows = get_int("Height: ");
    }
    while (1 > number_of_rows || number_of_rows > 8);
    return number_of_rows;
}

void print_pyramid(rows)
{
    int spaces;
    // Print pyramid
    for (int i = 1; i < rows + 1; i++)
    {
        // Print spaces, determine value for spaces by subtracting the value of i from rows
        for (spaces = rows - i; spaces != 0; spaces--)
        {
            printf(" ");
        }

        //Print #'s
        for (int j = i; j > 0; j--)
        {
            printf("#");
        }


        printf("  ");

        // Print #'s on the left side'
        for (int h = 1; h <= i; h++)
        {
            printf("#");
        }


        printf("\n");

    }
}