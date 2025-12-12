# Список всех исходных .c файлов (добавьте сюда все свои файлы)
SRC = s21_decimal.c \
       $(wildcard Arithmetic/*.c) \
       $(wildcard Comparison/*.c) \
       $(wildcard Convertors/*.c) \
       $(wildcard Other/*.c)
# Автоматически создаём список объектных файлов: .c → .o
OBJ = $(SRC:.c=.o)
ADD_LIB := $(shell pkg-config --cflags --libs check)
# Компилятор и флаги
CC = gcc
CFLAGS = -Wall -Wextra -Werror

GCOV_FLAGS = -fprofile-arcs -ftest-coverage

ifeq ($(UNAME_S),Linux)
	ADD_LIB = -lcheck -lm -lsubunit
endif
ifeq ($(UNAME_S),Darwin)
	ADD_LIB = -lcheck -lm
endif

# Имя библиотеки
LIB = s21_decimal.a

# Имя тестовой программы
TEST = s21_test

# Цель по умолчанию
all: $(LIB) test

# Собираем статическую библиотеку из всех .o файлов
$(LIB): $(OBJ)
	ar rcs $(LIB) $(OBJ)
	ranlib $(LIB)  # Добавляет индексацию (лучше для производительности)
	rm -rf *.o */*.o

# Правило: как превратить .c файл в .o файл
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Собираем тест
test: $(TEST)
	./$(TEST) || true  # Запускаем тест, не падаем при ошибке


$(TEST): s21_test.c $(LIB)
	$(CC) $(CFLAGS) s21_test.c $(LIB) -o $(TEST) $(ADD_LIB)

test_anton: test_arif_anton.c anton.h $(LIB)
	$(CC) test_arif_anton.c $(LIB) -o test_arif_anton -lcheck -lm -lpthread
	./test_arif_anton || true

test_vasyan: clean s21_decimal.h s21_decimal.a test_ibbenber.c
	checkmk clean_mode=1 $(wildcard ./*.check) > test_ibbenber.c
	gcc s21_decimal.h s21_decimal.a test_ibbenber.c -lcheck -lm -lpthread -g -o test
	./test

# Форматирование кода через clang-format
format:
	clang-format -style=Google -n *.c *.h */*.c
	clang-format -style=Google -i *.c *.h */*.c

# Удаление временных файлов
clean:
	rm -f $(TEST) $(LIB) $(OBJ) *.o *.gcno *.gcda *.info *.gcov

gcov_report: clean ${SRC}
	gcc --coverage ${SRC} s21_test.c -o s21_test $(ADD_LIB)
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	lcov --remove s21_test.info "/usr/local/*" -o s21_test_filtered.info
	genhtml -o report s21_test_filtered.info
	open report/index.html

# Указываем, что это "фиктивные" цели (не файлы)
.PHONY: all test clean format

testik_leo: $(LIB)
	gcc -Wall -Wextra -Werror testik_leo.c s21_decimal.a -o testik_leo
	./testik_leo