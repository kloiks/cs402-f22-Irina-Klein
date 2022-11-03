#include <stdlib.h>
#include <stdio.h>
#include "readfile.h"

FILE *file;

// Fuctions to read int/float/string
void read_int(int* x)
{
  scanf("%d", x);
}

void read_float(float* x)
{
  scanf("%f", x);
}

void read_string(char x[])
{
  scanf("%s", x);
}

// Function to close the file
void close_file ()
{
    fclose(file);
}

// Function to open file
int open_file (char* inputfile)
{
    file = fopen (inputfile, "r");
    if (file == 0) // cannot be opened
    {
        return -1;
    }
    else          // success
    {
        return 0;
    }
}
