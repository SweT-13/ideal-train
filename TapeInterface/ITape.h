#ifndef ITAPE_H
#define ITAPE_H

template <typename T>
class ITape {
public:
    virtual ~ITape() {}

    // Чтение элемента с ленты
    virtual T read() = 0;

    // Запись элемента на ленту
    virtual void write(const T& element) = 0;

    // Сдвиг курсора на ленте
    virtual void shiftCursor(long long offset) = 0;

    // Получение текущей позиции курсора
    //virtual std::streampos getCurrentPosition() const = 0;
};

#endif
