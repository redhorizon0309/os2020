#include<stdio.h>
#include<pthread.h>

void *PrimeNum (void *args) {
        int n, a=0;
        printf("Prime number from 2 to 1000000: \n");
        for (n=2;n<=1000000;n++) {
                a=0;
                for (int i=1;i<=n;i++) {
                        if (n% i==0)
                                a++;
                        if (a>2) break;

                }
                if (a==2)
                        printf("%d\n",n);
        }
}

void *FiboSeq(void *args) {
        int a=1, b=1, c=0;
        printf("Fibonaci number sequence from 2 to 1000000: \n");

        while(c<=1000000) {
                c=a+b;
                a=b;
                b=c;
                printf("%d \n",c);
        }
}

int main () {
        pthread_t thread1;
        pthread_t thread2;
        pthread_create(&thread1, NULL,PrimeNum, NULL);
        pthread_create(&thread2, NULL,FiboSeq, NULL);
        pthread_join(thread1, NULL);
        pthread_join(thread2, NULL);
        return 0;
}
