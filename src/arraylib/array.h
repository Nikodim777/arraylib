#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED

/**
    \file
    \brief Заголовочный файл библиотеки
    \details Аргументы с общим для всех функций значением:
    \param mas (или же mas1 и mas2) - это указатели на обрабатывемые функцией массивы.
    \param newmas - это указатель на массив в который будет записываться результат.
    \param szEl - это размер обрабатываемого элемента массива.
    \param size (или же size1 и size2 или newsize) - это число элементов в массиве.
    \param iterate - указатель на функцию возвращающую адрес следующего элементаы, NULL - стоп-символ.
    \details Значение суффиксов для функций:\n
    New - означает что при работе результат будет записываться в новый массив.\n
    Data - означает работу с любой структурой данных и принятие функции итерации как параметра.
    \warning Память под новый массив должна быть выделена!
    \details Значение суффиксов для макросов:\n
    l(буква) - означает работу с одномерным массивом.
    \warning Работа с двумерным массивом с помощью макросов с суффиксом l приведёт к сбою!
    \details t - означает работу с двумерным массивом.\n
    n - означает что при работе результат будет записываться в новый массив.
    \warning Память под новый массив должна быть выделена!
    \details i - означает работу с типом int.\n
    f - означает работу с типом float.\n
    d - означает работу с типом double.\n
    e - означает работу с типом double в экспоненциальном виде.\n
    c - означает работу с типом complex.\n
    d - означает работу с либой структурой данных.
*/

#include <memory.h>

/**\brief Беззнаковый тип для задания очень больших размеров*/
typedef unsigned long long largeSize_tp;


/** @name Вспомогательные функции для вывода массива
* \brief Предустановленные вспомогательные функции для вывода массива
* \param arg Указатель на значение которое нужно вывести.
* \details Функции служат для вывода значений базовых типов.
* Можно создать аналогичные собзственные функции для вывода значений любого типа.
* \example Пример_функции_вывода_элемента
* void printDbl(const void *arg)\n
* {\n
*     printf("%.6f\t", *(double*)arg);\n
* }
*/
/** @{ */
void printInt(const void *arg);
void printFlt(const void *arg);
void printDbl(const void *arg);
void printExp(const void *arg);
void printCmplx(const void *arg);
/** @} */
/**
* \brief Функция вывода массива
* \param title Указатель на строку заголовка печатаемого массива.
* \param print Указатель на функцию печатающую элемент определённого типа.
* \details Функция предназначена для форматированного вывода одномерного или двумерного массива.
*/
void aprint(void *mas, const size_t szEl, const largeSize_tp size1, const largeSize_tp size2, const char *title,
            void (*print)(const void *arg));
/*Макросы вывода двумерного массива определённого типа*/
#define aprinti(mas,size1,size2,title) aprint((mas),sizeof(int),(size1),(size2),(title),printInt);
#define aprintf(mas,size1,size2,title) aprint((mas),sizeof(float),(size1),(size2),(title),printFlt);
#define aprintd(mas,size1,size2,title) aprint((mas),sizeof(double),(size1),(size2),(title),printDbl);
#define aprinte(mas,size1,size2,title) aprint((mas),sizeof(double),(size1),(size2),(title),printExp);
#define aprintc(mas,size1,size2,title) aprint((mas),sizeof(double complex),(size1),(size2),(title),printCmplx);
/*Макрос вывода одномерного массива*/
#define aprintl(mas,size,title,print) aprint((mas),sizeof(mas[0]),1,(size),(title),(print));
/*Макрос вывода двумерного массива*/
#define aprintt(mas,size1,size2,title,print) aprint((mas),sizeof(mas[0][0]),(size1),(size2),(title),(print));
/*Макросы вывода одномерного массива определённого типа*/
#define aprintli(mas,size,title) aprint((mas),sizeof(int),1,(size),(title),printInt);
#define aprintlf(mas,size,title) aprint((mas),sizeof(float),1,(size),(title),printFlt);
#define aprintld(mas,size,title) aprint((mas),sizeof(double),1,(size),(title),printDbl);
#define aprintle(mas,size,title) aprint((mas),sizeof(double),1,(size),(title),printExp);
#define aprintlc(mas,size,title) aprint((mas),sizeof(double complex),1,(size),(title),printCmplx);
/**
* \brief Функция вывода структуры данных
* \param title Указатель на строку заголовка печатаемой структуры данных.
* \param print Указатель на функцию печатающую элемент определённого типа.
* \details Функция предназначена для форматированного вывода структуры данных.
*/
void dprint(void *data, const char *title, void (*print)(const void *arg), void* (*iterate)(void *curEl));

/** @name Вспомогательные функции для заполнения массива
* \brief Предустановленные вспомогательные функции для заполнения массива
* \param masEl Указатель на элемент массива значение которого нужно изменить.
* \param num Порядковый номер элемента.
* \details Функции служат для заполнения массива обределённым образом.\n
* step - заполняет целыми числами по порядку.\n
* stepTwc - то же но с двойным шагом.\n
* Функции с суффиксом Rnd - заполняют случайными числами.
* Можно создать аналогичные собственные функции.
* \example Пример_функции_изменения_элемента
* void setRnd(void* masEl, largeSize_tp num)\n
* {\n
*     *(int*)masEl = rand() % 100;\n
* }
*/
/** @{ */
void step(void* masEl, largeSize_tp num);
void stepTwc(void* masEl, largeSize_tp num);
void setRnd(void* masEl, largeSize_tp num);
void setDblRnd(void* masEl, largeSize_tp num);
/** @} */
/**
* \brief Функция изменения элементов массива в зависимости от их номеров
* \param setEl Указатель на функцию изменяющую элемент определённого типа.\n
* Функция принимает в качестве параметров указатель на элемент массива и его номер\n
* и изменяет этот элемент определённым образом.
* \result Возвращает указатель на изменённый массив
*/
void *setArr(void *mas, const size_t szEl, const largeSize_tp size, void (*setEl)(void* masEl, largeSize_tp num));
/*Функция для изменения элементов массива в зависимости от номера элемента  с созданием нового массива*/
void *setArrNew(void *mas, void *newmas, const size_t szEl, const largeSize_tp size,
                void (*setEl)(void* masEl, largeSize_tp num));
/*Макрос изменения элементов одномерного массива*/
#define setArrl(mas,size,func) setArr((mas),sizeof(mas[0]),(size),(func));
#define setArrln(mas,newmas,size,func) setArrNew((mas),(newmas),sizeof(mas[0]),(size),(func));
/*Макрос изменения элементов двумерного массива*/
#define setArrt(mas,size,func) setArr((mas),sizeof(mas[0][0]),(size),(func));
#define setArrtn(mas,newmas,size,func) setArrNew((mas),(newmas),sizeof(mas[0][0]),(size),(func));
/** @name Макросы заполнения массива
* \brief Макросы заполнения массива определённого типа
*/
/** @{ */
#define setArrStep(mas,size) setArr((mas),sizeof(int),(size),step);
#define setArrStepTwc(mas,size) setArr((mas),sizeof(int),(size),stepTwc);
#define setArrRnd(mas,size) setArr((mas),sizeof(int),(size),setRnd);
#define setArrDblRnd(mas,size) setArr((mas),sizeof(double),(size),setDblRnd);
/** @} */
/*Функция заполнения структуры данных*/
void *setData(void *data, void (*setEl)(void* masEl, largeSize_tp num), void* (*iterate)(void *curEl));


/**
* \brief Макроопределение функции обработки массива для простых функций обработки
*/
#define mapArrMcr(mas,size,func) {\
                                    long long i;\
                                    for(i = 0;i < (size);i++)\
                                        mas[i] = func(mas[i]);\
                                }
/**
* \brief Функция обработки элементов массива
* \param procEl Указатель на функцию обрабатывающую элемент определённого типа.\n
* Функция принимает в качестве параметров указатель на элемент массива\n
* и изменяет этот элемент определённым образом.
* \result Возвращает указатель на обработанный массив
*/
void *mapArr(void *mas, const size_t szEl, const largeSize_tp size, void (*procEl)(void *masEl));
/*Функция обработки элементов массива с созданием нового массива*/
void *mapArrNew(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, void (*procEl)(void *masEl));
/*Макрос обработки элементов одномерного массива*/
#define mapArrl(mas,size,func) mapArr((mas),sizeof(mas[0]),(size),(func));
#define mapArrln(mas,newmas,size,func) mapArrNew((mas),(newmas),sizeof(mas[0]),(size),(func));
/*Макрос обработки элементов двумерного массива*/
#define mapArrt(mas,size,func) mapArr((mas),sizeof(mas[0][0]),(size),(func));
#define mapArrtn(mas,newmas,size,func) mapArrNew((mas),(newmas),sizeof(mas[0][0]),(size),(func));
/*Функция обработки элементов структуры данных*/
void *mapData(void *data, void (*procEl)(void *masEl), void* (*iterate)(void *curEl));

/** @name Вспомогательные макросы редукции массива
* \brief Макросы суммирования и перемножения элементов массива
*/
/** @{ */
#define sumArrElMcr(mas,size,acc)    {\
                                    long long i;\
                                    acc = 0;\
                                    for(i = 0;i < (size);i++)\
                                        acc += mas[i];\
                                }
#define mulArrElMcr(mas,size,acc)    {\
                                    long long i;\
                                    acc = 1;\
                                    for(i = 0;i < (size);i++)\
                                        acc *= mas[i];\
                                }
/** @} */

/** @name Вспомогательные функции для редукции массива
* \brief Предустановленные вспомогательные функции для редукции массива
* \param acc Переменная аккумулятор.
* \param masEl Указатель на элемент массива.
* \details Функции служат для редукции массива определённым образом.
* \example Пример_функции_редукции_элемента
* void mulDblArrEl(void *acc, const void *masEl)\n
* {\n
*     *(double*)acc *= *(double*)masEl;\n
* }
*/
/** @{ */
void sumArrEl(void *acc, const void *masEl);
void sumDblArrEl(void *acc, const void *masEl);
void mulArrEl(void *acc, const void *masEl);
void mulDblArrEl(void *acc, const void *masEl);
/** @} */
/**
* \brief Функция редукции массива
* \param procEl Указатель на функцию редукции массива определённого типа.\n
* Функция принимает в качестве параметров указатель на элемент массива и указатель на аккумулятор\n
* и изменяет аккумулятор определённым образом.
* \result Возвращает указатель на аккумулятор
*/
void *reduceArr(void *mas, const size_t szEl, const largeSize_tp size, void *acc,
                void (*procEl)(void *acc, const void *masEl));
/*Макрос редукции одномерного массива*/
#define reduceArrl(mas,size,acc,func) reduceArr((mas),sizeof(mas[0]),(size),(acc),(func));
/*Макрос редукции двумерного массива*/
#define reduceArrt(mas,size,acc,func) reduceArr((mas),sizeof(mas[0][0]),(size),(acc),(func));
/*Функция редукции элементов структуры данных*/
void *reduceData(void *data, void *acc, void (*procEl)(void *acc, const void *masEl), void* (*iterate)(void *curEl));

/** Перечисление хранящее результат соответствия элементов массива некоторому условию*/
enum checkRes {
    RES_OK = 1, /**< Соответствует */
    RES_NOT = 0, /**< Не соответствует */
};
/** Перечисление хранящее тип соответствия элементов массива некоторому условию*/
enum typeAppr {
    ALL_APPR, /**< Все элементы соответствуют */
    ANY_APPR, /**< Хотя бы один элемент соответствуют */
    CNT_APPR  /**< Определённое число элементов соответствуют */
};
/**
* \brief Функция возвращающая число зависящее от соответствия элементов массива функции-условию
* \param type Тип соответствия.\n
* \param checkEl Указатель на функцию проверки соответствия элемента массива определённому условию.\n
* Функция принимает в качестве параметров указатель на элемент массива\n
* и возвращает RES_NOT в случае несоответствия и RES_OK в случае соответствия.
* \result Возвращает или признак соответствия/несоответствия или число соответствующих элементов\n
* в зависимости от типа соответствия
*/
int Appropriate(void *mas, const size_t szEl, const largeSize_tp size, enum typeAppr type,
                enum checkRes (*checkEl)(const void *masEl));
/*Макрос проверяющая все ли элементы массива соответствуют функции-условию*/
#define allApprl(mas,size,func) Appropriate((mas),sizeof(mas[0]),(size),ALL_APPR,(func));
#define allApprt(mas,size,func) Appropriate((mas),sizeof(mas[0][0]),(size),ALL_APPR,(func));
/*Макрос проверяющая есть ли элементы массива соответствующие функции-условию*/
#define anyApprl(mas,size,func) Appropriate((mas),sizeof(mas[0]),(size),ANY_APPR,(func));
#define anyApprt(mas,size,func) Appropriate((mas),sizeof(mas[0][0]),(size),ANY_APPR,(func));
/*Макрос подсчитывающая число элементов массива соответствующих функции-условию*/
#define cntApprl(mas,size,func) Appropriate((mas),sizeof(mas[0]),(size),CNT_APPR,(func));
#define cntApprt(mas,size,func) Appropriate((mas),sizeof(mas[0][0]),(size),CNT_APPR,(func));
int AppropriateData(void *data, enum typeAppr type, enum checkRes (*checkEl)(const void *masEl), void* (*iterate)(void *curEl));
/*Макрос проверяющая все ли элементы массива соответствуют функции-условию*/
#define allApprd(mas,func,iter) AppropriateData((mas),ALL_APPR,(func),(iter));
/*Макрос проверяющая есть ли элементы массива соответствующие функции-условию*/
#define anyApprd(mas,func,iter) AppropriateData((mas),ANY_APPR,(func),(iter));
/*Макрос подсчитывающая число элементов массива соответствующих функции-условию*/
#define cntApprd(mas,func,iter) AppropriateData((mas),CNT_APPR,(func),(iter));

/**
* \brief Функция фильтрующая массив по определённому условию
* \param checkEl Указатель на функцию проверки соответствия элемента массива определённому условию.\n
* Функция принимает в качестве параметров указатель на элемент массива\n
* и возвращает RES_NOT в случае несоответствия и RES_OK в случае соответствия.
* \result Возвращает указатель на новый массив.
*/
void *filterArr(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, largeSize_tp *newsize,
                enum checkRes (*checkEl)(const void *masEl));
/*Макросы для реализации функций фильтрации для одномерных и двумерных массивов*/
#define filterArrl(mas,newmas,size,newsize,func) filterArr((mas),(newmas),sizeof(mas[0]),(size),(newsize),(func));
#define filterArrt(mas,newmas,size,newsize,func) filterArr((mas),(newmas),sizeof(mas[0][0]),(size),(newsize),(func));

/** @name Макросы для реализации срезов массивов
* \brief Макросы для реализации срезов массивов
*/
/** @{ */
#define slicel(mas,newmas,num1,len) memcpy((newmas),(mas) + (num1),len * sizeof(mas[0]));
#define slicet(mas,newmas,num1,len) memcpy((newmas),(mas) + (num1),len * sizeof(mas[0][0]));
/** @} */

/** @name Вспомогательные функции для обработки двух массивов
* \brief Предустановленные вспомогательные функции для обработки двух массивов
* \param masEl1,masEl2 Указатели на элемент массива.
* \param resEl Указатель на элемент массива результата.
* \param num Номер элемента.
* \example Пример_функции_обработки_двух_массивов
* void sumArraysEl(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num)\n
* {\n
*     *(double*)resEl = (*(double*)masEl1) + (*(double*)masEl2);\n
* }
*/
/** @{ */
void sumArraysEl(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num);
void mulArraysEl(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num);
/** @} */

/**
* \brief Функция обрабатывающая два массива и возвращающая новый
* \param procEl Указатель на функцию обрабатывающую 2 элемента массивов.\n
* Функция принимает в качестве параметров 2 указателя на элементы исходных массивов\n
* и указатель на элемент-результат, а также порядковый номер элемента.
* \result Возвращает указатель на массив-результат.
*/
void *procArrays(void *mas1, void *mas2, void *newmas, const size_t szEl, const largeSize_tp size,
                 void (*procEl)(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num));
/*Макросы функций вычисления массива по элементам и номеру элементов двух других массивов*/
#define procArraysl(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0]),(size),(func));
#define procArrayst(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0][0]),(size),(func));
/** @name Вспомогательные макросы для предустановленных функций
* \brief Вспомогательные макросы для предустановленных функций
*/
/** @{ */
#define sumArraysld(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0]),(size),sumArraysEl);
#define sumArraystd(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0][0]),(size),sumArraysEl);
#define mulArraysld(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0]),(size),mulArraysEl);
#define mulArraystd(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0][0]),(size),mulArraysEl);
/** @} */

/** @name Макросы обнуления массива
* \brief Макросы обнуления массива
*/
/** @{ */
#define zeroArrl(mas,size) memset((mas),0,(size*sizeof(mas[0])));
#define zeroArrt(mas,size) memset((mas),0,(size*sizeof(mas[0][0])));
/** @} */

#endif
