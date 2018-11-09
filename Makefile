# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ihuang <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 13:35:39 by ihuang            #+#    #+#              #
#    Updated: 2018/11/08 19:02:18 by ihuang           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls
SRCS = main.c params.c get_list.c append.c print.c ls.c free.c
OBJS = main.o params.o get_list.o append.o print.o ls.o free.o
FLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	@make -C libft/ fclean && make -C libft/
	@gcc -c $(SRCS)
	@gcc -o $(NAME) $(OBJS) libft/libft.a
	@echo "Compiled $(NAME)"

clean:
	@/bin/rm -f $(OBJS)

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Cleaned $(NAME)"

re: fclean all

norm:
	norminette $(SRCS) ft_ls.h

sanitize:
	clang -fsanitize=address $(FLAGS) -o $(NAME) $(SRCS)
