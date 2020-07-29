#ifndef __ARRAYDLL_H__
#define __ARRAYDLL_H__

#include <windows.h>

/*  To use this exported function of dll, include this header
 *  in your project.
 */

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif


#ifdef __cplusplus
extern "C"
{
#endif

/**
    \file
    \brief ������������ ���� ����������
    \details ��������� � ����� ��� ���� ������� ���������:
    \param mas (��� �� mas1 � mas2) - ��� ��������� �� ������������� �������� �������.
    \param newmas - ��� ��������� �� ������ � ������� ����� ������������ ���������.
    \param szEl - ��� ������ ��������������� �������� �������.
    \param size (��� �� size1 � size2 ��� newsize) - ��� ����� ��������� � �������.
    \param iterate - ��������� �� ������� ������������ ����� ���������� ���������, NULL - ����-������
    \details �������� ��������� ��� �������:\n
    New - �������� ��� ��� ������ ��������� ����� ������������ � ����� ������.\n
    Data - �������� ������ � ����� ���������� ������ � �������� ������� �������� ��� ���������
    \warning ������ ��� ����� ������ ������ ���� ��������!
    \details �������� ��������� ��� ��������:\n
    l(�����) - �������� ������ � ���������� ��������.
    \warning ������ � ��������� �������� � ������� �������� � ��������� l ������� � ����!
    \details t - �������� ������ � ��������� ��������.\n
    n - �������� ��� ��� ������ ��������� ����� ������������ � ����� ������.
    \warning ������ ��� ����� ������ ������ ���� ��������!
    \details i - �������� ������ � ����� int.\n
    f - �������� ������ � ����� float.\n
    d - �������� ������ � ����� double.\n
    e - �������� ������ � ����� double � ���������������� ����.\n
    c - �������� ������ � ����� complex.
    d - �������� ������ � ����� ���������� ������
*/

#include <memory.h>

/**\brief ����������� ��� ��� ������� ����� ������� ��������*/
typedef unsigned long long largeSize_tp;


/** @name ��������������� ������� ��� ������ �������
* \brief ����������������� ��������������� ������� ��� ������ �������
* \param arg ��������� �� �������� ������� ����� �������.
* \details ������� ������ ��� ������ �������� ������� �����.
* ����� ������� ����������� ������������ ������� ��� ������ �������� ������ ����.
* \example ������_�������_������_��������
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
* \brief ������� ������ �������
* \param title ��������� �� ������ ��������� ����������� �������.
* \param print ��������� �� ������� ���������� ������� ������������ ����.
* \details ������� ������������� ��� ���������������� ������ ����������� ��� ���������� �������.
*/
void aprint(void *mas, const size_t szEl, const largeSize_tp size1, const largeSize_tp size2, const char *title,
            void (*print)(const void *arg));
/*������� ������ ���������� ������� ������������ ����*/
#define aprinti(mas,size1,size2,title) aprint((mas),sizeof(int),(size1),(size2),(title),printInt);
#define aprintf(mas,size1,size2,title) aprint((mas),sizeof(float),(size1),(size2),(title),printFlt);
#define aprintd(mas,size1,size2,title) aprint((mas),sizeof(double),(size1),(size2),(title),printDbl);
#define aprinte(mas,size1,size2,title) aprint((mas),sizeof(double),(size1),(size2),(title),printExp);
#define aprintc(mas,size1,size2,title) aprint((mas),sizeof(double complex),(size1),(size2),(title),printCmplx);
/*������ ������ ����������� �������*/
#define aprintl(mas,size,title,print) aprint((mas),sizeof(mas[0]),1,(size),(title),(print));
/*������ ������ ���������� �������*/
#define aprintt(mas,size1,size2,title,print) aprint((mas),sizeof(mas[0][0]),(size1),(size2),(title),(print));
/*������� ������ ����������� ������� ������������ ����*/
#define aprintli(mas,size,title) aprint((mas),sizeof(int),1,(size),(title),printInt);
#define aprintlf(mas,size,title) aprint((mas),sizeof(float),1,(size),(title),printFlt);
#define aprintld(mas,size,title) aprint((mas),sizeof(double),1,(size),(title),printDbl);
#define aprintle(mas,size,title) aprint((mas),sizeof(double),1,(size),(title),printExp);
#define aprintlc(mas,size,title) aprint((mas),sizeof(double complex),1,(size),(title),printCmplx);
/**
* \brief ������� ������ ��������� ������
* \param title ��������� �� ������ ��������� ���������� ��������� ������.
* \param print ��������� �� ������� ���������� ������� ������������ ����.
* \details ������� ������������� ��� ���������������� ������ ��������� ������.
*/
void dprint(void *data, const char *title, void (*print)(const void *arg), void* (*iterate)(void *curEl));

/** @name ��������������� ������� ��� ���������� �������
* \brief ����������������� ��������������� ������� ��� ���������� �������
* \param masEl ��������� �� ������� ������� �������� �������� ����� ��������.
* \param num ���������� ����� ��������.
* \details ������� ������ ��� ���������� ������� ����������� �������.\n
* step - ��������� ������ ������� �� �������.\n
* stepTwc - �� �� �� � ������� �����.\n
* ������� � ��������� Rnd - ��������� ���������� �������.
* ����� ������� ����������� ����������� �������.
* \example ������_�������_���������_��������
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
* \brief ������� ��������� ��������� ������� � ����������� �� �� �������
* \param setEl ��������� �� ������� ���������� ������� ������������ ����.\n
* ������� ��������� � �������� ���������� ��������� �� ������� ������� � ��� �����\n
* � �������� ���� ������� ����������� �������.
* \result ���������� ��������� �� ��������� ������
*/
void *setArr(void *mas, const size_t szEl, const largeSize_tp size, void (*setEl)(void* masEl, largeSize_tp num));
/*������� ��� ��������� ��������� ������� � ����������� �� ������ ��������  � ��������� ������ �������*/
void *setArrNew(void *mas, void *newmas, const size_t szEl, const largeSize_tp size,
                void (*setEl)(void* masEl, largeSize_tp num));
/*������ ��������� ��������� ����������� �������*/
#define setArrl(mas,size,func) setArr((mas),sizeof(mas[0]),(size),(func));
#define setArrln(mas,newmas,size,func) setArrNew((mas),(newmas),sizeof(mas[0]),(size),(func));
/*������ ��������� ��������� ���������� �������*/
#define setArrt(mas,size,func) setArr((mas),sizeof(mas[0][0]),(size),(func));
#define setArrtn(mas,newmas,size,func) setArrNew((mas),(newmas),sizeof(mas[0][0]),(size),(func));
/** @name ������� ���������� �������
* \brief ������� ���������� ������� ������������ ����
*/
/** @{ */
#define setArrStep(mas,size) setArr((mas),sizeof(int),(size),step);
#define setArrStepTwc(mas,size) setArr((mas),sizeof(int),(size),stepTwc);
#define setArrRnd(mas,size) setArr((mas),sizeof(int),(size),setRnd);
#define setArrDblRnd(mas,size) setArr((mas),sizeof(double),(size),setDblRnd);
/** @} */
/*������� ���������� ��������� ������*/
void *setData(void *data, void (*setEl)(void* masEl, largeSize_tp num), void* (*iterate)(void *curEl));


/**
* \brief ���������������� ������� ��������� ������� ��� ������� ������� ���������
*/
#define mapArrMcr(mas,size,func) {\
                                    long long i;\
                                    for(i = 0;i < (size);i++)\
                                        mas[i] = func(mas[i]);\
                                }
/**
* \brief ������� ��������� ��������� �������
* \param procEl ��������� �� ������� �������������� ������� ������������ ����.\n
* ������� ��������� � �������� ���������� ��������� �� ������� �������\n
* � �������� ���� ������� ����������� �������.
* \result ���������� ��������� �� ������������ ������
*/
void *mapArr(void *mas, const size_t szEl, const largeSize_tp size, void (*procEl)(void *masEl));
/*������� ��������� ��������� ������� � ��������� ������ �������*/
void *mapArrNew(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, void (*procEl)(void *masEl));
/*������ ��������� ��������� ����������� �������*/
#define mapArrl(mas,size,func) mapArr((mas),sizeof(mas[0]),(size),(func));
#define mapArrln(mas,newmas,size,func) mapArrNew((mas),(newmas),sizeof(mas[0]),(size),(func));
/*������ ��������� ��������� ���������� �������*/
#define mapArrt(mas,size,func) mapArr((mas),sizeof(mas[0][0]),(size),(func));
#define mapArrtn(mas,newmas,size,func) mapArrNew((mas),(newmas),sizeof(mas[0][0]),(size),(func));
/*������� ��������� ��������� ��������� ������*/
void *mapData(void *data, void (*procEl)(void *masEl), void* (*iterate)(void *curEl));

/** @name ��������������� ������� �������� �������
* \brief ������� ������������ � ������������ ��������� �������
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

/** @name ��������������� ������� ��� �������� �������
* \brief ����������������� ��������������� ������� ��� �������� �������
* \param acc ���������� �����������.
* \param masEl ��������� �� ������� �������.
* \details ������� ������ ��� �������� ������� ����������� �������.
* \example ������_�������_��������_��������
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
* \brief ������� �������� �������
* \param procEl ��������� �� ������� �������� ������� ������������ ����.\n
* ������� ��������� � �������� ���������� ��������� �� ������� ������� � ��������� �� �����������\n
* � �������� ����������� ����������� �������.
* \result ���������� ��������� �� �����������
*/
void *reduceArr(void *mas, const size_t szEl, const largeSize_tp size, void *acc,
                void (*procEl)(void *acc, const void *masEl));
/*������ �������� ����������� �������*/
#define reduceArrl(mas,size,acc,func) reduceArr((mas),sizeof(mas[0]),(size),(acc),(func));
/*������ �������� ���������� �������*/
#define reduceArrt(mas,size,acc,func) reduceArr((mas),sizeof(mas[0][0]),(size),(acc),(func));
/*������� �������� ��������� ��������� ������*/
void *reduceData(void *data, void *acc, void (*procEl)(void *acc, const void *masEl), void* (*iterate)(void *curEl));

/** ������������ �������� ��������� ������������ ��������� ������� ���������� �������*/
enum checkRes {
    RES_OK = 1, /**< ������������� */
    RES_NOT = 0, /**< �� ������������� */
};
/** ������������ �������� ��� ������������ ��������� ������� ���������� �������*/
enum typeAppr {
    ALL_APPR, /**< ��� �������� ������������� */
    ANY_APPR, /**< ���� �� ���� ������� ������������� */
    CNT_APPR  /**< ����������� ����� ��������� ������������� */
};
/**
* \brief ������� ������������ ����� ��������� �� ������������ ��������� ������� �������-�������
* \param type ��� ������������.\n
* \param checkEl ��������� �� ������� �������� ������������ �������� ������� ������������ �������.\n
* ������� ��������� � �������� ���������� ��������� �� ������� �������\n
* � ���������� RES_NOT � ������ �������������� � RES_OK � ������ ������������.
* \result ���������� ��� ������� ������������/�������������� ��� ����� ��������������� ���������\n
* � ����������� �� ���� ������������
*/
int Appropriate(void *mas, const size_t szEl, const largeSize_tp size, enum typeAppr type,
                enum checkRes (*checkEl)(const void *masEl));
/*������ ����������� ��� �� �������� ������� ������������� �������-�������*/
#define allApprl(mas,size,func) Appropriate((mas),sizeof(mas[0]),(size),ALL_APPR,(func));
#define allApprt(mas,size,func) Appropriate((mas),sizeof(mas[0][0]),(size),ALL_APPR,(func));
/*������ ����������� ���� �� �������� ������� ��������������� �������-�������*/
#define anyApprl(mas,size,func) Appropriate((mas),sizeof(mas[0]),(size),ANY_APPR,(func));
#define anyApprt(mas,size,func) Appropriate((mas),sizeof(mas[0][0]),(size),ANY_APPR,(func));
/*������ �������������� ����� ��������� ������� ��������������� �������-�������*/
#define cntApprl(mas,size,func) Appropriate((mas),sizeof(mas[0]),(size),CNT_APPR,(func));
#define cntApprt(mas,size,func) Appropriate((mas),sizeof(mas[0][0]),(size),CNT_APPR,(func));
int AppropriateData(void *data, enum typeAppr type, enum checkRes (*checkEl)(const void *masEl), void* (*iterate)(void *curEl));
/*������ ����������� ��� �� �������� ������� ������������� �������-�������*/
#define allApprd(mas,func,iter) AppropriateData((mas),ALL_APPR,(func),(iter));
/*������ ����������� ���� �� �������� ������� ��������������� �������-�������*/
#define anyApprd(mas,func,iter) AppropriateData((mas),ANY_APPR,(func),(iter));
/*������ �������������� ����� ��������� ������� ��������������� �������-�������*/
#define cntApprd(mas,func,iter) AppropriateData((mas),CNT_APPR,(func),(iter));

/**
* \brief ������� ����������� ������ �� ������������ �������
* \param checkEl ��������� �� ������� �������� ������������ �������� ������� ������������ �������.\n
* ������� ��������� � �������� ���������� ��������� �� ������� �������\n
* � ���������� RES_NOT � ������ �������������� � RES_OK � ������ ������������.
* \result ���������� ��������� �� ����� ������.
*/
void *filterArr(void *mas, void *newmas, const size_t szEl, const largeSize_tp size, largeSize_tp *newsize,
                enum checkRes (*checkEl)(const void *masEl));
/*������� ��� ���������� ������� ���������� ��� ���������� � ��������� ��������*/
#define filterArrl(mas,newmas,size,newsize,func) filterArr((mas),(newmas),sizeof(mas[0]),(size),(newsize),(func));
#define filterArrt(mas,newmas,size,newsize,func) filterArr((mas),(newmas),sizeof(mas[0][0]),(size),(newsize),(func));

/** @name ������� ��� ���������� ������ ��������
* \brief ������� ��� ���������� ������ ��������
*/
/** @{ */
#define slicel(mas,newmas,num1,len) memcpy((newmas),(mas) + (num1),len * sizeof(mas[0]));
#define slicet(mas,newmas,num1,len) memcpy((newmas),(mas) + (num1),len * sizeof(mas[0][0]));
/** @} */

/** @name ��������������� ������� ��� ��������� ���� ��������
* \brief ����������������� ��������������� ������� ��� ��������� ���� ��������
* \param masEl1,masEl2 ��������� �� ������� �������.
* \param resEl ��������� �� ������� ������� ����������.
* \param num ����� ��������.
* \example ������_�������_���������_����_��������
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
* \brief ������� �������������� ��� ������� � ������������ �����
* \param procEl ��������� �� ������� �������������� 2 �������� ��������.\n
* ������� ��������� � �������� ���������� 2 ��������� �� �������� �������� ��������\n
* � ��������� �� �������-���������, � ����� ���������� ����� ��������.
* \result ���������� ��������� �� ������-���������.
*/
void *procArrays(void *mas1, void *mas2, void *newmas, const size_t szEl, const largeSize_tp size,
                 void (*procEl)(const void *masEl1, const void *masEl2, void *resEl, largeSize_tp num));
/*������� ������� ���������� ������� �� ��������� � ������ ��������� ���� ������ ��������*/
#define procArraysl(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0]),(size),(func));
#define procArrayst(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0][0]),(size),(func));
/** @name ��������������� ������� ��� ����������������� �������
* \brief ��������������� ������� ��� ����������������� �������
*/
/** @{ */
#define sumArraysld(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0]),(size),sumArraysEl);
#define sumArraystd(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0][0]),(size),sumArraysEl);
#define mulArraysld(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0]),(size),mulArraysEl);
#define mulArraystd(mas1,mas2,newmas,size,func) procArrays((mas1),(mas2),(newmas),sizeof(mas1[0][0]),(size),mulArraysEl);
/** @} */

/** @name ������� ��������� �������
* \brief ������� ��������� �������
*/
/** @{ */
#define zeroArrl(mas,size) memset((mas),0,(size*sizeof(mas[0])));
#define zeroArrt(mas,size) memset((mas),0,(size*sizeof(mas[0][0])));
/** @} */

#ifdef __cplusplus
}
#endif

#endif // __ARRAYDLL_H__
