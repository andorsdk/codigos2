#include <stdio.h>    // Librería para entrada/salida estándar
#include <stdlib.h>   // Librería para funciones estándar de C
#include <pthread.h>  // Librería para trabajar con hilos

#define NUM_THREADS 5 // Definimos el número de hilos

int shared_memory = 0; // Variable que representará la memoria compartida
pthread_mutex_t mutex; // Mutex para evitar condiciones de carrera

// Función que cada hilo ejecutará
void *write_shared_memory(void *threadid) {
    long tid = (long)threadid; // Obtenemos el identificador del hilo
    
    // Bloquear el acceso a la memoria compartida
    pthread_mutex_lock(&mutex);
    shared_memory += 1; // Incrementar la memoria compartida
    printf("Thread #%ld incrementa shared_memory: %d\n", tid, shared_memory);
    // Desbloquear el acceso a la memoria compartida
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL); // Terminar el hilo
}

int main() {
    pthread_t threads[NUM_THREADS]; // Arreglo para almacenar los identificadores de los hilos

    pthread_mutex_init(&mutex, NULL); // Inicializamos el mutex

    // Crear los hilos, cada uno ejecuta la función write_shared_memory
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_create(&threads[i], NULL, write_shared_memory, (void *)i);
    }

    // Esperar a que todos los hilos terminen su ejecución
    for (long i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    pthread_mutex_destroy(&mutex); // Destruir el mutex
    printf("Memoria compartida final: %d\n", shared_memory); // Mostrar el valor final de la memoria compartida

    return 0; // Terminar el programa
}
