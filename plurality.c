#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

#define pass (void)0

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name)
{
    // Checks if the input is valid
    int found = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(name, candidates[j].name) == 0)
        {
            found += 0;
            candidates[j].votes += 1;
            //printf("Candidate %s has %i vote(s) thus far.\n", candidates[j].name, candidates[j].votes);
            return true;
        }
        else
        {
            found += 1;
            //printf("%i\n", found);
        }
    }
    if (found > 0)
    {
        return false;
    }
    
    
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int current_most_vote = 0;
    for (int k = 0; k < MAX; k++)
    {
        if (current_most_vote < candidates[k].votes)
        {
            current_most_vote = candidates[k].votes;
            //printf("Current most votes = %i\n", current_most_vote);
        }
    }
    //printf("Winner(s)!: ");
    for (int l = 0; l < MAX; l++)
    {
        if (current_most_vote == candidates[l].votes)
        {
            printf("%s\n", candidates[l].name);
        }
    }
    //printf("\n");
    return;
}

