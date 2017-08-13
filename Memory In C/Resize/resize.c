/**
 * Copies a BMP piece by piece, just because.
 */
 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Resize                                 *
 * Description:                                    *
 * Implement a program that resizes BMPs files.    *
 * ************************************************/
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./resize n infile outfile\n");
        return 1;
    }
    // ensure that n is a posive integer
    int n = atoi(argv[1]);
    if ( n < 1 || n > 100)
    {
        fprintf(stderr, "(n) must be a positive integer not greather than 100\n");
        return 2;
    }
    // remember filenames
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
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
    
    // Old header info 
    LONG oldHeight = bi.biHeight;
    LONG oldWidth = bi.biWidth;
    
    // Updated header info
    bi.biHeight *= n;
    bi.biWidth *= n;
    
    // old padding for scanlines
    int oldPadding = (4 - (oldWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    // new padding for scanlines
    int newPadding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // new biSizeImage
    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + newPadding) * abs(bi.biHeight);
    
    // new bfSize 
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // allocate a space in memory 
    RGBTRIPLE *newTriple = malloc(sizeof(RGBTRIPLE) * (bi.biWidth));
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(oldHeight); i < biHeight; i++)
    {
        // keep track of pixels
        int pix_track = 0;
        
        // iterate over pixels in scanline
        for (int j = 0; j < oldWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // iterate over pixels n times 
            for (int counter = 0; counter < n; counter++)
            {
                *(newTriple+(pix_track)) = triple;
                pix_track++;
            }
        }

        // skip over padding, if any
        fseek(inptr, oldPadding, SEEK_CUR);
        
        // Write new RGB triple to outfile 
        for (int x = 0; x < n; x++)
        {
            fwrite((newTriple), sizeof(RGBTRIPLE), bi.biWidth, outptr);
        
            // then add it back (to demonstrate how)
            for (int k = 0; k < newPadding; k++)
            {
                fputc(0x00, outptr);
            }
        }
    }
    
    // free up momory
    free(newTriple);
    
    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}
