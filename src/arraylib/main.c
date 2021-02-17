/*Библиотека для упрощения работы с массивами на языке си
//slice(mas,beg,end,step)
//filter(mas,func)
//merge(mas1,mas2,filter)
//fill(mas,func)
//all(mas,func)
//any(mas,func)
//count(mas,func)
//map(mas,func)
//reduce(mas,func)
//mprintf(mas,func)*/
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <complex.h>

#include "array.h"

void printInt(const void *arg)
{
    printf("%d\t", *(int*)arg);
}
void printFlt(const void *arg)
{
    printf("%.3f\t", *(float*)arg);
}
void printDbl(const void *arg)
{
    printf("%.6f\t", *(double*)arg);
}
void printExp(const void *arg)
{
    printf("%.3e\t", *(double*)arg);
}
void printCmplx(const void *arg)
{
    printf("%.3f+%.3f*i\t", creal(*(double complex*)arg), cimag(*(double complex*)arg));
}

void aprint(void *mas, const size_t szEl, const largeSize_tp size1, const largeSize_tp size2, const char *title, void (*print)(const void *arg))
{
    long long i, j;
    printf("%s\n", title);
    for(i = 0; i < size1; i++) {
        for(j = 0; j < size2; j++, mas += szEl) {
            print(mas);
        }
        printf("\n");
    }
}

void dprint(void *data, const char *title, void (*print)(const void *arg), void* (*iterate)(void *curEl))
{
    printf("%s\n", title);
    while(data) {
        print(data);
        data = iterate(data);
    }
    printf("\n");
}





void step(void* masEl, largeSize_tp num)
{
    *(int*)masEl = (int)num;
}
void stepTwc(void* masEl, largeSize_tp num)
{
    *(int*)masEl = (int)num * 2;
}
void setRnd(void* masEl, largeSize_tp num)
{
    *(int*)masEl = rand() % 100;
}
void setDblRnd(void* masEl, largeSize_tp num)
{
    *(double*)masEl = (rand() % 10000) / 100;
}

void *setArr(void *mas, const size_t szEl, const largeSize_tp size, void (*setEl)(void* masEl, largeSize_tp num))
{
    long long i;
    void *tmpptr = mas;
    for(i = 0; i < size; i++, mas += szEl) {
        setEl(mas, i);
    }
    return tmpptr;
}

void *setArrNew(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, void (*setEl)(void* masEl, largeSize_tp num))
{
    long long i;
    void *tmpptr = newmas;

    memcpy(newmas, mas, szEl * size);
    for(i = 0; i < size; i++, newmas += szEl) {
        setEl(newmas, i);
    }

    return tmpptr;
}

void *setData(void *data, void (*setEl)(void* masEl, largeSize_tp num), void* (*iterate)(void *curEl))
{
    long long i;
    void *tmpptr = data;
    for(i = 0; (data = iterate(data)); i++) {
        setEl(data, i);
    }
    return tmpptr;
}






void *mapArr(void *mas, const size_t szEl, const largeSize_tp size, void (*procEl)(void* masEl))
{
    long long i;
    void *tmpptr = mas;
    for(i = 0; i < size; i++, mas += szEl) {
        procEl(mas);
    }
    return tmpptr;
}

void *mapArrNew(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, void (*procEl)(void* masEl))
{
    long long i;
    void *tmpptr = newmas;

    memcpy(newmas, mas, szEl * size);
    for(i = 0; i < size; i++, newmas += szEl) {
        procEl(newmas);
    }

    return tmpptr;
}

void *mapData(void *data, void (*procEl)(void *masEl), void* (*iterate)(void *curEl))
{
    void *tmpptr = data;
    while(data) {
        procEl(data);
        data = iterate(data);
    }
    return tmpptr;
}





void sumArrEl(void *acc, const void *masEl)
{
    *(int*)acc += *(int*)masEl;
}
void sumDblArrEl(void *acc, const void *masEl)
{
    *(double*)acc += *(double*)masEl;
}
void mulArrEl(void *acc, const void *masEl)
{
    *(int*)acc *= *(int*)masEl;
}
void mulDblArrEl(void *acc, const void *masEl)
{
    *(double*)acc *= *(double*)masEl;
}

void *reduceArr(void *mas, const size_t szEl, const largeSize_tp size, void *acc, void (*procEl)(void *acc, const void *masEl))
{
    long long i;
    for(i = 0; i < size; i++, mas += szEl) {
        procEl(acc, mas);
    }
    return acc;
}

void *reduceData(void *data, void *acc, void (*procEl)(void *acc, const void *masEl), void* (*iterate)(void *curEl))
{
    while(data) {
        procEl(acc, data);
        data = iterate(data);
    }
    return acc;
}







int Appropriate(void *mas, const size_t szEl, const largeSize_tp size, enum typeAppr type, enum checkRes (*checkEl)(const void *masEl))
{
    long long i;
    long long tmp;

    if(type == ALL_APPR) {
        tmp = 1;
    } else {
        tmp = 0;
    }

    for(i = 0; i < size; i++, mas += szEl)
        if(type == ALL_APPR) {
            tmp &= checkEl(mas);
        } else if(type == ANY_APPR) {
            tmp |= checkEl(mas);
        } else if(type == CNT_APPR) {
            tmp += checkEl(mas);
        }

    return tmp;
}

int AppropriateData(void *data, enum typeAppr type, enum checkRes (*checkEl)(const void *masEl), void* (*iterate)(void *curEl))
{
    long long tmp;

    if(type == ALL_APPR) {
        tmp = 1;
    } else {
        tmp = 0;
    }

    while(data){
        if(type == ALL_APPR) {
            tmp &= checkEl(data);
        } else if(type == ANY_APPR) {
            tmp |= checkEl(data);
        } else if(type == CNT_APPR) {
            tmp += checkEl(data);
        }
        data = iterate(data);
    }

    return tmp;
}





void *filterArr(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, largeSize_tp *newsize, enum checkRes (*checkEl)(const void *masEl))
{
    long long i;
    void *tmpptr = newmas;
    *newsize = 0;

    for(i = 0; i < size; i++, mas += szEl)
        if(checkEl(mas) == 1) {
            memcpy(newmas, mas, szEl);
            newmas += szEl;
            (*newsize)++;
        }

    newmas = tmpptr;
    newmas = realloc(newmas, szEl * (*newsize));
    return newmas;
}





void sumArraysEl(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num)
{
    *(double*)resEl = (*(double*)masEl1) + (*(double*)masEl2);
}
void mulArraysEl(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num)
{
    *(double*)resEl = (*(double*)masEl1) * (*(double*)masEl2);
}

void *procArrays(void *mas1, void *mas2, void *newmas, const size_t szEl, const largeSize_tp size,
                 void (*procEl)(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num))
{
    long long i;
    void *tmpptr = newmas;

    for(i = 0; i < size; i++, mas1 += szEl, mas2 += szEl, newmas += szEl) {
        procEl(mas1, mas2, newmas, i);
    }

    return tmpptr;
}


