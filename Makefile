# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: conoel <conoelstudent.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/01/10 21:14:13 by conoel            #+#    #+#              #
#    Updated: 2019/06/24 04:27:01 by conoel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#################################################################################
##################################### VARS ######################################
#################################################################################

NAME =			asm
AUTEUR =		"conoel"

###### SOURCES #######

SRC_NAME =		main.c\
				utils.c\
				$(LEXER)\
				$(PARSER)\
				$(COMPILER)
#sub-directories
LEXER_SRC =		lexer.c\
				token_utils.c\
				string_variants.c\
				print_tokens.c
LEXER_DIR =		lexer/
LEXER =			${addprefix $(LEXER_DIR), $(LEXER_SRC)}

PARSER_SRC =		parser.c\
					op.c\
					instruction_utils.c\
					line_byte_len.c
PARSER_DIR =		parser/
PARSER =			${addprefix $(PARSER_DIR), $(PARSER_SRC)}

COMPILER_SRC =		compile.c\
					add_line.c\
					label_addr.c\
					reverse.c\
					utils.c
COMPILER_DIR =		compile/
COMPILER =			${addprefix $(COMPILER_DIR), $(COMPILER_SRC)}
#main sources
SRC_DIR =			./sources/
SRC =				${addprefix $(SRC_DIR), $(SRC_NAME)}
#objects
OBJ_NAME =		$(SRC_NAME:.c=.o)
OBJ_DIR =		./objects/
OBJ =			${addprefix $(OBJ_DIR), $(OBJ_NAME)}
#object sub-directories
	ALL_OBJ_DIR =	$(OBJ_DIR)$(LEXER_DIR)\
					$(OBJ_DIR)$(PARSER_DIR)\
					$(OBJ_DIR)$(COMPILER_DIR)

###### HEADERS ########

HEADER_DIR =	./include/
HEADER_NAME =	asm.h\
				lexer.h\
				op.h\
				parser.h
HEADER =		${addprefix $(HEADER_DIR), $(HEADER_NAME)}

#######  LIBS  ########

LIB_NAME =		haflib.a
LIB_DIR =		./haflib/
LIB_HEADER =	./haflib/includes/
LIB =			${addprefix $(LIB_DIR), $(LIB_NAME)}

#######  MISC  ########

FLAGS =			-Wall -Werror -Wextra -g
DEBUG_FLAGS =	$(FLAGS) -O0 -fsanitize=address
CC =			clang

#################################################################################
##################################### RULES #####################################
#################################################################################

.PHONY: all clean fclean re lre
.SILENT:

########## GENERALS ##########

all: ./auteur $(LIB) $(OBJ_DIR) $(NAME) $(HEADER)

re: fclean all

lre:
	rm -r $(OBJ_DIR)
	make all

clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIB_DIR)

fclean:
	make fclean -C $(LIB_DIR)
	rm -rf $(OBJ_DIR) $(NAME) *.dSYM
	echo "\033[31m\033[1m\033[4mCleaning\033[0m\033[31m : Everything\033[0m [$(NAME)]";

debug:
	rm -r $(OBJ_DIR)
	make $(NAME)_debug

######### COMPILATION #########

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) $(LIB) -o $(NAME) -I$(HEADER_DIR) -I$(LIB_DIR)
	echo "\n \033[1m\033[4m\033[35m\\^/ Done compiling \\^/\033[0m [$(NAME)] --> $(LIB_NAME)"
	make header_print

$(NAME)_debug: ./auteur $(LIB) $(OBJ_DIR) $(HEADER) $(OBJ)
	$(CC) $(DEBUG_FLAGS) $(OBJ) $(LIB) -o $(NAME) -I$(HEADER_DIR) -I$(LIB_DIR)
	echo "\n \033[1m\033[4m\033[35m\\^/ Done compiling \\^/\033[0m [$(NAME)] --> $(LIB_NAME)"
	make header_print

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADER)
	$(CC) $(FLAGS) -c $< -o $@ -I$(HEADER_DIR) -I$(LIB_HEADER)
	printf "\033[32m\033[1m\033[4mCompiling\033[0m\033[32m : %-30s \033[0m [$(NAME)]\n" $@

$(OBJ_DIR): $(ALL_OBJ_DIR)
	mkdir -p $(OBJ_DIR)

$(ALL_OBJ_DIR):
	mkdir -p $@
	echo "\033[32m\033[1m\033[4mCreated\033[0m\033[32m : $@ obj dir\033[0m"

./auteur:
	echo $(AUTEUR) > ./auteur
	echo "\033[32m<Created Author file>\033[0m"

header_print:
	clear
	echo "############################"
	echo "##\033[32m   ___   ____  __  __   \033[0m##"
	echo "##\033[32m  /   \ /  __\|  \/  |  \033[0m##"
	echo "##\033[32m | /_\ ||__  || \__/ |  \033[0m##"
	echo "##\033[32m |_|_|_|\____/|__||__|  \033[0m##"
	echo "##\033[32m |_| |_|\____/|__||__|  \033[0m##"
	echo "##                        ##"
	echo "##########\033[32m CONOEL \033[0m##########"

############# LIB #############

$(LIB):
	make -C $(LIB_DIR)
