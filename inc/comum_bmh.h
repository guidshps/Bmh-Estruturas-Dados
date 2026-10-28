#ifndef COMUM_BMH_H
#define COMUM_BMH_H
#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BMH_DEBUG 1

/*
    Ao Ínves de Usar Um Comparação Ímplicita Use Comparadores Internos
*/
typedef enum {
    BMH_OK = 0, BMH_ERRO_AO_ALOCAR = 1, BMH_ESTRUTURA_EXISTE = 2, 
    BMH_ESTRUTURA_N_EXISTE = 3, BMH_ERRO = 4, BMH_USO_INCORRETO = 5
} BmhStatus;

typedef enum {
    BMH_DADOS_IGUAIS = 0, BMH_DADOS_DIFERENTES = 1,
    BMH_DADO_1_MAIOR_QUE_2 = 2, BMH_DADO_2_MAIOR_QUE_1 = 3,
    BMH_DADO_1_MENOR_QUE_2 = 4, BMH_DADO_2_MENOR_QUE_1 = 5,
    BMH_DADO_1_NAO_EXISTE = 6, BMH_DADO_2_NAO_EXISTE = 7,
} BmhComparadorStatus;

typedef void * BmhDadoGenerico; //Pode Receber Tanto Quanto Dado Especifico E Qualquer

typedef BmhStatus(BmhChamadoFuncao1)(BmhDadoGenerico); //Usado Para Chamar Funções
typedef BmhStatus(BmhChamadoFuncao2)(BmhDadoGenerico, BmhDadoGenerico); //Usado Para Chamar Funções
typedef BmhStatus(BmhChamadoFuncao3)(BmhDadoGenerico, BmhDadoGenerico, BmhDadoGenerico); //Usado Para Chamar Funções
typedef BmhStatus(BmhChamadoFuncao4)(BmhDadoGenerico, BmhDadoGenerico, BmhDadoGenerico); //Usado Para Chamar Funções

typedef BmhComparadorStatus(BmhComparador)(BmhDadoGenerico, BmhDadoGenerico); //Método Usado Para Comparações
typedef BmhDadoGenerico BmhDadoQlqr; //Pode Atribuir Qualquer Tipo De Dado
typedef BmhDadoGenerico BmhDadoEspecifico; //Recebe Apenas Um Tipo De Dado

#endif