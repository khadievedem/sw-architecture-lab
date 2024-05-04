/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoComplex1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoComplex1
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
#include "CEcoComplex1.h"
#include <math.h>


/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoComplex1
 * </описание>
 *
 */
 
int16_t ECOCALLMETHOD CEcoComplex1_QueryInterface(/* in */ struct IEcoComplex1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoComplex1) ) {
        *ppv = &pCMe->m_pVTblIEcoComplex1;
        pCMe->m_pVTblIEcoComplex1->AddRef((IEcoComplex1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoComplex1;
        pCMe->m_pVTblIEcoComplex1->AddRef((IEcoComplex1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoComplex1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoComplex1_AddRef(/* in */ struct IEcoComplex1* me) {
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

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
 *   Функция Release для интерфейса IEcoComplex1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoComplex1_Release(/* in */ struct IEcoComplex1* me) {
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoComplex1((IEcoComplex1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция AddComplex
 * </сводка>
 *
 * <описание>
 *   Функция считает сумму комплексных чисел num1 и num2
 * </описание>
 *
 */
complex_t CEcoComplex1_AddComplex(/* in */ struct IEcoComplex1* me, /* int */ complex_t num1, /* int */ complex_t num2)
{
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

    return (complex_t) {.re = num1.re + num2.re, .im = num1.im + num2.im};
}

/*
 *
 * <сводка>
 *   Функция SubComplex
 * </сводка>
 *
 * <описание>
 *   Функция считает разность комплексных чисел num1 и num2
 * </описание>
 *
 */
complex_t CEcoComplex1_SubComplex(/* in */ struct IEcoComplex1* me, /* int */ complex_t num1, /* int */ complex_t num2)
{
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

    return (complex_t) {
        .re = num1.re - num2.re,
        .im = num1.im - num2.im
    };
}

/*
 *
 * <сводка>
 *   Функция MultiplyComplex
 * </сводка>
 *
 * <описание>
 *   Функция считает произведение комплексных чисел num1 и num2
 * </описание>
 *
 */
complex_t CEcoComplex1_MultiplyComplex(/* in */ struct IEcoComplex1* me, /* int */ complex_t num1, /* int */ complex_t num2)
{
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

    return (complex_t) {
      .re = (num1.re * num2.re) - (num1.im * num2.im),
      .im = (num1.re * num2.im) + (num1.im * num2.re)
    };
}

/*
 *
 * <сводка>
 *   Функция ExpComplex
 * </сводка>
 *
 * <описание>
 *   Функция экспоненту от комплексного числа num
 * </описание>
 *
 */
complex_t CEcoComplex1_ExpComplex(/* in */ struct IEcoComplex1* me, /* int */ complex_t num)
{
    CEcoComplex1* pCMe = (CEcoComplex1*)me;

    complex_t res;
    double r;
    
    r = exp(num.re);

    return (complex_t) {
        .re = r * cos(num.im),
        .im = r * sin(num.im)
    };
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
int16_t ECOCALLMETHOD initCEcoComplex1(/*in*/ struct IEcoComplex1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoComplex1* pCMe = (CEcoComplex1*)me;
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



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoComplex1 */
IEcoComplex1VTbl g_x277FC00C35624096AFCFC125B94EEEEEVTbl = {
    CEcoComplex1_QueryInterface,
    CEcoComplex1_AddRef,
    CEcoComplex1_Release,
    CEcoComplex1_AddComplex,
    CEcoComplex1_SubComplex,
    CEcoComplex1_MultiplyComplex,
    CEcoComplex1_ExpComplex
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
int16_t ECOCALLMETHOD createCEcoComplex1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoComplex1** ppIEcoComplex1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoComplex1* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoComplex1 == 0 || pIUnkSystem == 0) {
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

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoComplex1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoComplex1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoComplex1 */
    pCMe->m_pVTblIEcoComplex1 = &g_x277FC00C35624096AFCFC125B94EEEEEVTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoComplex1 = (IEcoComplex1*)pCMe;

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
void ECOCALLMETHOD deleteCEcoComplex1(/* in */ IEcoComplex1* pIEcoComplex1) {
    CEcoComplex1* pCMe = (CEcoComplex1*)pIEcoComplex1;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoComplex1 != 0 ) {
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
