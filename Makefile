# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dkovalen <dkovalen@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/01/10 19:33:18 by dkovalen          #+#    #+#              #
#    Updated: 2017/05/12 12:49:36 by dkovalen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =				libftprintf.a

CC =				gcc
FLAGS =				-Wall -Werror -Wextra

FT_SRC_DIR =		./libft
PRINTF_SRC_DIR =	./printf

HEADER =			./libft/includes/libft.h
PRINTF_SRC_HEADER =	./ft_printf.h

SRCO_LIBFT			= 	./libft/ft_strjoin3.o ./libft/ft_strjoin2.o ./libft/ft_lstiter.o	./libft/ft_putendl.o	./libft/ft_strdup.o	./libft/ft_strnequ.o ./libft/ft_lstmap.o	./libft/ft_putendl_fd.o	./libft/ft_strequ.o					\
						./libft/ft_strnew.o ./libft/ft_atoi.o	./libft/ft_lstnew.o	./libft/ft_putnbr.o	./libft/ft_striter.o	./libft/ft_strnstr.o ./libft/ft_bzero.o	./libft/ft_memalloc.o	./libft/ft_putnbr_fd.o		\
						./libft/ft_striteri.o	./libft/ft_strrchr.o ./libft/ft_isalnum.o	./libft/ft_memccpy.o	./libft/ft_putstr.o	./libft/ft_strjoin.o	./libft/ft_strsplit.o ./libft/ft_isalpha.o					\
						./libft/ft_memchr.o	./libft/ft_putstr_fd.o	./libft/ft_strlcat.o	./libft/ft_strstr.o ./libft/ft_isascii.o	./libft/ft_memcmp.o	./libft/ft_reduce.o	./libft/ft_strlcpy.o	./libft/ft_strsub.o \
						./libft/ft_isdigit.o	./libft/ft_memcpy.o	./libft/ft_strcat.o	./libft/ft_strlen.o	./libft/ft_strtrim.o ./libft/ft_isprint.o	./libft/ft_memdel.o	./libft/ft_strchr.o	./libft/ft_strmap.o			\
						./libft/ft_tolower.o ./libft/ft_itoa.o	./libft/ft_memmove.o	./libft/ft_strclr.o	./libft/ft_strmapi.o	./libft/ft_toupper.o ./libft/ft_lstadd.o	./libft/ft_memset.o	./libft/ft_strcmp.o		\
						./libft/ft_strncat.o ./libft/ft_lstdel.o	./libft/ft_putchar.o	./libft/ft_strcpy.o	./libft/ft_strncmp.o ./libft/ft_lstdelone.o	./libft/ft_putchar_fd.o	./libft/ft_strdel.o	./libft/ft_strncpy.o


PRINTF_COMPILED =	new.o create_type.o create_type_adds.o adress_wch.o str_c.o w_chars.o ft_printf.o itoa_bases_counts.o itoa_bases.o int_plus.o int_space.o print_int.o print_int_dot_small.o print_int_dot.o colors.o


all: $(NAME)

$(NAME): $(PRINTF_COMPILED)
	@ make -C ./libft
	@ar rc $(NAME) $(PRINTF_COMPILED) $(SRCO_LIBFT)
	@ranlib $(NAME)
	@echo "made" $(NAME)

$(PRINTF_COMPILED): %.o: %.c
	@$(CC) -c $(FLAGS) -I $(PRINTF_SRC_HEADER) -o $@ $<

clean:
	@-/bin/rm -f $(PRINTF_COMPILED)
	@-/bin/rm -f $(SRCO_LIBFT)
	@echo "cleaned" $(NAME)

fclean: clean
	@-/bin/rm -f $(NAME)
	@echo "fcleaned" $(NAME)

re: fclean all
