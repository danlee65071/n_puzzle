NAME = test

HEADERS_DIR = ../includes

PROJECT_OBJS_DIR = ../objs
PROJECT_OBJS = $(shell find $(PROJECT_OBJS_DIR) -name '*.o')

SRCS = test.cpp
SRCS_DIR = srcs

HEADERS_TESTS_ROOT_DIR = includes
HEADERS_TESTS_DIRS = HEADERS_TESTS_DIR

ASTAR_TESTS_DIR = AStarTests
ASTAR_TESTS_SRCS = TestManhattanMetric.cpp
ASTAR_HEADER_DIR = AStarTests
DIRS = ASTAR_TESTS_DIR
SRCS += $(addprefix $(ASTAR_TESTS_DIR)/, $(ASTAR_TESTS_SRCS))
HEADERS_TESTS_DIRS += $(addprefix $(HEADERS_TESTS_ROOT_DIR)/, $(ASTAR_HEADER_DIR))

SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))

HEADERS_TESTS_DIRS

OBJS_DIR = objs
OBJS = $(patsubst %.cpp, %.o, $(SRCS_PATH))
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

CC = g++
FLAGS = -Wall -Werror -Wextra -g -O3 -std=c++17


all: $(NAME)

$(NAME): $(OBJS_PATH)
	@make -C ..
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -I $(HEADERS_TESTS_DIRS) -o $@ $(OBJS_PATH) $(PROJECT_OBJS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -I $(HEADERS_TESTS_DIRS) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
