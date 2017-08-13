 /**************************************************
 * Name: Ansoumane Camara                          *
 * Project: Recover                                *
 * Description:                                    *
 * Implement a program called recover that recovers*
 * JPEGs from a forensic image                     *
 * ************************************************/
       
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>

typedef uint8_t  BYTE;

// creates a buffer of 512 bytes
BYTE buffer[512];

int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }
    
    // open input file
    FILE *infile = fopen(argv[1], "r");
    
    // if infile is empty, print message to screen
    if (infile == NULL)
    {
        fprintf(stderr, "Could not open file %s.\n", argv[1]);
        return 2;
    }
    
    // create "outfile" and initialize to NULL
    FILE *outfile = NULL;
    
    // integer counter
    int count = 0;
    
    // Iterate over infile until the end is reached
    while(fread(&buffer, sizeof(buffer), 1, infile) == 1)
    {
        // check to see if the first 4 bytes are JPEG signature
        if((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && (buffer[3] & 0xf0) == 0xe0)
        {
            // if outfile is not empty, close the current open outfile
            if(outfile != NULL)
            {
                fclose(outfile);
            }
            
            // create an array of 9 character
            char filename[8];
            
            // Name the files found in this format "###.jpg"
            sprintf(filename, "%03i.jpg", count);
            
            // open new found file for writing and assign to outfile
            outfile = fopen(filename, "w");
            
            // write the new files to outfile
            fwrite(&buffer, sizeof(buffer), 1, outfile);
            
            // increament the file counter
            count++;
        }
        else
        {
            // check to see if outfile is not empty
            if(outfile != NULL)
            {
                // write new found JPEGs to outfile
                fwrite(&buffer, sizeof(buffer), 1, outfile);
            }
        }
    }
    // close infile
    fclose(infile);
    
    // close outfile
    fclose(outfile);
    
    // success!!!
    return 0;
}
    

