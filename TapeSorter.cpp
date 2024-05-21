#include "TapeSorter.h"

TapeSorter::TapeSorter(int64_t memoryLimit) : _memoryLimit(memoryLimit) {}

void TapeSorter::merge(ITape &left, ITape &right, ITape &enter)
{
    while (enter.getCurrentPosition() < enter.getSize())
    {
        // std::cout << left.read() << " < "<< right.read() <<'\n';
        enter.writen(left.read() < right.read() ? left.readn() : right.readn());
        // left.read() < right.read() ? left.shiftCursor(left.getCurrentPosition() + 1) : right.shiftCursor(right.getCurrentPosition() + 1);
        if (left.getCurrentPosition() > left.getSize())
        {
            while (right.getCurrentPosition() < right.getSize())
            {
                enter.writen(right.readn());
            }
            return;
        }
        if (right.getCurrentPosition() > right.getSize())
        {
            while (left.getCurrentPosition() == left.getSize())
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
    int64_t n = 0; // ??Нужна ли??
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
    n = inTape.getSize() / availableSize;
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
        Tape out((std::string) "tmp/" + std::to_string(a) + ".tape", availableSize);
        for (i = 0; i < availableSize; i++)
        {
            out.writen(ram[i]);
        }
        out.singSize(availableSize);
        out.~Tape();
    }
    if (inTape.getSize() % availableSize != 0)
    {
        // input ram
        for (i = 0; inTape.getCurrentPosition() < inTape.getSize() && i < availableSize; i++)
        {
            ram[i] = inTape.readn();
        }
        // ram[i++] = inTape.read();
        n = i;
        if (n != inTape.getSize() % availableSize)
        {
            throw std::invalid_argument(" file error size ");
        }
        // ram sort
        for (i = 1; i < n; i++)
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
        Tape out((std::string) "tmp/" + std::to_string(a) + ".tape", n);
        for (i = 0; i < n; i++)
        {
            out.writen(ram[i]);
        }
        out.singSize(n);
        out.~Tape();
        a++;
    }
    // merge
    tmp = availableSize;
    // 0 -- a[по availSize] + ?1[< availSize]
    //
    j = 0;
    n = a - 1;
    while (n > 0)
    {
        tmp = a;
        for (i = 0; i < (n / 2); i++)
        {
            std::cout << n << " a: " << a << " ";
            Tape left("tmp/" + std::to_string(i + j) + ".tape");
            Tape right("tmp/" + std::to_string(i + j + (n / 2)) + ".tape");
            std::cout << "i: " << i << " " << std::to_string(i + j) << "+" << std::to_string(i + j + (n / 2)) << " siz: " << left.getSize() << " " << right.getSize() << "\n";
            Tape c("tmp/" + std::to_string(a++) + ".tape", left.getSize() + right.getSize());
            merge(left, right, c);
            c.singSize(left.getSize() + right.getSize());
        }
        if (n % 2 != 0)
        {
            Tape left("tmp/" + std::to_string(j + n) + ".tape");
            Tape right("tmp/" + std::to_string(a - 1) + ".tape");
            std::cout << n << " a: " << a << " he   " << std::to_string(j + n) << "+" << std::to_string(a - 1) << " siz: " << left.getSize() << "+" << right.getSize() << "\n";
            Tape c("tmp/" + std::to_string(a - 1) + ".tape", left.getSize() + right.getSize());
            merge(left, right, c);
            c.singSize(left.getSize() + right.getSize());
        }
        j = tmp;
        n = n / 2;
    }

    return;
    /*
    (i; 0 < n / 2; i++)
    {
        merge(i, i * 2, a++)
    }
    if (n / 2 != 0)
    {
        merge(n * 2 + 1, a - 1, a++)
    }

    while (n <= 1)
    {
        for (i = 0; i < n / tmp; i++)
        {
            Tape left("tmp/" + std::to_string(i));
            Tape right("tmp/" + std::to_string(i));
            if (left.getSize() + right.getSize() == inTape.getSize())
            {
            }
            Tape c("tmp/" + std::to_string(a), left.getSize() + right.getSize());
            merge(left, right, c);
        }
    }
    */
}
