NAME = libft.a
FLAGS = -Wall -Wextra -Werror
SRC = ft_atoi.c	ft_memalloc.c ft_putchar.c ft_strcat.c ft_striter.c	ft_strncmp.c ft_strsub.c \
		ft_bzero.c ft_memccpy.c	ft_putchar_fd.c	ft_strchr.c	ft_striteri.c ft_strncpy.c ft_strtrim.c \
		ft_isalnum.c ft_memchr.c ft_putendl.c ft_strclr.c ft_strjoin.c ft_strnequ.c ft_tolower.c \
		ft_isalpha.c ft_memcmp.c ft_putendl_fd.c ft_strcmp.c ft_strlcat.c ft_strnew.c ft_toupper.c \
		ft_isascii.c ft_memcpy.c ft_putnbr.c ft_strcpy.c ft_strlen.c ft_strnstr.c ft_strstr.c \
		ft_isdigit.c ft_memdel.c ft_putnbr_fd.c	ft_strdel.c	ft_strmap.c	ft_strrchr.c ft_strncat.c \
		ft_isprint.c ft_memmove.c ft_putstr.c ft_strdup.c ft_strmapi.c ft_strsplit.c ft_strequ.c \
		ft_itoa.c ft_memset.c ft_putstr_fd.c ft_strrev.c ft_space.c ft_lstmap.c ft_lstnew.c ft_lstadd.c \
		ft_lstdel.c ft_lstdelone.c ft_lstiter.c ft_max.c ft_min.c ft_sqrt.c
OBJ = ft_atoi.o	ft_memalloc.o ft_putchar.o ft_strcat.o ft_striter.o	ft_strncmp.o ft_strsub.o \
		ft_bzero.o ft_memccpy.o	ft_putchar_fd.o	ft_strchr.o	ft_striteri.o ft_strncpy.o ft_strtrim.o \
		ft_isalnum.o ft_memchr.o ft_putendl.o ft_strclr.o ft_strjoin.o ft_strnequ.o ft_tolower.o \
		ft_isalpha.o ft_memcmp.o ft_putendl_fd.o ft_strcmp.o ft_strlcat.o ft_strnew.o ft_toupper.o \
		ft_isascii.o ft_memcpy.o ft_putnbr.o ft_strcpy.o ft_strlen.o ft_strnstr.o ft_strstr.o \
		ft_isdigit.o ft_memdel.o ft_putnbr_fd.o	ft_strdel.o	ft_strmap.o	ft_strrchr.o ft_strncat.o \
		ft_isprint.o ft_memmove.o ft_putstr.o ft_strdup.o ft_strmapi.o ft_strsplit.o ft_strequ.o \
		ft_itoa.o ft_memset.o ft_putstr_fd.o ft_strrev.o ft_space.o ft_lstmap.o ft_lstdelone.o ft_lstiter.o \
		ft_lstdel.o ft_lstnew.o ft_lstadd.o ft_max.o ft_min.o ft_sqrt.o
HEADERS = libft.h

all: $(NAME)

$(NAME):
	gcc $(FLAGS) -c $(SRC) -I $(HEADERS)
	ar rc $(NAME) $(OBJ)
	ranlib $(NAME)

clean:
	/bin/rm -f *.o

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all

.PHONY: clean fclean re