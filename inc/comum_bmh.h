#ifndef COMUM_BMH_H
#define COMUM_BMH_H
#pragma once

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define BMH_DEBUG 1

typedef enum {
    BMH_OK = 0, BMH_ERRO_AO_ALOCAR = 1, BMH_ESTRUTURA_EXISTE = 2, 
    BMH_ESTRUTURA_N_EXISTE = 3, BMH_ERRO = 4, BMH_USO_INCORRETO = 5
} BmhStatus;

typedef BmhStatus(BmhChamadoFuncao)(void *, void*); /*Usado Para Chamar Funções Para Conseguir Generalizar o Código*/
typedef void * BmhDadoQlqr; //Pode Atribuir Qualquer Tipo De Dado
typedef void * BmhDadoEspecifico; //Recebe Apenas Um Tipo De Dado

#endif