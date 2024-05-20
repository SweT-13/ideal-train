#include "FileTape.h"

Tape::Tape(const std::string &filename, size_t length)
    : _fileName(filename), _maxSize(length)
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

/*
void Tape::print()
{
    testTape(_file);
    std::cout << "content in file: " << _fileName << " \n==================\n";
    std::streampos posishon = _file.tellg();

    int32_t tmp = 0;
    for (int i = 0; i < _maxSize; i++)
    {
        std::cout << this->read(tmp) << "\n";
        this->shiftCur(i);
    }
}
*/
std::streampos Tape::shiftCur(long long index)
{
    if (index)
    {
        testTape(_file);
        if (index < 0)
        {
            // ограничение в левую сторону
            if (_file.tellg() < abs(index))
            {
                _shiftCounter += _file.tellg();
                _file.seekg(-1 * _file.tellg() * singleElementSize, std::ios::cur);
            }
            else
            {
                _shiftCounter += abs(index);
                _file.seekg(index * singleElementSize, std::ios::cur);
            }
        }
        else
        {
            // должно быть ограниечение в правую сторону
            if (_maxSize - index < _file.tellg())
            {
                _shiftCounter += _maxSize - _file.tellg();
                _file.seekg((_maxSize - _file.tellg()) * singleElementSize, std::ios::cur);
            }
            else
            {
                _shiftCounter += index;
                _file.seekg(index * singleElementSize, std::ios::cur);
            }
        }
        return _file.tellg();
    }
    return -1;
}

// typeTape Tape::read()
// {
//     testTape(_fileTape);
//     typeTape tmp = 0;
//     _fileTape.read((char *)&tmp, sizeof(typeTape));
//     _fileTape.seekg(-1 * (sizeof(typeTape)), std::ios::cur);
//     _readCounter++;
//     return tmp;
// }

/* Дабы оперция чтения обычно стоит куда меньше чем операция записи
    то логично бы было сначало проеверить ячейки на идентичность
    но т.к. запись должна быть изначально на пустую ленту то выигрыш от такого теряется */
/*
typeTape Tape::write(typeTape needWrite)
{
    testTape(_file);
    // typeTape tmp = this->read();
    // if(tmp != needWrite){}
    _file.write((char *)&needWrite, sizeof(typeTape));
    _file.seekg(-1 * (sizeof(typeTape)), std::ios::cur);
    _writeCounter++;
    return 0;
}
*/