/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
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
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"

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
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;

    clock_t t; 
    uint16_t N;
    uint32_t i;
    double time_taken;

    int32_t *v_src;
    double complex *v_res;


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

    N = 8;
    /* Выделение блока памяти */
    v_src = (int32_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(int32_t));
    v_res = (double complex *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(double complex));

    v_src[0] = 1;
    v_src[1] = -1;
    v_src[2] = 1;
    v_src[3] = -1;
    v_src[4] = 5;
    v_src[5] = 4;
    v_src[6] = 3;
    v_src[7] = 2;

    for (i = 0; i < N; ++i) {
      v_res[i] = 0;
    }

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* pIEcoLab1->pVTbl->dft(pIEcoLab1, N, k, v); */
    t = clock(); 
    for (i = 0; i < 1000000; ++i) {
      pIEcoLab1->pVTbl->fft(pIEcoLab1, 1, N, v_src, v_res);
    }
    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("FFT [%f]: \n", time_taken);
    for(i = 0; i < N; ++i)
        printf("%8.4f + %.4fi\n", creal(v_res[i]), cimag(v_res[i]));
    putc('\n', stdout);
    t = clock(); 
    for (i = 0; i < 1000000; ++i) {
      pIEcoLab1->pVTbl->dft(pIEcoLab1, N, v_src, v_res);
    }
    t = clock() - t; 
    time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
    printf("DFT [%f]: \n", time_taken);
    for(i = 0; i < N; ++i)
        printf("%8.4f + %.4fi\n", creal(v_res[i]), cimag(v_res[i]));


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
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

