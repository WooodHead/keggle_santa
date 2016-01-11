#include "file_provider.h"

file_provider * __prov = nullptr;

const file_provider & file_prov(){
    if(__prov == nullptr)
        __prov = new file_provider();

    return *__prov;
}
