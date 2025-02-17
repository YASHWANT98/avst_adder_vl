#include "Vadder_avst.h"

Vadder_avst* create_Vadder_avst() {
    return new Vadder_avst();
}

void eval (Vadder_avst* obj) {
    obj->eval();
}

void finalize (Vadder_avst* obj) {
    obj->final();
}
