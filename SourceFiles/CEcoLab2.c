/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab2
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
#include "CEcoLab2.h"
#include "IEcoCalculatorX.h"
#include "IEcoCalculatorY.h"
#include "IdEcoLab1.h"
#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorC.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab2
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab2_QueryInterface(/* in */ struct IEcoLab2* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab2) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab2;
        pCMe->m_pVTblIEcoLab2->AddRef((IEcoLab2*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoLab2
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab2_AddRef(/* in */ struct IEcoLab2* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

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
 *   Функция Release для интерфейса IEcoLab2
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab2_Release(/* in */ struct IEcoLab2* me) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab2((IEcoLab2*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Addition
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int32_t ECOCALLMETHOD CEcoLab2_Addition(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* out */ int32_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Subtraction
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int32_t ECOCALLMETHOD CEcoLab2_Subtraction(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* out */ int32_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Multiplication
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int32_t ECOCALLMETHOD CEcoLab2_Multiplication(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* out */ int32_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Division
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int32_t ECOCALLMETHOD CEcoLab2_Division(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* out */ int32_t b) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}

void ECOCALLMETHOD CEcoLab2_fft(/* in */ struct IEcoLab2* me, /* in */ uint32_t stride, /* in */ uint32_t N, /* in */ int32_t *v_in, /* out */ complex_t *v_out) {
    CEcoLab2* pCMe = (CEcoLab2*)me;

    /* Проверка указателей */
    if (me == 0 || v_in == 0 || v_out == 0) {
        fprintf(stderr, "[ERR] Invalid pointers in fft\n");
        return;
    }

    /* Проверка указателя включаемого компонента и вызов метода */
    if (pCMe->m_pILab1 != 0) {
        pCMe->m_pILab1->pVTbl->fft(pCMe->m_pILab1, stride, N, v_in, v_out);
    }
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
int16_t ECOCALLMETHOD initCEcoLab2(/*in*/ struct IEcoLab2* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab2* pCMe = (CEcoLab2*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    IEcoLab1* pILab1 = 0;

    IEcoCalculatorX* pIX = 0;
    IEcoCalculatorY* pIY = 0;

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

    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pILab1);
    if (result != 0 || pILab1 == 0) {
        fprintf(stderr, "[ERR] Cannot get IEcoLab1\n");
        return result;
    }

    /* Получение интерфейса по работе с умножением и делением у компонента "E" агрегирующего компонент "B" */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY, (void**) &pIY);
    /* Проверка */
    if (result == 0 && pIY != 0) {
        /* Получение интерфейса по работе со сложением и вычитанием у компонента "B" */
        result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**) &pIX);
        if (result != 0 || pIX == 0) {
            fprintf(stderr, "[ERR] Get IY from E, but cannot get IX from E -> B\n");
            return result;
        }
    }
    else {

        /* Получение интерфейса по работе с умножением и делением у компонента "D" включающего компонент "A" */
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void**) &pIY);
        /* Проверка */
        if (result == 0 && pIY != 0) {
            /* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
            result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**) &pIX);
            if (result != 0 || pIX == 0) {
                fprintf(stderr, "[ERR] Get IY from D, but cannot get IX from D -> A\n");
                return result;
            }
        }
        else {

            /* Получение интерфейса по работе с умножением и делением у компонента "C" */
            result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorC, 0, &IID_IEcoCalculatorY, (void**) &pIY);
            /* Проверка */
            if (result == 0 && pIY != 0) {
                /* Получение интерфейса по работе со сложением и вычитанием у компонента "C" */
                result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void**) &pIX);
                if (result != 0 || pIX == 0) {
                    fprintf(stderr, "[ERR] Cannot intialize IY from C, but IX was initialized\n");
                    return result;
                }
            }
            else {
                /* Получение интерфейса по работе со сложением и вычитанием у компонента "B" c поддержкой агрегирования */
                result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, 0, &IID_IEcoCalculatorX, (void**) &pIX);
                /* Проверка */
                if (result != 0 || pIX == 0) {
                    /* Получение интерфейса по работе со сложением и вычитанием у компонента "A" */
                    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX, (void**) &pIX);
                    if (result != 0 || pIX == 0) {
                        fprintf(stderr, "[ERR] Cannot intialize X and Y comps \n");
                        return result;
                    }
                }
            }
        }
    }

    pCMe->m_pILab1 = pILab1;
    pCMe->m_pIX = pIX;
    pCMe->m_pIY = pIY;


    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoLab2 */
IEcoLab2VTbl g_x277FC00C35624096AFCFC125B9EEEE92VTbl = {
    CEcoLab2_QueryInterface,
    CEcoLab2_AddRef,
    CEcoLab2_Release,
    CEcoLab2_Addition,
    CEcoLab2_Subtraction,
    CEcoLab2_Multiplication,
    CEcoLab2_Division,
    CEcoLab2_fft
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
int16_t ECOCALLMETHOD createCEcoLab2(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab2** ppIEcoLab2) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    CEcoLab2* pCMe = 0;
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;
	
    /* Проверка указателей */
    if (ppIEcoLab2 == 0 || pIUnkSystem == 0) {
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
    pCMe = (CEcoLab2*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab2));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab2 */
    pCMe->m_pVTblIEcoLab2 = &g_x277FC00C35624096AFCFC125B9EEEE92VTbl;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab2 = (IEcoLab2*)pCMe;

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
void ECOCALLMETHOD deleteCEcoLab2(/* in */ IEcoLab2* pIEcoLab2) {
    CEcoLab2* pCMe = (CEcoLab2*)pIEcoLab2;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab2 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        if ( pCMe->m_pILab1 != 0 ) {
            pCMe->m_pILab1->pVTbl->Release(pCMe->m_pILab1);
        }
        if ( pCMe->m_pIX != 0 ) {
            pCMe->m_pIX->pVTbl->Release(pCMe->m_pIX);
        }
        if ( pCMe->m_pIY != 0 ) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
