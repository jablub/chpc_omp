//TODO: add the relevant OpenMP header here
#include <stdio.h>
#include <stdlib.h>

using namespace std;

// function prototype
void printOmpInfo();

int main(int argc,char **argv)
{
  // This is the entry point to the program.

  printf("Hello, world.\n"); // Its tradition, what could I do =/     feel free to comment this line out, and uncomment printOmpInfo() below!

  // Call the printOmpInfo method
  //printOmpInfo();  // Uncomment this line to run OMP code

  return 0;
}

void printOmpInfo()
{
  // A nice way to print formatted text to the std out. NOTE: \n is a new line character. http://www.cplusplus.com/reference/clibrary/cstdio/printf/
  printf("\n\n      --==== Basic OpenMP information ===--\n\n");


  // Task 1.1
  // These variables have all been initalised to -1.
  // You will have to find the correct functions to get the relevent information.
  // http://msdn.microsoft.com/en-us/library/k1h4zbed(v=VS.80).aspx

  int num_procs = -1;     //TODO 1.1: Find the correct OpenMP Routine to get the number of processors.
  int num_threads = -1;   //TODO 1.1: Find the correct OpenMP Routine to get the number of threads.
  int max_threads = -1;   //TODO 1.1: Find the correct OpenMP Routine to get the maximum number of threads.
  int thread_num = -1;    //TODO 1.1: Find the correct OpenMP Routine to get the number of this thread

  //Outputting the info
  printf("There are %i processors.\n", num_procs );
  printf("There are currently %i thread(s).\n", num_threads );
  printf("The maximum number of threads is %i.\n", max_threads );
  printf("This is thread number %i.\n", thread_num );

  //TODO 1.4: Change the number of threads



  printf("\nStart parallel execution...\n");

  //TODO 1.3: Make the section below run in parallel by adding a relevant #pragma
  {
    thread_num = -1;  //TODO 1.2: Find the correct OpenMP Routine to get this info.
    num_threads = -1; //TODO 1.2: Find the correct OpenMP Routine to get this info.
    printf("Hello from thread %02d, of %02d threads.\n", thread_num, num_threads);

    //TODO 1.5: Make the section below run by only thread 0
    {
      printf("I am the master thread! I am thread %02d, of %02d.\n", thread_num, num_threads);
    }
  }

  printf("\n");
}

