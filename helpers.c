#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Take the original values for manipulation
            int blue = image[y][x].rgbtBlue;
            int green = image[y][x].rgbtGreen;
            int red = image[y][x].rgbtRed;

            // Find the average of each value
            float average = (float)(red + green + blue) / 3;
            int average_int = round(average);

            // Assign value
            image[y][x].rgbtBlue = average_int;
            image[y][x].rgbtGreen = average_int;
            image[y][x].rgbtRed = average_int;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Take original values for manipulation
            int originalBlue = image[y][x].rgbtBlue;
            int originalGreen = image[y][x].rgbtGreen;
            int originalRed = image[y][x].rgbtRed;

            // Sepia algorithm
            float sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue;
            float sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue;
            float sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue;

            // Assign value
            sepiaBlue = round(sepiaBlue);
            sepiaGreen = round(sepiaGreen);
            sepiaRed = round(sepiaRed);

            // In case the value is greater than the limit
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }

            // Assign value
            image[y][x].rgbtBlue = sepiaBlue;
            image[y][x].rgbtGreen = sepiaGreen;
            image[y][x].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < (width / 2); x++)
        {
            // Create a copy of the image to reference after original image has been manipulated
            RGBTRIPLE img = image[y][x];

            // Invert image
            image[y][x] = image[y][width - (x + 1)];
            image[y][width - (x + 1)] = img;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE img[height][width];
    // Creates a copy of the image to refer to after manipulating the original
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            img[y][x] = image[y][x];
        }
    }
    // Make conditions for the corners and edges
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            // Upper left
            if ((y == 0) && (x == 0))
            {
                int b = round((float)(img[0][0].rgbtBlue + img[0][1].rgbtBlue + img[1][0].rgbtBlue + 
                                      img[1][1].rgbtBlue) / 4);

                int g = round((float)(img[0][0].rgbtGreen + img[0][1].rgbtGreen + img[1][0].rgbtGreen + 
                                      img[1][1].rgbtGreen) / 4);

                int r = round((float)(img[0][0].rgbtRed + img[0][1].rgbtRed + img[1][0].rgbtRed + 
                                      img[1][1].rgbtRed) / 4);


                image[0][0].rgbtBlue = b;
                image[0][0].rgbtGreen = g;
                image[0][0].rgbtRed = r;
            }

            // Lower left
            else if ((y == height - 1) && (x == 0))
            {
                int b = round((float)(img[height - 1][0].rgbtBlue + img[height - 1][1].rgbtBlue + 
                                      img[height - 2][0].rgbtBlue + img[height - 2][1].rgbtBlue) / 4);

                int g = round((float)(img[height - 1][0].rgbtGreen + img[height - 1][1].rgbtGreen + 
                                      img[height - 2][0].rgbtGreen + img[height - 2][1].rgbtGreen) / 4);

                int r = round((float)(img[height - 1][0].rgbtRed + img[height - 1][1].rgbtRed + 
                                      img[height - 2][0].rgbtRed + img[height - 2][1].rgbtRed) / 4);


                image[height - 1][0].rgbtBlue = b;
                image[height - 1][0].rgbtGreen = g;
                image[height - 1][0].rgbtRed = r;
            }

            // Upper right
            else if ((y == 0) && (x == width - 1))
            {
                int b = round((float)(img[0][width - 1].rgbtBlue + img[1][width - 1].rgbtBlue + 
                                      img[0][width - 2].rgbtBlue + img[1][width - 2].rgbtBlue) / 4);

                int g = round((float)(img[0][width - 1].rgbtGreen + img[1][width - 1].rgbtGreen + 
                                      img[0][width - 2].rgbtGreen + img[1][width - 2].rgbtGreen) / 4);

                int r = round((float)(img[0][width - 1].rgbtRed + img[1][width - 1].rgbtRed + 
                                      img[0][width - 2].rgbtRed + img[1][width - 2].rgbtRed) / 4);


                image[0][width - 1].rgbtBlue = b;
                image[0][width - 1].rgbtGreen = g;
                image[0][width - 1].rgbtRed = r;
            }

            // Lower right
            else if ((y == height - 1) && (x == width - 1))
            {
                int b = round((float)(img[height - 1][width - 1].rgbtBlue + img[height -2][width - 1].rgbtBlue + 
                                      img[height - 1][width - 2].rgbtBlue + img[height - 2][width - 2].rgbtBlue) / 4);

                int g = round((float)(img[height - 1][width - 1].rgbtGreen + img[height -2][width - 1].rgbtGreen + 
                                      img[height - 1][width - 2].rgbtGreen + img[height - 2][width - 2].rgbtGreen) / 4);

                int r = round((float)(img[height - 1][width - 1].rgbtRed + img[height -2][width - 1].rgbtRed + 
                                      img[height - 1][width - 2].rgbtRed + img[height - 2][width - 2].rgbtRed) / 4);


                image[height - 1][width - 1].rgbtBlue = b;
                image[height - 1][width - 1].rgbtGreen = g;
                image[height - 1][width - 1].rgbtRed = r;
            }

            // Edges

            // Top
            else if (y == 0 && x != 0 && x != width - 1)
            {
                int b = round((float)(img[y + 1][x - 1].rgbtBlue + img[y][x - 1].rgbtBlue + img[y + 1][x].rgbtBlue + 
                                      img[y][x + 1].rgbtBlue + img[y][x].rgbtBlue + img[y + 1][x + 1].rgbtBlue) / 6);

                int g = round((float)(img[y + 1][x - 1].rgbtGreen + img[y][x - 1].rgbtGreen + img[y + 1][x].rgbtGreen + 
                                      img[y][x + 1].rgbtGreen + img[y][x].rgbtGreen + img[y + 1][x + 1].rgbtGreen) / 6);

                int r = round((float)(img[y + 1][x - 1].rgbtRed + img[y][x - 1].rgbtRed + img[y + 1][x].rgbtRed + 
                                      img[y][x + 1].rgbtRed + img[y][x].rgbtRed + img[y + 1][x + 1].rgbtRed) / 6);


                image[y][x].rgbtBlue = b;
                image[y][x].rgbtGreen = g;
                image[y][x].rgbtRed = r;
            }

            // Bottom
            else if (y == height - 1 && x != 0 && x != width - 1)
            {
                int b = round((float)(img[y - 1][x - 1].rgbtBlue + img[y][x + 1].rgbtBlue + img[y - 1][x].rgbtBlue + 
                                      img[y][x - 1].rgbtBlue + img[y][x].rgbtBlue + img[y - 1][x + 1].rgbtBlue) / 6);

                int g = round((float)(img[y - 1][x - 1].rgbtGreen + img[y][x + 1].rgbtGreen + img[y - 1][x].rgbtGreen + 
                                      img[y][x - 1].rgbtGreen + img[y][x].rgbtGreen + img[y - 1][x + 1].rgbtGreen) / 6);

                int r = round((float)(img[y - 1][x - 1].rgbtRed + img[y][x + 1].rgbtRed + img[y - 1][x].rgbtRed + 
                                      img[y][x - 1].rgbtRed + img[y][x].rgbtRed + img[y - 1][x + 1].rgbtRed) / 6);


                image[y][x].rgbtBlue = b;
                image[y][x].rgbtGreen = g;
                image[y][x].rgbtRed = r;
            }
            
            // Left
            else if (y != 0 && y != height - 1 && x == 0)
            {
                int b = round((float)(img[y - 1][x].rgbtBlue + img[y + 1][x].rgbtBlue + img[y - 1][x + 1].rgbtBlue + 
                                      img[y][x + 1].rgbtBlue + img[y][x].rgbtBlue + img[y + 1][x + 1].rgbtBlue) / 6);

                int g = round((float)(img[y - 1][x].rgbtGreen + img[y + 1][x].rgbtGreen + img[y - 1][x + 1].rgbtGreen + 
                                      img[y][x + 1].rgbtGreen + img[y][x].rgbtGreen + img[y + 1][x + 1].rgbtGreen) / 6);

                int r = round((float)(img[y - 1][x].rgbtRed + img[y + 1][x].rgbtRed + img[y - 1][x + 1].rgbtRed + 
                                      img[y][x + 1].rgbtRed + img[y][x].rgbtRed + img[y + 1][x + 1].rgbtRed) / 6);


                image[y][x].rgbtBlue = b;
                image[y][x].rgbtGreen = g;
                image[y][x].rgbtRed = r;
            }

            // Right
            else if (y != 0 && y != height - 1 && x == width - 1)
            {
                int b = round((float)(img[y - 1][x].rgbtBlue + img[y + 1][x].rgbtBlue + img[y - 1][x - 1].rgbtBlue + 
                                      img[y][x - 1].rgbtBlue + img[y][x].rgbtBlue + img[y + 1][x - 1].rgbtBlue) / 6);

                int g = round((float)(img[y - 1][x].rgbtGreen + img[y + 1][x].rgbtGreen + img[y - 1][x - 1].rgbtGreen + 
                                      img[y][x - 1].rgbtGreen + img[y][x].rgbtGreen + img[y + 1][x - 1].rgbtGreen) / 6);

                int r = round((float)(img[y - 1][x].rgbtRed + img[y + 1][x].rgbtRed + img[y - 1][x - 1].rgbtRed + 
                                      img[y][x - 1].rgbtRed + img[y][x].rgbtRed + img[y + 1][x - 1].rgbtRed) / 6);


                image[y][x].rgbtBlue = b;
                image[y][x].rgbtGreen = g;
                image[y][x].rgbtRed = r;
            }

            // The rest of the image
            else
            {
                int b = round((float)(img[y - 1][x - 1].rgbtBlue + img[y + 1][x + 1].rgbtBlue + img[y - 1][x].rgbtBlue + 
                                      img[y][x + 1].rgbtBlue + img[y][x].rgbtBlue + img[y + 1][x - 1].rgbtBlue + 
                                      img[y - 1][x + 1].rgbtBlue + img[y][x - 1].rgbtBlue + img[y + 1][x].rgbtBlue) / 9);

                int g = round((float)(img[y - 1][x - 1].rgbtGreen + img[y + 1][x + 1].rgbtGreen + img[y - 1][x].rgbtGreen + 
                                      img[y][x + 1].rgbtGreen + img[y][x].rgbtGreen + img[y + 1][x - 1].rgbtGreen + 
                                      img[y - 1][x + 1].rgbtGreen + img[y][x - 1].rgbtGreen + img[y + 1][x].rgbtGreen) / 9);

                int r = round((float)(img[y - 1][x - 1].rgbtRed + img[y + 1][x + 1].rgbtRed + img[y - 1][x].rgbtRed + 
                                      img[y][x + 1].rgbtRed + img[y][x].rgbtRed + img[y + 1][x - 1].rgbtRed + 
                                      img[y - 1][x + 1].rgbtRed + img[y][x - 1].rgbtRed + img[y + 1][x].rgbtRed) / 9);


                image[y][x].rgbtBlue = b;
                image[y][x].rgbtGreen = g;
                image[y][x].rgbtRed = r;
            }
            
        }
    }
    return;
}
