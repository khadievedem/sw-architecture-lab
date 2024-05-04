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
 *   Данный заголовок описывает реализацию интерфейсов CEcoLab3EnumConnectionPoints
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__
#define __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__

#include "IEcoEnumConnectionPoints.h"
#include "IdEcoList1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab3EnumConnectionPoints {

    /* Таблица функций интерфейса IEcoEnumConnectionPoints */
    IEcoEnumConnectionPointsVTbl* m_pVTblIECP;

    /* Список */
    IEcoList1* m_List;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;

} CEcoLab3EnumConnectionPoints;

/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab3EnumConnectionPoints(/* in */ IEcoUnknown* pIUnkSystem, /* in */ struct IEcoConnectionPoint *pCP, /* out */ IEcoEnumConnectionPoints** ppIEnum);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab3EnumConnectionPoints(/* in */ IEcoEnumConnectionPoints* pIEnum);

#endif /* __C_ECOLAB1_ENUM_CONNECTION_POINTS_H__ */
