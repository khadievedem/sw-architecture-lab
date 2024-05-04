/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab3EnumConnectionPoints
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab3EnumConnectionPoints
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab3EnumConnectionPoints.h"

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
int16_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_QueryInterface(/* in */ struct IEcoEnumConnectionPoints* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if (IsEqualUGUID(riid, &IID_IEcoUnknown) || IsEqualUGUID(riid, &IID_IEcoEnumConnectionPoints)) {
        *ppv = me;
    }
    else {
        *ppv = 0;
        return -1;
    }
    me->pVTbl->AddRef(me);
    return 0;
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
uint32_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_AddRef(/* in */ struct IEcoEnumConnectionPoints* me) {
    return 0;
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
uint32_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_Release(/* in */ struct IEcoEnumConnectionPoints* me) {
    return 0;
}
/*
 *
 * <сводка>
 *   Функция Next
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_Next(/* in */ struct IEcoEnumConnectionPoints* me, /* in */ uint32_t cConnections, /* out */ struct IEcoConnectionPoint **ppCP, /* out */ uint32_t *pcFetched) {
    return -1;
}

/*
 *
 * <сводка>
 *   Функция Skip
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_Skip(/* in */ struct IEcoEnumConnectionPoints* me, /* in */ uint32_t cConnections) {
    return -1;
}

/*
 *
 * <сводка>
 *   Функция Reset
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_Reset(/* in */ struct IEcoEnumConnectionPoints* me) {
    return 0 ;
}

/*
 *
 * <сводка>
 *   Функция Clone
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab3EnumConnectionPoints_Clone(/* in */ struct IEcoEnumConnectionPoints* me, /* out */ struct IEcoEnumConnectionPoints **ppEnum) {
    return 0;
}

/* Create Virtual Table IEcoEnumConnectionPointsVTbl */
IEcoEnumConnectionPointsVTbl g_x0000000400000000C000000000000046VTblECP = {
	CEcoLab3EnumConnectionPoints_QueryInterface,
    CEcoLab3EnumConnectionPoints_AddRef,
    CEcoLab3EnumConnectionPoints_Release,
    CEcoLab3EnumConnectionPoints_Next,
    CEcoLab3EnumConnectionPoints_Skip,
    CEcoLab3EnumConnectionPoints_Reset,
    CEcoLab3EnumConnectionPoints_Clone	
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
int16_t ECOCALLMETHOD createCEcoLab3EnumConnectionPoints(/* in */ IEcoUnknown* pIUnkSystem, /* in */ struct IEcoConnectionPoint *pCP, /* out */ IEcoEnumConnectionPoints** ppIEnum) {
    CEcoLab3EnumConnectionPoints* pCMe = 0;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;	
    UGUID* rcid = (UGUID*)&CID_EcoMemoryManager1;		
    int16_t result = -1;

    /* Проверка указателей */
    if (ppIEnum == 0 || pIUnkSystem == 0 || pCP == 0) {
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
    pCMe = (CEcoLab3EnumConnectionPoints*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab3EnumConnectionPoints));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Создание таблицы функций интерфейса IEcoEnumConnections */
    pCMe->m_pVTblIECP = &g_x0000000400000000C000000000000046VTblECP;


    /* Создание экземпляра работы со списком */
    pCMe->m_List = 0;
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoList1, 0,  &IID_IEcoList1, (void**)&pCMe->m_List);
    if (result != 0 || pCMe->m_List == 0) {
        deleteCEcoLab3EnumConnectionPoints((IEcoEnumConnectionPoints*)pCMe);
        return result;
    }

    pCMe->m_List->pVTbl->Add(pCMe->m_List, pCP);

    /* Возврат указателя на интерфейс */
    *ppIEnum = (IEcoEnumConnectionPoints*)pCMe;

    /* Освобождение системного интерфейса */
    pISys->pVTbl->Release(pISys);

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
void ECOCALLMETHOD deleteCEcoLab3EnumConnectionPoints(/* in */ IEcoEnumConnectionPoints* pIEnum) {
    CEcoLab3EnumConnectionPoints* pCMe = (CEcoLab3EnumConnectionPoints*)pIEnum;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEnum != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if (pCMe->m_List != 0) {
            pCMe->m_List->pVTbl->Clear(pCMe->m_List);
            pCMe->m_List->pVTbl->Release(pCMe->m_List);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}
