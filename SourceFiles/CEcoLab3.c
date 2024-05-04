/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab3
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab3
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "IEcoComplex1.h"
#include "CEcoLab3.h"
#include "CEcoLab3EnumConnectionPoints.h"
#include "IEcoConnectionPointContainer.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab3
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3_QueryInterface(/* in */ struct IEcoLab3* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab3* pCMe = (CEcoLab3*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab3) ) {
        *ppv = &pCMe->m_pVTblIEcoLab3;
        pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer) ) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab3;
        pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab3
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab3_AddRef(/* in */ struct IEcoLab3* me) {
    CEcoLab3* pCMe = (CEcoLab3*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab3
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab3_Release(/* in */ struct IEcoLab3* me) {
    CEcoLab3* pCMe = (CEcoLab3*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab3((IEcoLab3*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Fire_OnFFTCallback
 * </сводка>
 *
 * <описание>
 *   Функция вызова обратного интерфейса
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3_Fire_OnFFTCallback(/* in */ struct IEcoLab3* me, /* in */ uint32_t N, /* out */ const complex_t* const vec, char_t side) {
    CEcoLab3* pCMe = (CEcoLab3*)me;
    int16_t result = 0;
    uint32_t count = 0;
    uint32_t index = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab3Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0 ) {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0) {
        result = ((IEcoConnectionPoint*)pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*)pCMe->m_pISinkCP, &pEnum);
        if ( (result == 0) && (pEnum != 0) ) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab3Events, (void**)&pIEvents);
                if ( (result == 0) && (pIEvents != 0) ) {
                    result = pIEvents->pVTbl->OnFFTCallback(pIEvents, N, vec, side);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}


void fft_(/* in */ IEcoLab3* me, /* in */ uint32_t stride, /* in */ uint32_t N, /* in */ const int32_t * const v_in, /* out */ complex_t *v_out, char_t side)
{
    CEcoLab3* pCMe = (CEcoLab3*)me;

    uint32_t k;
    complex_t t, tmp;

    /* Output array should be >= initial array */
    if (v_in == NULL || v_out == NULL) return;

    // At the lowest level pass through
    if (N == 1) {
        v_out[0].re = v_in[0];
        v_out[0].im = 0;
        return;
    }
    // Recursively split in two, then combine beneath.
    pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    fft_((IEcoLab3*)pCMe, 2*stride, N/2, v_in, v_out, 'l');
    pCMe->m_pVTblIEcoLab3->Release((IEcoLab3*)pCMe);

    pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    fft_((IEcoLab3*)pCMe, 2*stride, N/2, v_in + stride, v_out + N/2, 'r');
    pCMe->m_pVTblIEcoLab3->Release((IEcoLab3*)pCMe);

    for (k = 0; k < N/2; k++) {
        t.re = v_out[k].re;
        t.im = v_out[k].im;

        /* Odd numbers */
        tmp.re = 0;
        tmp.im = 2 * PI * k / N;

        tmp = pCMe->m_pICmplx->pVTbl->ExpComplex((IEcoComplex1*)pCMe, tmp);
        tmp = pCMe->m_pICmplx->pVTbl->MultiplyComplex((IEcoComplex1*)pCMe, tmp, v_out[k + N/2]);
        v_out[k] = pCMe->m_pICmplx->pVTbl->AddComplex((IEcoComplex1*)pCMe, t, tmp);

        /* Even numbers */
        tmp.re = 0;
        tmp.im = 2 * PI * k / N;

        tmp = pCMe->m_pICmplx->pVTbl->ExpComplex((IEcoComplex1*)pCMe, tmp);
        tmp = pCMe->m_pICmplx->pVTbl->MultiplyComplex((IEcoComplex1*)pCMe, tmp, v_out[k + N/2]);
        v_out[k + N/2] = pCMe->m_pICmplx->pVTbl->SubComplex((IEcoComplex1*)pCMe, t, tmp);
    }
    CEcoLab3_Fire_OnFFTCallback(me, N, v_out, side);
}
/*
 *
 * <сводка>
 *   Функция fft
 * </сводка>
 *
 * <описание>
 *   Функция считает Быстрое преобразование фурье со сложностью O(n*log(n))
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoLab3_fft(/* in */ IEcoLab3* me, /* in */ uint32_t N, /* in */ const int32_t * const v_in, /* out */ complex_t *v_out)
{
    printf("Start counting FFT:\n");
    sleep(2);
    fft_((IEcoLab3*)me, 1, N, v_in, v_out, 'n');
    CEcoLab3_Fire_OnFFTCallback(me, N, NULL, '\0');
}

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoConnectionPointContainer
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3_IEcoConnectionPointContainer_QueryInterface(/* in */ struct IEcoConnectionPointContainer* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab3* pCMe = (CEcoLab3*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab3) ) {
        *ppv = &pCMe->m_pVTblIEcoLab3;
        pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer) ) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab3;
        pCMe->m_pVTblIEcoLab3->AddRef((IEcoLab3*)pCMe);
    }
    else {
        *ppv = 0;
        return -1;
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoConnectionPointContainer
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab3_IEcoConnectionPointContainer_AddRef(/* in */ struct IEcoConnectionPointContainer* me) {
    CEcoLab3* pCMe = (CEcoLab3*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    if (me == 0 ) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoConnectionPointContainer
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab3_IEcoConnectionPointContainer_Release(/* in */ struct IEcoConnectionPointContainer* me) {
    CEcoLab3* pCMe = (CEcoLab3*)((uint64_t)me - sizeof(struct IEcoUnknown*));

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab3((IEcoLab3*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция EnumConnectionPoints
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3_IEcoConnectionPointContainer_EnumConnectionPoints(/* in */ struct IEcoConnectionPointContainer* me, /* out */ struct IEcoEnumConnectionPoints **ppEnum) {
    CEcoLab3* pCMe = (CEcoLab3*)((uint64_t)me - sizeof(struct IEcoUnknown*));
    int16_t result = 0;

    if (me == 0 || ppEnum == 0 ) {
        return -1;
    }

    result = createCEcoLab3EnumConnectionPoints((IEcoUnknown*)pCMe->m_pISys, &pCMe->m_pISinkCP->m_pVTblICP, ppEnum);

    return result;
}

/*
 *
 * <сводка>
 *   Функция FindConnectionPoint
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3_IEcoConnectionPointContainer_FindConnectionPoint(/* in */ struct IEcoConnectionPointContainer* me, /* in */ const UGUID* riid, /* out */ struct IEcoConnectionPoint **ppCP) {
    CEcoLab3* pCMe = (CEcoLab3*)((uint64_t)me - sizeof(struct IEcoUnknown*));
    int16_t result = 0;

    if (me == 0 || ppCP == 0 ) {
        return -1;
    }

    if ( !IsEqualUGUID(riid, &IID_IEcoLab3Events ) ) {
        *ppCP = 0;
        /* CONNECT_E_NOCONNECTION */
        return -1;
    }

    if (pCMe->m_pISinkCP == 0) {
        /* E_FAIL */
        return -1;
    }

    pCMe->m_pISinkCP->m_pVTblICP->AddRef(&pCMe->m_pISinkCP->m_pVTblICP);
    *ppCP =  &pCMe->m_pISinkCP->m_pVTblICP;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab3(/*in*/ struct IEcoLab3* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab3* pCMe = (CEcoLab3*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

    /* Проверка указателей */
    if (me == 0 ) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1*)pIUnkSystem;

    /* Создание точки подключения */
    result = createCEcoLab3ConnectionPoint((IEcoUnknown*)pCMe->m_pISys, &pCMe->m_pVTblICPC, &IID_IEcoLab3Events, (IEcoConnectionPoint**)&((pCMe)->m_pISinkCP));
    if (result == 0 && pCMe->m_pISinkCP != 0) {
        result = 0;
    }


    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/* Create Virtual Table IEcoLab3 */
IEcoLab3VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab3_QueryInterface,
    CEcoLab3_AddRef,
    CEcoLab3_Release,
    CEcoLab3_fft
};

/* Create Virtual Table IEcoConnectionPointContainer */
IEcoConnectionPointContainerVTbl g_x0000000500000000C000000000000046VTblCPC = {
    CEcoLab3_IEcoConnectionPointContainer_QueryInterface,
    CEcoLab3_IEcoConnectionPointContainer_AddRef,
    CEcoLab3_IEcoConnectionPointContainer_Release,
    CEcoLab3_IEcoConnectionPointContainer_EnumConnectionPoints,
    CEcoLab3_IEcoConnectionPointContainer_FindConnectionPoint
};


/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab3(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab3** ppIEcoLab3) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoComplex1* pICmplx = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab3* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
    UGUID* rcidCmplx = (UGUID*)&CID_EcoComplex1;
	
    /* Проверка указателей */
    if (ppIEcoLab3 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **)&pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);

	/* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void**)&pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Получение интерфейса для работы с комплексными числами */
    pIBus->pVTbl->QueryComponent(pIBus, rcidCmplx, 0, &IID_IEcoComplex1, (void**) &pICmplx);

    /* Проверка */
    if (result != 0 && pICmplx == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab3*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab3));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Сохранение указателя на интерфейс для работы комплексными числами */
    pCMe->m_pICmplx = pICmplx;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab3 */
    pCMe->m_pVTblIEcoLab3 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Создание таблицы функций интерфейса IEcoConnectionPointContainer */
    pCMe->m_pVTblICPC = &g_x0000000500000000C000000000000046VTblCPC;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab3 = (IEcoLab3*)pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab3(/* in */ IEcoLab3* pIEcoLab3) {
    CEcoLab3* pCMe = (CEcoLab3*)pIEcoLab3;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab3 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
