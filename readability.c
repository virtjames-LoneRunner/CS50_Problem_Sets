#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int n;
int number_of_characters;

char alphabet[4] = {'A', 'Z', 'a', 'z'};

int num_of_letters;
int num_of_words = 1;
int num_of_sentences;
//float index_score;

void check_level(int letters, int sentences, int words);

int main(void)
{
    // Prompt user input
    string sentences = get_string("Text: ");
    n = strlen(sentences);

    /* Separate characters and determine the number of
    letters,
    words,
    and sentences
    */
    char characters[n];
    for (int i = 0; i < n; i++)
    {
        characters[i] = sentences[i];
        number_of_characters++;
        if (isalpha(characters[i]))
        {
            num_of_letters += 1;
        }
        if (isspace(characters[i]))
        {
            num_of_words += 1;
        }
        if ((int)characters[i] == 46 || (int)characters[i] == 33 || (int)characters[i] == 63)
        {
            num_of_sentences += 1;
        }

    }

    check_level(num_of_letters, num_of_sentences, num_of_words);
    return 0;
}


void check_level(int letters, int sentences, int words)
{
    float L = (letters / (float)words) * 100;
    float S = (sentences / (float)words) * 100;

    //L = round(L);
    //S = roundf(S);

    float index_score = 0.0588 * L - 0.296 * S - 15.8;

    index_score = round(index_score);

    // Determine Readability
    if (index_score < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index_score > 1 && index_score < 16)
    {
        printf("Grade %i\n", (int)index_score);
    }
    else
    {
        printf("Grade 16+\n");
    }
}