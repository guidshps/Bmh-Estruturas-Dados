#include "bmh_arvore_binaria.h"

typedef enum {
    BMH_ARV_BINARIA_ESQ = 0, //Onde Ficam Elementos Menores
    BMH_ARV_BINARIA_DIR = 1 //Onde Ficam Elementos Maiores
} BmhConstantesArvoreBinaria; /*Constante Para 
Facilitar Acesso Ou Leitura Nas Árvores Binárias */

BmhStatus insercao_ordenada_bmh_arvore_binaria(BmhArvoreN_Aria **ptr_para_arvore, 
BmhDadoEspecifico dado) { //Insere Ordenadamente Dados Na Árvore. 
    BmhNoArvoreN_Aria *no_criado = NULL; //Variável Auxiliar Para Criação Do Nó
    BmhNoArvoreN_Aria *no_atual = NULL; //Variável Auxiliar Para Navegar Na Árvore
    int altura_atual = 0; //Variável Que Conta Quanto Nó Atual Subiu Para Atualizações
    int *dado_convertido = NULL; //Variável Que Converte O Tipo De Dado Enviado

    if (*ptr_para_arvore == NULL) {
        if (BMH_DEBUG) printf("Insercão Ordenada Bmh Árvore Binária: Esta Árvore Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (dado == NULL) {
        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Este Dado Não Existe!\n");
        return BMH_USO_INCORRETO;
    }

    else if ((*ptr_para_arvore)->ftr_ramificacao != 2) {
        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Esta Árvore Não É Binária!\n");
        return BMH_USO_INCORRETO;
    }

    //Caso Não Exista Raiz Cria Uma 
    if ((*ptr_para_arvore)->no_raiz == NULL) {
        no_criado = criar_bmh_no_arvore_n_aria(dado, 0, NULL);
        if (no_criado == NULL) {
            if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Ocorreu Um Erro Ao Criar A Raiz!\n");
            return BMH_ERRO_AO_ALOCAR;
        }
        (*ptr_para_arvore)->no_raiz = no_criado;
        (*ptr_para_arvore)->qtd_nos = 1;
        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Raiz Foi Criada!\n");
    }

    else {
        no_atual = (*ptr_para_arvore)->no_raiz;
        dado_convertido = (int *) dado;

        while (true) {
            BmhStatus status_operacaoes = BMH_OK; //Status Das Operações Realizadas
            int *dado_atual = (int *) no_atual->dado; //Adapte Para Tipo De Dado Específico

            //Caso Que Não Existe Dados Na Árvore Binária (Caso 1)
            if (no_atual->qtd_nos_filhos == 0 && no_atual->nos_filhos == NULL) {
                status_operacaoes = extender_array_filhos_bmh_no_arvore_n_aria(&no_atual);
                if (status_operacaoes == BMH_ERRO_AO_ALOCAR) {
                    if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Não Foi Possível Extender Os Array Dos Filhos! (Caso 1)\n");
                    (*ptr_para_arvore)->status = BMH_ERRO; //Indica Erro Na Árvore
                    return BMH_ERRO_AO_ALOCAR; //Sai Caso Não Consiga Alocar Memória
                }
                
                no_criado = criar_bmh_no_arvore_n_aria(dado_convertido, 0, NULL);
                if (no_criado == NULL) { //Verifica Se Criou O Nó
                    if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Não Foi Possível Criar O Nó! (Caso 1)\n");
                    (*ptr_para_arvore)->status = BMH_ERRO;
                    return BMH_ERRO_AO_ALOCAR;
                }

                no_atual->nos_filhos[0] = no_criado; //Atribui Nó Filho
                no_atual->qtd_nos_filhos = 1; //Incrementa No Número De Filhos
                altura_atual = altura_atual + 1; //Incrementa Um A Mais Na Altura De Referência
                if (altura_atual > (*ptr_para_arvore)->altura) (*ptr_para_arvore)->altura = altura_atual; //Recebe Nova Altura Caso SejA mAIOR
                if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: A Inserção Foi Feita Corretamente! (Caso 1)\n");
                break; //Sai do Loop
            }

            else if (no_atual->qtd_nos_filhos == 2 && no_atual->nos_filhos != NULL) { //Caso Que Nó Já Tenha 2 Filhos (Caso 2)
                if (*dado_atual > *dado_convertido) no_atual = no_atual->nos_filhos[BMH_ARV_BINARIA_ESQ];
                else if (*dado_atual <= *dado_convertido) no_atual = no_atual->nos_filhos[BMH_ARV_BINARIA_DIR];
                altura_atual = altura_atual + 1; //Aumenta Altura De Referência, Pois Subiu na Árvore
            }

            else if (no_atual->qtd_nos_filhos == 1 && no_atual->nos_filhos != NULL) { //Caso 3 No Qual Árvore Já Possui Um Filho
                int *prox_dado = (no_atual->nos_filhos[0])->dado;

                if (prox_dado == NULL || dado_atual == NULL) {
                    if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Comportamento Inesperado (Caso 2)\n");
                    return BMH_ERRO;
                }

                else if (*dado_atual < *dado_convertido && *prox_dado > *dado_atual) { //Caso (3.1)
                    //Caso Que Dado Do Nó Atual É Menor Que O Dado Enviado E O Nó Filho Possui Um Dado Maior Que O Dado Do Pai
                    no_atual = no_atual->nos_filhos[0]; //Recebe Próximo Filho
                    altura_atual = altura_atual + 1; //Incrementa 1 Na Altura De Referência
                }

                else if (*dado_atual <= *dado_convertido && *prox_dado < *dado_atual) { //Caso (3.2)
                    //Caso Que Dado Do Nó Atual É Menor Que O Dado Enviado E O Nó Filho Possui Um Dado Menor Que O Dado Do Pai
                    status_operacaoes = extender_array_filhos_bmh_no_arvore_n_aria(&no_atual); //Extende Array Dos Filhos

                    if (status_operacaoes == BMH_ERRO_AO_ALOCAR) { //Verifica Se Conseguiu Alocar
                        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Erro Ao Extender Array Dos Filhos! (Caso 3.2)\n");
                        return BMH_ERRO_AO_ALOCAR;
                    }

                    no_criado = criar_bmh_no_arvore_n_aria(dado_convertido, 0, NULL); //Tenta Criar Nó

                    if (no_criado == NULL) { //Verifica Se Conseguiu Alocar
                        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Erro Ao Criar Nó! (Caso 3.2)\n");
                        return BMH_ERRO_AO_ALOCAR;
                    }

                    no_atual->nos_filhos[BMH_ARV_BINARIA_DIR] = no_criado; //Não É Necessário Deslocar Dado Menor, Pois Já Está Na Posição Correta
                    no_atual->qtd_nos_filhos++; //Incrementa A Quantidade De Filhos Que Possui
                    if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: O Dado Foi Inserido Corretamente! (Caso 2.2)\n");
                    break; //Sai do Loop 
                }

                else if (*dado_atual > *dado_convertido && *prox_dado < *dado_atual) { //Caso (3.3)
                    //Caso Que Dado Do Nó Atual É Maior Que O Dado Enviado E O Nó Filho Possui Um Dado Menor Que O Dado Do Pai
                    no_atual = no_atual->nos_filhos[0]; //Recebe Próximo Filho
                    altura_atual = altura_atual + 1; //Incrementa 1 Na Altura De Referência
                }

                else if (*dado_atual > *dado_convertido && *prox_dado > *dado_atual) { //Caso (3.4)
                    //Caso Que Dado Do Nó Atual É Menor Que O Dado Enviado E O Nó Filho Possui Um Dado Menor Que O Dado Do Pai
                    status_operacaoes = extender_array_filhos_bmh_no_arvore_n_aria(&no_atual); //Extende Array Dos Filhos

                    if (status_operacaoes == BMH_ERRO_AO_ALOCAR) { //Verifica Se Conseguiu Alocar
                        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Erro Ao Extender Array Dos Filhos! (Caso 3.4)\n");
                        return BMH_ERRO_AO_ALOCAR;
                    }

                    no_criado = criar_bmh_no_arvore_n_aria(dado_convertido, 0, NULL); //Tenta Criar Nó

                    if (no_criado == NULL) { //Verifica Se Conseguiu Alocar
                        if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: Erro Ao Criar Nó! (Caso 3.4)\n");
                        return BMH_ERRO_AO_ALOCAR;
                    }

                    no_atual->nos_filhos[BMH_ARV_BINARIA_DIR] = no_atual->nos_filhos[BMH_ARV_BINARIA_ESQ]; //Transfere Dado
                    no_atual->nos_filhos[BMH_ARV_BINARIA_ESQ] = no_criado; //Coloca Dado Menor Na Posição Correta
                    no_atual->qtd_nos_filhos++; //Incrementa A Quantidade De Filhos Que Possui
                    if (BMH_DEBUG) printf("Inserção Ordenada Bmh Árvore Binária: O Dado Foi Inserido Corretamente! (Caso 2.4)\n");
                    break; //Sai do Loop 
                }
            }
        }
    }

    return BMH_OK;
}

BmhDadoEspecifico busca_ordenada_bmh_arvore_binaria(BmhArvoreN_Aria *arvore_binaria, 
BmhDadoEspecifico dado) { /*Realiza Busca Ordenada Em Árvore Binária Que Está Ordenada
Necessário Definir Tipo De Dado, Nesse Caso Foi Para Inteiro (Devolve Endereço Do Dado)*/
    BmhNoArvoreN_Aria *no_atual = NULL; //Variável Para Navegar Na Árvore
    int *dado_convertido = NULL; //Definir Tipo De Dado Utilizado

    if (arvore_binaria == NULL) { //Verifica Se Árvore Existe
        if (BMH_DEBUG) printf("Busca Ordenada Bmh Árvore Binária: Árvore Não Existe!\n");
        return NULL;
    }

    else if (dado == NULL) { //Verifica Se Dado Existe
        if (BMH_DEBUG) printf("Busca Ordenada Bmh Árvore Binária: Não É Possível Buscar Um Dado Nulo!\n");
        return NULL;
    }

    no_atual = arvore_binaria->no_raiz; //Recebe Nó Raiz Para Iniciar Navegação
    dado_convertido = (int *) dado; //Converte Para Tipo De Dado Utilizado

    while (true) {
        int *dado_atual = no_atual->dado; //Definir Tipo De Dado Utilizado

        if (*dado_convertido == *dado_atual) { //Compara Dados
            if (BMH_DEBUG) printf("Busca Ordenada Bmh Árvore Binária: Dado Achado! (Endereço Do Dado Devolvido)\n");
            return dado_atual; //Retorna Endereço De Dado Encontrado
        }

        else if (no_atual->nos_filhos == NULL && no_atual->qtd_nos_filhos == 0) { //Verifica Se Pode Continuar
            if (BMH_DEBUG) printf("Busca Ordenada Bmh Árvore Binária: O Elemento Não Foi Achado! (Endereço Nulo Devolvido)\n");
            return NULL; //Devolve Endereço Nulo
        }

        else if (no_atual->qtd_nos_filhos == 1 && no_atual->nos_filhos != NULL) {
            int *prox_dado = (int *)no_atual->nos_filhos[0]->dado; //Definir Tipo De Dado Utilizado

            //Verifica Se Próximo Dado É Maior Que O Atual E Se Dado Enviado É Maior Ou Igual O Próximo Dado
            if (*dado_atual <= *prox_dado && *dado_convertido >= *dado_atual) no_atual = no_atual->nos_filhos[0];
            //Verifica Se Próximo Dado É Menor Que O Atual E Se Dado Enviado É Menor Ou Igual O Próximo Dado
            else if (*dado_atual >= *prox_dado && *dado_convertido <= *dado_atual) no_atual = no_atual->nos_filhos[0];
            else {
                if (BMH_DEBUG) printf("Busca Ordenada Bmh Árvore Binária: O Elemento Não Foi Achado! (Endereço Nulo Devolvido)\n");
                return NULL; //Retorna Endereço Nulo
            }
        }

        else if (no_atual->qtd_nos_filhos == 2 && no_atual->nos_filhos != NULL) { //Caso O Nó Esteja Com O Máximo De Folhas
            if (*dado_atual > *dado_convertido) no_atual = no_atual->nos_filhos[BMH_ARV_BINARIA_ESQ];
            else if (*dado_atual < *dado_convertido) no_atual = no_atual->nos_filhos[BMH_ARV_BINARIA_DIR];
        }
    }

    if (BMH_DEBUG) printf("Busca Ordenada Bmh Árvore Binária: Comportamento Indevido!\n");
    return NULL;
}