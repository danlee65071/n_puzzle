# Programm name
NAME = n_puzzle

# Dirs for srcs, objs and headers
SRCS_DIR = srcs
OBJS_DIR = objs
HEADERS_DIR = includes

# srcs
SRCS = main.cpp

# A-star
ASTAR_DIR = AStar
DIRS = $(addprefix $(OBJS_DIR)/, $(ASTAR_DIR))
ASTAR_SRCS = AStar.cpp
ASTAR_SRCS_PATH = $(addprefix $(ASTAR_DIR)/, $(ASTAR_SRCS))
SRCS += $(ASTAR_SRCS_PATH)

SRCS_PATH = $(addprefix $(SRCS_DIR)/, $(SRCS))

# objs
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

# headers
HEADERS = AStar.hpp \
		  Point.hpp
HEADERS_PATH = $(addprefix $(HEADERS_DIR)/, $(HEADERS))

# compiler
CC = g++

# flags
FLAGS = -Wall -Werror -Wextra -g -O3 -std=c++17

# colors for beautiful output
GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)

$(NAME): create_dirs $(OBJS_PATH)
	@echo "$(GREEN)\nObjects was created $(RESET)"
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -o $@ $(OBJS_PATH)
	@echo "$(GREEN)N-puzzle was compiled $(RESET)"

create_dirs:
	@mkdir -p $(OBJS_DIR) $(DIRS)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.cpp $(HEADERS_PATH) Makefile
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -c $< -o $@
	@echo "$(GREEN).$(RESET)\c"

clean:
	@rm -rf $(OBJS_DIR)
	@echo "$(GREEN) clean instruction was executed $(RESET)"

fclean: clean
	@rm -rf $(NAME)
	@echo "$(GREEN) fclean instruction was executed $(RESET)"

re: fclean all

.PHONY: all clean fclean re create_dirs