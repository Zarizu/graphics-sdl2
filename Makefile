# Variáveis
CXX = g++
CXXFLAGS = -Iinclude -g
LDFLAGS = -lmingw32 -lSDL2main -lSDL2 -mconsole
SRC = $(wildcard src/*.cpp)
OBJ = $(patsubst src/%.cpp, build/obj/%.o, $(SRC))
TARGET = build/bin/main.exe

# Regra padrão
all: build_dirs $(TARGET)

# Diretórios necessários
build_dirs:
	if not exist build\obj mkdir build\obj
	if not exist build\bin mkdir build\bin

# Criação do executável
$(TARGET): $(OBJ)
	$(CXX) -o $@ $^ $(LDFLAGS)

# Compilação de arquivos .cpp para build/obj
build/obj/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpeza
clean:
	del /Q build\obj\*.o build\bin\main.exe
