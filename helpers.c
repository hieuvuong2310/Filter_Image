#include "helpers.h"
#include <math.h>
#include <stdlib.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    RGBTRIPLE color;
    int avg;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            color = image[i][j];
            avg = round(((float)color.rgbtBlue + (float)color.rgbtRed + (float)color.rgbtGreen) / 3); // get the avg
            if (avg > 0 && avg < 255) // within bounds
            {
                color.rgbtBlue = (avg);
                color.rgbtRed = (avg);
                color.rgbtGreen = (avg);
            }
            else if (avg >= 255) // out of upper bound
            {
                color.rgbtBlue = 255;
                color.rgbtRed = 255;
                color.rgbtGreen = 255;
            }
            else //out of lower bound
            {
                color.rgbtBlue = 0;
                color.rgbtRed = 0;
                color.rgbtGreen = 0;
            }
            new_image[i][j] = color; //copy to new array
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j]; // return back old array
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE color;
    int sepiaBlue;
    int sepiaRed;
    int sepiaGreen;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            color = image[i][j]; // get the color
            sepiaRed = round(.393 * color.rgbtRed + .769 * color.rgbtGreen + .189 * color.rgbtBlue);
            sepiaGreen = round(.349 * color.rgbtRed + .686 * color.rgbtGreen + .168 * color.rgbtBlue);
            sepiaBlue = round(.272 * color.rgbtRed + .534 * color.rgbtGreen + .131 * color.rgbtBlue);
            if (sepiaRed > 255) //check whether it is out of bounds or not
            {
                sepiaRed = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaRed < 0)
            {
                sepiaRed = 0;
            }
            if (sepiaBlue < 0)
            {
                sepiaBlue = 0;
            }
            if (sepiaGreen < 0)
            {
                sepiaGreen = 0;
            }
            color.rgbtRed = sepiaRed; // copy back a new color
            color.rgbtBlue = sepiaBlue;
            color.rgbtGreen = sepiaGreen;
            image[i][j] = color;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int j;
    int reflection;
    RGBTRIPLE colorFront;
    RGBTRIPLE colorBack;
    for (int i = 0; i < height; i++)
    {
        j = 0;
        while (j <= (width / 2 - 1)) // move to the mid position then stop
        {
            reflection = width - j - 1;
            colorBack = image[i][reflection];
            colorFront = image[i][j];
            image[i][reflection] = colorFront; // move back to front
            image[i][j] = colorBack; // move front to back
            j++;
        }
    }
    return;
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE new_image[height][width];
    RGBTRIPLE color;
    float red = 0;
    float blue = 0;
    float green = 0;
    float count = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // avg_of_all(height, width, image, i, j);
            red = green = blue = 0;
            count = 0;
            // add itself
            red += image[i][j].rgbtRed;
            green += image[i][j].rgbtGreen;
            blue += image[i][j].rgbtBlue;
            count++;
            // add left
            if (j - 1 >= 0)
            {
                red += image[i][j - 1].rgbtRed;
                green += image[i][j - 1].rgbtGreen;
                blue += image[i][j - 1].rgbtBlue;
                count++;
            }
            // add right
            if (j + 1 < width)
            {
                red += image[i][j + 1].rgbtRed;
                green += image[i][j + 1].rgbtGreen;
                blue += image[i][j + 1].rgbtBlue;
                count++;
            }
            // add uper line
            if (i - 1 >= 0)
            {
                // add upper left
                if (j - 1 >= 0)
                {
                    red += image[i - 1][j - 1].rgbtRed;
                    green += image[i - 1][j - 1].rgbtGreen;
                    blue += image[i - 1][j - 1].rgbtBlue;
                    count++;
                }
                // add upper middle
                red += image[i - 1][j].rgbtRed;
                green += image[i - 1][j].rgbtGreen;
                blue += image[i - 1][j].rgbtBlue;
                count++;
                // add upper right
                if (j + 1 < width)
                {
                    red += image[i - 1][j + 1].rgbtRed;
                    green += image[i - 1][j + 1].rgbtGreen;
                    blue += image[i - 1][j + 1].rgbtBlue;
                    count++;
                }
            }
            // add lower line
            if (i + 1 < height)
            {
                if (j - 1 >= 0)
                {
                    red += image[i + 1][j - 1].rgbtRed;
                    green += image[i + 1][j - 1].rgbtGreen;
                    blue += image[i + 1][j - 1].rgbtBlue;
                    count++;
                }
                // add upper middle
                red += image[i + 1][j].rgbtRed;
                green += image[i + 1][j].rgbtGreen;
                blue += image[i + 1][j].rgbtBlue;
                count++;
                // add upper right
                if (j + 1 < width)
                {
                    red += image[i + 1][j + 1].rgbtRed;
                    green += image[i + 1][j + 1].rgbtGreen;
                    blue += image[i + 1][j + 1].rgbtBlue;
                    count++;
                }
            }
            //copy to another array
            new_image[i][j].rgbtRed = round(red / count);
            new_image[i][j].rgbtGreen = round(green / count);
            new_image[i][j].rgbtBlue = round(blue / count);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j]; // copy back
        }
    }
    return;
}