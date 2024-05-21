#include "TapeSorter.h"

TapeSorter::TapeSorter(int64_t memoryLimit) : _memoryLimit(memoryLimit) {}

void TapeSorter::merge(ITape &left, ITape &right, ITape &enter)
{
    while (enter.getCurrentPosition() <= enter.getSize() - 1)
    {
        enter.writen(left.read() < right.read() ? left.readn() : right.readn());
        // left.read() < right.read() ? left.shiftCursor(left.getCurrentPosition() + 1) : right.shiftCursor(right.getCurrentPosition() + 1);
        if (left.getCurrentPosition() == left.getSize() - 1)
        {
            while (right.getCurrentPosition() <= right.getSize() - 1)
            {
                enter.writen(right.readn());
            }
            return;
        }
        if (right.getCurrentPosition() <= right.getSize() - 1)
        {
            while (left.getCurrentPosition() == left.getSize() - 1)
            {
                enter.writen(left.readn());
            }
            return;
        }
    }
}

void TapeSorter::sort(ITape &inTape, ITape &outTape)
{
    // memoryLimit это байты для получения количества возможно сохраняемых элементов надо бы разделить на 4
    // ?надо бы использовать вектора?
    int64_t n = inTape.getSize();
    std::streampos i = 0;
    std::streampos j = 0;
    int64_t tmp = 0;

    int64_t availableSize = (_memoryLimit - sizeof(n) - sizeof(i) - sizeof(j) - sizeof(tmp)) / 4;
    if (availableSize <= 0)
    {
        throw std::invalid_argument("available memory absent");
    }
    int32_t *ram = new int32_t[availableSize];
    // Простите, но я уже чет подзапутался в мыслях поэтому буду делеть в лоб
    // Планируется сделать что то на подобии алгоритма быстрой сортировки
    availableSize--;
    //уф, осталось только оперативу сортирануть и прописать логику мерджа до верхнего уровня
    if (availableSize == 2)
    {
        ITape left();
        ITape right();
    }
    if (availableSize >= 3)
    {
        for (i = 0; i < n - availableSize; i += 1)
        {
            ram[availableSize] = 0;
            for (j = 0; j < availableSize; j += 1)
            {
                ram[availableSize] += ram[j] = inTape.read();
                inTape.shiftCursor(i + j);
            }
            ram[availableSize] /= availableSize;
            for (j = 0; j < availableSize; j += 1)
            {
                ram[availableSize] += ram[j] = inTape.read();
                inTape.shiftCursor(i + j);
            }
        }
    }
}