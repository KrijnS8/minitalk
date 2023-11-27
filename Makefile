# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: kschelvi <kschelvi@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2023/11/23 13:29:36 by kschelvi      #+#    #+#                  #
#    Updated: 2023/11/23 14:49:28 by kschelvi      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

CLIENT_NAME = client
SERVER_NAME = server

CFLAGS = -Wall -Werror -Wextra

CLIENT = ./client_src/client.c
SERVER = ./server_src/server.c

CLIENT_OBJ = $(CLIENT:%.c=%.o)
SERVER_OBJ = $(SERVER:%.c=%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(CLIENT_NAME) $(SERVER_NAME)

$(LIBFT):
	if [ ! -d "libft" ]; then \
		git clone https://github.com/KrijnS8/libft.git; \
	fi
	cd $(LIBFT_PATH) && $(MAKE)

$(CLIENT_NAME): $(CLIENT_OBJ)
	$(CC) $(CFLAGS) $(CLIENT_OBJ) $(LIBFT) -o $(CLIENT_NAME)

$(SERVER_NAME): $(SERVER_OBJ)
	$(CC) $(CFLAGS) $(SERVER_OBJ) $(LIBFT) -o $(SERVER_NAME)

clean:
	$(RM) $(CLIENT_OBJ) $(SERVER_OBJ)
	cd $(LIBFT_PATH) && $(MAKE) clean

fclean:
	$(RM) $(CLIENT_OBJ) $(CLIENT_NAME) $(SERVER_OBJ) $(SERVER_NAME)
	cd $(LIBFT_PATH) && $(MAKE) fclean

re: fclean all

.PHONY: all clean fclean re