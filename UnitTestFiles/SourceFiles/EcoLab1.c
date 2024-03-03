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
#include "IdEcoDateTime1.h"
#include "IdEcoComplex1.h"
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
    /* Указатель на интерфейс рабоns со временем */
    IEcoDateTime1* pIDTime = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1 = 0;
    /* Source vector for dft/fft counting */
    int32_t   *v_src = 0;
    /* Result vector for dft/fft result */
    complex_t *v_res = 0;

    ECOTIMEVAL t_start, t_end;
    double_t time_taken;

    uint32_t i, j, N;


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
    /* Регистрация статического компонента для работы со временем */
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoDateTime1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_5B2BA17BEA704527BC708F88568FE115);
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

    /* Получение интерфейса для работы со временем */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoDateTime1, 0, &IID_IEcoDateTime1, (void**) &pIDTime);

    /* Проверка */
    if (result != 0 || pIDTime == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Seed for random numbers */
    pIDTime = pIDTime->pVTbl->Now(pIDTime);
    srand((uint32_t)pIDTime->pVTbl->get_TimeOfDayUSec(pIDTime));

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Macros for counting time spent on the function */
    #define COUNT_TIME(FUNC) \
            do { \
                pIDTime = pIDTime->pVTbl->Now(pIDTime); \
                t_start = *pIDTime->pVTbl->get_SystemTime(pIDTime); \
                FUNC; \
                pIDTime = pIDTime->pVTbl->Now(pIDTime); \
                t_end   = *pIDTime->pVTbl->get_SystemTime(pIDTime); \
                printf("Took: %5us %9uus", t_end.tv_sec - t_start.tv_sec, t_end.tv_usec - t_start.tv_usec); \
            } while (0)
    
    printf("Iterations:\t\t|\tDFT:\t\t\t|\tFFT:\n");
    for (i = 100; i < 50001; i += 3000) {
        N = i; /* Number of elements in vector */

        /* Allocate memory for source and result vectors */
        v_src = (int32_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(int32_t));
        v_res = (complex_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(complex_t));

        /* Fill source vector with random numbers */
        for (j = 0; j < N; ++j) {
            v_src[j] = rand() % 1000000; 
        }

        printf("%9d\t\t|", N);
        COUNT_TIME(pIEcoLab1->pVTbl->dft(pIEcoLab1, N, v_src, v_res));
        putc('\t', stdout);
        putc('|', stdout);
        COUNT_TIME(pIEcoLab1->pVTbl->fft(pIEcoLab1, 1, N, v_src, v_res));
        putc('\n', stdout);

        /* Free allocated memory */
        pIMem->pVTbl->Free(pIMem, v_src);
        pIMem->pVTbl->Free(pIMem, v_res);
    }

    putc('\n', stdout);
    putc('\n', stdout);
    time_taken = 0;
    printf("Spent time on 100 iters with N = 5000:\n");
    printf("DFT: ");
    {
        for (i = 0; i < 100; ++i) {
            N = 5000; /* Number of elements in vector */

            /* Allocate memory for source and result vectors */
            v_src = (int32_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(int32_t));
            v_res = (complex_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(complex_t));

            /* Fill source vector with random numbers */
            for (j = 0; j < N; ++j) {
                v_src[j] = rand() % 1000000; 
            }
            pIDTime = pIDTime->pVTbl->Now(pIDTime);
            t_start = *pIDTime->pVTbl->get_SystemTime(pIDTime);
                pIEcoLab1->pVTbl->dft(pIEcoLab1, N, v_src, v_res);
            pIDTime = pIDTime->pVTbl->Now(pIDTime);
            t_end   = *pIDTime->pVTbl->get_SystemTime(pIDTime);
            time_taken = ((double_t)(t_end.tv_sec - t_start.tv_sec) + ((double_t)(t_end.tv_usec - t_start.tv_usec) / 1000000.0)) / 60.0;
            /* Free allocated memory */
            pIMem->pVTbl->Free(pIMem, v_src);
            pIMem->pVTbl->Free(pIMem, v_res);
        }
        printf("%6.6fm", time_taken); \
    }
    putc('\n', stdout);
    printf("FFT: ");
    {
        for (i = 0; i < 100; ++i) {
            N = 5000; /* Number of elements in vector */

            /* Allocate memory for source and result vectors */
            v_src = (int32_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(int32_t));
            v_res = (complex_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(complex_t));

            /* Fill source vector with random numbers */
            for (j = 0; j < N; ++j) {
                v_src[j] = rand() % 1000000; 
            }
            pIDTime = pIDTime->pVTbl->Now(pIDTime);
            t_start = *pIDTime->pVTbl->get_SystemTime(pIDTime);
                pIEcoLab1->pVTbl->fft(pIEcoLab1, 1, N, v_src, v_res);
            pIDTime = pIDTime->pVTbl->Now(pIDTime);
            t_end   = *pIDTime->pVTbl->get_SystemTime(pIDTime);
            time_taken = ((double_t)(t_end.tv_sec - t_start.tv_sec) + ((double_t)(t_end.tv_usec - t_start.tv_usec) / 1000000.0)) / 60.0;
            /* Free allocated memory */
            pIMem->pVTbl->Free(pIMem, v_src);
            pIMem->pVTbl->Free(pIMem, v_res);
        }
        printf("%6.6fm", time_taken); \
    }
    putc('\n', stdout);

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

