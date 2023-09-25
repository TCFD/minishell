# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rciaze <rciaze@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/28 09:28:24 by rciaze            #+#    #+#              #
#    Updated: 2023/09/25 16:33:25 by rciaze           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell
CFLAGS			=	-Wall -Wextra -Werror -g3 
PFLAGES			=	-lreadline
CC				=	gcc 
CLEANF 			=	@(find . -name "*.o" -type f -delete)
OBJ 			=	$(addprefix obj/,${SRCS:.c=.o})

INCLUDE			= 	includes/
SRC				=	src/

UTILS  			=	$(SRC)utils/
PARSING		  	=	$(SRC)parsing/

PIPEX  			=	$(SRC)pipe_and_redirections/pipe/
REDIRECTIONS	=	$(SRC)pipe_and_redirections/redirections/

COMMAND_UTILS  	=	$(UTILS)command_utils/
MALLOC_UTILS	=	$(UTILS)malloc_utils/
DESIGN_PATTERN  =   $(UTILS)design_pattern/
GLOBAL			=	$(UTILS)global/

ALL_H_FILES	=	$(INCLUDE)/minishell.h					\
				$(INCLUDE)/pipex.h

SRCS 		=	main.c									\
				$(SRC)start_init.c						\
				$(SRC)run_minishell.c					\
				$(SRC)run_minishell2.c					\
				$(SRC)minishell_args.c					\
				$(SRC)run_minishell_utils.c				\
				$(UTILS)len_utils.c						\
				$(UTILS)signals_utils.c					\
				$(UTILS)prompt_utils.c					\
				$(UTILS)prompt_utils2.c					\
				$(UTILS)init_utils.c					\
				$(UTILS)dollar_completion.c				\
				$(UTILS)others_utils.c					\
				$(DESIGN_PATTERN)design_p_username.c	\
				$(DESIGN_PATTERN)design_p_home_path.c	\
				$(DESIGN_PATTERN)design_p_env.c			\
				$(DESIGN_PATTERN)design_p_env2.c		\
				$(DESIGN_PATTERN)design_p_pwd.c			\
				$(DESIGN_PATTERN)design_p_sign.c		\
				$(DESIGN_PATTERN)design_p_cd.c			\
				$(DESIGN_PATTERN)design_p_tmp.c			\
				$(GLOBAL)errno_management.c				\
				$(MALLOC_UTILS)free_utils.c				\
				$(MALLOC_UTILS)free_utils2.c			\
				$(MALLOC_UTILS)realloc_utils.c			\
				$(COMMAND_UTILS)shlvl_utils.c			\
				$(COMMAND_UTILS)underscore_value.c		\
				$(COMMAND_UTILS)execute_utils.c			\
				$(COMMAND_UTILS)execute_utils2.c		\
				$(COMMAND_UTILS)execute_utils3.c		\
				$(COMMAND_UTILS)cd_utils.c				\
				$(COMMAND_UTILS)cd_utils2.c				\
				$(COMMAND_UTILS)echo_utils.c			\
				$(COMMAND_UTILS)env_utils.c				\
				$(COMMAND_UTILS)env_utils2.c			\
				$(COMMAND_UTILS)env_utils3.c			\
				$(COMMAND_UTILS)export_utils.c			\
				$(COMMAND_UTILS)pwd_utils.c				\
				$(COMMAND_UTILS)exit_utils.c			\
				$(PARSING)parsing_utils.c				\
				$(PARSING)parsing_utils2.c				\
				$(PARSING)check_correct_quotes.c		\
				$(PARSING)main_parsing.c				\
				$(PARSING)cases_for_parsing.c 			\
				$(REDIRECTIONS)right_rafter_utils.c		\
				$(REDIRECTIONS)right_rafter_utils2.c	\
				$(REDIRECTIONS)left_rafter_utils.c		\
				$(REDIRECTIONS)left_rafter_utils2.c		\
				$(PIPEX)childs.c							\
				$(PIPEX)init_pipex.c							\
				$(PIPEX)pipex_utils.c							\
				$(PIPEX)pipex.c							\

# Couleurs
BOLD		=	"\033[1m"
RESET		=	"\033[0m"
LIGHT_GREEN	=	"\033[92m"
LIGHT_CYAN	=	"\033[96m"

all : $(NAME)

obj/%.o: %.c $(ALL_H_FILES)
	@mkdir -p $(dir $@)
	@echo $(BOLD)$(LIGHT_CYAN)Compiling $<... $(RESET)
	@${CC} ${CFLAGS} -c $< -o $@ -I includes

$(NAME) : $(OBJ)
	@make -s -C $(INCLUDE)/libft_stuff
	@mv $(INCLUDE)/libft_stuff/libft.a .
	@echo $(LIGHT_GREEN)	Libft done.$(RESET)
	@$(CC) $(CFLAGS) $(OBJ) libft.a $(PFLAGES) -o $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) is created !$(RESET)

clean :
	@$(CLEANF)
	@echo $(BOLD)$(LIGHT_GREEN).o deleted.$(RESET)
	@rm -rf obj/

fclean : clean
	@rm -f libft.a
	@rm -f $(NAME)
	@echo $(BOLD)$(LIGHT_GREEN)$(NAME) deleted.$(RESET)

re : fclean all

.PHONY : all re clean fclean
