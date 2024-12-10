CC=gcc
CFLAGS=-Wall -Wextra -pthread -Isrc/include
LDFLAGS=
OBJ_DIR=obj
BIN_DIR=bin

# 自动查找所有源文件
SRCS := $(wildcard src/*.c)
OBJS := $(patsubst src/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# 定义最终的可执行文件
BINARIES := http_server

# 默认目标
all: $(BIN_DIR)/$(BINARIES)

# 链接目标
$(BIN_DIR)/$(BINARIES): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# 编译源文件为对象文件
$(OBJ_DIR)/%.o: src/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理构建文件
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

# 运行测试
test: $(BIN_DIR)/test_http_server $(BIN_DIR)/test_url_parser
	$(BIN_DIR)/test_http_server
	$(BIN_DIR)/test_url_parser

# 测试可执行文件的规则
$(BIN_DIR)/test_http_server: $(OBJ_DIR)/test_http_server.o $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BIN_DIR)/test_url_parser: $(OBJ_DIR)/test_url_parser.o $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

.PHONY: all clean test
