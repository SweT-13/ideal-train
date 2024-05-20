# Имя компилятора
CXX = g++

# Флаги компиляции
CXXFLAGS = -std=c++17 -Wall -Wextra

# Флаги компоновки
LDFLAGS =

# Исходные файлы
SRCS = 	man.cpp \
		TapeInterface/FileTape.cpp \
		TapeSorter.cpp

# Заголовочные файлы
HEADERS = 	TapeInterface/FileTape.h \
			TapeSorter.h

# Объектные файлы
OBJS = $(SRCS:.cpp=.o)

# Исполняемые файлы
TARGET = man.exe
 
# Правило для сборки всех целей
all: $(TARGET) 

# Правило для сборки основного приложения
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)


# Правило для сборки объектных файлов
%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Правило для очистки
clean:
	del *.o *.exe TapeInterface\*.o TapeInterface\*.exe

# Установка зависимостей
$(OBJS): $(HEADERS) | $(TMP_DIR)

.PHONY: all clean