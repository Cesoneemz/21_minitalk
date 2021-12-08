NAME			= minitalk
CLIENT			= client
SERVER			= server

FT_PRINTF		= ./ft_printf/libftprintf.a
FT_PRINTF_DIR	= ./ft_printf/

SRC_CLIENT		= ./srcs/main_client.c 
SRC_SERVER		= ./srcs/main_server.c
INCS			= ./includes/

CC				= gcc
CFLAGS			= -Wall -Wextra -Werror 
RM				= rm -rf

all:			$(SERVER) $(CLIENT)

$(NAME):		all 

$(SERVER): 		$(FT_PRINTF)
				$(CC) $(CFLAGS) -g $(SRC_SERVER) $(FT_PRINTF) -I$(INCS) -o $(SERVER)

$(CLIENT): 		$(FT_PRINTF)
				$(CC) $(CFLAGS) -g $(SRC_CLIENT) ./srcs/main_utils.c $(FT_PRINTF) -I$(INCS) -o $(CLIENT)

$(FT_PRINTF):
				@make all -C $(FT_PRINTF_DIR)

clean:			
				@make clean -C $(FT_PRINTF_DIR)
				$(RM) $(SERVER) $(CLIENT)

fclean:			clean
				@make fclean -C $(FT_PRINTF_DIR)

re:				fclean all

bonus:			all

.PHONY:			all $(NAME) $(SERVER) $(CLIENT) $(FT_PRINTF) clean fclean re bonus
