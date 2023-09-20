#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int average = round ((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0);
            image[i][j].rgbtBlue = image[i][j].rgbtGreen = image[i][j].rgbtRed = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE pixel;
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(j < width/2)
            {
                pixel = image[i][j];
                image[i][j] = image[i][width - 1 - j];
                image[i][width - 1 - j] = pixel;
            }
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_Image[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int average_Red = 0;
            int average_Green = 0;
            int average_Blue = 0;
            float counter = 0.00;
            for(int m = -1; m < 2; m++)
            {
                for(int n = -1; n < 2; n++)
                {
                    if(i + m > height - 1 || i + m < 0 || j + n < 0 || j +n > width - 1)
                    {
                        continue;
                    }
                    average_Red += image[i + m][j + n].rgbtRed;
                    average_Green += image[i + m][j + n].rgbtGreen;
                    average_Blue += image[i + m][j + n].rgbtBlue;
                    counter++;
                }

            new_Image[i][j].rgbtRed = round(average_Red / counter);
            new_Image[i][j].rgbtGreen = round(average_Green / counter);
            new_Image[i][j].rgbtBlue = round(average_Blue / counter);
            }
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = new_Image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = new_Image[i][j].rgbtGreen;
            image[i][j].rgbtRed = new_Image[i][j].rgbtRed;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE new_Image[height][width];

            int Gx[3][3] = {    {-1, 0, 1},
                                {-2, 0, 2},
                                {-1, 0, 1}
                        };
            int Gy[3][3] = {    {-1, -2, -1},
                                {0, 0, 0},
                                {1, 2, 1}
                        };
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sum_Gx_Red = 0;
            int sum_Gy_Red = 0;

            int sum_Gx_Green = 0;
            int sum_Gy_Green = 0;

            int sum_Gx_Blue = 0;
            int sum_Gy_Blue = 0;
            for(int m = -1; m < 2; m++)
            {
                for(int n = -1; n < 2; n++)
                {
                    if(i + m > height - 1 || i + m < 0 || j + n < 0 || j +n > width - 1)
                    {
                        continue;
                    }
                sum_Gx_Red += image[i + m][j + n].rgbtRed * Gx[m + 1][n + 1];
                sum_Gy_Red += image[i + m][j + n].rgbtRed * Gy[m + 1][n + 1];

                sum_Gx_Green += image[i + m][j + n].rgbtGreen * Gx[m + 1][n + 1];
                sum_Gy_Green += image[i + m][j + n].rgbtGreen * Gy[m + 1][n + 1];

                sum_Gx_Blue += image[i + m][j + n].rgbtBlue * Gx[m + 1][n + 1];
                sum_Gy_Blue += image[i + m][j + n].rgbtBlue * Gy[m + 1][n + 1];

                }

            }
            new_Image[i][j].rgbtRed = fmin(round( sqrt(pow(sum_Gx_Red, 2) + pow(sum_Gy_Red, 2) )), 255);
            new_Image[i][j].rgbtGreen = fmin(round( sqrt(pow(sum_Gx_Green, 2) + pow(sum_Gy_Green, 2))), 255);
            new_Image[i][j].rgbtBlue = fmin(round ( sqrt(pow(sum_Gx_Blue, 2) + pow(sum_Gy_Blue, 2))), 255);

        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = new_Image[i][j].rgbtBlue;
            image[i][j].rgbtGreen = new_Image[i][j].rgbtGreen;
            image[i][j].rgbtRed = new_Image[i][j].rgbtRed;
        }
    }
    return;
}
