#include "err.h"
#include "vm.h"
#include "parser.h"

int main(int argc, char *argv[]){
    ensuref(argc == 2, "Two arguments must be given.");
    run(parse(argv[1]));
}