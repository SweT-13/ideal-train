#ifndef ITAPE_H
#define ITAPE_H

#include <iostream>

class ITape
{
public:
    virtual ~ITape() {}

    // Чтение элемента с ленты
    virtual int32_t read(void) = 0;

    // Запись элемента на ленту
    virtual void write(const int32_t &element) = 0;

    // Сдвиг курсора на ленте
    virtual void shiftCursor(long long index) = 0;

    // Получение текущей позиции курсора
    virtual std::streampos getCurrentPosition() const = 0;

    // Получение количества элементов
    virtual int64_t getSize() const = 0;
};

#endif
