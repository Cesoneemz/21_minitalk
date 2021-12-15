# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 12:45:09 by wlanette          #+#    #+#              #
#    Updated: 2021/12/15 12:32:03 by wlanette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minitalk
CLIENT			= client
SERVER			= server

FT_PRINTF		= ./ft_printf/libftprintf.a
FT_PRINTF_DIR	= ./ft_printf/

SRC_CLIENT		= ./srcs/main_client.c ./srcs/main_utils.c
SRC_SERVER		= ./srcs/main_server.c 
INCS			= ./includes/
INCS_HEADER		= ./includes/minitalk.h

OBJS_CLIENT		= $(SRC_CLIENT:.c=.o)
OBJS_SERVER		= $(SRC_SERVER:.c=.o)

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror -I$(INCS)
RM				= rm -rf

all:		$(NAME)

$(NAME):	$(SERVER) $(CLIENT)

$(SERVER):  $(FT_PRINTF) $(OBJS_SERVER) $(INCS_HEADER)
			$(CC) $(CFLAGS) $(OBJS_SERVER) $(FT_PRINTF) -o $(SERVER)

$(CLIENT):  $(FT_PRINTF) $(OBJS_CLIENT) $(INCS_HEADER)
			$(CC) $(CFLAGS) $(OBJS_CLIENT) $(FT_PRINTF) -o $(CLIENT)

$(FT_PRINTF):
			make all -C $(FT_PRINTF_DIR)

clean:		
			make clean -C $(FT_PRINTF_DIR)
			$(RM) $(OBJS_SERVER) $(OBJS_CLIENT)

fclean:		clean
			make fclean -C $(FT_PRINTF_DIR)
			$(RM) $(CLIENT) $(SERVER)

re:			fclean all 

bonus:		$(SERVER) $(CLIENT)

norm:		
			norminette

.PHONY:		all clean fclean bonus re 
