#include "TapeSorter.h"

TapeSorter::TapeSorter(size_t memoryLimit) : memoryLimit(memoryLimit) {}

#define first(x) (int)(x & 0xffffffff)
#define second(x) (int)((x >> 32) & 0xffffffff)
void TapeSorter::sort(Tape &inTape, Tape &outTape)
{

    int32_t a = 0;
    int32_t b = 0;
    
    for (int i = 0; i < 6; i++)
    {
        //Стыдно конечно за такое решение но я верю что успею его подправить
        a = inTape.read(a);
        inTape.shiftCur(1);
        b = inTape.read(b);
        inTape.shiftCur(1);
        if(a > b){
            std::cout << "a " << a << " ";
            std::cout << "b " << b << "\n";
            outTape.write(b);
            outTape.shiftCur(1);
            outTape.write(a);
            outTape.shiftCur(1);
        }
        /* if (first(tmp) > second(tmp))
        {
            std::cout << "f " << first(tmp) << " ";
            std::cout << "s " << second(tmp) << " ";
            tmp = (int64_t)0 | (int64_t)second(tmp) | (((int64_t)first(tmp)) << 32);
            std::cout << "t " << tmp << "\n";
        }
        */
    }
}