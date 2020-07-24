#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <assert.h>

#include "array.h"

//Размеры массивов
#define SZMI 10
#define SZMF 7
#define SZMD 8
#define SZMCx1 2
#define SZMCx2 3
#define SZPR   4
//Макроопределение создания комплексного числа
#define CMPLX(x, y) ((double complex) ((double) (x) + I*(double) (y)))

struct Person {
    char name[20];
    unsigned age;
};

//Пользовательская функция для вывода структуры
void printPers(const void *arg)
{
    printf("Возраст человека по имени %s - %d\n", (*(struct Person*)arg).name, (*(struct Person*)arg).age);
}

//Пользовательские функции для заполнения массива
void setSinX(void *masEl, long long num)
{
    *(float*)masEl = sin(num);
}
void setCosX(void *masEl, long long num)
{
    *(double*)masEl = cos(num);
}
void setCmplx(void *masEl, long long num)
{
    *(double complex*)masEl = CMPLX(cosh((double)num), sinh((double)num));
}

//Пользовательские функции для обработки массива
void squareFlt(void *masEl){
    *(float*)masEl = pow(*(float*)masEl,2.0);
}
void squareDbl(void *masEl){
    *(double*)masEl = pow(*(double*)masEl,2.0);
}
void growOld(void *masEl){
    ((struct Person*)masEl)->age +=10;
}

//Пользовательские функции для редукции массива
void sumAge(void *acc, const void *masEl){
    *(int*)acc += ((struct Person*)masEl)->age;
}

//Функции условия (должны возвращать RES_NOT или RES_OK)
enum checkRes isOdd(const void *masEl){
    if(*(int*)masEl % 2)
        return RES_OK;
    else
        return RES_NOT;
}
enum checkRes lessMillion(const void *masEl){
    if(*(float*)masEl < 1)
        return RES_OK;
    else
        return RES_NOT;
}
enum checkRes olderFifty(const void *masEl){
    if(((struct Person*)masEl)->age > 30)
        return RES_OK;
    else
        return RES_NOT;
}

//Пользовательские функции фильтрации
enum checkRes biggerOne(const void *masEl){
    if(cabs(*(double complex*)masEl) > 3)
        return RES_OK;
    else
        return RES_NOT;
}

//Пользовательская функция обработки двух массивов
void mergeArr(const void *masEl1, const void *masEl2, void *resEl, long long num){
    if((*(double*)masEl1) * 5 > 3)
        *(double*)resEl = *(double*)masEl1;
    else
        *(double*)resEl = *(double*)masEl2;
}

//Пользовательская функция произведения элемента на его номер
void newMasd(void *masEl, long long num)
{
    *(double*)masEl = (*(double*)masEl) * num;
}

int main()
{
    setlocale(LC_ALL, "rus");

    //Создание и инициализация массивов
    int masi[SZMI];
    setArrStepTwc(masi, SZMI);

    float masf[SZMF];
    setArr(masf, sizeof(masf[0]), SZMF, setSinX);

    double masd[SZMD];
    setArrl(masd, SZMD, setCosX);

    double complex mascx[SZMCx1][SZMCx2];
    setArrt(mascx, SZMCx1 * SZMCx2, setCmplx);

    struct Person persons[SZPR] = {
        {"Павел", 24},
        {"Вася", 15},
        {"Николай", 37},
        {"Дарья", 82}
    };


    //Тест вывода различных массивов
    aprintli(masi, SZMI, "Массив int:");
    aprintl(masi, SZMI, "Массив int:", printInt);

    aprintlf(masf, SZMF, "Массив float:");
    aprintl(masf, SZMF, "Массив float:", printFlt);

    aprintld(masd, SZMD, "Массив double:");
    aprintl(masd, SZMD, "Массив double:", printDbl);

    aprintle(masd, SZMD, "Массив double в Exp виде:");
    aprintl(masd, SZMD, "Массив double в Exp виде:", printExp);

    aprintc(mascx, SZMCx1, SZMCx2, "Массив complex:");
    aprintt(mascx, SZMCx1, SZMCx2, "Массив complex:", printCmplx);

    aprint(persons, sizeof(persons[0]), 1, SZPR, "Массив данных о людях:", printPers);

    //Тест функций обработки массива
    mapArrMcr(masi,SZMI,exp);
    mapArr(masf,sizeof(masf[0]),SZMF,squareFlt);
    mapArrl(persons,SZPR,growOld);

    //Вывод результатов
    aprintli(masi, SZMI, "Экспоненцированный массив int:");
    aprintlf(masf, SZMF, "Возведённый в квадрат массив float:");
    aprintl(persons, SZPR, "Массив данных о состарившихся людях:", printPers);

    //Тест функций редукции
    int acci;
    sumArrElMcr(masi,SZMI,acci);
    printf("Сумма элементов массива int - %d\n",acci);

    double accd = 1;
    reduceArr(masd,sizeof(masd[0]),SZMD,&accd,mulDblArrEl);
    printf("Произведение элементов массива double - %f\n",accd);

    int accp = 0;
    reduceArrl(persons,SZPR,&accp,sumAge);
    printf("Средний возраст людей - %.3f\n",(float)accp/SZPR);
    printf("\n");

    //Тест функций возвращающих число зависящее от соответствия элементов массива функции-условию
    int resi = allApprl(masi,SZMI,isOdd);
    printf("Все элементы массива int нечетные - %d\n",resi);

    int resf = anyApprl(masf,SZMF,lessMillion);
    printf("Все элементы массива float меньше 1 - %d\n",resf);

    int resp = cntApprl(persons,SZPR,olderFifty);
    printf("Число людей старше 30 - %d\n",resp);
    printf("\n");

    //Тест функций фильтраций
    long long newszmi;
    int *evenNum = NULL;
    evenNum = malloc(sizeof(int)*SZMI);
    assert(evenNum);

    long long newszcx;
    double complex *newCmplx = NULL;
    newCmplx = malloc(sizeof(double complex)*SZMCx1*SZMCx2);
    assert(newCmplx);

    filterArrl(masi,evenNum,SZMI,&newszmi,isOdd);
    filterArrt(mascx,newCmplx,SZMCx1*SZMCx2,&newszcx,biggerOne);

    aprintli(evenNum,newszmi,"Нечетные числа массива int:");
    aprintlc(newCmplx,newszcx,"Числа массива complex с модулем большим 3:");
    printf("\n");

    free(evenNum);
    free(newCmplx);

    //Тест функций срезания
    long long szSlice = 4;
    int *slicedArr;
    slicedArr = malloc(sizeof(int)*szSlice);
    assert(slicedArr);

    slicel(masi,slicedArr,2,szSlice);

    aprintli(slicedArr,szSlice,"\nСрез массива int:");
    printf("\n");

    free(slicedArr);

    //Тест функций обработки двух массивов
    double masd2[SZMD] = {1.25, 3.17, 0.12, 1.001, 5.30, 0.28, 9.04, 0.02};
    double *newmasd = NULL;
    newmasd = malloc(sizeof(double)*SZMD);
    assert(newmasd);

    procArraysl(masd,masd2,newmasd,SZMD,mergeArr);

    aprintld(newmasd,SZMD,"\nСлияние массивов double:");
    printf("\n");

    free(newmasd);

    //Тест макроса обнуления
    zeroArrl(masi,SZMI);

    aprintli(masi,SZMI,"\nОбнулённый массив int:");


    //Тест использования функций изменения массива с созданием нового массива
    newmasd = NULL;
    newmasd = malloc(sizeof(double)*SZMD);
    assert(newmasd);

    setArrln(masd,newmasd,SZMD,newMasd);


    aprintld(newmasd,SZMD,"\nПроизведение элементов массива double на номер элемента:");
    printf("\n");

    free(newmasd);


    //Тест использования функций обработки массива с созданием нового массива
    newmasd = NULL;
    newmasd = malloc(sizeof(double)*SZMD);
    assert(newmasd);

    mapArrln(masd,newmasd,SZMD,squareDbl);


    aprintld(newmasd,SZMD,"\nКвадрат элементов массива double:");
    printf("\n");

    free(newmasd);

    return 0;
}
