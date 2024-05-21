#include <iostream>
#include "TapeInterface/FileTape.h"

#define N_size (int64_t)5
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
    std::cout << "\n\n\n====================================\n";
    int32_t tmp = 0;

    test(3, 5, "My Test FAIL GOOD", __LINE__);
    test(5, 5, "My Test OK GOOD", __LINE__);

    genirateFile(nameFile, N_size);
    Tape inTape(nameFile, N_size);

    test(inTape.read(), inTape.read(), "Tape read fix", __LINE__);

    inTape.shiftCursor(0);
    int32_t start0 = inTape.read();
    seed = 1;
    test(my_rand(0), start0, "Checking the correctness of reading 0 element", __LINE__);
    inTape.shiftCursor(1);
    int32_t start1 = inTape.read();
    seed = 1;
    test(my_rand(1), start1, "Checking the correctness of reading 1 element", __LINE__);
    inTape.shiftCursor(-1);
    int32_t end0 = inTape.read();
    seed = 1;
    test(my_rand(N_size - 1), end0, "Checking the correctness of reading N_size - 1 element", __LINE__);
    inTape.shiftCursor(-2);
    int32_t end1 = inTape.read();
    seed = 1;
    test(my_rand(N_size - 2), end1, "Checking the correctness of reading N_size - 2 element", __LINE__);

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

    tmp = inTape.read();
    inTape.print();
    test(tmp, inTape.read(), "Print does not disrupt the position", __LINE__);

    tmp = inTape.read();
    inTape.singSize((int64_t)N_size);
    test(tmp, inTape.read(), "Checking position read after singSize", __LINE__);

    inTape.shiftCursor(-1);
    tmp = inTape.read();
    test(end0, tmp, "Checking for wear on the last element", __LINE__);

    tmp = inTape.read();
    test(N_size, inTape.checkSize(), "Verifying that the signature is recorded correctly", __LINE__);
    test(tmp, inTape.read(), "Checking position read after checkSize", __LINE__);
}
