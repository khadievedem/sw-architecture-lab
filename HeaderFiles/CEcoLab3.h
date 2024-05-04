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
 *   Данный заголовок описывает реализацию компонента CEcoLab3
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB1_H__
#define __C_ECOLAB1_H__

#include "IEcoLab3.h"
#include "IEcoLab3Events.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoComplex1.h"
#include "IEcoEnumConnections.h"
#include "IEcoConnectionPointContainer.h"
#include "CEcoLab3ConnectionPoint.h"

typedef struct CEcoLab3 {

    /* Таблица функций интерфейса IEcoLab3 */
    IEcoLab3VTbl* m_pVTblIEcoLab3;

    /* Таблица функций интерфейса IEcoConnectionPointContainer */
    IEcoConnectionPointContainerVTbl* m_pVTblICPC;

    /* Счетчик ссылок */
    uint32_t m_cRef;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

    /* Системный интерфейс */
    IEcoSystem1* m_pISys;

    /* Интерфейс для работы с комлексными числами */
    IEcoComplex1* m_pICmplx;

    /* Точка подключения */
    CEcoLab3ConnectionPoint* m_pISinkCP;

    /* Данные экземпляра */
    char_t* m_Name;

} CEcoLab3, *CEcoLab3Ptr;

/* Инициализация экземпляра */
int16_t ECOCALLMETHOD initCEcoLab3(/*in*/ struct IEcoLab3* me, /* in */ IEcoUnknown *pIUnkSystem);
/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab3(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab3** ppIEcoLab3);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab3(/* in */ IEcoLab3* pIEcoLab3);

#endif /* __C_ECOLAB1_H__ */
