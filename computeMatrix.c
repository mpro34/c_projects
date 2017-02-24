#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

/* Function Definitions */
float * readInputFile(int n, char* test_file);
void calculateMatrix(int c, int n, float* input_file);

int main(int argc, char* argv[])
{
  int c=0,n=0;
  float *I;
  char option;
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

//  printf("c: %i, n: %i, inputfile: %s\n", c, n, argv[argc-1]);

/* Compute the matrix operation */
  I = readInputFile(n, argv[argc-1]);
//  printf("first: %f, last: %f\n", I[0], I[299]);
  //float** result = calculateMatrix(c, n, I);
  calculateMatrix(c, n, I);
/* Print the resulting CxC matrix
  for (int i=0; i < c+1; i++) {
    for (int j=0; j < c+1; j++) {
        printf("%f   ", result[i][j]);
    }
    printf("\n");
  }*/

  //free(result);
  return 0;
}

/* Function to read the input TEST.PRN file */
float * readInputFile(int n, char* test_file)
{
//  printf("n %i", n);
  float line = 0; //Large enough for a single line
  FILE *in;
  float *input_list = malloc(n-1);
  int i=0;
  /* Open file stream, check for errors */
  if (!(in = fopen(test_file, "r"))) {
    fprintf(stderr, "Can't open the file.\n");
  };
  /* Read each line into the float line value. */
//  printf("start\n");
  while (fscanf(in, "%f\n", &line) == 1) {
    //printf("%f\n", line);
    input_list[i++] = line;
    /* Error checking for n-value input */
    if (i > n) {
    fprintf(stderr, "N-value not large enough for file!\n");
    break;
    }
  }
  fclose(in);
  return input_list;
}

/* Function to calculate the matrix */
void calculateMatrix(int c, int n, float* input_file)
{
  for (int i=0; i < n; i++)
    printf("input_data: %f\n", input_file[i]);

  //printf("first: %f, last: %f\n", input_file[0], input_file[n-1]);
  //float output[c+1][c+1];//float** output= float*[c+1];
  float **output = (float **)malloc(c * sizeof(float *));// = malloc(c*sizeof( float* ));
  for (int e=0; e<c+1; e++) {
    output[e] = (float *)malloc(c * sizeof(float));
  //  printf("out: %f", output[e][0]);
  }
  /*for (int p=0; p<=c; p++) {
    output[p] = float[c+1];
  }*/
  for (int k=0; k <= c; k++) {
    for (int j=0; j <= c; j++) {
      for (int i=c; i < n; i++) {
    //    printf("Prior OUTPUT: %f, k%i,j%i\n", output[k][j], k, j);
        output[k][j] += input_file[i-k] * input_file[i-j];
      }
  //    printf("output: %f, [k]: %i, [j]: %i\n", output[k][j], k, j);
    }
  }
  printf("END OF TEST\n");
  /* Print the resulting CxC matrix */
    for (int i=0; i < c+1; i++) {
      for (int j=0; j < c+1; j++) {
          printf("%f   ", output[i][j]);
      }
      free(output[i]);
      printf("\n");
    }
    free(output);
  //return output;
}
