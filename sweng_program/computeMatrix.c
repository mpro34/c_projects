/* Compute Matrix tool, while command line options and tests
 * Created by Chris Whiting
 * 02/24/2017
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Function Definition */
void computeMatrix(int c, int n, char* test_file);

int main(int argc, char* argv[])
{
  int c=0,n=0;
  float *I;
  char option;

  if (argc != 6) {
    fprintf(stderr, "Usage: ./computeMatrix -c value -n floatingNums testfileName\n");
    return 1;
  }
  else {
  /* Parse command line arguments for c, N and filename */
    while ((option = getopt(argc, argv, "c:n:")) != EOF)
      switch (option) {
      case 'c':
        c = atoi(optarg);    /* Convert char* to int */
        break;
      case 'n':
        n = atoi(optarg);    /* Convert char* to int */
        break;
      default:
        fprintf(stderr, "Unknown options '%s'\n", optarg);
        return 1;
      }
    argc -= optind;
    argv += optind;
/* Compute the matrix operation */
    computeMatrix(c, n, argv[argc-1]);
  }

  return 0;
}


/* Function to read the input TEST.PRN file */
void computeMatrix(int c, int n, char* test_file)
{
  /* Variable initialization */
  float *input_list = (float *)malloc(n * sizeof(float));
  float **output = (float **)malloc(c * sizeof(float *));
  for (int e=0; e<c+1; e++) {
    output[e] = (float *)malloc(c * sizeof(float));
  }
  int i=0;
  float line = 0; //Large enough for a single line
  FILE *in;

  /* Start reading Test file - Open file stream, check for errors */
  if (!(in = fopen(test_file, "r"))) {
    fprintf(stderr, "Can't open the file.\n");
  };
  /* Read each line into the float line value. */
  while (fscanf(in, "%f\n", &line) == 1) {
    input_list[i++] = line;
  /* Error checking for n-value input */
    if (i > n) {
    fprintf(stderr, "N-value not large enough for file!\n");
    break;
    }
  }
  fclose(in);

  /* Perform matrix computation and fill out matrix */
  for (int k=0; k <= c; k++) {
    for (int j=0; j <= c; j++) {
      for (int i=c; i < n; i++) {
        output[k][j] += input_list[i-k] * input_list[i-j];
      }
    }
  }
  /* Print the resulting CxC matrix */
    for (int i=0; i < c+1; i++) {
      for (int j=0; j < c+1; j++) {
          printf("%f   ", output[i][j]);
      }
      free(output[i]);  //Free the allocated memory from the heap
      printf("\n");
    }
    free(input_list);
    free(output);
}
