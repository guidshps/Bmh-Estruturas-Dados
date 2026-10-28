#ifndef BMH_ARVORE_BINARIA_H
#define BMH_ARVORE_BINARIA_H
#pragma once

/*
    Esse Arquivo É Uma Extensão Da Árvore N-Ária, Basicamente
    Se Usa As Estruturas de Dado Anteriores Para Formar Uma Árvore 
    Binária Com Os Casos Dela
*/

#include "bmh_arvore_n_aria.h"

BmhStatus insercao_ordenada_bmh_arvore_binaria(BmhArvoreN_Aria **ptr_para_arvore, 
BmhDadoEspecifico dado); //Insere Dados Ordenadamentes Em Uma Árvore Binária
BmhDadoQlqr busca_ordenada_bmh_arvore_binaria(BmhArvoreN_Aria *arvore_binaria, 
BmhDadoEspecifico dado); //Procura Dados Que Estejam Em Uma Árvore Binária Que Está Ordenada

#endif