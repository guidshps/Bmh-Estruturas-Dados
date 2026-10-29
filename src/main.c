#include "bmh_array.h"

int main() {
    BmhArray *array = NULL;
    criar_bmh_array(&array, 32);
    acessar_endereco_bmh_array(array, 20); 
    destruir_bmh_array(&array);

    return 0;
}