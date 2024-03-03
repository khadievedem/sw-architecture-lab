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
 *   Данный заголовок описывает реализацию компонента CEcoComplex1
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOCOMPLEX1_H__
#define __C_ECOCOMPLEX1_H__

#include "IEcoComplex1.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoComplex1 {

    /* Таблица функций интерфейса IEcoComplex1 */
    IEcoComplex1VTbl* m_pVTblIEcoComplex1;


    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoComplex1, *CEcoComplexPtr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoComplex1(/*in*/ struct IEcoComplex1* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoComplex1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoComplex1** ppIEcoComplex1);
/* Удаление */
void ECOCALLMETHOD deleteCEcoComplex1(/* in */ IEcoComplex1* pIEcoComplex1);

#endif /* __C_ECOCOMPLEX1_H__ */
