# Имя проекта
TARGET := viterbi_model_in_awgn_channel

# Компилятор
CXX := g++

# Флаги
CXXFLAGS := -std=c++20 -Wall -Wextra -Wpedantic

# Исходники
SRC := $(wildcard src/*.cpp)

# Объектные файлы (в build/)
OBJ := $(patsubst src/%.cpp, build/%.o, $(SRC))

# Папка сборки с датой
DATE := $(shell date +"%Y-%m-%d_%H-%M-%S")
BIN_DIR := bin/$(DATE)

# Итоговый бинарник
OUT := $(BIN_DIR)/$(TARGET)

# Основная цель
build_all: $(OUT)

# Линковка
$(OUT): $(OBJ)
	@mkdir -p $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $^ -o $@
	@echo "Build complete: $(OUT)"

# Компиляция .cpp -> .o
build/%.o: src/%.cpp
	@mkdir -p build
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# Очистка
clean:
	rm -rf build
	rm -rf bin

# Пересборка
rebuild: clean build_all

.PHONY: build_all clean rebuild