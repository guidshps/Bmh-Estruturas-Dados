#include "bmh_arvore_n_aria.h"

BmhStatus criar_bmh_arvore_n_aria(BmhArvoreN_Aria **ptr_para_arvore, 
int ftr_ramificacao) { /*Cria Árvore e Indica Qtd De Filhos Que
Cada Nó Irá Possuir */
    if (*ptr_para_arvore != NULL) { //Verifica Se Árvore Já Existe
        if (BMH_DEBUG) printf("Criar Árvore N-Ária: Essa Árvore Já Existe!\n");
        return BMH_ESTRUTURA_EXISTE;
    }

    else if (ftr_ramificacao <= 0) { //Verifica Se É Valido O Fator
    //De Ramificação
        if (BMH_DEBUG) printf("Criar Árvore N-Ária: O Fator De Ramificação Deve Ser Maior Que 0!\n");
        return BMH_ERRO;
    }

    *ptr_para_arvore = calloc(1, sizeof(BmhArvoreN_Aria));

    if (ptr_para_arvore == NULL) { //Verifica Se Alocou Memória
        if (BMH_DEBUG) printf("Criar Árvore N-Ária: Aconteceu Um Erro Com A Árvore N-Ária.\n");
        return BMH_ERRO;
    }

    (*ptr_para_arvore)->no_raiz = NULL;
    (*ptr_para_arvore)->altura = 0;
    (*ptr_para_arvore)->qtd_nos = 0;
    (*ptr_para_arvore)->ftr_ramificacao = ftr_ramificacao;
    (*ptr_para_arvore)->status = BMH_OK;
    if (BMH_OK) printf("Criar Árvore N-Ária: A Árvore Foi Criada Corretamente!\n");
    return BMH_OK;
}

BmhStatus inserir_dado_bmh_arvore_n_aria(BmhArvoreN_Aria **ptr_para_arvore, 
BmhDadoQlqr dado, BmhChamadoFuncao metodo_insercao) { /*Função Que Insere Dado
Conforme O Método De Inserção Proposto*/
    if (*ptr_para_arvore == NULL) { /*Verifica Se A Árvore Existe*/
        if (BMH_DEBUG)("Inserir Dado Em Árvore N-Ária: Esta Árvore Não Existe.\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if ((*ptr_para_arvore)->status == BMH_ERRO) { /*Verifica Se Árvore 
    Está Com Erro */
        if(BMH_DEBUG)printf("Inserir Dado Em Árvore N-Ária: Esta Árvore Possui Um Erro.\n");
        return BMH_ERRO;
    }

    else if (metodo_insercao == NULL) { /*Verifica Se Existe 
    Método De Inserção.*/
        if (BMH_DEBUG) printf("Inserir Dado Em Árvore N-Ária: Método de Inserção Não Existe.\n");
        return BMH_USO_INCORRETO;
    }

    //Chama Método de Inserção Proposto Enviado
    BmhStatus retorno_status = metodo_insercao(ptr_para_arvore, dado);

    return retorno_status; //Retorna Status Do Método De Inserção
}

BmhNoArvoreN_Aria *criar_bmh_no_arvore_n_aria(BmhDadoQlqr dado, 
int qtd_filhos, struct BmhNoArvoreN_Aria **nos_filhos) { /* Função Auxiliar Que Cria Um Nó Da Árvore N-Aria*/
    BmhNoArvoreN_Aria *no_criado = NULL;
    no_criado = calloc(1, sizeof(BmhNoArvoreN_Aria));
    if (no_criado == NULL) return NULL; //Verifica Se Calloc Funcionou
    no_criado->dado = dado;
    no_criado->qtd_nos_filhos = qtd_filhos;
    no_criado->nos_filhos = nos_filhos;
    if (BMH_DEBUG) printf("Criar Bmh Nó Árvore N-Ária: O Nó Foi Criado Com Sucesso!\n");
    return no_criado; //Retorna No Criado
}

BmhStatus extender_array_filhos_bmh_no_arvore_n_aria(BmhNoArvoreN_Aria **ptr_no) {
/*Aumenta O Array Dos Filhos Em Uma Espaço E Transfere Os Dados Antigos.
Obs: Aumenta Um Espaço De Cada Vez*/
    BmhNoArvoreN_Aria **nos_filhos_aux = NULL;
    int lar_array_filhos; //Largura do Array Dos Filhos

    if (ptr_no != NULL) {
        if (BMH_DEBUG) printf("Extender Array Filhos Bmh Nó Árvore N-Ária: Este Nó Não Existe.\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    lar_array_filhos = (*ptr_no)->qtd_nos_filhos + 1; //Incrementa 1 Na Quantidade De Filhos
    nos_filhos_aux = calloc(lar_array_filhos, sizeof(BmhNoArvoreN_Aria*)); //Tenta Aloca Memória

    if (nos_filhos_aux == NULL) { //Verifica Se Conseguiu Alocar Memória
        if (BMH_DEBUG) printf("Extender Array Filhos Bmh Nó Árvore N-Ária: Ocorreu Um Erro Na Alocação De Memória.\n");
        return BMH_ERRO;
    }

    for (int i = 0; i < (*ptr_no)->qtd_nos_filhos; i++) { /*
    Transfere Dados Para Novo Array*/
        nos_filhos_aux[i] = (*ptr_no)->nos_filhos[i];
    }

    free((*ptr_no)->nos_filhos); //Limpa Array Antigo Utilizado
    (*ptr_no)->nos_filhos = nos_filhos_aux; //Atribui Novo Array
    if (BMH_DEBUG) printf("Extender Array Filhos Bmh Nó Árvore N-Ária: O Array Foi Extendido!\n");
    return BMH_OK;
}