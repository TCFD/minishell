# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 09:28:24 by rciaze            #+#    #+#              #
#    Updated: 2023/06/24 15:03:29 by wolf             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -g
PFLAGES		=	-lreadline
CC			=	gcc 
CLEANF 		=	@(find . -name "*.o" -type f -delete)
OBJ 		=	${SRCS:.c=.o}


SRCS 		=	maintest.c 		 	         \
				utils/len_utils.c		      \
				utils/signals_utils.c	       \
				utils/parsing_utils.c	        \
				utils/prompt_utils.c	         \
				utils/init_utils.c	              \
				utils/malloc_utils/free_utils.c	   \
				utils/malloc_utils/realloc_utils.c	\
				utils/command_utils/execute_utils.c	 \
				utils/command_utils/execute_utils2.c  \
				utils/command_utils/cd_utils.c	       \
				utils/command_utils/echo_utils.c        \
				utils/command_utils/env_utils.c			 \
				utils/dollar_completion.c				  \
				utils/design_pattern/design_p1.c		   \
				quotes_stuff/check_correct_quotes.c		    \
				quotes_stuff/interpret_quotes.c			     \

INCLUDE = INCLUDES
PIPEX   = pipe_stuff/pipex

# Couleurs
BOLD		=	"\033[1m"
RESET		=	"\033[0m"
LIGHT_GREEN	=	"\033[92m"
LIGHT_CYAN	=	"\033[96m"

all : $(NAME)

.c.o:
	@echo $(BOLD)$(LIGHT_CYAN)Compiling $<... $(RESET)
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ)
	@make -s -C $(INCLUDE)
	@make -s -C $(PIPEX)
	@mv $(INCLUDE)/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) libft.a $(PIPEX)/pipex.a $(PFLAGES) -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

clean :
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)

fclean : clean
	@rm -f libft.a
	@rm -f $(NAME)
	@make -s fclean -C $(PIPEX)/
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) deleted.$(RESET)

re : fclean all


.PHONY : all re clean fclean 
