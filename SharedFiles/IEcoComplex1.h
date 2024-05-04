/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IEcoComplex1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IEcoComplex1
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

#ifndef __I_ECOCOMPLEX1_H__
#define __I_ECOCOMPLEX1_H__

#include "IEcoBase1.h"

#define PI 3.14159265358979323846

typedef struct complexType {
    double re;
    double im;
} complex_t;


/* IEcoComplex1 IID = {277FC00C-3562-4096-AFCF-C125B94EEEEE} */
#ifndef __IID_IEcoComplex1
static const UGUID IID_IEcoComplex1 = {0x01, 0x10, 0x27, 0x7F, 0xC0, 0x0C, 0x35, 0x62, 0x40, 0x96, 0xAF, 0xCF, 0xC1, 0x25, 0xB9, 0x4E, 0xEE, 0xEE};
#endif /* __IID_IEcoComplex1 */

typedef struct IEcoComplex1VTbl {

    /* IEcoUnknown */
    int16_t (ECOCALLMETHOD *QueryInterface)(/* in */ struct IEcoComplex1* me, /* in */ const UGUID* riid, /* out */ void **ppv);
    uint32_t (ECOCALLMETHOD *AddRef)(/* in */ struct IEcoComplex1* me);
    uint32_t (ECOCALLMETHOD *Release)(/* in */ struct IEcoComplex1* me);

    /* IEcoComplex1 */
    complex_t (ECOCALLMETHOD *AddComplex)(/* in */ struct IEcoComplex1* me, /* int */ complex_t num1, /* int */ complex_t num2);
    complex_t (ECOCALLMETHOD *SubComplex)(/* in */ struct IEcoComplex1* me, /* int */ complex_t num1, /* int */ complex_t num2);
    complex_t (ECOCALLMETHOD *MultiplyComplex)(/* in */ struct IEcoComplex1* me, /* int */ complex_t num1, /* int */ complex_t num2);
    complex_t (ECOCALLMETHOD *ExpComplex)(/* in */ struct IEcoComplex1* me, /* int */ complex_t num);

} IEcoComplex1VTbl, *IEcoComplex1VTblPtr;

interface IEcoComplex1 {
    struct IEcoComplex1VTbl *pVTbl;
} IEcoComplex1;


#endif /* __I_ECOCOMPLEX1_H__ */
