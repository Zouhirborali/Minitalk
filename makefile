CC =cc 
CFLAGS =-Wall -Wextra -Werror
RM = rm -f 
NAME_C = client 
NAME_S = server 

NAME_C_B = client_bonus
NAME_S_B = server_bonus

SRC_S = ft_server.c lib.c 
SRC_C = ft_client.c lib.c 
SRC_C_B = ./bonus/ft_client_bonus.c ./bonus/lib_bonus.c 
SRC_S_B = ./bonus/ft_server_bonus.c ./bonus/lib_bonus.c 

OBJ_S = $(SRC_S:.c=.o)
OBJ_C = $(SRC_C:.c=.o)

OBJ_S_B = $(SRC_S_B:.c=.o)
OBJ_C_B = $(SRC_C_B:.c=.o)

all:$(NAME_S) $(NAME_C)

$(NAME_C):$(OBJ_C)
	$(CC) $(FLAGSE) $(OBJ_C) -o $(NAME_C)

$(NAME_S):$(OBJ_S)
	$(CC) $(FLAGSE) $(OBJ_S) -o $(NAME_S)

bonus: $(NAME_S_B) $(NAME_C_B)

$(NAME_C_B):$(OBJ_C_B)
	$(CC) $(FLAGSE) $(OBJ_C_B) -o $(NAME_C_B)

$(NAME_S_B):$(OBJ_S_B)
	$(CC) $(FLAGSE) $(OBJ_S_B) -o $(NAME_S_B)

$(OBJ_C) $(OBJ_S): minitalk.h
# $(OBJ_S): mintalk.h
$(OBJ_C_B) $(OBJ_S_B): ./bonus/minitalk_bonus.h
clean:
	$(RM) *.o 
	$(RM) ./bonus/*.o
fclean:clean
	$(RM) $(NAME_C) $(NAME_S) $(NAME_C_B) $(NAME_S_B)
	
re:fclean all

.PHONY:all clean fclean