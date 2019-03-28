#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pdomozhy <pdomozhy@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/01 23:44:17 by pdomozhy          #+#    #+#              #
#    Updated: 2017/12/01 23:44:17 by pdomozhy         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME	=	libq.a
HDRS	=	quaternion.h
FLGS	=	-Wall -Wextra -Werror
SRCS	=	add_q.c															\
			chb_q.c															\
			cmp_q.c															\
			cos_q.c															\
			crs_q.c															\
			dot_q.c															\
			dst_q.c															\
			lnr_q.c															\
			mag_q.c															\
			dst_q.c															\
			nrm_q.c															\
			opp_q.c															\
			rot_q.c															\
			scl_q.c															\
			sqr_q.c															\
			sub_q.c
OBJS	=	$(SRCS:.c=.o)
CC		=	clang

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)
	ranlib $(NAME)

%.o: %.c $(HDRS)
	$(CC) $(FLGS) -c $< -I $(HDRS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

norm: fclean
	norminette $(SRCS) $(HDRS)

.PHONY: all, clean, fclean, re, norm
