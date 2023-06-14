# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/03 10:50:48 by zbp15             #+#    #+#              #
#    Updated: 2023/06/14 16:21:06 by rciaze           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex
CFLAGS		=	-Wall -Wextra -Werror -pthread -ggdb -O0
CC			=	cc 
CLEANF 		=	@(rm -f *.o)
OBJ 		=	${SRCS:.c=.o}
OBJ_B		=	${SRCS_B:.c=.o}


SRCS 		=	main.c \
				pipex.c \
				childs.c

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

$(NAME) : $(OBJ)
	@make -s -C ./libft
	@mv libft/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) libft.a -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

clean :
	@make -s clean -C ./libft
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)


bonus : $(OBJ_B)
	@make -s -C ./libft
	@mv libft/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ_B) libft.a -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

fclean : clean
	@make fclean -s -C ./libft
	@rm -f libft.a
	@rm -f $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) deleted.$(RESET)

re : fclean all


.PHONY : all re clean fclean 
