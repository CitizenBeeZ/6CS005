#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <math.h>
#include <malloc.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer. Your personalised data set is included in the
  code.

  Compile with:
    cc -o CrackAZ99-With-Data CrackAZ99-With-Data.c -lcrypt -lpthread

  If you want to analyse the results then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:

    ./CrackAZ99-With-Data > results.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018
******************************************************************************/
#define n_threads 2

typedef struct arguments_t {
  int start;
  int end;
  int it;
} arguments_t;

int n_passwords = 4;

char *encrypted_passwords[] = {
  "$6$KB$0G24VuNaA9ApVG4z8LkI/OOr9a54nBfzgQjbebhqBZxMHNg0HiYYf1Lx/HcGg6q1nnOSArPtZYbGy7yc5V.wP/",
  "$6$KB$e0HAHUeBkbmMUYH50qM6XOcuMh5NIh4wWqaF5veFJ8lCCXO2WikTvJXMRUhQAE.L0c583VnKDUYYsz4hdRSPx.",
  "$6$KB$/g6qkCh2GqH3qbb9VpoY.LaOEfiuD3JQ9xt49hYMEGHxCWq26lsspDwYankcFID6OY2/pGKIa2ysBWzvaK87D0",
  "$6$KB$QIT0aY3OjXyMz7/0u/Evwrzcb44AwaQbsRFPZ3UeT8df8LoJzpDI8ULgvKw5ZfZJui3nj0k3OtkGaB/znQwrU1"
};

/**
 Required by lack of standard function in C.  
*/

void substr(char *dest, char *src, int start, int length){
  memcpy(dest, src + start, length);
  *(dest + length) = '\0';
}

void factorise(int x) {
  int i;
  pthread_t *t = malloc(sizeof(pthread_t) * n_threads);
  arguments_t *a = malloc(sizeof(arguments_t) * n_threads);
  for(i=0;i<2;i++){
    //a[i].start = i;
    //a[i].stride = n_threads;
    if(i == 0)
    {
      a[i].start = 'A';
      a[i].end = 'M';
      a[i].it  = x;
    }
    else
    {
      a[i].start = 'N';
      a[i].end = 'Z';
      a[i].it  = x;
    }
  }

  void *crack();
  for(i=0;i<2;i++){
    //pthread_create(&t[i], NULL, crack(encrypted_passwords[i], &a[i]), &a[i]);
    pthread_create(&t[i], NULL, crack, &a[i]);
  }
  for(i=0;i<2;i++){
    pthread_join(t[i], NULL);
  }
  free(t);
  free(a);
}
/**
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the
 start of the line. Note that one of the most time consuming operations that
 it performs is the output of intermediate results, so performance experiments
 for this kind of program should not include this. i.e. comment out the printfs.
*/

// void *crack(char *salt_and_encrypted, arguments_t *args){
void *crack(arguments_t *args){
  char *salt_and_encrypted = encrypted_passwords[args->it];
  int x, y, z;     // Loop counters
  char salt[7];    // String used in hashing the password. Need space for \0
  char plain[7];   // The combination of letters currently being checked
  char *enc;       // Pointer to the encrypted password
  int count = 0;   // The number of combinations explored so far

  substr(salt, salt_and_encrypted, 0, 6);

  for(x='A'; x<='Z'; x++){
    for(y='A'; y<='Z'; y++){
      for(z=0; z<=99; z++){
        sprintf(plain, "%c%c%02d", x, y, z);
        enc = (char *) crypt(plain, salt);
        count++;
        if(strcmp(salt_and_encrypted, enc) == 0){
          printf("#%-8d%s %s\n", count, plain, enc);
        } else {
          printf(" %-8d%s %s\n", count, plain, enc);
        }
      }
    }
  }
  printf("%d solutions explored\n", count);
}

int time_difference(struct timespec *start, struct timespec *finish,
   long long int *difference) {
   long long int ds = finish->tv_sec - start->tv_sec;
   long long int dn = finish->tv_nsec - start->tv_nsec;

      if (dn < 0) {
	ds--;
	dn += 1000000000;
	}
	   *difference = ds * 1000000000 + dn;
	   return !(*difference > 0);
}

int main(int argc, char *argv[]){
   struct timespec start, finish;
   long long int time_elapsed;

   clock_gettime(CLOCK_MONOTONIC, &start);
   int i;

  for(i=0;i<n_passwords;i<i++) {
     factorise(i);

  }
   clock_gettime(CLOCK_MONOTONIC, &finish);
   time_difference(&start, &finish, &time_elapsed);
   printf("Time elapsed was %lldns or %0.9lfs\n", time_elapsed,
   (time_elapsed / 1.0e9));

  return 0;
}
