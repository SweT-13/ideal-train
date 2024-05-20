# Имя компилятора
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra

# Флаги компоновки
LDFLAGS =

# Исходные файлы
SRCS = man.cpp \
       TapeInterface/FileTape.cpp \
       TapeSorter.cpp \
       UnitTest.cpp

# Заголовочные файлы
HEADERS = TapeInterface/FileTape.h \
          TapeSorter.h

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемые файлы
TARGET = man.exe
TEST_TARGET = UnitTest.exe

# Правило для сборки всех целей
all: $(TARGET)

# Правило для сборки основного приложения
$(TARGET): man.o TapeInterface/FileTape.o TapeSorter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Правило для сборки тестового приложения
$(TEST_TARGET): UnitTest.o TapeInterface/FileTape.o TapeSorter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

# Правило для сборки объектных файлов
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки
clean:
	del *.o *.exe TapeInterface\*.o

# Цель для сборки и запуска тестов
check: $(TEST_TARGET)
	@./$(TEST_TARGET)

# Установка зависимостей
$(OBJS): $(HEADERS)

.PHONY: all clean check