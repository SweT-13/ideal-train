#include <iostream>
#include "TapeInterface/FileTape.h"

#define N_size 5
#define nameFile "in.txt"

template <typename T>
void test(T expected, T actual, std::string testName, int line)
{
    if (expected == actual)
    {
        std::cout << "OK:\tline" << line << "\t" << testName << '\n';
    }
    else
    {
        std::cout << "FAIL:\tline" << line << "\t" << testName;
        std::cout << "\texpected " << expected << " answer " << actual << "\n";
    }
}

int64_t seed = 1;
int32_t my_rand(int32_t count = 0)
{
    for (int32_t i = 0; i <= count; i++)
    {
        seed = seed * 134775813 + 1; // Линейный конгруэнтный метод
    }
    return seed % 0xffffffff;
}
void genirateFile(const char *Name = "hello.txt", int64_t N = 100)
{
    std::fstream gen(Name, std::ios_base::out);
    if (gen.is_open())
    {
        for (int64_t i = 0; i < N; i++)
        {
            int32_t tmp = my_rand();
            gen.write((char *)&tmp, sizeof(int32_t));
            // std::cout << tmp << "\n";
        }
    }
    gen.close();
}

int main()
{
    test(3, 5, "My Test FAIL GOOD", __LINE__);
    test(5, 5, "My Test OK GOOD", __LINE__);

    genirateFile(nameFile, N_size);
    Tape inTape(nameFile, N_size);

    test(inTape.read(), inTape.read(), "Tape read fix", __LINE__);

    inTape.shiftCursor(0);
    int32_t start0 = inTape.read();
    inTape.shiftCursor(1);
    int32_t start1 = inTape.read();
    inTape.shiftCursor(-1);
    int32_t end0 = inTape.read();
    inTape.shiftCursor(-2);
    int32_t end1 = inTape.read();

    inTape.shiftCursor(-N_size - 1);
    test(start0, inTape.read(), "Exiting the left border -i < 0 (-N_size - 1)", __LINE__);
    inTape.shiftCursor(-N_size);
    test(start0, inTape.read(), "Exiting the left border -i = 0 (-N_size)", __LINE__);
    inTape.shiftCursor(-N_size + 1);
    test(start1, inTape.read(), "Exiting the left border -i+1 > 0 (-N_size + 1)", __LINE__);

    inTape.shiftCursor(N_size + 1);
    test(end0, inTape.read(), "Exiting the right border i > n (N_size+1)", __LINE__);
    inTape.shiftCursor(N_size);
    test(end0, inTape.read(), "Exiting the right border i = n (N_size)", __LINE__);
    inTape.shiftCursor(N_size - 1);
    test(end0, inTape.read(), "Exiting the right border i-1 < 0 (N_size - 1)", __LINE__);
    inTape.shiftCursor(N_size - 2);
    test(end1, inTape.read(), "Exiting the right border i-2 < 0", __LINE__);

    int32_t tmp = 0;
    tmp = inTape.read();
    inTape.print();
    test(tmp, inTape.read(), "print does not disrupt the position", __LINE__);
}
