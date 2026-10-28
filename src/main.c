#include "bmh_array.h"

int main() {
    BmhArray *array = NULL;

    criar_bmh_array(&array, 32); 
    destruir_bmh_array(&array);

    return 0;
}