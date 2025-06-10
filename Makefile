CC = gcc
CCFLAGS = -g
LDFLAGS = -lm

SRC_DIR = src
OBJ_DIR = obj

SOURCES = $(wildcard $(SRC_DIR)/*.c)
OBJECTS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SOURCES))
TARGET = decode  # This will create ./decode

# Default target
all: $(TARGET)

# Link objects to final binary
$(TARGET): $(OBJECTS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)
	@chmod +x $@

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean target
clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET) *-*.pgm *.dot *.svg
