#ifndef FILETAPE_H
#define FILETAPE_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include "ITape.h"

#define singleElementSize 4

#define testTape(x)                                         \
    if (!x.is_open())                                       \
    {                                                       \
        throw std::invalid_argument(_fileName + " file tape not faund"); \
    }

class Tape 
{
public:
    Tape(const std::string &filename, size_t N = 5u);
    ~Tape();

    template <typename T>
    T read(T &tmp) ;

    template <typename T>
    void write(const T &needWrite);

    //void print();

    // typeTape write(typeTape needWrite);

    /* перемещение же только по элементно ?
    типо даже если я могу прочитать 2 элемента (8 байт) двигаюсь за раз я на 1 элемент (4 байта) */
    std::streampos shiftCur(long long index);

    unsigned long long getReadCounter(void) const;
    unsigned long long getWriteCounter(void) const;
    unsigned long long getShiftCounter(void) const;
    unsigned long long getTravelCounter(void) const;

private:
    std::fstream _file;
    std::string _fileName;

    size_t _maxSize = 0u;

    /* Чтение запись сдвиг мне понятно что такое;
        а что такое прокрутка ленты мне не понятно.. */
    unsigned long long _writeCounter = 0u;
    unsigned long long _readCounter = 0u;
    unsigned long long _shiftCounter = 0u;
    unsigned long long _travelCounter = 0u;
};

template <typename T>
T Tape::read(T &tmp)
{
    testTape(_file);
    _file.read((char *)&tmp, sizeof(T));
    _file.seekg(-1 * (sizeof(T)), std::ios::cur);
    _readCounter++;
    return tmp;
}

template <typename T>
void Tape::write(const T &needWrite)
{
    testTape(_file);
    _file.write((char *)&needWrite, sizeof(T));
    _file.seekg(-1 * (sizeof(T)), std::ios::cur);
    _writeCounter++;
    return;
}

#endif