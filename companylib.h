#ifndef COMPANYLIB_H_INCLUDED
#define COMPANYLIB_H_INCLUDED

#include <string.h>
#include <time.h>
#define MAX_EMPLOYEES 1000

typedef struct
{
    char firstname[10];
    char lastname[10];
} name;

typedef struct
{
    int day;
    int month;
    int year;
} date;

typedef struct
{
    int home;
    char street[10];
} address;

typedef struct
{
    int ID;
    name name;
    int salary;
    date DOB;
    address Address;
    char mobilenumber[20];
    date DOE;
    char email[30];
} employee;

employee e[MAX_EMPLOYEES];
FILE *f;
long int recsize = sizeof(employee);
char searchName[10];
int totalNumberOfEmployees = 0;
int isValid;
int i;
int flag=0;
struct tm tm;

void loadEmployees()
{
    rewind(f);

    int c;
    int i = 0;
    char line[100]; // Assuming a reasonable line length

    while ((c = getc(f)) != EOF)
    {
        if (c == '\n')
        {
            line[i] = '\0'; // Null-terminate the string
            sscanf(line, "%d ,%s %s ,%d ,%d-%d-%d ,%d %s Street ,%s ,%d-%d-%d ,%s",
                   &e[totalNumberOfEmployees].ID,
                   e[totalNumberOfEmployees].name.firstname,
                   e[totalNumberOfEmployees].name.lastname,
                   &e[totalNumberOfEmployees].salary,
                   &e[totalNumberOfEmployees].DOB.day,
                   &e[totalNumberOfEmployees].DOB.month,
                   &e[totalNumberOfEmployees].DOB.year,
                   &e[totalNumberOfEmployees].Address.home,
                   e[totalNumberOfEmployees].Address.street,
                   e[totalNumberOfEmployees].mobilenumber,
                   &e[totalNumberOfEmployees].DOE.day,
                   &e[totalNumberOfEmployees].DOE.month,
                   &e[totalNumberOfEmployees].DOE.year,
                   e[totalNumberOfEmployees].email);

            totalNumberOfEmployees++;
            i = 0; // Reset the index for the next line
        }
        else
        {
            line[i++] = c;
        }
    }
}



// Function to check the validity of an email
int ValidEmail(char *email)
{
    int atCount = 0;
    int dotCount = 0;

    for (int i = 0; i < strlen(email); i++)
    {
        if (email[i] == '@')
        {
            atCount++;
        }
        else if (email[i] == '.')
        {
            dotCount++;
        }
    }

    if (atCount == 1 && dotCount >= 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to check the validity of a mobile number
int ValidMobileNumber(char *mobilenumber)
{
    if (mobilenumber[0] == '0' && mobilenumber[1] == '1' && strlen(mobilenumber) == 11)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// Function to check the validity of a date of birth
int ValidDOB(int day, int month, int year)
{
    if (day <= 31 && month <= 12 && year <= 2023 && 1 <= day && 1 <= month && 1 <= year)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void getCurrentDate(struct tm *tm)
{
    time_t t;
    t = time(NULL);
    *tm = *localtime(&t);
}

void ADDEMPLOYEE()
{
    if (totalNumberOfEmployees < MAX_EMPLOYEES)
    {
        int newID;

        do
        {
            isValid = 1;
            printf("Enter The ID: ");
            scanf("%d", &newID);

            for (int i = 0; i < totalNumberOfEmployees; i++)
            {
                if (e[i].ID == newID)
                {
                    isValid = 0;
                    printf("ID already exists. Please enter a unique ID.\n\n");
                    break;
                }
            }
        }
        while (!isValid);

        e[totalNumberOfEmployees].ID = newID;

        printf("Enter The Name (First and last): ");
        scanf("%s %s", e[totalNumberOfEmployees].name.firstname, e[totalNumberOfEmployees].name.lastname);

        printf("Enter The Salary: ");
        scanf("%d", &e[totalNumberOfEmployees].salary);

        do
        {
            printf("Enter The Date Of Birthday (Day,Month,Year): ");
            scanf("%d %d %d", &e[totalNumberOfEmployees].DOB.day, &e[totalNumberOfEmployees].DOB.month, &e[totalNumberOfEmployees].DOB.year);

            isValid = ValidDOB(e[totalNumberOfEmployees].DOB.day, e[totalNumberOfEmployees].DOB.month, e[totalNumberOfEmployees].DOB.year);

            if (!isValid)
            {
                printf("Invalid Date Of Birthday. Please enter a Correct Date Of Birthday.\n\n");
            }
        }
        while (!isValid);

        printf("Enter The Address (Number of Home and Street Name): ");
        scanf("%d %s", &e[totalNumberOfEmployees].Address.home, e[totalNumberOfEmployees].Address.street);

        do
        {
            printf("Enter The Mobile Number (01*********): ");
            scanf("%s", e[totalNumberOfEmployees].mobilenumber);

            isValid = ValidMobileNumber(e[totalNumberOfEmployees].mobilenumber);

            if (!isValid)
            {
                printf("Invalid Mobile Number format. Please enter a valid Mobile Number.\n\n");
            }
        }
        while (!isValid);

        do
        {
            printf("Enter The Email (example@domain.com): ");
            scanf("%s", e[totalNumberOfEmployees].email);

            isValid = ValidEmail(e[totalNumberOfEmployees].email);

            if (!isValid)
            {
                printf("Invalid email format. Please enter a valid email address.\n\n");
            }
        }
        while (!isValid);

        getCurrentDate(&tm);

        // Assign date of enrollment
        e[totalNumberOfEmployees].DOE.day = tm.tm_mday;
        e[totalNumberOfEmployees].DOE.month = tm.tm_mon + 1;
        e[totalNumberOfEmployees].DOE.year = tm.tm_year + 1900;

        fprintf(f, "%d ,%s %s ,%d ,%d-%d-%d ,%d %s Street ,%s ,%d-%d-%d ,%s\n",
                e[totalNumberOfEmployees].ID,
                e[totalNumberOfEmployees].name.firstname,
                e[totalNumberOfEmployees].name.lastname,
                e[totalNumberOfEmployees].salary,
                e[totalNumberOfEmployees].DOB.day,
                e[totalNumberOfEmployees].DOB.month,
                e[totalNumberOfEmployees].DOB.year,
                e[totalNumberOfEmployees].Address.home,
                e[totalNumberOfEmployees].Address.street,
                e[totalNumberOfEmployees].mobilenumber,
                e[totalNumberOfEmployees].DOE.day,
                e[totalNumberOfEmployees].DOE.month,
                e[totalNumberOfEmployees].DOE.year,
                e[totalNumberOfEmployees].email);

        totalNumberOfEmployees++;

        printf("Employee added successfully!\n");
    }
    else
    {
        printf("Maximum number of employees reached.\n");
    }
}


// Function to search for an employee by name
void searchByName(char *searchName, int numberOfEmployees)
{
    rewind(f);
    printf("Enter the name to search: ");
    scanf("%s", searchName);

    for (int i = 0; i < numberOfEmployees; i++)
    {
        if (strcmp(searchName, e[i].name.firstname) == 0 || strcmp(searchName, e[i].name.lastname) == 0)
        {
            printf("ID: %d\n", e[i].ID);
            printf("Name: %s %s\n", e[i].name.firstname, e[i].name.lastname);
            printf("Salary: %d\n", e[i].salary);
            printf("Date Of Birthday: %d-%d-%d\n", e[i].DOB.day, e[i].DOB.month, e[i].DOB.year);
            printf("Address: %d %s Street\n",e[i].Address.home, e[i].Address.street);
            printf("Mobile Number: %s\n", e[i].mobilenumber);
            printf("Date Of Enrollment: %d-%d-%d\n", e[i].DOE.day, e[i].DOE.month, e[i].DOE.year);
            printf("Email: %s\n", e[i].email);
            printf("\n");
            flag=1;
        }
    }
    if(flag == 0)
        printf("\nNot Found This Employee.\n");
}

// Function to swap two employee records
void SwapEmployees(employee *a, employee *b)
{
    employee temp = *a;
    *a = *b;
    *b = temp;
}

// Function to sort employees by name
void sortByName()
{
    employee temp; // Temporary variable for printing
    printf("Employees sorted by name:\n");

    for (int i = 0; i < totalNumberOfEmployees - 1; i++)
    {
        for (int j = 0; j < totalNumberOfEmployees - i - 1; j++)
        {
            char first1 = e[j].name.firstname[0];
            char secondLast2 = e[j].name.lastname[strlen(e[j].name.lastname) - 2];

            char first2 = e[j + 1].name.firstname[0];
            char secondLast1 = e[j + 1].name.lastname[strlen(e[j + 1].name.lastname) - 2];

            if (first1 > first2 || (first1 == first2 && secondLast1 > secondLast2))
            {
                SwapEmployees(&e[j], &e[j + 1]);
            }
        }
    }

}

// Function to sort employees by date of birth
void sortByDOB()
{
    printf("Employees sorted by date of birth:\n");
    for (int i = 0; i < totalNumberOfEmployees - 1; i++)
    {
        for (int j = 0; j < totalNumberOfEmployees - i - 1; j++)
        {
            if (e[j].DOB.year > e[j + 1].DOB.year ||
                    (e[j].DOB.year == e[j + 1].DOB.year &&
                     e[j].DOB.month > e[j + 1].DOB.month) ||
                    (e[j].DOB.year == e[j + 1].DOB.year &&
                     e[j].DOB.month == e[j + 1].DOB.month &&
                     e[j].DOB.day > e[j + 1].DOB.day))
            {
                SwapEmployees(&e[j], &e[j + 1]);
            }
        }
    }
}

// Function to sort employees by salary
void sortBySalary()
{
    printf("Employees sorted by salary:\n");
    for (int i = 0; i < totalNumberOfEmployees - 1; i++)
    {
        for (int j = 0; j < totalNumberOfEmployees - i - 1; j++)
        {
            if (e[j].salary < e[j + 1].salary)
            {
                SwapEmployees(&e[j], &e[j + 1]);
            }
        }
    }
}

// Function to print all employees
void printEmployees()
{
    for (int i = 0; i < totalNumberOfEmployees; i++)
    {
        printf("ID: %d\n", e[i].ID);
        printf("Name: %s %s\n", e[i].name.firstname, e[i].name.lastname);
        printf("Salary: %d\n", e[i].salary);
        printf("Date Of Birthday: %d-%d-%d\n", e[i].DOB.day, e[i].DOB.month, e[i].DOB.year);
        printf("Address: %d %s Street\n",e[i].Address.home, e[i].Address.street);
        printf("Mobile Number: %s\n", e[i].mobilenumber);
        printf("Date Of Enrollment: %d-%d-%d\n", e[i].DOE.day, e[i].DOE.month, e[i].DOE.year);
        printf("Email: %s\n", e[i].email);
        printf("\n");
    }
}

// Function to modify a field of an employee by ID
void modifyFieldByID(void)
{
    int employeefield = -1;
    int employeeID;

    printf("Enter the ID of the employee to modify: ");
    scanf("%d", &employeeID);

    // Search for the employee with the specified ID
    for (int i = 0; i < totalNumberOfEmployees; i++)
    {
        if (e[i].ID == employeeID)
        {
            printf("\nOld Employee Details:\n");
            printf("ID: %d\n", e[i].ID);
            printf("Name: %s %s\n", e[i].name.firstname, e[i].name.lastname);
            printf("Salary: %d\n", e[i].salary);
            printf("Date Of Birthday: %d-%d-%d\n", e[i].DOB.day, e[i].DOB.month, e[i].DOB.year);
            printf("Address: %d %s Street\n",e[i].Address.home, e[i].Address.street);
            printf("Mobile Number: %s\n", e[i].mobilenumber);
            printf("Date Of Enrollment: %d-%d-%d\n", e[i].DOE.day, e[i].DOE.month, e[i].DOE.year);
            printf("Email: %s\n", e[i].email);
            printf("\n");

            employeefield = i;
            break;
        }
    }

    if (employeefield == -1)
    {
        printf("\nEmployee with ID %d not found.\n", employeeID);
        return;
    }

    int fieldChoice;

    printf("\nSelect the field to modify:\n");
    printf("1. Name\n");
    printf("2. Salary\n");
    printf("3. Mobile Number\n");
    printf("4. Address\n");
    printf("5. Email\n");
    printf("\nEnter the field number: ");
    scanf("%d", &fieldChoice);

    switch (fieldChoice)
    {
    case 1:
        printf("\nEnter the new name (First and last): ");
        scanf("%s %s", e[employeefield].name.firstname, e[employeefield].name.lastname);
        break;

    case 2:
        printf("\nEnter the new salary: ");
        scanf("%d", &e[employeefield].salary);
        break;

    case 3:
        do
        {
            printf("Enter The Mobile Number (01*********): ");
            scanf("%s", e[employeefield].mobilenumber);

            isValid = ValidMobileNumber(e[employeefield].mobilenumber);

            if (!isValid)
            {
                printf("Invalid Mobile Number format. Please enter a valid Mobile Number.\n\n");
            }
        }
        while (!isValid);
        break;

    case 4:
        printf("\nEnter the new address (Number of Home and Street Name): ");
        scanf("%d %s", &e[employeefield].Address.home, e[employeefield].Address.street);
        break;

    case 5:
        do
        {
            printf("Enter The Email (example@domain.com): ");
            scanf("%s", e[employeefield].email);

            isValid = ValidEmail(e[employeefield].email);

            if (!isValid)
            {
                printf("Invalid email format. Please enter a valid email address.\n\n");
            }
        }
        while (!isValid);
        break;

    default:
        printf("\nInvalid field choice.\n");
        return;
    }

    fclose(f);


    remove("The Company.txt");

    f = fopen("The Company.txt", "a+");

    fseek(f, 0, SEEK_SET);

    for (int j = 0; j < totalNumberOfEmployees; j++)
    {
        fprintf(f, "%d ,%s %s ,%d ,%d-%d-%d ,%d %s Street ,%s ,%d-%d-%d ,%s\n",
                e[j].ID,
                e[j].name.firstname,
                e[j].name.lastname,
                e[j].salary,
                e[j].DOB.day,
                e[j].DOB.month,
                e[j].DOB.year,
                e[j].Address.home,
                e[j].Address.street,
                e[j].mobilenumber,
                e[j].DOE.day,
                e[j].DOE.month,
                e[j].DOE.year,
                e[j].email);
    }

    printf("\nField modified successfully!\n");

    // Display the modified employee details
    printf("\nModified Employee Details:\n");
    printf("ID: %d\n", e[employeefield].ID);
    printf("Name: %s %s\n", e[employeefield].name.firstname, e[employeefield].name.lastname);
    printf("Salary: %d\n", e[employeefield].salary);
    printf("Date Of Birthday: %d-%d-%d\n", e[employeefield].DOB.day, e[employeefield].DOB.month, e[employeefield].DOB.year);
    printf("Address: %d %s Street\n",e[employeefield].Address.home, e[employeefield].Address.street);
    printf("Mobile Number: %s\n", e[employeefield].mobilenumber);
    printf("Date Of Enrollment: %d-%d-%d\n", e[employeefield].DOE.day, e[employeefield].DOE.month, e[employeefield].DOE.year);
    printf("Email: %s\n", e[employeefield].email);
    printf("\n");
}

// Function to delete an employee by ID
void deleteEmployeeByID()
{
    int employeeID;
    printf("Enter the ID of the employee to delete: ");
    scanf("%d", &employeeID);

    int found = 0;
    int deleteChoice;

    for (int i = 0; i < totalNumberOfEmployees; i++)
    {
        if (e[i].ID == employeeID)
        {
            found = 1;
            printf("\nEmployee Details to be Deleted:\n");
            printf("ID: %d\n", e[i].ID);
            printf("Name: %s %s\n", e[i].name.firstname, e[i].name.lastname);
            printf("Salary: %d\n", e[i].salary);
            printf("Date Of Birthday: %d-%d-%d\n", e[i].DOB.day, e[i].DOB.month, e[i].DOB.year);
            printf("Address: %d %s Street",e[i].Address.home,e[i].Address.street);
            printf("Mobile Number: %s\n", e[i].mobilenumber);
            printf("Date Of Enrollment: %d-%d-%d\n", e[i].DOE.day, e[i].DOE.month, e[i].DOE.year);
            printf("Email: %s\n", e[i].email);
            printf("\n");

            // Ask for confirmation before deletion
            printf("Are you sure you want to delete this employee? (1 for Yes, 0 for No): ");
            scanf("%d", &deleteChoice);

            if (deleteChoice == 1)
            {
                for (int j = i; j < totalNumberOfEmployees - 1; j++)
                {
                    e[j] = e[j + 1];
                }

                totalNumberOfEmployees--;

                fclose(f);

                remove("The Company.txt");

                f = fopen("The Company.txt", "a+");

                fseek(f, 0, SEEK_SET);

                for (int j = 0; j < totalNumberOfEmployees; j++)
                {
                    fprintf(f, "%d ,%s %s ,%d ,%d-%d-%d ,%d %s Street ,%s ,%d-%d-%d ,%s\n",
                            e[j].ID,
                            e[j].name.firstname,
                            e[j].name.lastname,
                            e[j].salary,
                            e[j].DOB.day,
                            e[j].DOB.month,
                            e[j].DOB.year,
                            e[j].Address.street,
                            e[j].mobilenumber,
                            e[j].DOE.day,
                            e[j].DOE.month,
                            e[j].DOE.year,
                            e[j].Address.home,
                            e[j].email);
                }

                printf("Employee deleted successfully!\n");
            }
            else
            {
                printf("Deletion canceled.\n");
            }

            break;
        }
    }

    if (!found)
    {
        printf("Employee with ID %d not found.\n", employeeID);
    }
}

#endif // COMPANYLIB_H_INCLUDED