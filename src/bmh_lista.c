#include "bmh_lista.h"

BmhStatus mostrar_informacoes_bmh_lista(BmhLista *lista, bool mostrar_info, bool mostrar_dados) { //Mostra Dados 
//Armazenados Na Lista
    if (lista == NULL) {
        if (BMH_DEBUG) printf("Mostrar Informações Bmh Lista: Esta Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if (lista->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Mostrar Informações Bmh Lista: Esta Lista Possui Um Erro!\n");
        return BMH_ERRO;
    }

    if (mostrar_info) {
        printf("Dados Lista: \n");
        printf("Quantidade de Dados: %d\n", lista->qtd_dados);
        printf("Largura do Vetor: %d\n", lista->tamanho);
        printf("Status Atual do Vetor: %d\n", lista->status);
    }

    if (mostrar_dados) {
        for (int i = 0; i < lista->tamanho; i++) {
            if (lista->dados[i] == NULL) printf("Dado %d: NULL\n", i + 1);
            else printf("Dado %d: %d\n", i + 1, *(int *)(lista->dados[i]));
        }
    }
    return BMH_OK;
}

BmhStatus criar_bmh_lista(BmhLista **ptr_para_lista) { /*Função Responsável Por Criar
A Bmh Lista */
    if (*ptr_para_lista != NULL) { //Verifica Se Lista Existe Para Realizar Criação
        if (BMH_DEBUG) printf("Criar Bmh Lista: Essa Lista Já Existe!\n");
        return BMH_ESTRUTURA_EXISTE;
    }

    *ptr_para_lista = calloc(1, sizeof(BmhLista));

    if (*ptr_para_lista == NULL) { //Verifica Se Calloc Não Falhou
        if (BMH_DEBUG) printf("Criar Bmh Lista: Erro Ao Alocar Memória!\n");
        return BMH_ERRO_AO_ALOCAR;
    }

    (*ptr_para_lista)->dados = NULL;
    (*ptr_para_lista)->tamanho = 0;
    (*ptr_para_lista)->qtd_dados = 0;
    (*ptr_para_lista)->status = BMH_OK; //Coloca Status Ok Na Lista

    if (BMH_DEBUG) printf("Criar Bmh Lista: Bmh Lista Criado!\n");
    return BMH_OK;
}

BmhStatus destruir_bmh_lista(BmhLista **ptr_para_lista) { /*Função Responsável Por
Limpar ou Destruir A Bmh Lista */
    if (*ptr_para_lista == NULL) {
        if (BMH_DEBUG) printf("Destruir Bmh Lista: Essa Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    for (int i = 0; i < (*ptr_para_lista)->qtd_dados; i++) {
        if ((*ptr_para_lista)->dados[i] != NULL) {;
            free((*ptr_para_lista)->dados[i]);
        }
        else continue;
    } 

    free((*ptr_para_lista)->dados);
    (*ptr_para_lista)->dados = NULL;
    free(*ptr_para_lista);
    *ptr_para_lista = NULL;
    if (BMH_DEBUG)printf("Destruir Bmh Lista: Bmh Lista Destruida\n");
    return BMH_OK;
}

static BmhStatus extender_bmh_lista(BmhLista **ptr_para_lista) { /*Função Responsável Por
Extender A Lista, Caso Este Esteja Cheio. Restrita às Funções Abstratas. Realiza A Verifiçação
Do Tamanho do Vetor Obs: Sempre Dobra Tamanho da Lista.*/
    if (*ptr_para_lista == NULL) {
        if (BMH_DEBUG) printf("Extender Bmh Lista: Essa Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if ((*ptr_para_lista)->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Extender Bmh Lista: Bmh Lista Está Com Um Erro!\n");
        return BMH_ERRO;
    }

    if ((*ptr_para_lista)->tamanho >= (*ptr_para_lista)->qtd_dados) {
        if (BMH_DEBUG) printf("Extender Bmh Lista: Bmh Lista Já Possui Tamanho Suficiente!\n");
        return BMH_OK;
    }

    if ((*ptr_para_lista)->tamanho == 0) {
        (*ptr_para_lista)->dados = calloc(1, sizeof(BmhDadoQlqr));
        if ((*ptr_para_lista)->dados == NULL) { //Realiza Verificação
        //Para Caso Calloc Não Consiga Alocar Espaço
            (*ptr_para_lista)->status = BMH_ERRO;
        }
        (*ptr_para_lista)->tamanho = 1; //Define Espaço Inicial Alocado
    }

    else {
        void **lista_temporaria = NULL; //Variável Auxiliar Para Transferir Dados
        (*ptr_para_lista)->tamanho *= 2; //Dobra O Tamanho da Lista
        unsigned int novo_t = (*ptr_para_lista)->tamanho; //Varíavel Para Facilitar Leitura

        lista_temporaria = calloc(novo_t, sizeof(BmhDadoQlqr));

        if (lista_temporaria == NULL) { //Verifica Se A Lista Auxiliar Conseguiu Ser
        //Alocada
            (*ptr_para_lista)->status = BMH_ERRO;
        }

        else {
            for (int i = 0; i < (*ptr_para_lista)->qtd_dados - 1; i++) { //
            //Transferência de Dados Para Lista Temporária
                lista_temporaria[i] = (*ptr_para_lista)->dados[i]; //Passagem dos Dados
            }

            free((*ptr_para_lista)->dados); //Libera Lista de Dados Antiga
            (*ptr_para_lista)->dados = lista_temporaria; //Recebe a Lista Auxiliar
        }
    }

    if ((*ptr_para_lista)->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Extender Bmh Lista: Bmh Lista Está Com Erro.\n");
        return BMH_ERRO;
    }

    if (BMH_DEBUG) printf("Extender Bmh Lista: Bmh Lista Foi Extendido!\n");
    return BMH_OK;
}

BmhStatus inserir_dado_no_bmh_lista(BmhLista **ptr_para_lista, BmhDadoQlqr dado) { /*Função Responsável Por 
Inserir um Dado No Bmh Vetor. Extende Vetor Por Conta Própria.*/ 
    if (*ptr_para_lista == NULL) {
        if (BMH_DEBUG) printf("Inserir Dado Na Bmh Lista: Esse Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if ((*ptr_para_lista)->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Inserir Dado Na Bmh Lista: Bmh Lista Está Com Um Erro!\n");
        return BMH_ERRO;
    }

    (*ptr_para_lista)->qtd_dados++; //Incrementa Um Dado Que É o a Ser Adicionado
    extender_bmh_lista(ptr_para_lista); //Verifica Se Precisa Extender Vetor

    if ((*ptr_para_lista)->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Inserir Dado na Bmh Lista: Ocorreu Um Erro Com A Lista.\n");
        (*ptr_para_lista)->tamanho = (*ptr_para_lista)->tamanho / 2;
        (*ptr_para_lista)->qtd_dados--;
        return BMH_ERRO;
    }

    (*ptr_para_lista)->dados[(*ptr_para_lista)->qtd_dados - 1] = 
    dado; //Vetor Recebe Dado Passado Pela Função

    if (BMH_DEBUG) printf("Inserir Dado Na Bmh Lista: O Dado foi inserido!\n");
    return BMH_OK;
}

BmhStatus trocar_dados_internos_bmh_lista(BmhLista **ptr_para_lista, int end_1, int end_2) {
//Troca Dois Dados De Posição No Bmh Vetor
    if (*ptr_para_lista == NULL) {
        if (BMH_DEBUG) printf("Trocar Dados Internos Bmh Lista: Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if ((*ptr_para_lista)->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Trocar Dados Internos Bmh Lista: Este Lista Possui Erro!\n");
        return BMH_ERRO;
    }

    else if ((*ptr_para_lista)->qtd_dados == 0) {
        if (BMH_DEBUG) printf("Trocar Dados Internos Bmh Lista: A Lista Não Possui Dados");
        return BMH_USO_INCORRETO;
    }

    if (end_1 < 0 || end_1 >= (*ptr_para_lista)->qtd_dados ||
    end_2 < 0 || end_2 >= (*ptr_para_lista)->qtd_dados) {
        if (BMH_DEBUG) printf("Trocar Dados Internos Bmh Lista: Algum Ou Ambos Endereços Digitados Não Existem No Vetor!\n");
        return BMH_USO_INCORRETO;
    }

    BmhDadoQlqr dado_armazenado = (*ptr_para_lista)->dados[end_1];
    (*ptr_para_lista)->dados[end_1] = (*ptr_para_lista)->dados[end_2];
    (*ptr_para_lista)->dados[end_2] = dado_armazenado;
    if (BMH_DEBUG) printf("Trocar Dados Internos Bmh Lista: Os Dados Foram Trocados!\n");
    return BMH_OK;
}

BmhStatus trocar_dado_bmh_lista(BmhLista **ptr_para_lista, int end, void *dado_nv) { /*Função Que Pega
Um Dado Que Já Existem Na Lista E Trocam Por Outro.*/
    if (*ptr_para_lista == NULL) {
        if (BMH_DEBUG) printf("Trocar Dado Na Bmh Lista: Essa Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if ((*ptr_para_lista)->status == BMH_ERRO) {
        if (BMH_DEBUG) printf("Trocar Dado Bmh Lista: A Lista Está Com Erro!\n");
        return BMH_ERRO;
    }

    else if ((*ptr_para_lista)->qtd_dados <= end) {
        if (BMH_DEBUG) printf("Trocar Dado Bmh Lista: Esse Endereço Não Existe Na Lista!\n");
        return BMH_ERRO;
    }

    BmhDadoQlqr dado_guardado = (*ptr_para_lista)->dados[end];
    (*ptr_para_lista)->dados[end] = dado_nv; //Atribui Dado Novo
    free(dado_guardado); //Libera Guarda Dado Antigo
    if (BMH_DEBUG) printf("Trocar Dado Bmh Lista: O Dado Foi Trocado!\n");
    return BMH_OK;
}

BmhStatus remover_elemento_da_bmh_lista(BmhLista **ptr_para_lista, int end) {
//Remove Elemento Do Vetor E Após Isso Preenche Seu Espaço Vazio Movendo Os Dados Existentes
    if (*ptr_para_lista == NULL) {
        if (BMH_DEBUG) printf("Remover Elemento Da Bmh Lista: Essa Lista Não Existe!\n");
        return BMH_ESTRUTURA_N_EXISTE;
    }

    else if ((*ptr_para_lista)->status == BMH_ERRO){
        if (BMH_DEBUG) printf("Remover Elemento Da Bmh Lista: Essa Lista Possui Um Erro!\n");
        return BMH_ERRO;
    }

    else if (end < 0 || end >= (*ptr_para_lista)->qtd_dados) {
        if (BMH_DEBUG) printf("Remover Elemento Da Bmh Lista: Este Endereço Está Ultrapassa Os Limites.\n");
        return BMH_USO_INCORRETO;
    }

    free((*ptr_para_lista)->dados[end]);

    for (int i = end; i < (*ptr_para_lista)->qtd_dados; i++) { //Preencher Espaço Vazio
        (*ptr_para_lista)->dados[end] = (*ptr_para_lista)->dados[end + 1]; //Recebe Próximo Elemento
    }

    (*ptr_para_lista)->tamanho--; //Diminui Tamanho
    if (BMH_DEBUG) printf("Remover Elemento da Bmh Lista: O Elemento Foi Removido!\n");
    return BMH_OK;
}