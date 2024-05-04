/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab3Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab3Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab3Sink.h"
#include "IEcoConnectionPointContainer.h"
#include <stdio.h>

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3Sink_QueryInterface(/* in */ struct IEcoLab3Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if ( IsEqualUGUID(riid, &IID_IEcoLab3Events ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown ) ) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab3Sink_AddRef(/* in */ struct IEcoLab3Events* me) {
    CEcoLab3Sink* pCMe = (CEcoLab3Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab3Sink_Release(/* in */ struct IEcoLab3Events* me) {
    CEcoLab3Sink* pCMe = (CEcoLab3Sink*)me;

    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab3Sink((IEcoLab3Events*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция OnFFTCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3Sink_OnFFTCallback(/* in */ struct IEcoLab3Events* me, /* in */ uint32_t N, /* in */ const complex_t * const vec, char_t side) {
    CEcoLab3Sink* pCMe = (CEcoLab3Sink*)me;
    static uint32_t prevSize = 0;
    uint32_t i;
    
    if (vec == NULL && side == '\0') {
        printf("\n\033[22;33m↑");
        printf("\n└────Result. End up with FFT algorithm\033[0m\n");
        return 0;        
    }

    if (!N) return 0;
    
    printf("%*s\r", prevSize * 20, "");;
    printf("\033[22;32m");
    if (side == 'l') {
        printf("LEFT  SUBTREE: ");
    } else if (side == 'r') {
        printf("RIGHT SUBTREE: ");
    }
    for (i = 0; i < N; ++i) {
        printf("%.2f + %.2fi", vec[i].re, vec[i].im);
        if (i != N - 1) printf(" + ");
    }
    printf("\033[0m");

    putc('\r', stdout);
    fflush(stdout);
    /* putc('\n', stdout); */

    if (me == 0 ) {
        return -1;
    }
    
    sleep(2);
    prevSize = N;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Advise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3Sink_Advise(/* in */ struct CEcoLab3Sink* me, /* in */IEcoLab3 *pIEcoLab3) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    result = pIEcoLab3->pVTbl->QueryInterface(pIEcoLab3, &IID_IEcoConnectionPointContainer, (void**)&pCPC);

    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab3Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*)me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3Sink_Unadvise(/* in */ struct CEcoLab3Sink* me, /* in */IEcoLab3 *pIEcoLab3) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint * pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie) {
        result = pIEcoLab3->pVTbl->QueryInterface(pIEcoLab3, &IID_IEcoConnectionPointContainer, (void**)&pCPC);
        if (result == 0) {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab3Events, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0) {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

/* Create Virtual Table IEcoLab3VTblEvents */
IEcoLab3VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents = {
    CEcoLab3Sink_QueryInterface,
    CEcoLab3Sink_AddRef,
    CEcoLab3Sink_Release,
    CEcoLab3Sink_OnFFTCallback
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
int16_t ECOCALLMETHOD createCEcoLab3Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab3Events** ppIEcoLab3Events) {
    int16_t result = -1;
    CEcoLab3Sink* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab3Events == 0 || pIMem == 0 ) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab3Sink*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab3Sink));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab3Events = &g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents;

    *ppIEcoLab3Events = (IEcoLab3Events*)pCMe;

    return 0;
};

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
void ECOCALLMETHOD deleteCEcoLab3Sink(IEcoLab3Events* pIEcoLab3Events) {
    CEcoLab3Sink* pCMe = (CEcoLab3Sink*)pIEcoLab3Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab3Events != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
