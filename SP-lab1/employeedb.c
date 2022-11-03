#include <stdio.h>
#include <string.h>
#include "readfile.h"

#define MAXNAME 64
#define MAXEMPL 1024

extern FILE *file;
struct employee
{
    char first_name[MAXNAME];
    char last_name[MAXNAME];
    int six_digit_ID;
    int salary;
};

struct employee employees[MAXEMPL];
int employee_counter = 0;

// Declare functions
void load_employees (char* inputfile);
void print_employees (struct employee db[], int db_size);
int lookup_last_name (struct employee db[], int size, char* search_lname);
int lookup_id (struct employee db[], int size, int search_id);
int add_employee(struct employee db[]);
void swap(struct employee* xp, struct employee* yp);
void bubble_sort(struct employee db[], int n);

int main (int argc, char *argv[])
{
  load_employees (argv[1]);
  bubble_sort(employees, employee_counter);

  int option; //  input form user -- options selection
  int n = 0;  // for lookups
  int searchid;
  char searchlast_name[MAXNAME];

  // options
  while (1) {
      printf("\nEmployee DB Menu:\n");
      printf("----------------------------------\n");
      printf("   (1) Print the Database\n");
      printf("   (2) Lookup by ID\n");
      printf("   (3) Lookup by Last Name\n");
      printf("   (4) Add an Employee\n");
      printf("   (5) Quit\n");
      printf("----------------------------------\n");
      printf("Enter your choice: ");

      //scanf("%d", &option); // scan chosen option
      read_int (&option);
      // analyse the option choice
      switch (option) {
          case 1:
              print_employees (employees, employee_counter);
              break;
          case 2:

            printf("\nEnter a 6 digit employee id: ");
            read_int (&searchid);

            n = lookup_id (employees, employee_counter, searchid);
            if (n == -1)
            {
                printf("\nEmployee not found\n");
            }
            else
            {
                printf("\nNAME\t\t\t        SALARY\t    ID\n");
                printf("----------------------------------------------\n");
                printf("%-13s\t%-13s\t%d\t%d\n", employees[n].first_name,employees[n].last_name,employees[n].salary, employees[n].six_digit_ID);
                printf("----------------------------------------------\n");
            }

            break;
          case 3:

              printf("\nEnter Employee's last name (no extra spaces): ");
              read_string (searchlast_name);

              n = lookup_last_name (employees, employee_counter, searchlast_name);
              if (n == -1)
              {
                  printf("\nEmployee not found\n");
              }
              else
              {
                  printf("\nNAME\t\t\t        SALARY\t    ID\n");
                  printf("----------------------------------------------\n");
                  printf("%-13s\t%-13s\t%d\t%d\n", employees[n].first_name,employees[n].last_name,employees[n].salary, employees[n].six_digit_ID);
                  printf("----------------------------------------------\n");
              }
              break;
          case 4:
              add_employee (employees);
              break;
          case 5:
              printf("Goodbye!\n");
              return 0;
              break;
          default:
              printf("Hey, %d is not between 1 and 5, try again...", option);

                    }
          }
}

int add_employee(struct employee db[])
{
    char addfirst_name[MAXNAME];
    char addlast_name[MAXNAME];
    int addsalary;
    int ok;

    printf("\nEnter the first name of the employee: ");
    read_string(addfirst_name);
    printf("\nEnter the last name of the employee: ");
    read_string(addlast_name);
    printf("Enter employee's salary (30000 to 150000): ");
    read_int(&addsalary);

    if (strlen(addfirst_name) > 64 || strlen(addlast_name) > 64 || addsalary < 30000 || addsalary > 150000)
    {
        printf("Invalid entry.\n");
        add_employee (employees);
        return -1;
    }
    else
    {
    printf("\n\nDo you want to add the following employee to the DB?\n");
    printf("----------------------------------");
    printf("\t%s %s, \tSalary: %d\n", addfirst_name, addlast_name, addsalary);
    printf("----------------------------------");
    printf("\nEnter 1 for yes, 0 for no: ");
    read_int(&ok);

    if (ok == 1)
    {
        strcpy(employees[employee_counter].first_name, addfirst_name);
        strcpy(employees[employee_counter].last_name, addlast_name);
        employees[employee_counter].salary = addsalary;
        employees[employee_counter].six_digit_ID = employees[employee_counter -1].six_digit_ID + 1;
        employee_counter++;
    }
    return 0;
  }
}

// Function to print db
void print_employees (struct employee db[], int db_size)
{
    int i;

    printf("\nNAME\t\t\t        SALARY\t    ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < db_size; i++)
    {
        printf("%-13s\t%-13s\t%d\t%d\n", db[i].first_name,db[i].last_name,db[i].salary, db[i].six_digit_ID);
    }
    printf("----------------------------------------------\n");
    printf(" Number of Employees (%d)\n", db_size);
}

// Function to lookup employees based on last name
int lookup_last_name (struct employee db[], int size, char* search_lname)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (strcmp(db[i].last_name, search_lname) == 0)
        {
            return i;
        }
    }
    return -1;
}

// Function to lookup employees based on id
int lookup_id (struct employee db[], int size, int search_id)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (db[i].six_digit_ID == search_id)
        {
            return i;
        }
    }
    return -1;
}

void swap(struct employee* xp, struct employee* yp)
{
    struct employee temp= *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(struct employee db[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (db[j].six_digit_ID > db[j + 1].six_digit_ID)
                swap(&db[j], &db[j + 1]);
}

// Function to open the file
void load_employees (char* inputfile)
{
    if (open_file(inputfile) == 0)
    {
        char buffer[144]; // 64 + 64 + 4 spaces + 6 digits in id + 6 digits in salary
        int ret;
        while (fgets(buffer, sizeof(buffer), file))
        {
            sscanf(buffer, "%d %s %s %d", &employees[employee_counter].six_digit_ID, &employees[employee_counter].first_name[0], &employees[employee_counter].last_name[0], &employees[employee_counter].salary);
            employee_counter++;
        }
            close_file();
    }
}
