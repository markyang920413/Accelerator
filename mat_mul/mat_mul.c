#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <unistd.h>

extern void dgemm_(char*, char*, int*, int*,int*, double*, double*, int*, double*, int*, double*, double*, int*);

static int ROW_A = 1000;
static int COL_A = 1000;
static int COL_B = 1000;

double get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (double)tv.tv_sec + (double)1e-6 * tv.tv_usec;
}

void mat_mul_seq(float *A, float *B, float *C,
                 int ROW_A, int COL_A, int COL_B);
void mat_mul_opencl(float *A, float *B, float *C,
                    int ROW_A, int COL_A, int COL_B,int *each_global_size,int *each_local_size);
void verify(float *A, float *B, float *C,
            int ROW_A, int COL_A, int COL_B);

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <option> <local_size>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int option = atoi(argv[1]);
  int local_size=atoi(argv[2]);
  int global_size=0;

  float *A = (float*)malloc(sizeof(float) * ROW_A * COL_A);
  float *B = (float*)malloc(sizeof(float) * COL_A * COL_B);
  float *C = (float*)malloc(sizeof(float) * ROW_A * COL_B);
  int i, j;

  for (i = 0; i < ROW_A; i++) {
    for (j = 0; j < COL_A; j++) {
      A[i * COL_A + j] = (float)(rand() % 1000) / 100.0f;
    }
  }
  for (i = 0; i < COL_A; i++) {
    for (j = 0; j < COL_B; j++) {
      B[i * COL_B + j] = (float)(rand() % 1000) / 100.0f;
    }
  }

  /*
  printf("Matrix Multiplication\n");
  printf("C[%d X %d] = A[%d X %d] X B[%d X %d]\n",
         ROW_A, COL_B, ROW_A, COL_A, COL_A, COL_B);
  */
  if (option == 0) {                     // Sequential 하게 쓰겠다.
    printf("Sequential version...\n");
    double start_time = get_time();
    mat_mul_seq(A, B, C, ROW_A, COL_A, COL_B);
    double end_time = get_time();
    printf("Elapsed time: %f sec\n", end_time - start_time);

  } else if (option == 1) {             // OpenCL을 쓰겠다.
    printf("OpenCL version...\n");
    double start_time = get_time();
    mat_mul_opencl(A, B, C, ROW_A, COL_A, COL_B,&global_size,&local_size);
    double end_time = get_time();
    float Elapsed_time=end_time-start_time;
    verify(A, B, C, ROW_A, COL_A, COL_B);
    printf("Elapsed_time: %f sec\n", Elapsed_time);
    printf("global_size: %d local_size: %d\n",global_size,local_size);

  } else {
    printf("Invalid option!\n");
    exit(EXIT_FAILURE);
  }

  //verify(A, B, C, ROW_A, COL_A, COL_B);

  free(A);
  free(B);
  free(C);
  return 0;
}

void verify(float *A, float *B, float *C,
            int ROW_A, int COL_A, int COL_B) {
  int i, j, k;
  float sum;

  for (i = 0; i < ROW_A; i++) {
    for (j = 0; j < COL_B; j++) {
      sum = 0.0f;
      for (k = 0; k < COL_A; k++) {
        sum += A[i * COL_A + k] * B[k * COL_B + j];
      }
      if (fabsf(C[i * COL_B + j] - sum) > 0.1) {
        printf("Verification failed! C[%d][%d]: %f vs. %f\n",
               i, j, C[i * COL_B + j], sum);
        return;
      }
    }
  }
  printf("Verification success!\n");

}
