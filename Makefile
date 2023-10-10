SRCS_FILES	= 	minishell.c \
				prompt.c \
				errors/ft_errors.c \
				manage_data_structs/clean/ft_clean_string.c \
				manage_data_structs/clean/ft_clean_t_data.c \
				manage_data_structs/clean/ft_clean_t_envlist_node.c \
				manage_data_structs/clean/ft_clean_t_envlist.c \
				manage_data_structs/clean/ft_clean_t_info.c \
				manage_data_structs/clean/ft_clean_t_token.c \
				manage_data_structs/clean/ft_clean_t_cmd.c \
				manage_data_structs/clean/ft_clean_2d_array.c \
				manage_data_structs/clean/ft_clean_2d_array_struct.c \
				manage_data_structs/set/set_t_data.c \
				manage_data_structs/set/set_t_info.c \
				parsing/bools/ft_is_cmd_separator.c \
				parsing/bools/ft_is_operator.c \
				parsing/bools/ft_is_pipe.c \
				parsing/bools/ft_is_quote.c \
				parsing/bools/ft_is_separator.c \
				parsing/bools/ft_is_space.c \
				parsing/bools/ft_is_dollar.c \
				parsing/checks/ft_check_pipes.c \
				parsing/checks/ft_check_quotes.c \
				parsing/checks/ft_check_syntax.c \
				parsing/checks/ft_check_redir.c \
				parsing/checks/ft_pass_when_quote.c \
				parsing/checks/ft_check_syntax_with_tokens.c \
				parsing/envp/ft_get_envp.c \
				parsing/envp/ft_get_val.c \
				parsing/envp/ft_new_envvar.c \
				parsing/envp/ft_get_key.c \
				parsing/envp/ft_print_env.c \
				parsing/envp/ft_set_flag.c \
				parsing/lexer/ft_display_lexer.c \
				parsing/lexer/ft_lexer_get_token_type.c \
				parsing/lexer/ft_lexer_get_token_val.c \
				parsing/lexer/ft_lexer.c \
				parsing/lexer/ft_retreat_lexer_remove_quotes.c \
				parsing/lexer/ft_retreat_lexer_detach.c \
				parsing/lexer/ft_retreat_lexer.c \
				parsing/expand/ft_expand.c \
				parsing/expand/ft_expand_detach.c \
				parsing/expand/ft_expand_val.c \
				parsing/join/ft_join_nodes.c \
				parsing/lists/ft_lst_env_add_back.c \
				parsing/lists/ft_lst_env_add_front.c \
				parsing/lists/ft_lst_env_last.c \
				parsing/lists/ft_lst_env_new.c \
				parsing/lists/ft_lst_env_pop.c \
				parsing/parser/ft_count_cmd.c \
				parsing/parser/ft_display_tab_cmd.c \
				parsing/parser/ft_fill_cmd_count_args.c \
				parsing/parser/ft_fill_cmd_fill_tab_args.c \
				parsing/parser/ft_fill_cmd_init_tab_args.c \
				parsing/parser/ft_fill_cmd.c \
				parsing/parser/ft_fill_cmd_redirs.c \
				parsing/parser/ft_init_cmd.c \
				parsing/parser/ft_init_tab_cmd.c \
				parsing/parser/ft_parser.c \
				parsing/parsing.c
				
PREFIX	= srcs

SRCS = $(addprefix ${PREFIX}/, ${SRCS_FILES})

OBJS = $(SRCS:.c=.o)

LIB = -Llibft -lft -lreadline
LIBFT_DIR = libft/
LIBFT = $(LIBFT_DIR)/libft.a

INCLUDE	= -Ilibft -Iheader -Ireadline

CC    = cc

CFLAGS  = -Wall -Wextra -Werror -g3 #-fsanitize=address

NAME    = minishell

DEPS			=	${SRCS:.c=.d}


#################
#### DISPLAY ####
#################

RED=\033[0;31m
BOLD_WHITE=\033[1m
GREEN=\033[1;32m
ORANGE=\033[0;33m
YELLOW=\033[1;33m
BLUE=\033[1;36m
NC=\033[0m # No Color


#################
##### RULES #####
#################

all: ${LIBFT} ${NAME}

${LIBFT}:
	echo -n "${BOLD_WHITE}⏳ COMPILING LIBFT${NC}"
	${MAKE} -sC ${LIBFT_DIR}
	echo "${GREEN}Done 💅${NC}"

${NAME}: ${OBJS}
	echo -n "${BOLD_WHITE}⏳ COMPILING MINISHELL${NC}"
	${CC} ${CFLAGS} ${OBJS} ${LIB} -o ${NAME}
	echo "${GREEN}Done 💅${NC}"

.c.o:
	${CC} ${CFLAGS} ${CDCFLAGS} ${INCLUDE} -c $< -o ${<:.c=.o}


clean:
	echo -n "${BOLD_WHITE}🧹 CLEANING OBJECTS\t${NC}"
	${MAKE} -sC ${LIBFT_DIR} clean
	${RM} ${OBJS}
	${RM} ${DEPS}
	${RM} *.seed ${RM} */*.seed
	echo "${GREEN}Done 💅${NC}"


fclean: clean
	echo -n "${BOLD_WHITE}🧹 CLEANING EXEC\t${NC}"
	${MAKE} -sC ${LIBFT_DIR} fclean
	${RM} ${NAME}
	echo "${GREEN}Done 💅${NC}"

re : fclean
	${MAKE}

seed :
	${RM} *.seed ${RM} */*.seed

.PHONY: re fclean all seed
.SILENT:
#				parsing/parser/ft_parser.c \
				parsing/parser/ft_count_cmd.c \
				parsing/parser/ft_init_tab_cmd.c \
				parsing/parser/ft_init_cmd.c \
				parsing/parser/ft_fill_cmd.c \
				parsing/parser/ft_fill_cmd_test_in.c \
				parsing/parser/ft_fill_cmd_test_out.c \
				parsing/parser/ft_fill_cmd_count_args.c \
				parsing/parser/ft_fill_cmd_init_tab_args.c \
				parsing/parser/ft_fill_cmd_fill_tab_args.c \
				parsing/parser/ft_display_tab_cmd.c \
				exec/set_up_cmd.c\
				exec/exec.c\
				exec/close.c\
				exec/error.c\
				exec/free.c\
				exec/redir.c\
				exec/usefull.c\
				exec/heredoc.c\
				exec/signals.c
				builtins/cd.c \
				builtins/env.c \
				builtins/export.c \
				builtins/unset.c \
				builtins/exit.c\
				builtins/echo.c\
				builtins/pwd.c\