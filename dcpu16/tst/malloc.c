#include <dcpulib.h>

int main() {
    unsigned i = findHeapSize(1, 0x7FFF);   
    printf("Max heapsize: %u\n", i);
    return 0;
}

unsigned findHeapSize(unsigned min, unsigned max) {
    unsigned test = (min + max)/2;
    void* p = malloc(test);

    //printf("test %u words (%u, %u)\n", test, min, max);

    if (p) {
        //printf("pass! (%x)\n", p);
        free(p);
        if ( test + 1 == max ) {
            return test;
        }
        return findHeapSize(test, max);
    }
    else {
        //printf("fail!\n");
        return findHeapSize(min, test);
    }
}
