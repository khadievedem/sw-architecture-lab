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
 *   Данный заголовок описывает реализацию компонента CEcoLab3Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __C_ECOLAB1_SINK_H__
#define __C_ECOLAB1_SINK_H__

#include "IEcoLab3.h"
#include "IEcoLab3Events.h"
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"

typedef struct CEcoLab3Sink {

    /* Таблица функций интерфейса IEcoLab3Events */
    IEcoLab3VTblEvents* m_pVTblIEcoLab3Events;

    /* Вспомогательные функции */
    int16_t (ECOCALLMETHOD *Advise)(/* in */ struct CEcoLab3Sink* me, /* in */IEcoLab3 *pIEcoLab3);
    int16_t (ECOCALLMETHOD *Unadvise)(/* in */ struct CEcoLab3Sink* me, /* in */IEcoLab3 *pIEcoLab3);

    /* Счетчик ссылок */
    uint32_t m_cRef;
    uint32_t m_cCookie;

    /* Интерфейс для работы с памятью */
    IEcoMemoryAllocator1* m_pIMem;


} CEcoLab3Sink, *CEcoLab3SinkPtr;

/* Создание экземпляра */
int16_t ECOCALLMETHOD createCEcoLab3Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab3Events** ppIEcoLab3Events);
/* Удаление */
void ECOCALLMETHOD deleteCEcoLab3Sink(/* in */ IEcoLab3Events* pIEcoLab3Events);

#endif /* __C_ECOLAB1_SINK_H__ */
