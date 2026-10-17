#ifndef BMH_ARVORE_BINARIA_H
#define BMH_ARVORE_BINARIA_H
#pragma once

/*
    Esse Arquivo É Uma Extensão Da Árvore N-Ária, Basicamente
    Se Usa As Estruturas de Dado Anteriores Para Formar Uma Árvore 
    Binária Com Os Casos Dela
*/

#include "bmh_arvore_n_aria.h"

typedef enum {
    BMH_ARV_BINARIA_ESQ = 0,
    BMH_ARV_BINARIA_DIR = 1
} BmhConstantesArvoreBinaria; /*Constante Para 
Facilitar Acesso Ou Leitura Nas Árvores Binárias */

typedef struct BmhArvoreN_Aria BmhArvoreN_Aria; 
typedef enum BmhStatus BmhStatus; 
typedef struct BmhDado BmhDado;

BmhStatus insercao_desordenada_bmh_arvore_binaria(BmhArvoreN_Aria **ptr_para_arvore, 
BmhDado dado); /*Insere Dados De Forma Que A Árvore Fique Completa*/
BmhStatus insercao_ordenada_bmh_arvore_binaria(BmhArvoreN_Aria **ptr_para_arvore, 
BmhDado dado); /*Insere Ordenadamente Dados Na Árvore.*/
BmhStatus balancear_bmh_arvore_binaria(BmhArvoreN_Aria **ptr_para_arvore); /*
Balanceia Árvore Binária,*/

#endif