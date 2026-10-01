CPP = clang++
CPPFLAGS = -std=c++20 -Wall -Wextra -g -fsanitize=address,undefined -Iinclude -Itest -Isrc
LDFLAGS = -fsanitize=address,undefined

TARGET = test

SRCS =	test/assertions.cpp \
		test/test_constructors.cpp \
		test/test_destructors.cpp \
		test/test_operators.cpp \
		test/test_makes.cpp \
		test/test_swap.cpp \
		test/test_reset.cpp \
		test/test_unique_and_use_count.cpp \
		test/test_comparison.cpp \
		test/test_dyn_arr.cpp

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CPP) $(CPPFLAGS) test/test.cpp -o $@ $^

%.o: %.cpp
	$(CPP) $(CPPFLAGS) -c $< -o $@

run: $(TARGET)
	cmd.exe /c start cmd.exe /k "chcp 65001 && $(TARGET).exe"

clean:
	del test\*.o test.exe

rerun: clean all run

.PHONY: all clean run rerun
