// man.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

/* Известно ли мне N и на сколько оно велико ? (оно поместиться в u l l ? ) */
/* Что такое перемотка ленты ? */
/* С ленты читается минимум 4 байта (1 элемент) ?
    Можно ли прочитать за одну итерацию больше или меньше 4 байт ? */
/* Что понимается под словами "лента не предназначена для произвольного доступа" ?
    (Если это получение элемента за o(1) то это было ясно из слов про перемещения магнитной головки |
    или же это подразумевает что некоторые ячейки не доступны для чтения\записи >> ?как это детектить? ?) */
/* Можно ли использовать и хранить счетчик действий а не время затрачено на операции ?
    (Ну как бы логично что потом можно просто перемножить |
    или какая реализация предполагается за описанием временных задержек) */
/* Имеет ли смысл делать оптимизацию записи посредством предварительного чтения ? (по сути же от повторяемости данных зависит) */
/* На сколько мне надо бы за морочится с расчетом и реализацией оптимизации временных затрат по типу:
    заполнить оперативу (например 4 элементами) и один раз переместиться на другую ленту
    или же одно чтение одна запись ? (Read*4 + Travel + Write*4 | Read*4 + Travel*4 + Write*4) ;
    И если оперативы хватает только на 1 элемент (или не хватает) мне нужно считывать по разрядно сравнивать и записывать (надо бы посчитать) ? ;
    >> могу ли я установить нижний порог требуемой оперативы ? */
/* Полагается ли что оператива тратиться только на хранение элементов ?
    могу ли я хранить счетчики лент ? (получается что там упираемся в величину N минимум | а как тогда работать с магнитной головкой)
    Можно ли полагать что магнитная головка это отдельное устройство и о ее реализации можно не беспокоиться (к вопросу о распределения доступной RAM), \
    а работать только с тем что она возвращает ? */
/* При перемещении с одной ленты на другую что происходит с позицией магнитной головки ? */
/* 21 число включительно ? */
/*  */

#include <iostream>
#include <fstream>
#include <stdexcept>
#include <filesystem>
#include <chrono>
#include "TapeInterface/fileTape.h"
#include "TapeSorter.h"

#define alarm(x) throw std::invalid_argument(x);

int64_t seed = 1;
int32_t my_rand()
{
    seed = seed * 134775813 + 1; // Линейный конгруэнтный метод
    return seed % 0xffffffff;
}
void genirateFile(const char *Name = "hello.txt", int64_t N = 100)
{
    std::ofstream gen(Name, std::ios_base::out | std::ios_base::binary);
    if (gen.is_open())
    {
        for (int64_t i = 0; i < N; i++)
        {
            int32_t tmp = my_rand();
            gen.write((char *)&tmp, sizeof(int32_t));
            // gen.seekg(-sizeof(int32_t), std::ios::cur);
            // gen.read((char *)&tmp, sizeof(int32_t));
            // std::cout << tmp << "\n";
        }
    }
    gen.close();
}

void remove_all_files_in_directory(const std::filesystem::path &dir_path)
{
    try
    {
        if (std::filesystem::exists(dir_path) && std::filesystem::is_directory(dir_path))
        {
            for (const auto &entry : std::filesystem::directory_iterator(dir_path))
            {
                if (std::filesystem::is_regular_file(entry.path()))
                {
                    std::filesystem::remove(entry.path());
                }
            }
        }
    }
    catch (const std::filesystem::filesystem_error &e)
    {
        std::cerr << "Filesystem error: " << e.what() << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "General exception: " << e.what() << "\n";
    }
    catch (...)
    {
        std::cerr << "Unknown error occurred.\n";
    }
}

int main(int argc, char *argv[])
{

    try
    {
        std::filesystem::path tmp_path = std::filesystem::current_path() / "tmp";
        remove_all_files_in_directory(tmp_path);

        std::cout << "tape in/out: \"" << (argc < 3 ? "in.txt" : argv[1]) << "\" / \"" << (argc < 3 ? "out.txt" : argv[2]) << "\"";

        std::fstream confFile;
        confFile.open("conf.txt", std::ios_base::in);
        if (!confFile.is_open())
        {
            alarm("file config not exist");
        }
        // @Надо бы проверить на корректность числа
        int64_t N_size = 0;
        int64_t M_size = 0u;
        long long writeTime = 0u;
        long long readTime = 0u;
        long long shiftTime = 0u;
        long long travelTime = 0u;
        confFile >> N_size >> M_size >> writeTime >> readTime >> shiftTime >> travelTime;
        std::cout << "\ntape size:\t" << N_size;
        std::cout << "\nRAM size:\t" << M_size;
        std::cout << "\nwrite time(ms):\t" << writeTime;
        std::cout << "\nread  time(ms):\t" << readTime;
        std::cout << "\nshift time(ms):\t" << shiftTime;
        std::cout << "\ntravel time(ms):" << travelTime;
        if (N_size < 2)
        {
            alarm("need positive N_size and 3 min");
        }
        if (M_size < 40)
        {
            alarm("I need more memory (min 40)");
        }
        if (M_size / 4 >= N_size)
        {
            alarm("Someone doesn't fulfill their conditions");
        }
        if (readTime < 0 || writeTime < 0 || shiftTime < 0)
        {
            alarm("Time cannot be negative");
        }
        if (argc < 3)
        {
            genirateFile("in.txt", N_size);
            std::fstream clear_file("test.txt", std::ios::out);
            clear_file.close();
        }

        Tape inTape(argc < 3 ? "in.txt" : argv[1], N_size, readTime, writeTime, shiftTime);
        Tape outTape(argc < 3 ? "out.txt" : argv[2], N_size, readTime, writeTime, shiftTime);

        std::cout << "\n-----------------\nHello World Sort!\n-----------------\n";

        TapeSorter sorter(M_size);
        auto start = std::chrono::high_resolution_clock::now();
        sorter.sort(inTape, outTape);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> duration = end - start;
        std::cout << "Duration: " << duration.count() << " seconds\n";
        std::string x = "x";
        std::cout << "Press \"y\" to view --> ";
        std::cin >> x;
        if (x == "y" || x == "Y")
        {
            outTape.print();
        }
    }
    catch (std::invalid_argument &e)
    {
        std::cerr << "\n\nTHROW: " << e.what() << "\n\n";
        return -1;
    }

    return 0;
}
