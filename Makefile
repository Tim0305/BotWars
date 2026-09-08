# Directorios
BIN_DIR = bin
SRC_DIR = src
INC_DIR = include

# Compilador y banderas
CXX = g++
CXXFLAGS = -std=c++17 -I$(INC_DIR)

# Extraer todos los archivos fuente
SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BIN_DIR)/%.o)

# Target
TARGET = $(BIN_DIR)/main

# Regla por defecto: compila todo usando main.cpp
all: $(TARGET)

$(OBJS): | $(BIN_DIR)

# Enlazar los .o para crear el ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilar .cpp -> .o
$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Crear el directorio bin si no existe
$(BIN_DIR):
	mkdir $(BIN_DIR)

clean:
	rm bin/*
