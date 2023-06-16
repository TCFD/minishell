# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tboldrin <tboldrin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 09:28:24 by rciaze            #+#    #+#              #
#    Updated: 2023/06/16 16:36:11 by tboldrin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minishell
CFLAGS		=	-Wall -Wextra -Werror
PFLAGES		=	-lreadline
CC			=	cc 
CLEANF 		=	@(rm -f *.o)
OBJ 		=	${SRCS:.c=.o}
OBJ_B		=	${SRCS_B:.c=.o}


SRCS 		=	maintest.c

INCLUDE = INCLUDES

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
	@mv $(INCLUDE)/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) libft.a $(PFLAGES) -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

clean :
	@make -s clean -C $(INCLUDE)/
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)


bonus : $(OBJ_B)
	@make -s -C $(INCLUDE)/
	@mv $(INCLUDE)/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ_B) libft.a -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

fclean : clean
	@make fclean -s -C $(INCLUDE)/
	@rm -f libft.a
	@rm -f $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) deleted.$(RESET)

re : fclean all


.PHONY : all re clean fclean 
