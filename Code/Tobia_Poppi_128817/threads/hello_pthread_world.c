#include <stdio.h>
#include <pthread.h>

void *my_pthread(void *arg)
{
    //thread body
    printf("Hello Pthread world\nI am the newly created thread\n\n");
    return NULL;
}

int main()
{
    printf("Hello World!\nI am the main thread\n\n");

    ///COME è STRUTTURATA LA FUNZIONE

    /*int err = pthread_create(pthread_t *ID, (IL SUO ID)
                      pthread_attr_t * attr,  (IL PARAMETRO..... DA APPROFONDIRE)
                      void *(*body)(void *),  (IL BODY DELLA FUNZIONE DEL THREAD)
                      void *arg);             (IL PARAMETRO DELLA FUNZIONE)
    */

    ///QUINDI:

    pthread_attr_t attributo;
    pthread_attr_init(&attributo);
    pthread_t miothread;

    int err = pthread_create(&miothread, &attributo, my_pthread, NULL);
    printf("%d\n", err); //0 se non ci sono stati errori.

    //ORA HO CREATO UN THREAD DIVERSO DAL MAIN THREAD, CHE MI ESEGUE LA FUNZIONE IN QUESTIONE.
    //QUI INTANTO IL MAIN PUOò FARE QUALSIASI ALTRA COSA
    printf("I am the main thread and i can do other stuff here!\n\n");

    void *returnvalue;
    pthread_join(miothread, &returnvalue); //QUI ASPETTO CHE IL THREAD CREATO ABBIA FINITO DI ANDARE.

    return 0;
}
