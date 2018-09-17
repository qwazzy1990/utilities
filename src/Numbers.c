
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <stdarg.h>
#include "Numbers.h"



/******STATIC FUNCTIONS****/

int _____compare_ints(const void* a, const void* b)
{
    long long* first = (long long*)a;
    long long* second = (long long*)b;
    if(*first < *second)
    {
        return -1;
    }
    else if(*first == *second)
    {
        return 0;
    }
    else return 1;


}

int _____compare_doubles(const void* a, const void* b)
{
    long double* first = (long double*)a;
    long double* second = (long double*)b;
    if(*first < *second)return -1;
    else if(*first == *second)return 0;
    else return 1;
}

/****FUNCTIONS****/

/***CONSTRUCTORS***/

Int new_int(void)
{
    new_object(Int, n, 1);
    n->ints = NULL;
    n->size = 0;

    n->concat = concat_int;
    n->add = add_int;
    n->remove = remove_int;
    n->remove_at = remove_int_at;
    n->remove_smallest = remove_smallest_int;
    n->remove_largest = remove_largest_int;
    n->remove_all = remove_all_ints;
    n->destroy = destroy_int;

    n->print = print_int;
    n->sort = sort_int;

    return n;
}

void concat_int(Int dest, Int source)
{
    if(source == NULL)return;
    if(source->size == 0)return;
    if(dest == NULL)
    {
        return;
    }
    if(dest->size == 0)
    {
        forall(source->size)
        {
            dest->add(dest, 1, source->ints[x]);
        }
        return;
    }
    int index = dest->size;
    int memSize = dest->size + source->size;
    dest->ints = realloc(dest->ints, memSize * sizeof(long long));
    forall(source->size){
        dest->ints[x] = source->ints[x];
        index++;
        dest->size++;
    }
    return;
}

Double new_double( void )
{
    new_object(Double, n, 1);
    n->doubles = NULL;
    n->size = 0;

    n->add = add_double;
    n->concat = concat_double;
    n->remove = remove_double;
    n->remove_at = remove_double_at;
    n->remove_smallest = remove_smallest_double;
    n->remove_largest = remove_largest_double;
    n->remove_all = remove_all_doubles;
    n->destroy = destroy_double;

    n->print = print_double;
    n->sort = sort_double;
    return n;   
}

void concat_double(Double dest, Double source)
{
    if(source == NULL)return;
    if(source->size == 0)return;
    if(dest == NULL)
    {
        return;
    }
    if(dest->size == 0)
    {
        forall(source->size)
        {
            dest->add(dest, 1, source->doubles[x]);
        }
        return;
    }
    int index = dest->size;
    int memSize = dest->size + source->size;
    dest->doubles = realloc(dest->doubles, memSize * sizeof(long double));
    forall(source->size){
        dest->doubles[x] = source->doubles[x];
        index++;
        dest->size++;
    }
    return;
}
/***END CONSTRUCTORS***/


void add_int(Int m, int n, ...)
{
    if(m == NULL)return;
    if(n <=0)return;
    va_list myList;
    va_start(myList, n);
    int index = m->size;
    if(m->size == 0)
    {
        m->ints = calloc(n, sizeof(long long));
    }
    else{
        int memSize = n + m->size;
        m->ints = realloc(m->ints, memSize*sizeof(long long));
    }
    forall(n){
        long long temp = va_arg(myList, long long);
        m->ints[index] = temp;
        m->size++;
        index++;
    }
    va_end(myList);
}


void add_double(Double d, int n, ...)
{
    if(d == NULL)return;
    if(n <=0)return;
    va_list myList;
    va_start(myList, n);
    int index = d->size;
    if(d->size == 0)
    {
        d->doubles = calloc(n, sizeof(long double));
    }
    else{
        int memSize = n + d->size;
        d->doubles = realloc(d->doubles, memSize*sizeof(long double));
    }
    forall(n){
        long double temp = va_arg(myList, long double);
        d->doubles[index] = temp;
        index++;
        d->size++;
    }
    va_end(myList);   
}
/***END SETTERS***/

/***DESTROYERS***/

void remove_int(Int m, long long n)
{
    if(m == NULL)return;
    if(m->size == 0)return;

    Int newInts = new_int();
    forall(m->size)
    {
        if(m->ints[x] != n)
        {
            newInts->add(newInts, 1, m->ints[x]);
        }
    }
    clear(m->ints);
    m->size = 0;
    m->ints = newInts->ints;
    m->size = newInts->size;
    clear(newInts);
}

void remove_int_at(Int m, long long n)
{
    if(m == NULL)return;
    if(n <  0)return;
    if(m->size == 0)return;
    if(n >= m->size){
        n = m->size-1;
    }
    Int newInts = new_int();
    forall(m->size)
    {
        if(x != n)
        {
            newInts->add(newInts, 1, m->ints[x]);
        }
    }

    clear(m->ints);
    m->size = newInts->size;
    m->ints = newInts->ints;
    clear(newInts);
}
void remove_smallest_int(Int m)
{
    if(m == NULL)return;
    if(m->size == 0)return;
    int index = -1;
    long long temp = m->ints[0];
    forall(m->size)
    {
        if(m->ints[x] < temp)
        {
            temp = m->ints[x];
            index = x;
        }
    }
    Int newInt = new_int();
    forall(m->size)
    {
        if(x != index)
        {
            newInt->add(newInt, 1, m->ints[x]);
        }
    }
    clear(m->ints);
    m->ints = newInt->ints;
    m->size = newInt->size;
    clear(newInt);
    return;
}

void remove_largest_int(Int m)
{
    if(m == NULL)return;
    if(m->size == 0)return;
    int index = -1;
    long long temp = m->ints[0];
    forall(m->size)
    {
        if(m->ints[x] > temp)
        {
            temp = m->ints[x];
            index = x;
        }
    }
    Int newInt = new_int();
    forall(m->size)
    {
        if(x != index)
        {
            newInt->add(newInt, 1, m->ints[x]);
        }
    }
    clear(m->ints);
    m->ints = newInt->ints;
    m->size = newInt->size;
    clear(newInt);
    return; 
}
void remove_all_ints(Int m)
{
    if(m == NULL)return;
    if(m->size == 0)return;
    clear(m->ints);
    m->size = 0;
}

void destroy_int(Int m)
{
    if(m == NULL)return;
    clear(m->ints);
    clear(m);
}



void remove_double(Double d, long double n)
{
    if(d == NULL)return;
    if(d->size == 0)return;

    Double newDouble = new_double();
    forall(d->size)
    {
        if(d->doubles[x] != n)
        {
            newDouble->add(newDouble, 1, d->doubles[x]);
        }
    }
    clear(d->doubles);
    d->size = 0;
    d->doubles = newDouble->doubles;
    d->size = newDouble->size;
    clear(newDouble);
} 

void remove_double_at(Double d, long long n)
{
    if(d == NULL)return;
    if(n <  0)return;
    if(d->size == 0)return;
    if(n >= d->size){
        d->size = d->size-1;
    }
    Double newDouble = new_double();
    forall(d->size)
    {
        if(x != n)
        {
            newDouble->add(newDouble, 1, d->doubles[x]);
        }
    }

    clear(d->doubles);
    d->size = newDouble->size;
    d->doubles = newDouble->doubles;
    clear(newDouble);  
}
void remove_smallest_double(Double d)
{

    if(d == NULL)return;
    if(d->size == 0)return;
    int index = -1;
    long double temp = d->doubles[0];
    forall(d->size)
    {
        if(d->doubles[x] < temp)
        {
            temp = d->doubles[x];
            index = x;
        }
    }
    Double newDouble = new_double();
    forall(d->size)
    {
        if(x != index)
        {
            newDouble->add(newDouble, 1, d->doubles[x]);
        }
    }
    clear(d->doubles);
    d->doubles = newDouble->doubles;
    d->size = newDouble->size;
    clear(newDouble);
    return;    
}


void remove_largest_double(Double d)
{
    if(d == NULL)return;
    if(d->size == 0)return;
    int index = -1;
    long double temp = d->doubles[0];
    forall(d->size)
    {
        if(d->doubles[x] > temp)
        {
            temp = d->doubles[x];
            index = x;
        }
    }
    Double newDouble = new_double();
    forall(d->size)
    {
        if(x != index)
        {
            newDouble->add(newDouble, 1, d->doubles[x]);
        }
    }
    clear(d->doubles);
    d->doubles = newDouble->doubles;
    d->size = newDouble->size;
    clear(newDouble);
    return; 
}

void remove_all_doubles(Double d)
{
    if(d == NULL)return;
    if(d->size == 0)return;
    clear(d->doubles);
    d->size = 0;
}

void destroy_double(Double d)
{
    if(d == NULL)return;
    clear(d->doubles);
    clear(d);
}

/***END DESTROYERS***/


/****PRINTERS FIX ME****/
String print_int(Int m)
{
    String printer = NULL;
    forall(m->size)
    {
        String temp = tostring(INT, &(m->ints[x]));
        if(x == 0)
        {
            printer = stringcopy(temp);
            clear(temp);
        }
        else{
            printer = stringcat(printer, " ");
            printer = stringcat(printer, temp);
            clear(temp);
        }
    }
    return printer;
}

String print_double(Double d)
{
    String printer = NULL;

    forall(d->size)
    {
        String temp = tostring(DOUBLE, &(d->doubles[x]));
        if(x == 0)
        {
            printer = stringcopy(temp);
            clear(temp);
        }
        else
        {
            printer = stringcat(printer, " ");
            printer = stringcat(printer, temp);
            clear(temp);
        }
    }

    return printer;
}
/****END PRINTERS****/

/****SORTERS FIX ME***/

void sort_int(Int m)
{
    CompareFunc compareInts = _____compare_ints;
    qsort(m->ints, m->size, sizeof(long long*), compareInts);
}

void sort_double(Double d)
{
    CompareFunc compareDoubles = _____compare_doubles;
    qsort(d->doubles, d->size, sizeof(long double*), compareDoubles);  
}
/***END SORTERS***/