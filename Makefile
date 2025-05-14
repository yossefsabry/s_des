# Makefile for s_des project

# Compiler
CC = gcc
CFLAGS = -c -Wall

# Linker flags (adding -lz for zlib)
LDFLAGS = -lz

# Directories
SRC_DIR = .
DES_OP_DIR = ./des_operation
HELPERS_DIR = ./helpers
DIST_DIR = ./dist

# Source files
SRCS = main.c \
       $(DES_OP_DIR)/pn.c \
       $(DES_OP_DIR)/xor_operation.c \
       $(DES_OP_DIR)/Sbox_operation.c \
       $(DES_OP_DIR)/convert_operation.c \
       $(HELPERS_DIR)/shifting.c \
       $(HELPERS_DIR)/swapping_operation.c \
       $(HELPERS_DIR)/spliting.c \
       $(HELPERS_DIR)/handle_bits.c \
       run.c

# Object files
OBJS = $(addprefix $(DIST_DIR)/, $(notdir $(SRCS:.c=.o)))

# Executable
EXEC = s_des

.PHONY: all clean run

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Pattern rule for source files in root directory
$(DIST_DIR)/%.o: %.c | $(DIST_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Pattern rule for des_operation files
$(DIST_DIR)/%.o: $(DES_OP_DIR)/%.c | $(DIST_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Pattern rule for helpers files
$(DIST_DIR)/%.o: $(HELPERS_DIR)/%.c | $(DIST_DIR)
	$(CC) $(CFLAGS) $< -o $@

# Create dist directory if it doesn't exist
$(DIST_DIR):
	mkdir -p $(DIST_DIR)

clean:
	rm -rf $(DIST_DIR) $(EXEC)

run: $(EXEC)
	./$(EXEC)
