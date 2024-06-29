# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: frankgar <frankgar@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/22 17:14:59 by frankgar          #+#    #+#              #
#    Updated: 2024/06/29 20:26:21 by frankgar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
NAME_DEBUG = 
FLAGS = -Wall -Werror -Wextra -g 
INCLUDES = -I ./inc/
SRC = main.c parsing.c libft_utils.c simulation_utils.c philos_actions.c

DIR_SRC = ./src
DIR_OBJ = $(DIR_SRC)/obj
OBJ = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.o))
DEP = $(addprefix $(DIR_OBJ)/, $(SRC:.c=.d))


all: dir $(NAME)

debug: dir compile_debug

val: ./$(NAME) 
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose ./$(NAME) 124 500 230 200
	
-include $(DEP)

dir:
	mkdir -p $(DIR_OBJ)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c Makefile
	$(CC) -MMD $(FLAGS)  -c $< -o $@ $(INCLUDES)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $@ $(INCLUDES)
	echo "$(NAME) Created :D"

compile_debug: $(OBJ)
	$(CC) $(FLAGS) -fsanitize=thread $(OBJ) -o $(NAME) $(INCLUDES)
	echo "$(NAME) Created :D"

clean:
	rm -rf $(DIR_OBJ)
	echo "DEPENDENCIES Erased :D"

fclean: clean
	rm -rf $(NAME)
	echo "EVERYTHING Erased D:"

re: fclean all

.PHONY: fclean all clean re dir debug val
.SILENT:
