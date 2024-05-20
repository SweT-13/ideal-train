#ifndef TAPESORTER_H
#define TAPESORTER_H

#include <stdint.h>
#include "TapeInterface/ITape.h"

class TapeSorter {
public:
    TapeSorter(int64_t memoryLimit);
    void sort(ITape &inputTape, ITape &outputTape);

private:
    int64_t _memoryLimit;
};

#endif
