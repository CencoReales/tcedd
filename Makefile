CXX := g++
EMSDK := $(HOME)/emsdk
EMCC := $(EMSDK)/upstream/emscripten/emcc
CXXFLAGS := -Os -flto -Wall -Wextra -pedantic -std=c++17
LDFLAGS := -s -static
EMFLAGS := -O1 -s WASM=1 --bind \
           -s EXPORTED_RUNTIME_METHODS='["ccall","cwrap"]' \
           -s MODULARIZE=1 -s ENVIRONMENT=web \
           -s ALLOW_MEMORY_GROWTH=1 \
           -s SAFE_HEAP=1
           
# Directorios
SRC_DIR := src
INC_DIR := include
BIN_DIR := bin
WEB_DIR := web

# Fuentes CLI (solo los archivos necesarios)
CLI_SRCS := \
    $(SRC_DIR)/main.cpp \
    $(SRC_DIR)/cli/cli_interface.cpp

# Fuentes WASM
WEB_SRCS := \
    $(SRC_DIR)/web_main.cpp

.PHONY: all clean run web serve_web

all: cli web

cli: $(BIN_DIR)/data_structures_cli

$(BIN_DIR)/data_structures_cli: $(CLI_SRCS)
	@mkdir -p $(BIN_DIR)
	$(CXX) $(CXXFLAGS) -I$(INC_DIR) $^ -o $@ $(LDFLAGS)

web: $(WEB_DIR)/app.js

$(WEB_DIR)/app.js: $(WEB_SRCS)
	@mkdir -p $(WEB_DIR)
	$(EMCC) $(EMFLAGS) -I$(INC_DIR) $^ -o $(WEB_DIR)/app.js

run: cli
	./$(BIN_DIR)/data_structures_cli

serve_web: web
	cd $(WEB_DIR) && python3 -m http.server

clean:
	rm -rf $(BIN_DIR) $(WEB_DIR)/app.js $(WEB_DIR)/app.wasm

env_setup:
	@echo "export PATH=$(EMSDK):$$PATH" > env_setup.sh
	@echo "export PATH=$(EMSDK)/upstream/emscripten:$$PATH" >> env_setup.sh
	@chmod +x env_setup.sh