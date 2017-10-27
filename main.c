/**
   Author: Yassine Maalej (Github: yesoun) 
   email: maalej.yessine@gmail.com && maal4948@vandals.uidaho.edu
   Date: Frebuary 2016
   Class: CS541 Advanced Operating Systems
   Insitution: University Of Idaho

Assign1: The purpose of this assignment is to gain some familiarity with using pthreads, and to implement a message passing 
mechanism between threads. You should create a process with two threads - one thread will be the sender and the other thread 
will be the receiver. The message should consist of a character string, passed as a pointer to the receiving thread. 
This string should be input via the sending thread, placed in a buffer that is accessible to both threads, and then retrieved 
by the receiving thread and printed. The sending and receiving processes should protect the buffer operations with semaphores,
to provide the necessary synchronization to avoid any race conditions.

Files:
     makefile: gcc main.c -o main -lpthread
     hmwrk_1_main.c     
*/
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

typedef int bool;
#define true 1

/// sender thread identifier
pthread_t pth_sender;
/// receiver thread identifier
pthread_t pth_receiver;

/// semaphore used to lock access between either sending and changing buffer from sender or reading from receiver
static sem_t sem_lock_buffer;


/// declaration of the global variable buffer that will contain the string message sent from the sender thread
char* msg_buffer;
int count_message; // counter whenever the sender thread changes the message
int thread_write()
{
    msg_buffer="message from Thread";
}

/**
    the task of the sender is easy, we should not allow any other writer or any reader to access the variable that we are 
    writing and sending the message in the buffer. value of the sem_sender is set to value=1, before entering the critical 
    section to write, sem_wait => value=0 (cannot be reduced any longer so no other sender can intefere) after writing we 
    perform sem_post to increase the value=1
*/
void *send_message(void* a)
{
    sem_wait(&sem_lock_buffer); // before entering critical section and sending the message and changing the buffer sem-writer
    thread_write();    // writing the message in the buffer
    printf("sender write .. \n");
    sem_post(&sem_lock_buffer);
}

/**
    if the receiver is inside the critical sectoin and receiving the value that has been sent to buffer, no sender should 
    change the buffer by sending another the message make sure to decrease the value of the semaphore so that the sender 
    can't send and make another wait
*/
void *receive_message(void* a)
{
    sem_wait(&sem_lock_buffer);
    printf("Receiver: the message in buffer is : %s \n",msg_buffer);
    sem_post(&sem_lock_buffer);
}


/**
    Compilation : gcc main.c -o main -lpthread
    Main section
*/
int main()
{
    /// initialisation of the semaphore
    sem_init(&sem_lock_buffer,0,1); //  int sem_init(sem_t *sem, int pshared, unsigned int value)

    /// attempts of messages exchange between threads
    int num_attempts=0;
    while(true && num_attempts!=20){
        pthread_create(&pth_sender,NULL,send_message,NULL);
        pthread_create(&pth_receiver,NULL,receive_message,NULL);
        num_attempts+=1;

    }

    /// wait the threads to finish and then cleanup any resources associated wih the thread.
    pthread_join(pth_sender, NULL);
    pthread_join(pth_receiver, NULL);

    /// destroy semaphore
    sem_destroy(&sem_lock_buffer);

    return 0;
}
