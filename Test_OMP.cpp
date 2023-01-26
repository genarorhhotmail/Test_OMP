// Test_OMP: Este archivo contiene el programa para sumar dos arreglos en paralelo



// Incluimos la librería <omp.h>  

#include <iostream>
#include <omp.h>

// A continuacion declaramos 3 constantes de pre-compilacion :
//   1. N - para los valores por cada arreglo a, b y c
//   2. chunk - para el tamaño que tendrán los pedazos de los arreglos para que cada hilo creado se encargue de esta 
// cantidad de elementos
//   3. mostrar - que será la cantidad de datos a imprimir

#define N 1000
#define chunk 100
#define mostrar 100

// Enseguida declaramos la función que imprimirá los arreglos, debe recibir como parámetro un apuntador 
//que hace referencia al arreglo que contiene los datos a imprimir. La función se llama imprimeArreglo 
//y no retorna ningún valor.

void imprimeArreglo(float *d);


// Ahora declaramos los 3 arreglos a, b y c, los dos primeros serán utilizados para asignarles los 
// valores pares (a) e impares (b), y el tercer arreglo llamado c servirá para almacenar el resultado
//  de la suma de los dos primeros. Enseguida declaramos la función que imprimirá los arreglos, debe 
// recibir como parámetro un apuntador.
//  

int main()

// Enseguida declaramos los arreglos de un tamaño N (constante que definimos previamente) y asignamos valores a 
// los arreglos a y b conforme comentamos pares e impares respectivamente a y b. 


{
    std::cout << "Sumando Arreglos en Paralelo!\n";
    float a[N], b[N], c[N];
    int i;

    for (i = 0; i < N; i++)
    {
        a[i] = i * 2;
        b[i] = (i * 2) + 1;
    }
    int pedazos = chunk;

// Definimos  la instrucción for que se realizará en paralelo por medio de las instrucciones de la librería 
// OpenMP, indicandole que los arreglos estarán en un área de memoria compartida para que los diferentes
// hilos puedan accesar a los valores, le indicamos  el tamaño de los pedazos que debe tomar cada hilo 
// de los arreglos sin olvidar que la variable i de cada hilo creado,  es privada para que no se mezcle con la
// de los ciclos de otro hilo, finalmente establecemos la planificación como estática y le indicamos también 
// el tamaño de los pedazos que tomamos para la planificación para cada hilo; y colocamos la instrucción for como si 
// fuera una suma de arreglos común, pero en realidad ya está configurado para que se ejecute en paralelo.


    #pragma omp parallel for \
    shared (a,b,c,pedazos) private(i) \
    schedule (static, pedazos)

    for (i = 0; i < N; i++)
        c[i] = a[i] + b[i];

    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arregle a:" << std::endl;
    imprimeArreglo(a);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arregle b:" << std::endl;
    imprimeArreglo(b);
    std::cout << "Imprimiendo los primeros " << mostrar << " valores del arregle c:" << std::endl;
    imprimeArreglo(c);

}

// Una vez realizada la suma en paralelo , comprobamos los resultados y podemos imprimir parte de 
// los arreglos a y b así como el resultado de la suma almacenado en el arreglo c. 
// Mediante la función imprimeArreglo.


void imprimeArreglo(float *d)
{
    for (int x = 0; x < mostrar; x++)
        std::cout << d[x] << " - ";
    std::cout << std::endl;
}
