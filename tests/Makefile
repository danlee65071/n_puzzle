NAME = test

HEADERS_DIR = ../includes

PROJECT_OBJS_DIR = ../objs

OBJS_DIR = objs

SRCS = test.cpp
SRCS_DIR = srcs

HEADERS_TESTS_ROOT_DIR = includes

ASTAR_TESTS_DIR = AStarTests
DIRS = $(addprefix $(OBJS_DIR)/, $(ASTAR_TESTS_DIR))
ASTAR_TESTS_SRCS = TestManhattanMetric.cpp
SRCS += $(addprefix $(ASTAR_TESTS_DIR)/, $(ASTAR_TESTS_SRCS))

SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))

OBJS = $(patsubst %.cpp, %.o, $(SRCS))
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

CC = g++
FLAGS = -Wall -Werror -Wextra -g -O3 -std=c++17


all: $(NAME)

make_project:
	@make -C ..

PROJECT_OBJS_ = $(shell find $(PROJECT_OBJS_DIR) -name '*.o')
PROJECT_OBJS = $(filter-out ../objs/main.o, $(PROJECT_OBJS_))

$(NAME): make_project create_dirs $(OBJS_PATH)
	@make -C ..
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -I $(HEADERS_TESTS_ROOT_DIR) -o $@ $(OBJS_PATH) $(PROJECT_OBJS)

create_dirs:
	@mkdir -p $(OBJS_DIR) $(DIRS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp Makefile
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -I $(HEADERS_TESTS_ROOT_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
