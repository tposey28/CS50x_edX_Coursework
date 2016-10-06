/**
 * recover.c
 *
 * Taylor Posey
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image, which is hardcoded to be card.raw.
 */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <cs50.h>
typedef uint8_t BYTE;

bool isJPEG(BYTE*);

int main(int argc, char* argv[])
{
    // open card.raw image
    FILE* image = fopen("card.raw", "r");
    
    // verify that the file was opened
    if (image == NULL)
    {
        printf("Could not open %s.\n", "card.raw");
        return 1;
    }
    
    // set variables for reading
    int jpeg_num = 0;
    int block_size = 512;
    char title[8];
    bool found = false;
    BYTE buffer[block_size];
    FILE* jpeg;
    
    // read until first image is found, then write images block by block
    while(fread(&buffer, block_size, 1, image) == 1)
    {
        // if we have found a new JPEG
        if (isJPEG(buffer))
        {
            // check if it is the first
            if (found)
            {
                fclose(jpeg);
            } 
            else
            {
                found = true;
            }
            // then write to a new JPEG file in this folder
            sprintf(title, "%'.03d.jpg", jpeg_num);
            jpeg = fopen(title, "w");
            jpeg_num++;
        }
        // only write if we've found a JPEG
        if (found)
        {
            fwrite(&buffer, block_size, 1, jpeg);
        }
    }
    
    // close our file streams
    fclose(jpeg);
    fclose(image);
}

/**
 * Returns a boolean representing if the given array of bytes is the
 * beginning of a JPEG file. Assumes the JPEG is block aligned, ie the
 * file starts at the first byte of the block.
 */
bool isJPEG(BYTE* buffer)
{
    // Do the first four bytes indicate a (likely) JPEG file?
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && buffer[3] >= 224)
    {
        return true;
    } 
    else
    {
        return false;
    }
}
