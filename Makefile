##
## EPITECH PROJECT, 2025
## C Lib OOP
## File description:
## Makefile
##

CC		= gcc
CFLAGS	= -I./include -std=gnu17 \
		  -Wall -Wextra -Werror -pedantic -Wconversion -g3 \
		  -Werror=unused-result \
		  -O3

AR		= ar
ARFLAGS	= rc

SRC_DIR	= lib
OBJ_DIR	= objects

NAME	= libstring.a

SRC = $(wildcard $(SRC_DIR)/*.c) \
	  $(wildcard $(SRC_DIR)/utils/*.c) \
	  $(wildcard $(SRC_DIR)/class/*.c) \
	  $(wildcard $(SRC_DIR)/iterator/*.c) \
	  $(wildcard $(SRC_DIR)/string/*.c) \
	  $(wildcard $(SRC_DIR)/array/*.c) \
	  $(wildcard $(SRC_DIR)/list/*.c)

SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

GREEN	= \033[1;32m
RED		= \033[1;31m
ILC		= \033[3m
ORANGE	= \033[38;5;214m
RST		= \033[0m

all: $(NAME)

$(NAME): $(SRC_OBJ)
	@$(AR) $(ARFLAGS) $(NAME) $^
	@ranlib $(NAME)
	@printf "$(GREEN)[✅] ARCHIVED:\t$(RST) $(ILC)$(NAME)$(RST)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING:\t$(RST) $(ILC)$<$(RST)\n"

test: $(NAME)
	@gcc main.c $(CFLAGS) -L. -lstring -o test
	@printf "$(GREEN)[✅] COMPILED:\t$(RST) $(ILC)test$(RST)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)[❌] CLEAN:\t$(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n"

fclean: clean
	@rm -f $(NAME)
	@rm -f vgcore* test *.log
	@printf "$(RED)[❌] FCLEAN:\t$(RST) Removed $(ILC)$(NAME)$(RST)\n"

re: fclean all

.PHONY: all clean fclean test re
