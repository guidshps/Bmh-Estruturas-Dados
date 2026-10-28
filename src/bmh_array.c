#include "bmh_array.h"

BmhStatus criar_bmh_array(BmhArray **ptr_array, size_t t_dados) { //Cria Bmh Array
    if (*ptr_array != NULL) { //Verifica Se Ponteiro Exsite
        bmh_log_fracasso("Criar Bmh Array: Este Array Já Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (t_dados <= 0) { //Verifica Se Tamanho Dos Dados É Válido
        bmh_log_fracasso("Criar Bmh Array: Tamanho De Dado Inválido!");
        return BMH_USO_INCORRETO;
    }

    *ptr_array = bmh_calloc (1, sizeof(BmhArray)); //Tenta Alocar Memória

    if (*ptr_array == NULL) { //Verifica Se Conseguiu Alocar Espaço
        bmh_log_avisar("Criar Bmh Array: Erro Ao Alocar Memória!");
        return BMH_ERRO_AO_ALOCAR;
    }

    (*ptr_array)->t_dados = t_dados;
    bmh_log_sucesso("Criar Bmh Array: Sucesso Ao Criar Bmh Array!");
    return BMH_OK;
}

BmhStatus destruir_bmh_array(BmhArray **ptr_array) { //Destroí Bmh Array
    if (*ptr_array == NULL) { //Verifica Se Ponteiro Exsite
        bmh_log_fracasso("Destruir Bmh Array: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }

    if ((*ptr_array)->dados != NULL) { //Verifica Se Existem Dados
        bmh_free((*ptr_array)->dados); //Libera Lista De Dados
    }

    bmh_free(*ptr_array); //Libera Memória
    *ptr_array = NULL; //Define Como Valor Não Existente

    bmh_log_sucesso("Destruir Bmh Array: Array Destruido Com Sucesso!");
    return BMH_OK;
}

static BmhStatus talvez_aumente_bmh_array(BmhArray **ptr_array) { //Aumenta Array Caso Seja Necessário
    BmhPonteiroQualquer ptr_auxiliar = NULL; /*Variável Auxiliar Para
    Realizar Alocação De Memória E Transferência De Dados.*/

    if (*ptr_array == NULL) {
        bmh_log_fracasso("Aumentar Bmh Array: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }
    
    if ((*ptr_array)->q_dados > (*ptr_array)->lar) { //Verifica Se Lista Conforta Dado
        unsigned int tamanho_antigo = (*ptr_array)->lar; //Tamanho Antigo Do Array
        unsigned int novo_tamanho = tamanho_antigo * (1 + FATOR_CRESCIMENTO_BMH_ARRAY); /*Aumenta 
        Array Conforme A Funçaõ*/

        ptr_auxiliar = calloc(novo_tamanho, (*ptr_array)->t_dados); //Tenta Criar Novo Array

        if (ptr_auxiliar == NULL) {
            bmh_log_avisar("Aumentar Bmh Array: Falha Ao Alocar Ponteiro Auxiliar!");
            return BMH_ERRO_AO_ALOCAR;
        }

        BmhByte *ptr_auxiliar_convertido = (BmhByte *)ptr_auxiliar;
        BmhByte *ptr_array_convertido = (BmhByte *)(*ptr_array)->dados;

        for (int i = 0; i < tamanho_antigo * (*ptr_array)->t_dados; i++) {
            ptr_auxiliar_convertido[i] = ptr_array_convertido[i]; //Transfere Dados
        }

        free(ptr_array_convertido); //Limpa Lista Antiga De Dados
        (*ptr_array)->dados = ptr_auxiliar_convertido; //Recebe Lista Com Dados Novos
        (*ptr_array)->lar = novo_tamanho; //Atualiza Novo Tamanho Da Lista
    }
    return BMH_OK;
}

BmhStatus adicionar_dado_bmh_array(BmhArray **ptr_array, BmhPonteiroQualquer dado,
BmhAtribuicao metodo_atribuicao) { //Atribui Dado Para O Array
    if (*ptr_array == NULL) { //Verifica Se Array Existe
        bmh_log_fracasso("Adicionar Dado Bmh Array: Este Array Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (dado == NULL) { //Verifica Se Dado Existe
        bmh_log_fracasso("Adicionar Dado Bmh Array: Este Dado Não Existe!");
        return BMH_USO_INCORRETO;
    }

    else if (metodo_atribuicao == NULL) { //Verifica Se Existe Como Atribuir Dado
        bmh_log_fracasso("Adicionar Dado Bmh Array: Não Existe Método De Atribuir O Dado!");
        return BMH_USO_INCORRETO;
    }
    
    (*ptr_array)->q_dados++; //Incrementa Quantidade De Dados Para Se Referenciar

    if (talvez_aumente_bmh_array(ptr_array) != BMH_OK) { /*Verifica Se Conseguiu Aumentar 
    Tamanho Do Array Ou Se Está Tudo Certo*/
        bmh_log_fracasso("Adicionar Dado Bmh Array: Algo Aconteceu Errado Ao Aumentar O Array!\n");
        return BMH_ERRO; //Retorna Erro Para O Usuário
    }

    metodo_atribuicao(ptr_array, dado); //Atribui Dado Na Array

    return BMH_OK; //Retorna Operação Sucedida Caso Dê Certo
}