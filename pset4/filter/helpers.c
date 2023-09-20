#include "helpers.h"
#include <math.h>


// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            unsigned int a = (int) image[i][j].rgbtBlue;
            unsigned int b =(int) image[i][j].rgbtGreen;
            unsigned int c = (int) image[i][j].rgbtRed;

            unsigned int average = round( (a + b + c)/3.00 ); //stupid 0, it does things from right to left so make sure right side is a float, sothat it can be rounded

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        int l = 1;
        int k = 0;
        if( width % 2 != 0)
        {
            int middle = (width - 1) / 2;
            for( int j = 0; j < middle; j++)
            {
                RGBTRIPLE box;
                box = image[i][j];
                image[i][j] = image[i][width - (k + 1)];
                image[i][width - (k + 1)] = box;
                k++;
            }
        }
        else if( (width % 2 == 0) && width != 2 )
        {
            for(int m = 0; m < width/2; m++)
            {
                RGBTRIPLE box;
                box = image[i][m];
                image[i][m] = image[i][width - l];
                image[i][width - l] = box;
                l++;
            }
        }
        if( (width < 3) && ( width != 1 && width != 0) )
            {
                RGBTRIPLE box;
                box = image[i][0];
                image[i][0] = image[i][1];
                image[i][1] = box;
            }

    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newimage[height][width];

    for(int i = 0; i < height; i++ )
    {
        for(int j = 0; j < width; j++)
        {
            //each block has a sumvalue and a counter of blocks( edge block has 4, centre 9, side 6)
            int sumBlue, sumGreen, sumRed;
            sumBlue = sumGreen = sumRed = 0.0;

            float counter = 0.00;

            // let's create an imaginay 3x3 block
            for( int m = -1; m < 2; m++ )
            {
                for( int n = -1; n < 2; n++)
                {

                    // let's create an imaginay 3x3 block
                    int x = i + m; //this is x position of all the neighbor blocks surrounding the [i][j].block ( includung the current position )
                    int y = j + n; //this is y position of all the neighbor blocks surrounding the [i][j].block ( includung the current position )

                    //check for valid blocks
                    if( x < 0 || x > (height - 1) || y < 0 || y > (width - 1) ) //this is to make sure no block goes beyond the border of image
                    {
                        continue;
                    }

                    sumRed += image[x][y].rgbtRed;
                    sumGreen += image[x][y].rgbtGreen;
                    sumBlue += image[x][y].rgbtBlue;

                    counter++; //counter only increase when found a valid Block

                }

            }
            //calculate the average of each pixel's value of a pixel
                newimage[i][j].rgbtBlue = round(sumBlue / counter);
                newimage[i][j].rgbtGreen = round(sumGreen / counter);
                newimage[i][j].rgbtRed = round(sumRed / counter);
        }
    }

    //passing the value of newimage to the original image
    for( int i = 0; i < height; i++)
    {
        for( int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //make copy of image
    RGBTRIPLE copyimage[height][width];

    int Gx[3][3] = {

            { -1,0,1 },
            { -2,0,2 },
            { -1,0,1 }
    };

    int Gy[3][3] = {

            { -1,-2,-1 },
            { 0,0,0 },
            { 1,2,1 }
    };

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            int sumRed_Gx, sumGreen_Gx, sumBlue_Gx;
            sumRed_Gx = sumGreen_Gx = sumBlue_Gx = 0;

            int sumRed_Gy, sumGreen_Gy, sumBlue_Gy;
            sumRed_Gy = sumGreen_Gy = sumBlue_Gy = 0;


            for(int m = -1; m < 2; m++)
            {
                for(int n = -1; n < 2; n++ )
                {
                    int x = i + m;
                    int y = j + n;

                    if( x < 0 || x > (height - 1) || y < 0 || y > (width - 1) )
                    {
                        continue;
                    }

                    sumRed_Gx += image[x][y].rgbtRed * Gx[m + 1][n + 1];
                    sumGreen_Gx += image[x][y].rgbtGreen * Gx[m  + 1][n + 1];
                    sumBlue_Gx += image[x][y].rgbtBlue * Gx[m + 1][n + 1];

                    sumRed_Gy += image[x][y].rgbtRed * Gy[m + 1 ][n + 1];
                    sumGreen_Gy += image[x][y].rgbtGreen * Gy[m + 1][n + 1];
                    sumBlue_Gy += image[x][y].rgbtBlue * Gy[m + 1][n + 1];

                }
            }

            // calculate the value and cap in 255
            // fmin determines the smaller of the two specified values.
            copyimage[i][j].rgbtRed = fmin( round (sqrt(sumRed_Gx*sumRed_Gx + sumRed_Gy*sumRed_Gy)), 255 );
            copyimage[i][j].rgbtGreen = fmin( round (sqrt(sumGreen_Gx*sumGreen_Gx + sumGreen_Gy*sumGreen_Gy)), 255);
            copyimage[i][j].rgbtBlue = fmin( round (sqrt(sumBlue_Gx*sumBlue_Gx + sumBlue_Gy*sumBlue_Gy)), 255);


        }
    }

    for( int i = 0; i < height; i++)
    {
        for( int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = copyimage[i][j].rgbtBlue;
            image[i][j].rgbtGreen = copyimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = copyimage[i][j].rgbtRed;
        }
    }

    return;
}
