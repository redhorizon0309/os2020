#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>
#include<stdio.h>

sem_t mutex;
int max = 1000000;

void *PrimeNum (void *args) {
        int n, a;

        printf("Prime number from 2 to 1000000: \n");
        for (n=2;n<=max;n++) {
                a = 1;
                for (int i=2;i<=n/2;i++) {
                        if (n% i==0) {
                            a = 0;
                            break;
                        }                       
                }
                sem_wait(&mutex);
                if (a==1)
                        printf("%d\n",n);
                sem_post(&mutex);
        }
}

int fibo(int n){
	if ((n==0) || (n==1)) return 1;
	else return fibo(n-1) + fibo(n-2);
}

void *FiboSeq(void *args) {
        int a=0, b=0;
        printf("Fibonaci number sequence from 2 to 1000000: \n");
        while (a <= max) {
		    a = fibo(b);
		    sem_wait(&mutex);
		    if (a<=max) printf ("fibo %d ", a);
		    sem_post(&mutex);
		    b++;
	    }
}

int main () {
    	sem_init(&mutex, 0, 1);

        pthread_t thread1;
        pthread_create(&thread1, NULL,PrimeNum, NULL);
        pthread_join(thread1, NULL);

        pthread_t thread2;
        pthread_create(&thread2, NULL,FiboSeq, NULL);
        pthread_join(thread2, NULL);

        sem_destroy(&mutex);
        return 0;
}
