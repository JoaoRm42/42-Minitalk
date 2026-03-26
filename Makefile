NAME_SERVER		= server
NAME_CLIENT		= client

CC				= cc
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -f

PRINTF_DIR		= ft_printf
PRINTF_LIB		= $(PRINTF_DIR)/libftprintf.a

SRCS_SERVER		= src/server.c src/utils.c
SRCS_CLIENT		= src/client.c src/utils.c
SRCS_SERVER_BONUS	= bonus/server_bonus.c bonus/utils_bonus.c
SRCS_CLIENT_BONUS	= bonus/client_bonus.c bonus/utils_bonus.c

OBJS_SERVER		= $(SRCS_SERVER:.c=.o)
OBJS_CLIENT		= $(SRCS_CLIENT:.c=.o)
OBJS_SERVER_BONUS	= $(SRCS_SERVER_BONUS:.c=.o)
OBJS_CLIENT_BONUS	= $(SRCS_CLIENT_BONUS:.c=.o)

all: $(NAME_SERVER) $(NAME_CLIENT)

$(PRINTF_LIB):
	$(MAKE) -C $(PRINTF_DIR)

$(NAME_SERVER): $(OBJS_SERVER) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJS_SERVER) $(PRINTF_LIB) -o $(NAME_SERVER)

$(NAME_CLIENT): $(OBJS_CLIENT) $(PRINTF_LIB)
	$(CC) $(CFLAGS) $(OBJS_CLIENT) $(PRINTF_LIB) -o $(NAME_CLIENT)

bonus: $(PRINTF_LIB) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	$(CC) $(CFLAGS) $(OBJS_SERVER_BONUS) $(PRINTF_LIB) -o $(NAME_SERVER)
	$(CC) $(CFLAGS) $(OBJS_CLIENT_BONUS) $(PRINTF_LIB) -o $(NAME_CLIENT)

clean:
	$(RM) $(OBJS_SERVER) $(OBJS_CLIENT) $(OBJS_SERVER_BONUS) $(OBJS_CLIENT_BONUS)
	$(MAKE) -C $(PRINTF_DIR) clean

fclean: clean
	$(RM) $(NAME_SERVER) $(NAME_CLIENT)
	$(MAKE) -C $(PRINTF_DIR) fclean

re: fclean all

stress_mandatory: re
	bash ./stress_mandatory.sh

stress_bonus: bonus
	bash ./stress_bonus.sh

stress: stress_mandatory stress_bonus

.PHONY: all bonus clean fclean re stress stress_mandatory stress_bonus
