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
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

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

/** 
 * Function : load customer resources. 
 * 
 * Param : None
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

            c.maximum_resources = string_to_int_array(line, ",", (n_resources));
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

/**
 * Prints arrays of all available customer resources
 *  
 * @author Pranav Verma
 * @author Anshul Khatri
 */
void display_status()
{
    // print status
    int c;
    printf("Available Resources:\n");
    print_array(avail_resources, n_resources);

    printf("Maximum Resources:\n");

    for (c = 0; c < n_customers; c++)
    {
        print_array(c_resources[c].maximum_resources, n_resources); //printing the max resoures
    }

    printf("Allocated Resources:\n");

    for (c = 0; c < n_customers; c++)
    {
        print_array(c_resources[c].allocated_resources, n_resources); //printing the allocated resoures
    }
    printf("Need Resources:\n");

    for (c = 0; c < n_customers; c++)
    {
        print_array(c_resources[c].need_resources, n_resources); //printing the required resoures
    }
}

/**
 * Function : Prints an integer array with good spacing.
 * Params : Pass the array and the length of the array.
 * 
 * @author Pranav Verma
 */
void print_array_proper(int *arr, int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d", arr[i]);
        if (i == len - 1)
            printf("\n");
        else
            printf(" ");
    }
}

/**
 * Takes a string, delimeter, and length of array and creates and
 * fills an array with integer conversions of the contents of the
 * string split by the delimeter.
 *
 * @author Anshul Khatri
 */
int *string_to_int_array(char *msg, char *delimeter, int len)
{
    int *arr = (int *)malloc(len * sizeof(int));

    int count = 0;
    char *token;
    while ((token = strsep(&msg, delimeter)) != NULL)
    {
        if (token != "")
        {
            arr[count] = atoi(token);
            count++;
        }
    }
    return arr;
}
/**
 * Program event loop.
 * Loops until the user types 'close'
 * Allows user to actively interact with the program.
 * 
 * @author Pranav Verma
 */
void start_program()
{
    // initialising tools for reading from console.
    char *in = NULL;
    size_t length = 0;
    ssize_t read = 0;

    // repeats untill stop is done.
    int begin = true;
    while (begin)
    {
        printf("Enter Command: ");
        read = getline(&in, &length, stdin); // reading line by line.
        if (read == -1)
            // exit if error
            begin = false;
        else
        {
            // converts input(in) to lowercase
            char *char_pointer = in;
            for (; *char_pointer; ++char_pointer)
            {
                // cleaning the lines
                if (*char_pointer == '\n')
                    *char_pointer = '\0';
                else

                    *char_pointer = tolower(*char_pointer); // Convert each letter to lower case
            }

            // calls appropriate functions as per commands and print the messages as per requirements
            if (strlen(in) >= 2 && in[0] == 'r' && in[1] == 'q')
                printf("%s", handle_request(in, length, resources_request));

            else if (strlen(in) >= 2 && in[0] == 'r' && in[1] == 'l')
                printf("%s", handle_request(in, length, release_resources));
            // "Status"

            else if (strcmp(in, "status") == 0)
                display_status();

            // "begin"
            else if (strcmp(in, "begin") == 0)
                begin_resources();
            // "Close"

            else if (strcmp(in, "close") == 0)
            {
                printf("Exiting...\n");
                begin = false;
            }
            // Other command is entered then prints "Invalid Command"
            else
                printf("Invalid Command\n");
        }
    }
    free(in); // avoid leaks
}

/**
 * Releases resources from a customer and makes them available again.
 *  
 * @author Anshul Khatri
 * @author Pranav Verma
 */
char *release_resources(int customer_number, int *request)
{
    int r, c = customer_number;

    bool isvlaid = true;

    // check if release vector > allocation vector,
    //else a release request might "create new resources"

    for (r = 0; r < n_resources; r++)
    {

        if (request[r] > c_resources[c].allocated_resources[r])
            isvlaid = false;
    }
    if (isvlaid)
    {
        // releasing the resources
        for (r = 0; r < n_resources; r++)
        {
            // avialing the resources again
            avail_resources[r] += request[r];
        }
        return "Resources have been released\n";
    }
    else
        return "Cannot release resources that are not in use\n";
}

/**
 * Processes request for resources from bank.
 * Check if request is possible and safe to fulfill else 
 * tells customer to  wait or make a different request.
 *  
 * @author Pranav Verma
 * @author Anshul Khatri
 */
char *resources_request(int customer_number, int *request)
{
    // uses resource-request algorithm from lecture notes
    int r, c = customer_number;
    bool isvlaid = true, safe;
    // condition 1: request vector <= customer's need vector, request has exceeding it's maximum claim
    for (r = 0; r < n_resources && isvlaid; r++)
        isvlaid = request[r] <= c_resources[c].need_resources[r];

    if (isvlaid)
    {
        // condition 2: request vector <= available vector, customer must wait til resources are available
        for (r = 0; r < n_resources && isvlaid; r++)
            isvlaid = request[r] <= avail_resources[r];
        if (isvlaid)
        {
            // temporarily modify values to determine if safe
            for (r = 0; r < n_resources; r++)
            {
                avail_resources[r] -= request[r];
                c_resources[c].allocated_resources[r] += request[r];
                c_resources[c].need_resources[r] -= request[r];
            }
            if (is_safe(NULL))
            {
                // if system is safe after fulfilling the resource request, print success message
                return "State is safe, and request is satisfied\n";
            }
            else
            {
                // if system becomes unsafe, undo temporary changes to value and print failure message
                for (r = 0; r < n_resources; r++)
                {
                    avail_resources[r] += request[r];
                    c_resources[c].allocated_resources[r] -= request[r];
                    c_resources[c].need_resources[r] += request[r];
                }
                return "State is not safe, not enough resources available for that request\n";
            }
        }
        else
        {
            return "Enough resources unavailable, wait\n";
        }
    }
    else
    {
        return "Request exceeds maximum resource claim, cannot be satisfied\n";
    }
}

/*main is where we will pass the commandline arguments for the filename 
and we call readFile().
main will listen to the user and push the command "RL, RQ or *"
to beginCommand function*/

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

    start_program(); // handles the start of the program.
}

/**
 * Uses a Saftey Algorithm to determine whether the system is in a safe state or not.
 * 
 * @author Pranav Verma
 */

bool safe(int *seq[]) {
    int *work = (int *)malloc(n_resources * sizeof(int));
    bool *fin = (bool *)malloc(n_customers * sizeof(bool));
    int a, b, i, count = 0;
    for (a = 0; a < n_resources; a++)
        work[a] = avail_resources[a];
    for (b = 0; b < n_customers; b++)
        fin[b] = false;

    // loops until either safe state or unsafe state and there were no changes made to the system
    bool safe, customer_wait;
    for (i = 0; i < n_customers; i++) {
        safe = true;
        // attempts to find a customer to finish
        for (b = 0; b < n_customers; b++) {
            if (fin[b] == false) {  // situation 1:  customer is not finished
                customer_wait = false;
                // situation 2: customer needs a vector which must be <= work vector
                for (a = 0; a < n_resources && !customer_wait; a++) {
                    if (c_resources[b].need_resources[a] > work[a])
                        customer_wait = true;
                }
                // if both situations are met
                if (!customer_wait) {
                    // puts the customer number in the sequence and moves to the next number
                    if (seq)
                        (*seq)[count++] = b;
                    // updates work and finish vectors to reflect any changes that were made
                    for (int a = 0; a < n_resources; a++)
                        work[a] += c_resources[b].allocated_resources[a];
                    fin[b] = true;
                }
            }
        }
        // checks if all customers are finished or not
        for (b = 0; b < n_customers; b++)
            safe = safe && fin[b]; 
    }
    // frees the memory and makes a null if there is no safe sequence
    if (!safe) {
        if (seq) {
            free(*seq);
            *seq = NULL;
        }
    }
    // made to avoid memory leaks
    free(work);
    free(fin);
    return safe;
}