#ifndef FILETAPE_H
#define FILETAPE_H

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <stdint.h>
#include "ITape.h"
#include <thread>
#include <chrono>

#define singleElementSize 4

#define testTape(x)                                                      \
    if (!x.is_open())                                                    \
    {                                                                    \
        throw std::invalid_argument(_fileName + " file tape not faund"); \
    }

class Tape : public ITape
{
public:
    Tape(const std::string &filename, long readDelay = 0, long writeDalay = 0, long shiftDalay = 0);
    Tape(const std::string &filename, long long length, long readDelay = 0, long writeDalay = 0, long shiftDalay = 0);
    ~Tape();

    int32_t read(void) override;
    int32_t readn(void) override;
    void write(const int32_t &needWrite) override;
    void writen(const int32_t &needWrite) override;
    void shiftCursor(long long index) override;
    std::streampos getCurrentPosition() const override;
    int64_t getSize() const override;

    int64_t checkSize(void);
    void singSize(const int64_t &needWrite);

    void print(void);
    unsigned long long getReadCounter(void) const;
    unsigned long long getWriteCounter(void) const;
    unsigned long long getShiftCounter(void) const;
    unsigned long long getTravelCounter(void) const;

private:
    std::fstream _file;
    std::string _fileName;
    int64_t _maxSize = 0u;
    std::streampos _position;

    unsigned long long _readCounter = 0u;
    unsigned long long _writeCounter = 0u;
    unsigned long long _shiftCounter = 0u;
    unsigned long long _travelCounter = 0u;

    long _readDelay = 0;
    long _writeDelay = 0;
    long _shiftDelay = 0;
    long _travelDelay = 0;
};

/*
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
*/
#endif