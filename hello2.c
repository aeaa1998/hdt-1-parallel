#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
void openmp_hello(void);
int main(int argc, char *argv[])
{
    int thread_count = strtol(argv[1], NULL, 10);
    int i;

#pragma omp parallel for num_threads(thread_count) private(i)
    for (int i = 0; i < 21; i++)
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
        char *message;
        if (id % 2 == 0)
        {
            message = "Saludos del hilo: %d";
        }
        else
        {
            message = "Saludos del hilo: %d";
        }
        prrintf()
            printf("Hola :)\nAhorita mostraremos el id %d\nY ahora el total de hilos corriendo: %d\n", id, total);
    }

    return 0;
}
void openmp_hello(void)
{
    for (int i = 0; i < 21; i++)
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
        char *message;
        if (id % 2 == 0)
        {
            message = "Saludos del hilo: %d";
        }
        else
        {
            message = "Saludos del hilo: %d";
        }
        printf("Hola mundo\nAhorita mostraremos el id %d\nY ahora el total de hilos corriendo: %d\n", id, total);
    }

} /*openmp_hello*/