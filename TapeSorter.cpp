#include "TapeSorter.h"

TapeSorter::TapeSorter(int64_t memoryLimit) : _memoryLimit(memoryLimit) {}

void TapeSorter::sort(ITape &inTape, ITape &outTape)
{
// memoryLimit это байты для получения количества возможно сохраняемых элементов надо бы разделить на 4
// ?надо бы использовать вектора?
int64_t availableSize = _memoryLimit/4;

int32_t *ram = new int32_t[availableSize];




}