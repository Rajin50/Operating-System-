#include <pthread.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAX 10 //producers and consumers can produce and consume up to MAX
#define BUFLEN 6
#define NUMTHREAD 2 /* number of threads */

void *consumer(int *id);
void *producer(int *id);

char buffer[BUFLEN];
char source[BUFLEN]; //from this array producer will store its production into buffer
int pCount = 0;
int cCount = 0;
int buflen;
//initializing pthread mutex and condition variables
pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0,1};
int i = 0;
int j = 0;

int main()
{
    int i;
    /* define the type to be pthread */
    pthread_t thread[NUMTHREAD];
    strcpy(source, "abcdef");
    buflen = strlen(source);
    /* create 2 threads*/
    /* create one consumer and one producer */
    /* define the properties of multi threads for both threads */
    //Write Code Here
    for (i = 0; i < NUMTHREAD; i++)
    {
        if (i == 0)
            pthread_create(&thread[i], NULL, producer, &thread_id[i]);
        else
            pthread_create(&thread[i], NULL, consumer, &thread_id[i]);
           
    }

    for (i = 0; i < NUMTHREAD; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(int *id)
{
    /*
    1. Producer stores the values in the buffer (Here copies values from source[] to buffer[]).
    2. Use mutex and thread communication (wait(), sleep() etc.) for the critical section.
    3. Print which producer is storing which values using which thread inside the critical section.
    4. Producer can produce up to MAX
   */
   //Write code here
   
    int *thread_id = (int *)id;
    while (pCount < MAX)
    {
        pthread_mutex_lock(&count_mutex);
        while (strlen(buffer) == BUFLEN)
        {
            pthread_cond_wait(&full, &count_mutex);
        }
        buffer[pCount % BUFLEN] = source[pCount % buflen];
        printf("%d produced %c by Thread %d\n", pCount, buffer[pCount % BUFLEN], *thread_id);
        pCount++;
        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

void *consumer(int *id)
{
     /*
    1. Consumer takes out the value from the buffer and makes it empty.
    2. Use mutex and thread communication (wait(), sleep() etc.) for critical section
    3. Print which consumer is taking which values using which thread inside the critical section.
    4. Consumer can consume up to MAX
   */
   //Write code here
   
    int *thread_id = (int *)id;
    while (cCount < MAX)
    {
        pthread_mutex_lock(&count_mutex);
        while (strlen(buffer) == 0)
        {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }
        printf("%d consumed %c by Thread %d\n", cCount, buffer[cCount % BUFLEN], *thread_id);
        buffer[cCount % BUFLEN] = '\0';
        cCount++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
        sleep(1);
    }
    pthread_exit(NULL);
}

