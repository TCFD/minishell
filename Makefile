# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wolf <wolf@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 09:28:24 by rciaze            #+#    #+#              #
#    Updated: 2023/07/05 12:15:57 by wolf             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CFLAGS			=	-Wall -Wextra -Werror -g3 
PFLAGES			=	-lreadline
CC				=	gcc 
CLEANF 			=	@(find . -name "*.o" -type f -delete)
OBJ 			=	$(addprefix obj/,${SRCS:.c=.o})
INCLUDE			= 	INCLUDES
PIPEX  			=	pipe_and_redirections/pipe/pipex
REDIRECTIONS	=	pipe_and_redirections/redirections/
UTILS  			=	utils/
COMMAND_UTILS  	=	$(UTILS)command_utils/
MALLOC_UTILS	=	$(UTILS)malloc_utils/
DESIGN_PATTERN  =   $(UTILS)design_pattern/
GLOBAL			=	$(UTILS)global/
QUOTES_STUFF  	=	quotes_stuff/

SRCS 		=	maintest.c								\
				$(UTILS)len_utils.c						\
				$(UTILS)signals_utils.c					\
				$(UTILS)parsing_utils.c					\
				$(UTILS)prompt_utils.c					\
				$(UTILS)init_utils.c					\
				$(UTILS)dollar_completion.c				\
				$(UTILS)others_utils.c					\
				$(DESIGN_PATTERN)design_p_username.c	\
				$(DESIGN_PATTERN)design_p_env.c			\
				$(GLOBAL)errno_management.c				\
				$(MALLOC_UTILS)free_utils.c				\
				$(COMMAND_UTILS)shlvl_utils.c			\
				$(MALLOC_UTILS)realloc_utils.c			\
				$(COMMAND_UTILS)execute_utils.c			\
				$(COMMAND_UTILS)execute_utils2.c		\
				$(COMMAND_UTILS)cd_utils.c				\
				$(COMMAND_UTILS)echo_utils.c			\
				$(COMMAND_UTILS)env_utils.c				\
				$(COMMAND_UTILS)env_utils2.c			\
				$(COMMAND_UTILS)env_utils3.c			\
				$(COMMAND_UTILS)export_utils.c			\
				$(COMMAND_UTILS)pwd_utils.c				\
				$(COMMAND_UTILS)exit_utils.c			\
				$(QUOTES_STUFF)check_correct_quotes.c	\
				$(QUOTES_STUFF)interpret_quotes.c		\
				$(REDIRECTIONS)right_rafter_utils.c		\
				$(REDIRECTIONS)right_rafter_utils2.c	\

# Couleurs
BOLD		=	"\033[1m"
RESET		=	"\033[0m"
LIGHT_GREEN	=	"\033[92m"
LIGHT_CYAN	=	"\033[96m"

all : $(NAME)

obj/%.o: %.c
	@mkdir -p $(dir $@)
	@echo $(BOLD)$(LIGHT_CYAN)Compiling $<... $(RESET)
	@${CC} ${CFLAGS} -c $< -o $@

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
	@rm -rf obj/

fclean : clean
	@rm -f libft.a
	@rm -f $(NAME)
	@make -s fclean -C $(PIPEX)/
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) deleted.$(RESET)

re : fclean all

.PHONY : all re clean fclean
