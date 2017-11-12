#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <signal.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <errno.h>

int N,B,P,C, p_count, c_count;

pthread_t* pid;
pthread_t* cid;

int* boundedBuffer;
int pindex;
int cindex;

struct timeval time_val;

sem_t spaces, mutex, items, prod_mux, con_mux;

// int semval(sem_t * sem) {
//     int sval;
//     sem_getvalue(&spaces, &sval);
//     return sval;
// }

void init(int B) {
    sem_init(&mutex, 0, 1);
    sem_init(&spaces, 0, B);
    sem_init(&items, 0, 0);

    sem_init(&prod_mux, 0, 1); // mutex for updating producer count
    sem_init(&con_mux, 0, 1); // mutext for updating consumer count

    p_count = 0;
    c_count = 0;

    pindex = 0;
    cindex = 0;
}

// producers produce -> add to buffer
void add_to_buffer(int target) {
    sem_wait(&spaces);
    sem_wait(&mutex);

    boundedBuffer[pindex] = target;
    pindex = (pindex + 1) % B; // update producer index

    sem_post(&mutex);
    sem_post(&items);
}

// consumers consume -> remove from buffer
int remove_from_buffer() {
    sem_wait(&items);
    sem_wait(&mutex);

    int target = boundedBuffer[cindex];
    cindex = (cindex + 1) % B; // update consumer index
    
    sem_post(&mutex);
    sem_post(&spaces);
    return target;
}

void* producer(void* arg) {
    int id = *(int*) arg;
    free(arg); // c is crazy
    int next_number = id;

    while(1) {
        sem_wait(&prod_mux);
        if (next_number > N) {
            sem_post(&prod_mux);
            break;
        }
        p_count++;
        sem_post(&prod_mux);

        // Add to buffer
        add_to_buffer(next_number);
        next_number = next_number + P; // next number to produce
    }
    return NULL;
}

void* consumer(void* arg) {
    int id = *(int*) arg;
    free(arg);
    int num;
    double root;

    while(1) {
        sem_wait(&con_mux);
        if (c_count > N - 1) {
	    sem_post(&con_mux);
            break;
        }
        c_count++;
        sem_post(&con_mux);

        // Remove from buffer
        num = remove_from_buffer();
        // Calculate square root
        double root = sqrt((float)num);
        // Only print perfect roots 
        if(root == (int)root) {
            printf("Consumer id: %d, num: %d, root: %f \n", id, num, root);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        printf("Please supply 4 arguments, in the order: <NumIntegers> <BufferSize> <NumProducers> <NumConsumers> \n");
        return 0;
    }

    N = atoi(argv[1]); // number of numbers that producers will produce
	B = atoi(argv[2]); // buffer size
	P = atoi(argv[3]); // number of producers
    C = atoi(argv[4]); // number of consumers

    boundedBuffer = (int*) malloc(B * sizeof(int));
	pid = (pthread_t*) malloc(P * sizeof(pthread_t));
	cid = (pthread_t*) malloc(C * sizeof(pthread_t));
    
    init(B);

    // start counting program duration
    gettimeofday(&time_val, NULL);
    double start_time = ((double) time_val.tv_sec) + time_val.tv_usec/1000000.0;

    // Create threads
    // - create producer
    for (int p = 0; p < P; p++) {
        int* p_id = malloc(sizeof(int));
        *p_id = p;
		pthread_create(&pid[p], NULL, producer, p_id);
    }
    // - create consumer
    for (int c = 0; c < C; c++) {
        int* c_id = malloc(sizeof(int));
        *c_id = c;
        pthread_create(&cid[c], NULL, consumer, (void*)c_id);
    }

    // Collect results
    // - collect producer results
    for (int p = 0; p < P; p++) { 
        pthread_join(pid[p], NULL);
    }

    // - collect consumer results
    for (int c = 0; c < C; c++) {
        pthread_join(cid[c], NULL);
    }

    gettimeofday(&time_val, NULL);    
    double end_time = ((double) time_val.tv_sec) + time_val.tv_usec/1000000.0;
    printf("System execution time: %f\n", end_time - start_time);
}
