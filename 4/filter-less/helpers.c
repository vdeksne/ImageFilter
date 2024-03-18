#include "helpers.h"
#include "math.h"
#include "stdlib.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int sum = 0;
    for (int i = 0; i < height; i++)
    {
        {
            for (int j = 0; j < width; j++)
            {
                sum = image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue;
                sum = round(sum / 3.00);
                image[i][j].rgbtRed = sum;
                image[i][j].rgbtGreen = sum;
                image[i][j].rgbtBlue = sum;
            }
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int originalRed, originalGreen, originalBlue, sepiaRed, sepiaGreen, sepiaBlue;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            originalRed = image[i][j].rgbtRed;
            originalGreen = image[i][j].rgbtGreen;
            originalBlue = image[i][j].rgbtBlue;
            sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            int new_j = width - j - 1;
            temp = image[i][j];
            image[i][j] = image[i][new_j];
            image[i][new_j] = temp;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_blur[height][width];
    double avgRed, avgGreen, avgBlue;
    float counter;

    // cycle rows
    for (int i = 0; i < height; i++)
    {
        // cycle columns
        for (int j = 0; j < width; j++)
        {
            counter = 0;
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;

            // cycle rows within 9 cell square
            for (int s = -1; s < 2; s++)
            {
                // cycle columns within 9 cell square
                for (int n = -1; n < 2; n++)
                {
                    // work only with cells that exist
                    int d = i + s;
                    int k = j + n;

                    if (d < height && k < width && d >= 0 && k >= 0)
                    {

                        avgRed = avgRed + image[d][k].rgbtRed;
                        avgGreen = avgGreen + image[d][k].rgbtGreen;
                        avgBlue = avgBlue + image[d][k].rgbtBlue;

                        // count existing cells within 9 cell square
                        counter++;
                    }
                }
            }

            // Find average value and round floats to nearest integer
            avgRed = round(avgRed / counter);
            avgGreen = round(avgGreen / counter);
            avgBlue = round(avgBlue / counter);

            // Update blured image array with average values
            image_blur[i][j].rgbtRed = avgRed;
            image_blur[i][j].rgbtGreen = avgGreen;
            image_blur[i][j].rgbtBlue = avgBlue;
        }
    }

    // overwrite the variable image with blured image

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = image_blur[i][j];
        }
    }

    return;
}
