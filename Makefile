CC=g++
CFLAGS  = -Wall -Werror -Wextra -std=c++17
OS = $(shell uname -s)
OBJDIR = obj
TESTS := $(wildcard tests/*.cpp)
TESTS_OBJ := $(TESTS:tests/%.cpp=$(OBJDIR)/%.o);
LIBS = -lgtest -lgtest_main -lpthread # do smth about mac
STYLE_CONFIG = ../materials/linters/.clang-format
all: test
rebuild: clean all

$(OBJDIR)/%.o: tests/%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@  

test: $(TARGET) $(TESTS_OBJ) 
	$(CC) $(TESTS) $(CFLAGS) $(LIBS) -o s21_test
	./s21_test

gtest:	
ifeq ($(OS), Darwin)
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install gtest
else
	sudo apt-get install libgtest-dev
endif

clean :
	rm -rf s21_test
	rm -rf *.a
	rm -rf a.out
	rm -rf *.gcov
	rm -rf $(OBJDIR)


clang_format:
	clang-format -style=file:$(STYLE_CONFIG) -i source/s21_*.cpp s21_*.h
	clang-format -style=file:$(STYLE_CONFIG) -i  tests/*.cpp tests/*.h

style:
	clang-format -style=file:$(STYLE_CONFIG) -n source/s21_*.cpp
	clang-format -style=file:$(STYLE_CONFIG) -n  tests/*.cpp


.PHONY: clean