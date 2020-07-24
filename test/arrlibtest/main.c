#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <assert.h>

#include "array.h"

//������� ��������
#define SZMI 10
#define SZMF 7
#define SZMD 8
#define SZMCx1 2
#define SZMCx2 3
#define SZPR   4
//���������������� �������� ������������ �����
#define CMPLX(x, y) ((double complex) ((double) (x) + I*(double) (y)))

struct Person {
    char name[20];
    unsigned age;
};

//���������������� ������� ��� ������ ���������
void printPers(const void *arg)
{
    printf("������� �������� �� ����� %s - %d\n", (*(struct Person*)arg).name, (*(struct Person*)arg).age);
}

//���������������� ������� ��� ���������� �������
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

//���������������� ������� ��� ��������� �������
void squareFlt(void *masEl){
    *(float*)masEl = pow(*(float*)masEl,2.0);
}
void squareDbl(void *masEl){
    *(double*)masEl = pow(*(double*)masEl,2.0);
}
void growOld(void *masEl){
    ((struct Person*)masEl)->age +=10;
}

//���������������� ������� ��� �������� �������
void sumAge(void *acc, const void *masEl){
    *(int*)acc += ((struct Person*)masEl)->age;
}

//������� ������� (������ ���������� RES_NOT ��� RES_OK)
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

//���������������� ������� ����������
enum checkRes biggerOne(const void *masEl){
    if(cabs(*(double complex*)masEl) > 3)
        return RES_OK;
    else
        return RES_NOT;
}

//���������������� ������� ��������� ���� ��������
void mergeArr(const void *masEl1, const void *masEl2, void *resEl, long long num){
    if((*(double*)masEl1) * 5 > 3)
        *(double*)resEl = *(double*)masEl1;
    else
        *(double*)resEl = *(double*)masEl2;
}

//���������������� ������� ������������ �������� �� ��� �����
void newMasd(void *masEl, long long num)
{
    *(double*)masEl = (*(double*)masEl) * num;
}

int main()
{
    setlocale(LC_ALL, "rus");

    //�������� � ������������� ��������
    int masi[SZMI];
    setArrStepTwc(masi, SZMI);

    float masf[SZMF];
    setArr(masf, sizeof(masf[0]), SZMF, setSinX);

    double masd[SZMD];
    setArrl(masd, SZMD, setCosX);

    double complex mascx[SZMCx1][SZMCx2];
    setArrt(mascx, SZMCx1 * SZMCx2, setCmplx);

    struct Person persons[SZPR] = {
        {"�����", 24},
        {"����", 15},
        {"�������", 37},
        {"�����", 82}
    };


    //���� ������ ��������� ��������
    aprintli(masi, SZMI, "������ int:");
    aprintl(masi, SZMI, "������ int:", printInt);

    aprintlf(masf, SZMF, "������ float:");
    aprintl(masf, SZMF, "������ float:", printFlt);

    aprintld(masd, SZMD, "������ double:");
    aprintl(masd, SZMD, "������ double:", printDbl);

    aprintle(masd, SZMD, "������ double � Exp ����:");
    aprintl(masd, SZMD, "������ double � Exp ����:", printExp);

    aprintc(mascx, SZMCx1, SZMCx2, "������ complex:");
    aprintt(mascx, SZMCx1, SZMCx2, "������ complex:", printCmplx);

    aprint(persons, sizeof(persons[0]), 1, SZPR, "������ ������ � �����:", printPers);

    //���� ������� ��������� �������
    mapArrMcr(masi,SZMI,exp);
    mapArr(masf,sizeof(masf[0]),SZMF,squareFlt);
    mapArrl(persons,SZPR,growOld);

    //����� �����������
    aprintli(masi, SZMI, "������������������ ������ int:");
    aprintlf(masf, SZMF, "���������� � ������� ������ float:");
    aprintl(persons, SZPR, "������ ������ � ������������� �����:", printPers);

    //���� ������� ��������
    int acci;
    sumArrElMcr(masi,SZMI,acci);
    printf("����� ��������� ������� int - %d\n",acci);

    double accd = 1;
    reduceArr(masd,sizeof(masd[0]),SZMD,&accd,mulDblArrEl);
    printf("������������ ��������� ������� double - %f\n",accd);

    int accp = 0;
    reduceArrl(persons,SZPR,&accp,sumAge);
    printf("������� ������� ����� - %.3f\n",(float)accp/SZPR);
    printf("\n");

    //���� ������� ������������ ����� ��������� �� ������������ ��������� ������� �������-�������
    int resi = allApprl(masi,SZMI,isOdd);
    printf("��� �������� ������� int �������� - %d\n",resi);

    int resf = anyApprl(masf,SZMF,lessMillion);
    printf("��� �������� ������� float ������ 1 - %d\n",resf);

    int resp = cntApprl(persons,SZPR,olderFifty);
    printf("����� ����� ������ 30 - %d\n",resp);
    printf("\n");

    //���� ������� ����������
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

    aprintli(evenNum,newszmi,"�������� ����� ������� int:");
    aprintlc(newCmplx,newszcx,"����� ������� complex � ������� ������� 3:");
    printf("\n");

    free(evenNum);
    free(newCmplx);

    //���� ������� ��������
    long long szSlice = 4;
    int *slicedArr;
    slicedArr = malloc(sizeof(int)*szSlice);
    assert(slicedArr);

    slicel(masi,slicedArr,2,szSlice);

    aprintli(slicedArr,szSlice,"\n���� ������� int:");
    printf("\n");

    free(slicedArr);

    //���� ������� ��������� ���� ��������
    double masd2[SZMD] = {1.25, 3.17, 0.12, 1.001, 5.30, 0.28, 9.04, 0.02};
    double *newmasd = NULL;
    newmasd = malloc(sizeof(double)*SZMD);
    assert(newmasd);

    procArraysl(masd,masd2,newmasd,SZMD,mergeArr);

    aprintld(newmasd,SZMD,"\n������� �������� double:");
    printf("\n");

    free(newmasd);

    //���� ������� ���������
    zeroArrl(masi,SZMI);

    aprintli(masi,SZMI,"\n��������� ������ int:");


    //���� ������������� ������� ��������� ������� � ��������� ������ �������
    newmasd = NULL;
    newmasd = malloc(sizeof(double)*SZMD);
    assert(newmasd);

    setArrln(masd,newmasd,SZMD,newMasd);


    aprintld(newmasd,SZMD,"\n������������ ��������� ������� double �� ����� ��������:");
    printf("\n");

    free(newmasd);


    //���� ������������� ������� ��������� ������� � ��������� ������ �������
    newmasd = NULL;
    newmasd = malloc(sizeof(double)*SZMD);
    assert(newmasd);

    mapArrln(masd,newmasd,SZMD,squareDbl);


    aprintld(newmasd,SZMD,"\n������� ��������� ������� double:");
    printf("\n");

    free(newmasd);

    return 0;
}
