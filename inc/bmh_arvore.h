#ifndef BMH_ARVORE_H
#define BMH_ARVORE_H
#pragma once

#include "comum_bmh.h"

typedef struct BmhNoArvore {
    BmhPonteiroQualquer dado; //Dado Do Nó
    struct BmhNoArvore *filho_esq; //Filho Onde Fica Elemento Menor
    struct BmhNoArvore *filho_dir; //Filho Onde Fica Elemento Maior
} BmhNoArvore; //Nó Da Arvore Binária

typedef struct BmhArvore {
    BmhNoArvore *no_raiz; //Nó Raiz Da Árvore
    size_t qtd_nos; //Quantidade de Nós Na Árvore
    size_t altura; //Altura Da Árvore
    size_t t_dados; //Tamanho Dos Dados Da Árvore
} BmhArvore; //Árvore Binária

//Definição dos Métodos da Bmh Árvore

BmhStatus criar_bmh_arvore(
    BmhArvore **ptr_arvore, //Ponteiro Para Árvore Destino
    size_t t_dados //Tamanho Dos Dados Que Os Nós Irão Guardar
); //Cria Árvore Que Possui Dados Com Tamanho De Dados Especificado

BmhStatus destruir_bmh_arvore(
    BmhArvore **ptr_arvore //Ponteiro Para Árvore Destino
); //Destrói Árvore Enviada Pelo Usuário

BmhNoArvore buscar_dado_bmh_arvore(
    BmhArvore *arvore, //Árvore Que Irá Ser Procurado Os Dados
    BmhPonteiroQualquer dado, //Dado Que Irá Ser Procurado
    BmhComparador metodo_comparacao //Metódo Para Comparar Dados
); //Busca Dado Na Árvore E Devolve Endereço

#endif