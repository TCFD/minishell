# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 10:50:48 by zbp15             #+#    #+#              #
#    Updated: 2023/06/17 19:37:33 by wolf             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CFLAGS		=	-Wall -Wextra -Werror -pthread -ggdb -O0
CC			=	cc 
CLEANF 		=	@(rm -f *.o)
OBJ_B		=	${SRCS_B:.c=.o}

SRCS_B		=	main_bonus.c \
				pipex_bonus.c \
				childs_bonus.c \
				utils_bonus.c

# Couleurs
BOLD		=	"\033[1m"
RESET		=	"\033[0m"
LIGHT_GREEN	=	"\033[92m"
LIGHT_CYAN	=	"\033[96m"

all : $(NAME)

.c.o:
	@echo $(BOLD)$(LIGHT_CYAN)Compiling $<... $(RESET)
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

$(NAME) : $(OBJ_B)
	@make -s -C ./libft
	@mv libft/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@ar rc pipex_bonus.a $(OBJ_B)

clean :
	@make -s clean -C ./libft
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)

fclean : clean
	@make fclean -s -C ./libft
	@rm -f libft.a
	@rm pipex_bonus.a
	@rm -f $(NAME)

re : fclean all

.PHONY : all re clean fclean
