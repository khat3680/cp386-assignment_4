/**
 * 
 * CP 386 - Assignment 4
 * 
 * @author Anshul Khatri (193313680) 
 * Github login - https://github.com/khat3680/
 * @author Pranav Verma (193272030) 
 * Github login - https://github.com/Navsan1
 * 
 * @see https://github.com/khat3680/cp386-assignment_4
 * 
 */
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <pthread.h>
#include <time.h>

typedef struct customer
{
    int *need_resources;
    int *allocated_resources;
    int *maximum_resources;
} Customer;

Customer *c_resources;

int n_resources;
int n_customers;

int *avail_resources; //available array for the resources

/*main is where we will pass the commandline arguments for the filename 
and we call readFile().
main will listen to the user and push the command "RL, RQ or *"
to runCommand function*/

int main(int argc, char *argv[])
{
    // checking arguements
    if (argc < 3) //check if we have enough resources
    {
        printf("INVALID: Enter at least 2 values with space - demilited\n");

        return 1;
    }
    else
    {
        printf("\n\nWelcome to the program made by Anshul and Pranav. :D\n\n");

        int n_resources = argc - 1;

        avail_resources = (int *)malloc((n_resources) * sizeof(int)); // allocate memory for array

        for (int i = 1; i < n_resources; i++) //put argv into available array
        {
            avail_resources[i] = atoi(argv[i + 1]);
        }
    }

    load_c_resources(); // Loads customer resource data from the file.
}
/** 
 * Function to load customer resources. 
 * 
 * @author Anshul 
 * @author Pranav
 */

int load_c_resources()
{
    // for reading from file
    FILE *file_p;
    char *line;
    size_t len = 0;
    ssize_t read;

    // Open from file
    if ((file_p = fopen("sample4_in.txt", "r")) == NULL)
    {

        printf("File opening error."); // Issue in opening file
        return -1;
    }

    n_customers = 1; // start at one since last line does not have line break
    // count number of lines in the file
    char ch;
    while ((ch = fgetc(file_p)) != EOF)
    {
        if (ch == '\n')
        {
            n_customers++;
            // if line was actually empty then don't count it
            if ((ch = fgetc(file_p)) == EOF)
                n_customers--;
        }
    }

    fseek(file_p, 0, SEEK_SET); // reset file_p back to start after counting

    // allocate memory for customer resources data structure
    c_resources = malloc(n_customers * sizeof(Customer));

    // read customer data from file
    int r, k = 0;
    while ((read = getline(&line, &len, file_p)) != -1)

    { // for each line in file
        // ignore blank lines
        if (strlen(line) > 1)
        {
            // create customer data structure to initialise it.
            Customer c;

            c.maximum_resources = delimited_string_to_int_array(line, ",", (n_resources));
            c.allocated_resources = malloc(sizeof(int) * n_resources);
            c.need_resources = malloc(sizeof(int) * n_resources);

            // ensure no memory-related value issues occur by setting values to 0 (frick C)
            for (r = 0; r < n_resources; r++)
                c.allocated_resources[r] = 0;
            // need = max - allocation, allocation is all 0s now, so set to need = max to start

            for (r = 0; r < n_resources; r++)
                c.need_resources[r] = c.maximum_resources[r];

            c_resources[k] = c;
            k++;
        }
    }

    //avoid memory leaks
    free(line);
    fclose(file_p);
}