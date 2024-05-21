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
    int64_t n = inTape.getSize(); // ??Нужна ли??
    int64_t i = 0;
    int64_t j = 0;
    int64_t a = 0;
    int64_t tmp = 0;

    int64_t availableSize = (_memoryLimit - sizeof(n) - sizeof(n) - sizeof(i) - sizeof(j) - sizeof(tmp)) / 4;
    if (availableSize <= 0)
    {
        throw std::invalid_argument("available memory absent");
    }
    int32_t *ram = new int32_t[availableSize];
    n = n / availableSize;
    for (a = 0; a < n; a++)
    {
        // input ram
        for (i = 0; i < availableSize; i++)
        {
            ram[i] = inTape.readn();
        }
        // ram sort
        for (i = 1; i < availableSize; i++)
        {
            j = i;
            tmp = ram[i];
            while (j > 0 && (ram[j - 1] >= tmp))
            {
                ram[j] = ram[j - 1];
                j--;
            }
            ram[j] = tmp;
        }
        // output file
        Tape out((std::string) "tmp/" + std::to_string(a) + "_" + std::to_string(availableSize), availableSize);
        for (i = 0; i < availableSize; i++)
        {
            out.writen(ram[i]);
        }
        out.~Tape();
    }
    if (inTape.getSize() % availableSize != 0)
    {

        // надо добить остаток что не получилось изначально разбить и до мерджить
    }
    // merge
    tmp = availableSize;
    while (n <= 1)
    {
        for (i = 0; i < n / tmp; i++)
        {
            ITape a(std::string tempFilename = "tmp/" + N);
            ITape b(std::string tempFilename = "tmp/" + N);
            ITape c(a.getSize() + b.getSize());
            merge(a, b, c)
        }
    }
}
