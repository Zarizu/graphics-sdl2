# Variáveis
CXX = g++
CXXFLAGS = -Isrc/include -Lsrc/lib -g -mconsole -fdiagnostics-color=always -lmingw32 -lSDL2main -lSDL2
SRCS = $(wildcard *.cpp)  # Todos os arquivos .cpp no diretório atual
TARGET = main.exe

# Regra padrão
all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Limpeza dos arquivos gerados
clean:
	rm -f $(TARGET)
