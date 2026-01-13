# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mehdi <mehdi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/11 16:30:00 by mehdi             #+#    #+#              #
#    Updated: 2026/01/11 16:25:12 by mehdi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                 VARIABLES                                    #
# **************************************************************************** #

NAME        = minishell

CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g
LDFLAGS     = -lreadline
RM          = rm -f

# **************************************************************************** #
#                                 DIRECTORIES                                  #
# **************************************************************************** #

PARSE_DIR   = src/parsing/
OBJ_DIR     = obj/
INC_DIR     = include/
LIBFT_DIR   = libft/

# **************************************************************************** #
#                                  LIBFT                                       #
# **************************************************************************** #

LIBFT       = $(LIBFT_DIR)libft.a
LIBFT_FLAGS = -L$(LIBFT_DIR) -lft

# **************************************************************************** #
#                               SOURCE FILES                                   #
# **************************************************************************** #

# Main
MAIN_SRC    = main.c

# Parsing
PARSE_SRC   = tokenize.c \
              tokenize_word.c \
              tokenize_word_utils.c \
              tokenize_utils.c \
              tokenize_free.c \
              parse_commands.c \
              parse_single_cmd.c \
              parse_syntax.c \
              parse_redir.c \
              parse_free.c

# Expansion
EXPAND_SRC  = expand_tokens.c \
              expand_utils.c \
              expand_str.c

# **************************************************************************** #
#                               OBJECT FILES                                   #
# **************************************************************************** #

MAIN_OBJ    = $(OBJ_DIR)main.o
PARSE_OBJ   = $(addprefix $(OBJ_DIR)parsing/, $(PARSE_SRC:.c=.o))
EXPAND_OBJ  = $(OBJ_DIR)expand_tokens.o $(OBJ_DIR)expand_utils.o $(OBJ_DIR)expand_str.o

OBJS        = $(MAIN_OBJ) $(PARSE_OBJ) $(EXPAND_OBJ)

# **************************************************************************** #
#                                  COLORS                                      #
# **************************************************************************** #

DEF_COLOR   = \033[0;39m
GRAY        = \033[0;90m
RED         = \033[0;91m
GREEN       = \033[0;92m
YELLOW      = \033[0;93m
BLUE        = \033[0;94m
MAGENTA     = \033[0;95m
CYAN        = \033[0;96m
WHITE       = \033[0;97m

# **************************************************************************** #
#                                   RULES                                      #
# **************************************************************************** #

all: $(LIBFT) $(NAME)
	@echo "$(GREEN)✅ Compilation terminée !$(DEF_COLOR)"

$(NAME): $(OBJS)
	@echo "$(CYAN)🔗 Linking $(NAME)...$(DEF_COLOR)"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_FLAGS) $(LDFLAGS) -o $(NAME)
	@echo "$(GREEN)✨ $(NAME) créé avec succès !$(DEF_COLOR)"

# Compilation de la libft
$(LIBFT):
	@echo "$(YELLOW)📚 Compilation de la libft...$(DEF_COLOR)"
	@make -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✅ Libft compilée !$(DEF_COLOR)"

# Règle générique pour les objets du main
$(OBJ_DIR)main.o: src/main.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔨 Compilation de src/main.c$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c src/main.c -o $@

# Règle pour expand_tokens et expand_utils
$(OBJ_DIR)expand_%.o: src/expand_%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔨 Compilation de $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Règle pour les objets du parsing
$(OBJ_DIR)parsing/%.o: $(PARSE_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)🔨 Compilation de $<$(DEF_COLOR)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

# Clean
clean:
	@echo "$(RED)🧹 Nettoyage des fichiers objets...$(DEF_COLOR)"
	@$(RM) -r $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean --no-print-directory
	@echo "$(GREEN)✅ Nettoyage terminé !$(DEF_COLOR)"

fclean: clean
	@echo "$(RED)🗑️  Suppression de $(NAME)...$(DEF_COLOR)"
	@$(RM) $(NAME)
	@make -C $(LIBFT_DIR) fclean --no-print-directory
	@echo "$(GREEN)✅ Tout a été supprimé !$(DEF_COLOR)"

re: fclean all

# **************************************************************************** #
#                                  BONUS                                       #
# **************************************************************************** #

# Affiche les fichiers à compiler
show:
	@echo "$(CYAN)📋 Fichiers sources :$(DEF_COLOR)"
	@echo "$(YELLOW)Main:$(DEF_COLOR)"
	@echo "  $(MAIN_SRC)"
	@echo "$(YELLOW)Parsing:$(DEF_COLOR)"
	@echo "  $(PARSE_SRC)"
	@echo "$(YELLOW)Expansion:$(DEF_COLOR)"
	@echo "  $(EXPAND_SRC)"

# Vérifie la norme
norm:
	@echo "$(MAGENTA)📏 Vérification de la norme...$(DEF_COLOR)"
	@norminette $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR) || true

# Lance valgrind
valgrind: all
	@echo "$(MAGENTA)🔍 Lancement de valgrind...$(DEF_COLOR)"
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--suppressions=readline.supp ./$(NAME)

# Crée le fichier de suppression pour readline
readline.supp:
	@echo "$(YELLOW)📝 Création du fichier de suppression readline...$(DEF_COLOR)"
	@echo "{" > readline.supp
	@echo "   readline_leak" >> readline.supp
	@echo "   Memcheck:Leak" >> readline.supp
	@echo "   ..." >> readline.supp
	@echo "   fun:readline" >> readline.supp
	@echo "}" >> readline.supp
	@echo "$(GREEN)✅ Fichier créé !$(DEF_COLOR)"

# **************************************************************************** #
#                                  PHONY                                       #
# **************************************************************************** #

.PHONY: all clean fclean re show norm valgrind readline.supp