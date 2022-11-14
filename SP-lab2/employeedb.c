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
void bubble_sort_id(struct employee db[], int n);
void bubble_sort_salary(struct employee db[], int n);
int update_employee(struct employee db[], int n, int option);
int remove_employee(struct employee db[], int n);
void highest_salary(struct employee db[], int counter);
void print_last_name (struct employee db[], int size, char* search_lname);


int main (int argc, char *argv[])
{
  load_employees (argv[1]);
  bubble_sort_id(employees, employee_counter);

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
      printf("   (6) Remove an Employee\n");
      printf("   (7) Update Employee Information\n");
      printf("   (8) Highest Salary\n");
      printf("   (9) Print All Employees with Matching Last Name\n");
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
          case 6:
            printf("\nEnter a 6 digit employee id: ");
            read_int (&searchid);

            n = lookup_id (employees, employee_counter, searchid);
            if (n == -1)
            {
                printf("\nEmployee not found\n");
            }
            else
            {
              int rm_option;

              printf("\nNAME\t\t\t        SALARY\t    ID\n");
              printf("----------------------------------------------\n");
              printf("%-13s\t%-13s\t%d\t%d\n", employees[n].first_name,employees[n].last_name,employees[n].salary, employees[n].six_digit_ID);
              printf("----------------------------------------------\n");
              printf("Would you like to remove this employee? Type 1 for yes, 0 for no.\n");
              read_int (&rm_option);
              if (rm_option == 0)
              {
                printf("Employee not removed.\n");
              }
              else if (rm_option == 1){
                remove_employee(employees, n);
              }
              else
              {
                printf("Invalid entry. Employee not removed.\n");
              }

            }
                break;
          case 7:
            printf("\nEnter a 6 digit employee id: ");
            read_int (&searchid);

            n = lookup_id (employees, employee_counter, searchid);
            if (n == -1)
            {
                printf("\nEmployee not found\n");
            }
            else
            {
              int update_option;

              printf("\nNAME\t\t\t        SALARY\t    ID\n");
              printf("----------------------------------------------\n");
              printf("%-13s\t%-13s\t%d\t%d\n", employees[n].first_name,employees[n].last_name,employees[n].salary, employees[n].six_digit_ID);
              printf("----------------------------------------------\n");
              printf("What would you like to update this employee? Type:\n");
              printf("1 for First Name\n");
              printf("2 for Last Name\n");
              printf("3 for Salary\n");
              printf("4 for All Fields\n");
              printf("0 to cancel update\n");

              read_int (&update_option);

              if (update_option == 0)
              {
                printf("Employee not updated.\n");
              }
              else if (update_option == 1 || update_option == 2 || update_option == 3 || update_option == 4){
                update_employee(employees, n, update_option);
              }
              else
              {
                printf("Invalid entry. Employee not updates.\n");
              }
            }
              break;
          case 8:
              highest_salary(employees, employee_counter);
              break;
          case 9:
            printf("\nEnter last name: ");
            read_string (searchlast_name);

            n = lookup_last_name (employees, employee_counter, searchlast_name);
            if (n == -1)
            {
                printf("\nEmployees not found\n");
            }
            else
            {
                print_last_name (employees, employee_counter, searchlast_name);
            }
            break;
          default:
              printf("Hey, %d is not between 1 and 8, try again...", option);

                    }
          }
}

void highest_salary(struct employee db[], int counter)
{
  struct employee db_salary[counter];
  int i, num;

  for (i = 0; i < counter; i++)
  {
      db_salary[i] = db[i];
  }

  bubble_sort_salary(db_salary, counter);

  printf("\nTop X employees with highest salries. Please enter X:\n");
  read_int(&num);
  if (num > counter)
  {
      num = counter;
  }
  print_employees(db_salary, num);
}



int update_employee(struct employee db[], int n, int option)
{
  char first[MAXNAME];
  char last[MAXNAME];
  int sal;
  switch (option) {
      case 1:
        printf("\n Please enter the updated first name: ");
        read_string(first);
        if (strlen(first) > 64)
        {
            printf("Invalid entry. Name should be within 64 characters.\n");
        }
        else {
          strcpy(db[n].first_name, first);
          printf("\n First Name updated.\n");
        }
        break;
      case 2:
        printf("\n Please enter the updated last name: ");
        read_string(last);
        if (strlen(last) > 64)
        {
            printf("Invalid entry. Name should be within 64 characters.\n");
        }
        else {
          strcpy(db[n].last_name, last);
          printf("\n Last Name updated.\n");
        }
        break;
      case 3:
        printf("\n Please enter the updated salary: ");
        read_int(&sal);
        if (sal < 30000 || sal > 150000)
        {
            printf("Invalid entry. Salary should be between 30K and 150K.\n");
        }
        else {
          db[n].salary = sal;
          printf("\n Salary updated.\n");
        }
        break;
      case 4:
        printf("\n Please enter the updated first name: ");
        read_string(first);
        printf("\n Please enter the updated last name: ");
        read_string(last);
        printf("\n Please enter the updated salary: ");
        read_int(&sal);

        if (sal < 30000 || sal > 150000 || strlen(last) > 64 || strlen(first) > 64)
        {
            printf("Invalid entry.\n");
        }
        else {
          strcpy(db[n].last_name, last);
          strcpy(db[n].first_name, first);
          db[n].salary = sal;
          printf("\n Fields updated.\n");
        }
        break;
      }
  printf("\nThe employee record.\n");
  printf("\nNAME\t\t\t        SALARY\t    ID\n");
  printf("----------------------------------------------\n");
  printf("%-13s\t%-13s\t%d\t%d\n", employees[n].first_name,employees[n].last_name,employees[n].salary, employees[n].six_digit_ID);
  printf("----------------------------------------------\n");
  return 0;
}



int remove_employee(struct employee db[], int n)
{
  for (int i = n; i < employee_counter; i++)
  {
      db[i] = db[i+1];
  }
  employee_counter--;
  return 0;
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

void print_last_name (struct employee db[], int size, char* search_lname)
{
    int i;

    printf("\nNAME\t\t\t        SALARY\t    ID\n");
    printf("----------------------------------------------\n");
    for (i = 0; i < size; i++)
    {
        if (strcmp(db[i].last_name, search_lname) == 0)
        {
            printf("%-13s\t%-13s\t%d\t%d\n", db[i].first_name,db[i].last_name,db[i].salary, db[i].six_digit_ID);
        }
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

void bubble_sort_id(struct employee db[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (db[j].six_digit_ID > db[j + 1].six_digit_ID)
                swap(&db[j], &db[j + 1]);
}

void bubble_sort_salary(struct employee db[], int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (db[j].salary < db[j + 1].salary)
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
