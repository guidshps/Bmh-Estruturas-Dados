#ifndef BMH_ARVORE_BINARIA_H
#define BMH_ARVORE_BINARIA_H
#pragma once

#include "comum_bmh.h"

typedef struct BmhNoArvoreN_Aria {
    BmhDadoQlqr dado; //Contém o Dado Efetivo do Nó
    struct BmhNoArvoreN_Aria **nos_filhos; //Filhos Que Ela Possui
    int qtd_nos_filhos; //Quantidade De Nós Filhos Salvos 
} BmhNoArvoreN_Aria; //Nós da Árvore N-Ária

typedef struct BmhArvoreN_Aria {
    BmhNoArvoreN_Aria *no_raiz; //Nó Inicial da Árvore
    BmhStatus status; //Indica A Situação Atual da Árvore
    unsigned int qtd_nos; //Quantidade de Nós Existentes na Árvore
    unsigned int ftr_ramificacao; //Quantidade De Nós Filhos Que Um No Possui, Caso Seja Nulo Não Existe
    unsigned int altura; //Indica A Altura Da Árvore
} BmhArvoreN_Aria; //Árvore Que Possui No Possui N Filhos

BmhStatus criar_bmh_arvore_n_aria(BmhArvoreN_Aria **ptr_para_arvore, 
int ftr_ramificacao); /*Cria Árvore e Indica Qtd Máximas De Filhos Que
Cada Nó Irá Possuir */
BmhStatus destruir_sub_bmh_arvore_n_aria(BmhNoArvoreN_Aria **ptr_no_destino); /*
Destroi Uma Sub-Árvore N-Ária, Vale Ressaltar Que A Raiz É Uma Sub-Árvore.*/
BmhStatus destruir_bmh_arvore_n_aria(BmhArvoreN_Aria **ptr_para_arvore); /*
Destroi Toda Árvore N-Ária.*/
BmhStatus inserir_dado_bmh_arvore_n_aria(BmhArvoreN_Aria **ptr_para_arvore,
BmhDadoQlqr dado, BmhChamadoFuncao metodo_insercao); /* Insere Dados Conforme
O Método Imposto Caso Não Seja Colocada Não Funciona */
BmhNoArvoreN_Aria *criar_bmh_no_arvore_n_aria(BmhDadoQlqr dado, 
int qtd_filhos, BmhNoArvoreN_Aria **nos_filhos); /*Cria Um Nó Genérico Da
Árvore N-Ária*/
BmhStatus extender_array_filhos_bmh_no_arvore_n_aria(BmhNoArvoreN_Aria **ptr_no); 
/*Aumenta O Array Dos Filhos Em Uma Espaço E Transfere Os Dados Antigos.
Obs: Aumenta Um Espaço De Cada Vez*/
BmhStatus diminuir_array_filhos_bmh_no_arvore_n_aria(BmhNoArvoreN_Aria **ptr_no); 
/*Diminui O Array Dos Filhos E Transfere Dados Do Array Antigo, Caso Todos Dados
Existam Um Dado Ele É Removido Ou Deletado. Obs: Diminui Um Espaço De Cada Vez*/

#endif