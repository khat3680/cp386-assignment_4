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
    int *allocation_resources;
    int *max_resources;
} Customer;

Customer *customer_resources;

int *avail_resources; //available array

/*main is where we will pass the commandline arguments for the filename 
and we call readFile().
main will listen to the user and push the command "RL, RQ or *"
to runCommand function*/

int main(int argc, char *argv[])
{
    char *fileName = "sample4_in.txt";
    // checking arguements
    if (argc < 3) //check if we have enough resources
    {
        printf("INVALID: Enter at least 2 values with space - demilited\n");

        return 1;
    }
    else
    {
        printf("\n\nWelcome to the program made by Anshul and Pranav. :D\n\n");

        avail_resources = (int *)malloc((argc - 1) * sizeof(int)); // allocate memory for array

        for (int i = 1; i < argc - 1; i++) //put argv into available array
        {
            avail_resources[i] = atoi(argv[i + 1]);
        }
    }
}