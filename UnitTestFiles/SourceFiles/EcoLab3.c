/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab3
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
#include "IEcoLab3Events.h"
#include "IdEcoLab3.h"
#include "IdEcoList1.h"
#include "CEcoLab3Sink.h"
#include "IEcoConnectionPointContainer.h"
#include "IdEcoComplex1.h"


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
    /* Source vector for fft counting */
    int32_t   *v_src = 0;
    /* Result vector for fft result */
    complex_t *v_res = 0;
    /* Size of fft src vector */
    uint32_t N;
    /* Указатель на тестируемый интерфейс */
    IEcoLab3* pIEcoLab3 = 0;
    /* Указатель на интерфейс контейнера точек подключения */
    IEcoConnectionPointContainer* pICPC = 0;
    /* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP = 0;
    /* Указатель на обратный интерфейс */
    IEcoLab3Events* pIEcoLab3Sink = 0;
    IEcoUnknown* pISinkUnk = 0;
    uint32_t cAdvise = 0;

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
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoLab3, (IEcoUnknown*)GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FE8F3A);
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
    result = pIBus->pVTbl->RegisterComponent(pIBus, &CID_EcoList1, (IEcoUnknown*)GetIEcoComponentFactoryPtr_53884AFC93C448ECAA929C8D3A562281);
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

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab3, 0, &IID_IEcoLab3, (void**) &pIEcoLab3);
    if (result != 0 || pIEcoLab3 == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Проверка поддержки подключений обратного интерфейса */
    result = pIEcoLab3->pVTbl->QueryInterface(pIEcoLab3, &IID_IEcoConnectionPointContainer, (void **)&pICPC);
    if (result != 0 || pICPC == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }

    /* Запрос на получения интерфейса точки подключения */
    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab3Events, &pICP);
    if (result != 0 || pICP == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    /* Освобождение интерфейса */
    pICPC->pVTbl->Release(pICPC);

    /* Создание экземпляра обратного интерфейса */
    result = createCEcoLab3Sink(pIMem, (IEcoLab3Events**)&pIEcoLab3Sink);

    if (pIEcoLab3Sink != 0) {
        result = pIEcoLab3Sink->pVTbl->QueryInterface(pIEcoLab3Sink, &IID_IEcoUnknown,(void **)&pISinkUnk);
        if (result != 0 || pISinkUnk == 0) {
            /* Освобождение интерфейсов в случае ошибки */
            goto Release;
        }
        /* Подключение */
        result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
        /* Проверка */
        if (result == 0 && cAdvise == 1) {
            /* Сюда можно добавить код */
        }
        /* Освобождение интерфейса */
        pISinkUnk->pVTbl->Release(pISinkUnk);
    }

    N = 8; /* Number of elements in vector */

    /* Allocate memory for source and result vectors */
    v_src = (int32_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(int32_t));
    v_res = (complex_t *)pIMem->pVTbl->Alloc(pIMem, N * sizeof(complex_t));
    pIMem->pVTbl->Fill(pIMem, v_res, 0, N * sizeof(complex_t));

    /* Fill source vector with random numbers */
    v_src[0] = 1; 
    v_src[1] = -1; 
    v_src[2] = 1; 
    v_src[3] = -1; 
    v_src[4] = 5; 
    v_src[5] = 4; 
    v_src[6] = 3; 
    v_src[7] = 2; 

    printf("Source array:\n");
    for (uint32_t i = 0; i < N; ++i) {
        printf("%d ", v_src[i]);
    }
    putc('\n', stdout);

    pIEcoLab3->pVTbl->fft(pIEcoLab3, N, v_src, v_res);

    /* Free allocated memory */
    pIMem->pVTbl->Free(pIMem, v_src);
    pIMem->pVTbl->Free(pIMem, v_res);
    
    if (pIEcoLab3Sink != 0) {
        /* Отключение */
        result = pICP->pVTbl->Unadvise(pICP, cAdvise);
        pIEcoLab3Sink->pVTbl->Release(pIEcoLab3Sink);
        pICP->pVTbl->Release(pICP);
    }

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
    if (pIEcoLab3 != 0) {
        pIEcoLab3->pVTbl->Release(pIEcoLab3);
    }


    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

