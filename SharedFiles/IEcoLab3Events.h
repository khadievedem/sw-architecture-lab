/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab3
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab3
 * </описание>
 *
 * <ссылка>
 *
 * </ссылка>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#ifndef __I_ECOLAB1EVENTS_H__
#define __I_ECOLAB1EVENTS_H__

#include "IEcoBase1.h"
#include "IEcoComplex1.h"

/* IEcoLab3Events IID = {B6D38661-6827-46D9-9135-FD4B204A68D7} */
#ifndef __IID_IEcoLab3Events
static const UGUID IID_IEcoLab3Events = {0x01, 0x10, 0xB6, 0xD3, 0x86, 0x61, 0x68, 0x27, 0x46, 0xD9, 0x91, 0x35, 0xFD, 0x4B, 0x20, 0x4A, 0x68, 0xD7};
#endif /* __IID_IEcoLab3Events */

/* Обратный интерфейс */
typedef struct IEcoLab3VTblEvents {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface )(/* in */ struct IEcoLab3Events* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef )(/* in */ struct IEcoLab3Events* me);
    uint32_t (ECOCALLMETHOD *Release )(/* in */ struct IEcoLab3Events* me);

    /* IEcoLab3Events */
    int16_t (ECOCALLMETHOD *OnLeftSubtreeFFTCallback)(/* in */ struct IEcoLab3Events* me, /* in */ uint32_t N, /* in */ const complex_t* const vec);
    int16_t (ECOCALLMETHOD *OnRightSubtreeFFTCallback)(/* in */ struct IEcoLab3Events* me, /* in */ uint32_t N, /* in */ const complex_t* const vec);
    int16_t (ECOCALLMETHOD *OnEndFFTCallback)(/* in */ struct IEcoLab3Events* me, /* in */ uint32_t N, /* in */ const complex_t* const vec);

} IEcoLab3VTblEvents, *IEcoLab3VTblEventsPtr;

interface IEcoLab3Events {
    struct IEcoLab3VTblEvents *pVTbl;
} IEcoLab3Events;


#endif /* __I_ECOLAB1EVENTS_H__ */
