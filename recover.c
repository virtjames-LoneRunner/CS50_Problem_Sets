#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t BYTE;
#define BUFFER_SIZE 512
unsigned char buffer[BUFFER_SIZE];
int files = 0;
bool found_jpg = false;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        fprintf(stderr, "Could not open file\n");
        return 1;
    }

    FILE *output;

    while (fread(buffer, BUFFER_SIZE, 1, file) == 1)
    {
        
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xe0) == 0xe0)
        {
            if (found_jpg == true)
            {
                fclose(output);
            }
            else
            {
                found_jpg = true;
            }
            
            char filename[8];
            sprintf(filename, "%03d.jpg", files);
            output = fopen(filename, "a");
            files++;
        }
        
        if (found_jpg == true)
        {
            fwrite(&buffer, BUFFER_SIZE, 1, output);
        }

    }

    fclose(file);
    fclose(output);
}
