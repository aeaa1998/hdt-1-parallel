/*----------------------------------------------
 * riemann.c - calculo de area bajo la curva
 *----------------------------------------------
 * Sumas de Riemann para calcular la integral f(x)
 *
 * Date:  2021-09-22
 */
#include <stdio.h>
#include <stdlib.h>
#define A 1
#define B 40
#define N 10e6
#define THREADS_NUM 20

double f(double x); // La funcion a integrar
double trapezoides(double a, double b, int n, int threads);
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
    //---- Aproximacion de la integral
    // h = (b-a)/n;
    integral = trapezoides(a, b, n, threads_num);
    printf("Con n = %d trapezoides, nuestra aproximacion \n", n);
    printf("de la integral de %f a %f es = %.10f\n", a, b, integral);
    return 0;
} /*main*/
//------------------------------------------
// trapezoides
// En esta función es donde se puede aplicar pragma
//
// Estimar la integral mediante sumas de Riemann
// Input: a,b,n,h
// Output: integral
//------------------------------------------
double trapezoides(double a, double b, int n, int threads)
{
    double integral, h;
    int k;
    //---- Ancho de cada trapezoide
    h = (b - a) / n;
    //---- Valor inicial de la integral (valores extremos)
    integral = (f(a) + f(b)) / 2.0;

#pragma omp parallel for num_threads(threads) private(k) reduction(+ \
                                                                   : integral)
    for (k = 1; k <= n - 1; k++)
    {
        integral += f(a + k * h);
    }
    integral = integral * h;
    return integral;
} /*trapezoides*/
//------------------------------------------
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