#ifndef COMUM_BMH_H
#define COMUM_BMH_H
#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define bmh_calloc calloc //Apelido Para A Função Calloc
#define bmh_malloc malloc //Apelido Para A Função Malloc
#define bmh_realloc realloc //Apelido Para A Função Realloc
#define bmh_free free //Apelido Para A Função Free

typedef enum BmhStatus {
    BMH_OK = 0, BMH_ERRO_AO_ALOCAR = 1, BMH_ESTRUTURA_EXISTE = 2, 
    BMH_ESTRUTURA_N_EXISTE = 3, BMH_ERRO = 4, BMH_USO_INCORRETO = 5
} BmhStatus; //Retorna Status De Operações Realizadas

typedef struct BmhDado {
    void *ptr_dado; //Ponteiro Para O Dado
    size_t qtd_bytes; //Quantidade De Bytes Do Dado
} BmhDado; //Estrutura Que Contém Um Dado Específico Ou Qualquer

#endif