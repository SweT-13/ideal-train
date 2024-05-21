#ifndef TAPESORTER_H
#define TAPESORTER_H

#include <stdint.h>
#include <stdexcept>
#include <fstream>
#include "TapeInterface/ITape.h"
#include "TapeInterface/FileTape.h"

class TapeSorter
{
public:
    TapeSorter(int64_t memoryLimit);

    void sort(ITape &inputTape, ITape &outputTape);

private:
    void merge(ITape &left, ITape &right, ITape &enter);
    int64_t _memoryLimit;
};

#endif
