# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wlanette <wlanette@student.21-school.ru    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/14 12:45:09 by wlanette          #+#    #+#              #
#    Updated: 2021/12/14 12:50:06 by wlanette         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= minitalk
CLIENT			= client
SERVER			= server

FT_PRINTF		= ./ft_printf/libftprintf.a
FT_PRINTF_DIR	= ./ft_printf/

SRC_CLIENT		= ./srcs/main_client.c 
SRC_SERVER		= ./srcs/main_server.c 
INCS			= ./includes/

CC				= clang
CFLAGS			= -Wall -Wextra -Werror
RM				= rm -rf

all:		$(SERVER) $(CLIENT)

$(NAME):	all

$(SERVER): $(FT_PRINTF)
	$(CC) $(CFLAGS) $(SRC_SERVER) $(FT_PRINTF) -I$(INCS) -o $(SERVER)

$(CLIENT): $(FT_PRINTF)
	$(CC) $(CFLAGS) $(SRC_CLIENT) ./srcs/main_utils.c $(FT_PRINTF) -I$(INCS) -o $(CLIENT)

$(FT_PRINTF):
			@make all -C $(FT_PRINTF_DIR)

clean:		
			@make clean -C $(FT_PRINTF_DIR)
			$(RM) $(CLIENT) $(SERVER)

fclean:		clean
			@make fclean -C $(FT_PRINTF_DIR)

re:			fclean all 

bonus:		all

.PHONY:		all clean fclean $(CLIENT) $(SERVER) $(FT_PRINTF) $(NAME)
