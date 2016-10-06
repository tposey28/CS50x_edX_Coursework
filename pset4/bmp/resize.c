/**
 * resize.c
 *
 * Taylor Posey
 * Computer Science 50
 * Problem Set 4
 *
 * Copies and resizes a BMP image.
 * Requires an integer argument representing the size
 * multiplier, a file name for input, and a file name
 * for output.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }
    
    if (atoi(argv[1]) < 1 || atoi(argv[1]) > 100) 
    {
         printf("Multiplier needs to be between 1 and 100 inclusive\n");   
         return 2;
    }    

    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    
    // remember multiplier
    int mult = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // copy metadata for the outfile
    BITMAPFILEHEADER bf_out = bf;
    BITMAPINFOHEADER bi_out = bi;
    
    // update outfile dimension metadata
    bi_out.biHeight = bi.biHeight * mult;
    bi_out.biWidth = bi.biWidth * mult;
    
    // determine padding for images
    int in_padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int out_padding = (4 - (bi_out.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update outfile size metadata
    bi_out.biSizeImage = abs(bi_out.biHeight) * (bi_out.biWidth * 3 + out_padding);
    bf_out.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi_out.biSizeImage;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // repeat a scanline to resize image vertically
        for (int j = 0; j < mult; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < bi.biWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile to resize horizontally
                for (int l = 0; l < mult; l++)
                {
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, in_padding, SEEK_CUR);
    
            // then add it back to resized
            for (int k = 0; k < out_padding; k++)
            {
                fputc(0x00, outptr);
            }
            
            // repeat the last scanline if needed
            if (j != mult - 1)
            {
                fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE) + in_padding), SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
