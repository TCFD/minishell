# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 09:28:24 by rciaze            #+#    #+#              #
#    Updated: 2023/06/20 15:58:03 by rciaze           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror -g
PFLAGES		=	-lreadline
CC			=	cc 
CLEANF 		=	@(rm -f *.o quotes_stuff/*.o)
OBJ 		=	${SRCS:.c=.o}


SRCS 		=	len_utils.c		            \
				signals_utils.c	             \
				parsing_utils.c	              \
				free_utils.c	               \
				prompt_utils.c	            	\
				init_utils.c	            	 \
				execute_utils.c	            	  \
				realloc_utils.c	            	   \
				maintest.c		            		\
				quotes_stuff/check_correct_quotes.c  \
				quotes_stuff/interpret_quotes.c		  \

INCLUDE = INCLUDES
PIPEX   = pipex

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
	@make -s -C $(INCLUDE)/
	@make -s -C $(PIPEX)/
	@mv $(INCLUDE)/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) libft.a $(PIPEX)/pipex.a $(PFLAGES) -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

clean :
	@make -s clean -C $(INCLUDE)/
	@make -s clean -C $(PIPEX)/
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)

fclean : clean
	@make -s fclean -C $(INCLUDE)/
	@make -s fclean -C $(PIPEX)/
	@rm -f libft.a
	@rm -f $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) deleted.$(RESET)

re : fclean all


.PHONY : all re clean fclean 
