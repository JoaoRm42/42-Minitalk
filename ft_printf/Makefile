# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: joaoped2 <joaoped2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/16 16:19:02 by joaoped2          #+#    #+#              #
#    Updated: 2026/03/24 23:30:00 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = libftprintf.a
SRCS = ft_printf.c ft_printaddr.c ft_printhexa.c ft_printnbr.c ft_printstr.c ft_singlechar.c
BONUS_SRCS = ft_printf_bonus.c ft_printf_parse_bonus.c ft_printf_format_bonus.c \
	ft_printf_text_bonus.c ft_printf_dispatch_bonus.c ft_printf_convert_bonus.c \
	ft_printf_output_bonus.c

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

bonus: $(BONUS_OBJS)
	ar rc $(NAME) $(BONUS_OBJS)

clean:
	rm -rf $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all
