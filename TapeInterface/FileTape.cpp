#include "FileTape.h"

Tape::Tape(const std::string &filename, long long length)
    : _fileName(filename), _maxSize(length), _position(0)
{
    _file.open(_fileName);
    testTape(_file);
}

Tape::~Tape()
{
    _file.close();
}

unsigned long long Tape::getReadCounter(void) const
{
    return _readCounter;
}
unsigned long long Tape::getWriteCounter(void) const
{
    return _writeCounter;
}
unsigned long long Tape::getShiftCounter(void) const
{
    return _shiftCounter;
}
unsigned long long Tape::getTravelCounter(void) const
{
    return _travelCounter;
}

void Tape::print()
{
    testTape(_file);
    std::cout << "\n================== START content in file: " << _fileName << " ==================\n";
    _file.seekg(0, std::ios::beg);
    for (long long i = 0; i < _maxSize; i++)
    {
        int32_t tmp = 0;
        _file.read((char *)&tmp, sizeof(int32_t));
        std::cout << tmp << "\n";
    }
    _file.seekg(_position * sizeof(int32_t), std::ios::beg);
    std::cout << "================== END content in file: " << _fileName << " ==================\n";
}

void Tape::shiftCursor(long long index)
{
    testTape(_file);
    if (index >= 0)
    {
        if (index >= _maxSize)
        {
            index = _maxSize-1;
            // throw ??
        }
        _position = index;
        _file.seekg(index * sizeof(int32_t), std::ios::beg);
    }
    else
    {
        if (-index > _maxSize)
        {
            index = -_maxSize;
            // throw ??
        }
        _position = _maxSize + index; // индекс отрицательный сюда приходит
        _file.seekg(index * sizeof(int32_t), std::ios::end);
    }
}

std::streampos Tape::getCurrentPosition() const
{
    return _position;
}

int32_t Tape::read()
{
    testTape(_file);
    int32_t tmp = 0;
    _file.read((char *)&tmp, sizeof(int32_t));
    _file.seekg(-1 * (sizeof(int32_t)), std::ios::cur);
    _readCounter++;
    return tmp;
}

void Tape::write(const int32_t &needWrite)
{
    testTape(_file);
    _file.write((char *)&needWrite, sizeof(int32_t));
    _file.seekg(-1 * (sizeof(int32_t)), std::ios::cur);
    _writeCounter++;
}