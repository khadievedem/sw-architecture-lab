/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoLab2.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IdEcoComplex1.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoCalculatorC.h"

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    int32_t a, b, N, i;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab2* pIEcoLab2 = 0;

    /* Source vector for dft/fft counting */
    int32_t   *v_src = 0;
    /* Result vector for dft/fft result */
    complex_t *v_res = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
        if (result != 0 && pISys == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
#ifdef ECO_LIB
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab2, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FEFFF2);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoCalculatorC, (IEcoUnknown*)GetIEcoComponentFactoryPtr_4828F6552E4540E78121EBD220DC360E);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }

    /* Регистрация статического компонента для работы с комплексными числами */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoComplex1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FFFFFF);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }
    
    /* Регистрация статического компонента для работы со списком */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
    if (result != 0 ) {
        /* Освобождение в случае ошибки */
        goto Release;
    }


#endif
    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Выделение блока памяти */
    N = 8;
    v_src = (int32_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(int32_t));
    v_res = (complex_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(complex_t));


    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab2, (void**) &pIEcoLab2);
    if (result != 0 || pIEcoLab2 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    a = 20;
    b = 5;
    fprintf(stdout, "%d + %d = %d\n", a, b, pIEcoLab2->pVTbl->Addition(pIEcoLab2, a, b));
    fprintf(stdout, "%d - %d = %d\n", a, b, pIEcoLab2->pVTbl->Subtraction(pIEcoLab2, a, b));
    fprintf(stdout, "%d * %d = %d\n", a, b, pIEcoLab2->pVTbl->Multiplication(pIEcoLab2, a, b));
    fprintf(stdout, "%d / %d = %d\n", a, b, pIEcoLab2->pVTbl->Division(pIEcoLab2, a, b));

    v_src[0] = 1;
    v_src[1] = -1;
    v_src[2] = 1;
    v_src[3] = -1;
    v_src[4] = 5;
    v_src[5] = 4;
    v_src[6] = 3;
    v_src[7] = 2;
    
    fprintf(stdout, "Source array for fft:\n");
    for (i = 0; i < N; ++i) {
        fprintf(stdout, "%d\n", v_src[i]);
    }

    pIEcoLab2->pVTbl->fft(pIEcoLab2, 1, N, v_src, v_res);

    fprintf(stdout, "Result fft array:\n");
    for (i = 0; i < N; ++i) {
        fprintf(stdout, "%.4f + %.4f * i\n", v_res[i].re, v_res[i].im);
    }

    /* Освлбождение блока памяти */
    pIMem->pVTbl->Free(pIMem, v_src);
    pIMem->pVTbl->Free(pIMem, v_res);

Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab2 != 0) {
        pIEcoLab2->pVTbl->Release(pIEcoLab2);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

