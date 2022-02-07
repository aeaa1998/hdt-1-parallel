#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <string>
#include <chrono>
#include <ostream>
#include <iostream>
template <
    class result_t = std::chrono::milliseconds,
    class clock_t = std::chrono::steady_clock,
    class duration_t = std::chrono::milliseconds>
auto since(std::chrono::time_point<clock_t, duration_t> const &start)
{
    return std::chrono::duration_cast<result_t>(clock_t::now() - start);
}
int main(int argc, char *argv[])
{
    int thread_count = strtol(argv[1], NULL, 10);
    int i;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

#pragma omp parallel for num_threads(thread_count) private(i)
    for (i = 0; i < thread_count; i++)
    {
        int id = omp_get_thread_num();
        int total = omp_get_num_threads();
        std::string message;
        if (id % 2 == 0)
        {
            message = "Saludos del hilo: " + std::to_string(id);
        }
        else
        {
            message = "Feliz cumple numero: " + std::to_string(i);
        }

        printf("%s\nAhorita mostraremos el id %d\nY ahora el total de hilos corriendo: %d\n\n", message.c_str(), id, total);
    }

    std::cout << "Elapsed(ms)=" << since(start).count() << std::endl;
    return 0;
}
