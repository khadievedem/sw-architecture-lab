﻿/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoLab2
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoLab2
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

#ifndef __I_ECOLAB2_H__
#define __I_ECOLAB2_H__

#include "IEcoBase1.h"
#include "IEcoComplex1.h"

/* IEcoLab2 IID = {277FC00C-3562-4096-AFCF-C125B9EEEE92} */
#ifndef __IID_IEcoLab2
static const UGUID IID_IEcoLab2 = {0x01, 0x10, 0x27, 0x7F, 0xC0, 0x0C, 0x35, 0x62, 0x40, 0x96, 0xAF, 0xCF, 0xC1, 0x25, 0xB9, 0xEE, 0xEE, 0x92};
#endif /* __IID_IEcoLab2 */

typedef struct IEcoLab2VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoLab2* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoLab2* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoLab2* me);

    /* IEcoLab2 */
    int32_t (ECOCALLMETHOD *Addition)(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* in */ int32_t b);
    int32_t (ECOCALLMETHOD *Subtraction)(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* in */ int32_t b);
    int32_t (ECOCALLMETHOD *Multiplication)(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* in */ int32_t b);
    int32_t (ECOCALLMETHOD *Division)(/* in */ struct IEcoLab2* me, /* in */ int32_t a, /* in */ int32_t b);
    void    (ECOCALLMETHOD *fft)(/* in */ struct IEcoLab2* me, /* in */ uint32_t stride, /* in */ uint32_t N, /* in */ int32_t *v_in, /* out */ complex_t *v_out);

} IEcoLab2VTbl, *IEcoLab2VTblPtr;

interface IEcoLab2 {
    struct IEcoLab2VTbl *pVTbl;
} IEcoLab2;


#endif /* __I_ECOLAB2_H__ */
