#include <stdio.h>

int test();
int funcion(int a, int b);
int main (void)
{
    if (test() != 0)
        printf ("TEST FALLO");
    else
        printf ("TEST OK");
    return 0;
}
int test()
{


    if(funcion(4,11) != 28)
    {
        return 1;
    }
    if(funcion(11,5) != 24)
    {
        return 2;
    }
    if(funcion(5,5) != 0)
    {
        return 3;
    }
    if(funcion(2,2) != 2)
    {
        return 4;
    }
    if(funcion(-4,-11) != -28)
    {
        return 5;
    }
    if(funcion(-4,11) != 24)
    {
        return 6;
    }
    if(funcion(-20,-7) != -98)
    {
        return 7;
    }
    return 0;

}
int funcion(int a, int b)
{
    int aux = a;
    int suma = 0;

    if(a > b)
    {
        a = b;
        b = aux;
    }
    while(a <= b)
    {
        if(a%2 == 0)
        {
            suma = suma + a;
        }
        a++;
    }
    return suma;
}
