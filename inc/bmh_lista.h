#ifndef BMH_LISTA_H
#define BMH_LISTA_H

#include "comum_bmh.h"

typedef struct BmhLista {
    BmhDadoQlqr *dados; //Array Dos Dados
    BmhStatus status; //Indica A Situação Atual Da Lista
    int qtd_dados; //Armazena A Quatidade De Dados Da Lista
    int tamanho; //Armezena O Tamanho Da Lista De Dados
} BmhLista; /*É Uma Lista Que Armazena Qualquer Tipo De Dado, Apesar Que Não Consegue Indentificar
O Tipo De Dado Que Está Guardado.*/

BmhStatus mostrar_informacoes_bmh_lista(BmhLista *lista, bool mostrar_info, bool mostrar_dados); //Mostra Informações Da Lista
BmhStatus criar_bmh_vetor(BmhLista **ptr_para_vetor); //Cria Bmh Lista
BmhStatus destruir_bmh_lista(BmhLista **ptr_para_vetor); //Destroi ou Limpa Bmh Vetor
BmhStatus inserir_dado_no_bmh_lista(BmhLista **ptr_para_vetor, BmhDadoQlqr dado); //Insere Dado Na Bmh Lista
BmhStatus trocar_dados_internos_bmh_lista(BmhLista **ptr_para_vetor, int end_1, int end_2); //Realiza Uma Troca Da Posição Dos Dados
BmhStatus trocar_dado_bmh_lista(BmhLista **ptr_para_vetor, int end, void *dado_nv); //Troca Dado Existente Por Outro
BmhStatus remover_elemento_da_bmh_lista(BmhLista **ptr_para_vetor, int end); //Remove Elemento E Preenche Espaço Vazio Movendo Os Elementos Existentes

#endif