/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1
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
#include "IEcoComplex1.h"
#include "CEcoLab1.h"

#define PI 3.14159265358979323846

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
 
int16_t ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ struct IEcoLab1* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if ( IsEqualUGUID(riid, &IID_IEcoLab1) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    }
    else if ( IsEqualUGUID(riid, &IID_IEcoUnknown) ) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
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
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

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
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ struct IEcoLab1* me) {
    CEcoLab1* pCMe = (CEcoLab1*)me;

    /* Проверка указателя */
    if (me == 0 ) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if ( pCMe->m_cRef == 0 ) {
        deleteCEcoLab1((IEcoLab1*)pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция dft
 * </сводка>
 *
 * <описание>
 *   Функция считает Дискретное преобразование фурье со сложностью O(n^2)
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoLab1_dft(/* in */ struct IEcoLab1* me, /* in */ uint32_t N, /* in */ int32_t *v_in, /* out */ complex_t *v_out)
{
    CEcoLab1* pCMe = (CEcoLab1*)me;

    uint32_t i, j;
    complex_t res_dft[N], v_exp, tmp;

    /* Проверка указателей */
    if (me == 0 ) {
        return;
    }

    /* Output array should be >= initial array */
    if (v_in == NULL || v_out == NULL) return;

    for(j = 0; j < N; ++j) {
      res_dft[j].re = 0;
      res_dft[j].im = 0;

      for (i = 0; i < N; ++i) {
        /* Compute the principal Nth root of unity */
        v_exp.re = 0;
        v_exp.im = (-1 * 2 * PI * j * i) / N;

        pCMe->m_pICmplx->pVTbl->AddRef((IEcoComplex1*)pCMe);
        v_exp = pCMe->m_pICmplx->pVTbl->ExpComplex((IEcoComplex1*)pCMe, v_exp);
        pCMe->m_pICmplx->pVTbl->Release((IEcoComplex1*)pCMe);

        pCMe->m_pICmplx->pVTbl->AddRef((IEcoComplex1*)pCMe);
        pCMe->m_pICmplx->pVTbl->AddRef((IEcoComplex1*)pCMe);
        
        /* tmp.re = 0;
        tmp.im = v_in[i]; */
        tmp.re = v_in[i];
        tmp.im = 0;
        tmp = pCMe->m_pICmplx->pVTbl->MultiplyComplex((IEcoComplex1*)pCMe, tmp, v_exp);
        res_dft[j] = pCMe->m_pICmplx->pVTbl->AddComplex((IEcoComplex1*)pCMe, res_dft[j], tmp);
        pCMe->m_pICmplx->pVTbl->Release((IEcoComplex1*)pCMe);
        pCMe->m_pICmplx->pVTbl->Release((IEcoComplex1*)pCMe);
      }
    }

    /* Copy the result to the destination array */
    for(i = 0; i < N; ++i) {
      v_out[i].re = res_dft[i].re;
      v_out[i].im = res_dft[i].im;
    }
}

/*
 *
 * <сводка>
 *   Функция fft
 * </сводка>
 *
 * <описание>
 *   Функция считает Быстрое преобразование фурье со сложностью O(n*log(n))
 * </описание>
 *
 */
void ECOCALLMETHOD CEcoLab1_fft(/* in */ IEcoLab1* me, /* in */ uint32_t stride, /* in */ uint32_t N, /* in */ int32_t *v_in, /* out */ complex_t *v_out)
{
    CEcoLab1* pCMe = (CEcoLab1*)me;

    uint32_t k;
    complex_t t, tmp;

    /* Output array should be >= initial array */
    if (v_in == NULL || v_out == NULL) return;

    // At the lowest level pass through
    if (N == 1) {
        v_out[0].re = v_in[0];
        v_out[0].im = 0;
        return;
    }
    // Recursively split in two, then combine beneath.
    pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    pCMe->m_pVTblIEcoLab1->fft((IEcoLab1*)pCMe, 2*stride, N/2, v_in, v_out);
    pCMe->m_pVTblIEcoLab1->Release((IEcoLab1*)pCMe);

    pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1*)pCMe);
    pCMe->m_pVTblIEcoLab1->fft((IEcoLab1*)pCMe, 2*stride, N/2, v_in + stride, v_out + N/2);
    pCMe->m_pVTblIEcoLab1->Release((IEcoLab1*)pCMe);

    for (k = 0; k < N/2; k++) {
        t.re = v_out[k].re;
        t.im = v_out[k].im;

        /* Odd numbers */
        tmp.re = 0;
        tmp.im = 2 * PI * k / N;

        tmp = pCMe->m_pICmplx->pVTbl->ExpComplex((IEcoComplex1*)pCMe, tmp);
        tmp = pCMe->m_pICmplx->pVTbl->MultiplyComplex((IEcoComplex1*)pCMe, tmp, v_out[k + N/2]);
        v_out[k] = pCMe->m_pICmplx->pVTbl->AddComplex((IEcoComplex1*)pCMe, t, tmp);

        /* Even numbers */
        tmp.re = 0;
        tmp.im = 2 * PI * k / N;

        tmp = pCMe->m_pICmplx->pVTbl->ExpComplex((IEcoComplex1*)pCMe, tmp);
        tmp = pCMe->m_pICmplx->pVTbl->MultiplyComplex((IEcoComplex1*)pCMe, tmp, v_out[k + N/2]);
        v_out[k + N/2] = pCMe->m_pICmplx->pVTbl->SubComplex((IEcoComplex1*)pCMe, t, tmp);
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
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

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



    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);
	
    return result;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
    CEcoLab1_QueryInterface,
    CEcoLab1_AddRef,
    CEcoLab1_Release,
    CEcoLab1_dft,
    CEcoLab1_fft
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
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown* pIUnkSystem, /* in */ IEcoUnknown* pIUnkOuter, /* out */ IEcoLab1** ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1* pISys = 0;
    IEcoInterfaceBus1* pIBus = 0;
    IEcoInterfaceBus1MemExt* pIMemExt = 0;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoComplex1* pICmplx = 0;
    CEcoLab1* pCMe = 0;
    UGUID* rcidMem = (UGUID*)&CID_EcoMemoryManager1;
    UGUID* rcidCmplx = (UGUID*)&CID_EcoComplex1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
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
        rcidMem = (UGUID*)pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcidMem, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Получение интерфейса для работы с комплексными числами */
    pIBus->pVTbl->QueryComponent(pIBus, rcidCmplx, 0, &IID_IEcoComplex1, (void**) &pICmplx);

    /* Проверка */
    if (result != 0 && pICmplx == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1*)pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Сохранение указателя на интерфейс для работы комплексными числами */
    pCMe->m_pICmplx = pICmplx;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1*)pCMe;

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
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1* pIEcoLab1) {
    CEcoLab1* pCMe = (CEcoLab1*)pIEcoLab1;
    IEcoMemoryAllocator1* pIMem = 0;
    IEcoComplex1* pICmplx = 0;

    if (pIEcoLab1 != 0 ) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if ( pCMe->m_Name != 0 ) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if ( pCMe->m_pISys != 0 ) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);

        pICmplx = pCMe->m_pICmplx;
        pICmplx->pVTbl->Release(pICmplx);
    }
}
