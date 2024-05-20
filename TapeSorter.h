#ifndef TAPESORTER_H
#define TAPESORTER_H

#include "TapeInterface/fileTape.h"

class TapeSorter {
public:
    TapeSorter(size_t memoryLimit);
    void sort(Tape &inputTape, Tape &outputTape);

private:
    size_t memoryLimit;
};

#endif
