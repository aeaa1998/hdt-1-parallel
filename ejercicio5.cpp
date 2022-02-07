/*----------------------------------------------
 * riemann.c - calculo de area bajo la curva
 *----------------------------------------------
 * Sumas de Riemann para calcular la integral f(x)
 *
 * Date:  2021-09-22
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <omp.h>
#define A 1
#define B 40
#define N 10e6
#define THREADS_NUM 20
double f(double x); // La funcion a integrar
void Trap(double a, double b, int n, double *global_result_p);

int main(int argc, char *argv[])
{
    double integral;
    double a = A, b = B;
    int n = N;
    int threads_num = THREADS_NUM;
    double h;
    // Only if it is safe
    if (argc > 3)
    {
        a = strtol(argv[1], NULL, 10);
        b = strtol(argv[2], NULL, 10);
        threads_num = strtol(argv[3], NULL, 10);
    }
#pragma omp parallel num_threads(threads_num)
    Trap(a, b, n, &integral);

    printf("Con n = %d trapezoides, nuestra aproximacion \n", n);
    printf("de la integral de %f a %f es = %.10f\n", a, b, integral);
}

void Trap(double a, double b, int n, double *global_result_p)
{
    double h, x, partial_integral;
    double local_a, local_b;
    int i, local_n;
    int id = omp_get_thread_num();
    int thread_count = omp_get_num_threads();

    h = (b - a) / n;
    local_n = n / thread_count;
    local_a = a + id * local_n * h;
    local_b = local_a + local_n * h;
    partial_integral = (f(local_a) + f(local_b)) / 2;
    for (i = 1; i < local_n; i++)
    {
        x = local_a + i * h;
        partial_integral += f(x);
    }
    partial_integral = partial_integral * h;

#pragma omp critical
    *global_result_p += partial_integral;
}

// f
//
// Funcion a ser integrada
// Input: x
//------------------------------------------
double f(double x)
{
    double return_val;
    return_val = x * x;
    return return_val;
} /*f*/
