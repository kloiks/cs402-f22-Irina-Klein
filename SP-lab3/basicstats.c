/* 
Irina Klein
11/24/2022

This is a C program to evaluate basic statistic
(mean, median, stdev) given a list of numbers as a txt file.
*/

// include necessary libraries

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Fuction declarations

// create_array loads in the input values from the txt file and creates the array
float * create_array(char* datafile, int* xp, int* yp);

// print_stats prints out the statistical analysis measures (mean, median, stdev)        
void print_stats(float arr[], int size, int total_size);

// _swap funciton swaps two values in an array; used for soring
void _swap(float* xp, float* yp);
  
// bubble_sort sorts numbers in ascending order
void bubble_sort(float arr[], int n);

// median calculates the median given the array of numers and its size
float median(float arr[], int size);

// summarize sums all the values
float summarize(float arr[], int size);

// mean calculates the mean given the array of numers and its size
double mean(float arr[], int size);

// stdev calculates the population standard deviation given the array of numers and its size
// stdev = sqrt((sum((x_i - mean)^2))/n) for i from 1 to n
double stdev(float arr[], int size);

// memory_alloc_check checks if memory is allocated, if not prints an error message and exits
void memory_alloc_check(float arr[]);

// print_array prints the contents of the array (for debugging)
void print_array(float arr[], int array_size);

// main function alls functions to create array, sort it, calculate stats and print them out
int main(int argc, char *argv[])
{
 
   if( argc == 2 ) {
      printf("\n\nExecuting %s given %s.\n\n", argv[0], argv[1]);
      
      float* df; // dataframe
      int df_count = 0;
      int array_size = 20;

      // Create df from the input data file   
      df = create_array(argv[1], &df_count, &array_size); 
      
      // sort df in ascending order
      bubble_sort(df, df_count);
      
      //print_array(df, df_count);

      // output stats 
      print_stats(df, df_count, array_size); 

   }
   else if( argc > 2 ) {
      printf("Too many arguments supplied. Please specify one input file.\n");
   }
   else {
      printf("One argument expected. Please specify one input file.\n");
   }
}


void print_array(float arr[], int array_size)
{
   for(int i  = 0 ; i < array_size; i++)
      {
         printf("%d: %lf\n", i, arr[i]);

      }
}

float * create_array(char* filename, int* df_count, int* array_size)
{
   int n = 20;
   // allocate memory
   float* df = (float*)malloc(n * sizeof(float)); 
   
   // check is memory allocated 
   memory_alloc_check(df);

   // read data from the input file
   int mmr_counter = 0;
   float data = 0;

   // open file
   FILE *file;
   file = fopen(filename, "r");
   
   // read data
   char buffer[200];   
   while (fgets(buffer, sizeof(buffer), file)) 
   {
      data = strtof(buffer, NULL);
      df[mmr_counter] = data;
      mmr_counter++; 

      // double if reached array capacity
      if (mmr_counter == n)
      {
         n = n*2;
         float* df_tmp = (float*)malloc(n * sizeof(float)); 
         memory_alloc_check(df_tmp);

         memcpy(df_tmp, df, n * sizeof(float));
         free(df);
         df = (float*)malloc(n * sizeof(float)); 
         memcpy(df, df_tmp, n * sizeof(float));
         free(df_tmp);
      }
   }
      if (feof(file)) 
      { 
         fclose(file);
      }
      *array_size = n;
      *df_count = mmr_counter-1;
      return df;

}      


void memory_alloc_check(float arr[]){
   if (arr == NULL) 
   { 
      printf("Memory not allocated.\n"); 
      exit(0); 
   }
}

void print_stats(float arr[], int n, int size)
{
   printf("\nResults:\n");
   printf("-------------------------------------------\n");
   printf("%*s  %d\n", 25, "Num Values:", n);
   printf("%*s  %lf\n", 25, "Mean:", mean(arr, n));
   printf("%*s  %lf\n", 25, "Median:", median(arr, n));
   printf("%*s  %lf\n", 25, "Stdev:", stdev(arr, n));
   printf("%*s  %d\n", 25, "Unused Array Capacity:", (size-n));  
   printf("\n"); 
}

void _swap(float* xp, float* yp)
{
   float temp= *xp;
   *xp = *yp;
   *yp = temp;
   }

void bubble_sort(float arr[], int n)
{
   int i, j;
   for (i = 0; i < n - 1; i++)
   {
      for (j = 0; j < n - i - 1; j++)
         if (arr[j] > arr[j + 1])
               _swap(&arr[j], &arr[j + 1]);
   }
}

float median(float arr[], int size)
{
   float median = 0;

   // if even number of elements
   if(size % 2 == 0)
   {
      median = (arr[(size-1)/2] + arr[size/2])/2.0;
   }
   // if odd number of elements 
   else
   {
      median = arr[size/2];
   }
   return median;
}

float summarize(float arr[], int size)
{
   float sum = 0;

   for(int i = 0; i < size; i++) 
      {
         sum = sum + arr[i];
      }
   return sum;
}

double mean(float arr[], int size)
{
    
   double avg = 0;
   float sum;

   sum = summarize(arr, size);
   avg = (double)sum / size;
   return avg;
}

double stdev(float arr[], int size)
{
   float sum_sq_diff;
   double avg, stdev;

   avg = mean(arr, size); 

   for(int i = 0; i < size; i++) 
   {
      sum_sq_diff = sum_sq_diff + ((arr[i] - avg) * (arr[i] - avg));
   }

   stdev = (double) sqrt(sum_sq_diff / size);
   return stdev;

}