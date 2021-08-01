<h1 align="center"> 
  CP386_ A4 : Bankers Algorithm
</h1>


<br/>

## About the project

- In this asssignment we have to write a multi-thread program that implements the banker's algorithm. Customers request and release resources from the bank. The banker will keep track of the resources. The banker grants request if it satisfies the safety algorithm. If a request does not leave the system in a safe state the banker will deny it.

## Motivation

- We made this project as a part of our assignment (assignment 4) for CP386 as it was a great learning experince.
- We decided to do this project because it is a requirement for the compeltion of our Operating Systems course at University.

## Installation

- C Programming language
- GCC Complier
- A Linux Enviornment 

### _REQUIREMENTS:_ Compile and run on **Linux** or **VM running linux shell** (Made on Ubuntu)

1. Download the file as you would a normal Github Repository.

1. Transfer to your VM if necessary and put into a seperate folder.

1. Use Makefile command **"make"** without quotes for compilation using C99.

    1. "make warnings_ok" for ignoring warnings.

1. Run on linux using "./Assignment_4 X X X X"  --replace X X X X with the Max Resources you desire.

    1. you may check file name by typing "ls", the created file will be highlited green.

    1. an input file has been provided to you for convinience.

1. If an emergency stop is required you may use "CTRL+C" on your keyboard to abort the program.


## Preview

![Screenshot1](/SC_1.png "Program Start")

![Screenshot2](/SC2.png "RQ, RL and * Example")

## Contributors

- [Anshul Khatri](https://github.com/khat3680)<br/>
- [Pranav Verma](https://github.com/Navsan1)<br/>

```c
int main();   // anshul and pranav

void load_c_resources(); // anshul and pranav
void start_program();     // pranav

void display_status();    // pranav
char *resources_request(int cust_number, int *request); // pranav
char *release_resources(int cust_number, int *request);  // anshul
void begin_resources(); //anshul and pranav
 
bool is_safety_check();  //anshul

char *handle_request(char *input, int len, char *(*func)(int, int *)); // anshul and pranav

int *string_to_int_array(char *msg, char *delimeter, int len); // anshul
void print_proper_array(int *arr, int len);   //anshul and pranav
```
## Features
1. Error checking for case sensitive commands.
2. String split using fgets instead of scanf for saftey of buffer.
3. Error checking for requesting or releasing more unnecessary number of resources.


## TESTS

EX: ./193313680_193272030_a04 10 10 10 10

    RQ 0 1 1 1 1

    RQ 2 9 9 9 9

    RL 2 9 9 9 9

    *

    RUN

## CODE EXAMPLE

RQ: Request Resource
RL: Release Resource
* : Show current resources
RUN: Run safety Algorithm and find Safe sequence
999: Stop the program


Commands are case sensitive


## About Developers

- [Anshul Khatri](https://github.com/khat3680)<br/>
- [Pranav Verma](https://github.com/Navsan1)<br/>

## Credits

- [Anshul Khatri](https://github.com/khat3680)<br/>
- [Pranav Verma](https://github.com/Navsan1)<br/>

-[GeeksforGeeks - Banker’s Algorithm in Operating System](https://www.geeksforgeeks.org/bankers-algorithm-in-operating-system-2/)<br/>
## License

This project uses the **MIT License**

Copyright 2020 Anshul Khatri AND Pranav Verma

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.