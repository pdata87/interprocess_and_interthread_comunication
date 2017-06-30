#include <stdio.h>
#include <zconf.h>
#include <pthread.h>
#include "List.h"




pthread_mutex_t mutex;
pthread_cond_t list_is_empty,list_is_full;




void* t_write(void *arg)
{
    while(1) {
        for(int i = 0; i < 30 ; i++) {
       pthread_mutex_lock(&mutex);
                int number_of_elemets = get_number_of_elements();
                int buff_size = get_max_size();
            if(number_of_elemets == buff_size)
                pthread_cond_wait(&list_is_empty,&mutex);
            printf("thread is writing \n");
            push(i);
            pthread_cond_signal(&list_is_full);
            pthread_mutex_unlock(&mutex);

        }
        sleep(10);
    }
    return NULL;
}

void* t_read(void *arg)
{

    while(1) {


        pthread_mutex_lock(&mutex);
        if (get_number_of_elements() < get_max_size() ) pthread_cond_wait(&list_is_full, &mutex);

        printf("thread_read = %li | value = %d | \n", pthread_self(), pop());

        pthread_cond_signal(&list_is_empty);

        pthread_mutex_unlock(&mutex);
    }
}


int main() {

    int no_of_threads = 4;

    pthread_t threads[no_of_threads];
    pthread_mutex_init(&mutex,NULL);

    pthread_cond_init(&list_is_empty, NULL);
    pthread_cond_init(&list_is_full,NULL);


    for(int i =0; i < no_of_threads;i++){
        pthread_create(&threads[i], NULL , (i==0)? &t_write : &t_read, NULL);
    }


    for(int i = 0 ; i < no_of_threads ; i++) {
        pthread_join(threads[i], NULL);
    }
    return 0;
}


