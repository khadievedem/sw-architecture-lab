/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   IdEcoComplex1
 * </сводка>
 *
 * <описание>
 *   Данный заголовок описывает интерфейс IdEcoComplex1
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

#ifndef __ID_ECOCOMPLEX1_H__
#define __ID_ECOCOMPLEX1_H__

#include "IEcoBase1.h"
#include "IEcoComplex1.h"

/* EcoComplex1 CID = {1F5DF16E-E1BF-43B9-99A4-34ED38FFFFFF} */
#ifndef __CID_EcoComplex1
static const UGUID CID_EcoComplex1 = {0x01, 0x10, 0x1F, 0x5D, 0xF1, 0x6E, 0xE1, 0xBF, 0x43, 0xB9, 0x99, 0xA4, 0x34, 0xED, 0x38, 0xFF, 0xFF, 0xFF};
#endif /* __CID_EcoComplex1 */

/* Фабрика компонента для динамической и статической компановки */
#ifdef ECO_DLL
ECO_EXPORT IEcoComponentFactory* ECOCALLMETHOD GetIEcoComponentFactoryPtr();
#elif ECO_LIB
extern IEcoComponentFactory* GetIEcoComponentFactoryPtr_1F5DF16EE1BF43B999A434ED38FFFFFF;
#endif

#endif /* __ID_ECOCOMPLEX1_H__ */
