##
## EPITECH PROJECT, 2025
## C Lib OOP
## File description:
## Makefile
##

CC      = gcc
CFLAGS  = -I./include -std=gnu17 \
          -Wall -Wextra -Werror -pedantic -Wconversion -g3 \
		  -Werror=unused-result \
		  -O3

LDFLAGS =

SRC_DIR   = src
OBJ_DIR   = objects

PROGRAMS  = oop

SRC = $(wildcard $(SRC_DIR)/*.c) \
	$(wildcard $(SRC_DIR)/utils/*.c) \
	$(wildcard $(SRC_DIR)/class/*.c) \
	$(wildcard $(SRC_DIR)/string/*.c)

SRC_OBJ = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

GREEN      = \033[1;32m
RED        = \033[1;31m
ILC 	   = \033[3m
ORANGE     = \033[38;5;214m
RST        = \033[0m

all: $(PROGRAMS)

oop: $(SRC_OBJ)
	@$(CC) $(CFLAGS) -o $(PROGRAMS) $^ $(LDFLAGS)
	@printf "$(GREEN)[✅] COMPILED: $(RST) $(ILC)$(PROGRAMS)$(RST)\n"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -o $@ -c $<
	@printf "$(ORANGE)[🚧] BUILDING: $(RST) $(ILC)$<$(RST)\n"

clean:
	@rm -rf $(OBJ_DIR)
	@printf "$(RED)[❌] CLEAN:    $(RST) Removed $(ILC)$(OBJ_DIR)$(RST)\n"

fclean: clean
	@rm -f $(PROGRAMS)
	@printf "$(RED)[❌] FCLEAN:   $(RST) Removed $(ILC)executables$(RST)\n"

re: fclean all

.PHONY: all oop clean fclean re
