#ifndef BMH_ARRAY_H
#define BMH_ARRAY_H

#include "comum_bmh.h"

#define FATOR_CRESCIMENTO_BMH_ARRAY 0.12 /*Valor Que Indica Quantos % Vai Crescer 
O Array Ao Aumentar O Array Dos Dados, Ou Seja, 
TAMANHO_ATUAL * (1 + "FATOR_CRESCIMENTO_BMH_ARRAY") */

typedef struct BmhArray {
    BmhPonteiroQualquer dados; //Array Dos Dados
    size_t t_dados; //Tamanho Que Tipo Dado Possui
    size_t q_dados; //Quantidade De Dados
    size_t lar; //Tamanho Atual Do Array
} BmhArray; //Estrutura Que Armazena Lista Com Dados Do Mesmo Tipo

BmhStatus criar_bmh_array(BmhArray **ptr_array, size_t t_dados); //Cria Bmh Array 
BmhStatus destruir_bmh_array(BmhArray **ptr_array); //Destroí Bmh Array

#endif