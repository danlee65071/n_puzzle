NAME = test

HEADERS_DIR = ../includes

PROJECT_OBJS_DIR = ../objs
PROJECT_OBJS = $(shell find $(PROJECT_OBJS_DIR) -name '*.o')

SRCS = test.cpp

OBJS_DIR = objs
OBJS = $(patsubst %.cpp, %.o, $(SRCS))
OBJS_PATH = $(addprefix $(OBJS_DIR)/, $(OBJS))

CC = g++
FLAGS = -Wall -Werror -Wextra -g -O3 -std=c++17


all: $(NAME)

$(NAME): $(OBJS_PATH)
	@make -C ..
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -o $@ $(OBJS_PATH)

$(OBJS_DIR)/%.o: %.cpp Makefile
	@$(CC) $(FLAGS) -I $(HEADERS_DIR) -c $< -o $@

clean:
	@rm -rf $(OBJS_DIR)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
