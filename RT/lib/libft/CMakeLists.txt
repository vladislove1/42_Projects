cmake_minimum_required( VERSION 3.9 FATAL_ERROR )

include_directories( ./include/ )

set( LIBFT_INCLUDE_DIR   ${CMAKE_CURRENT_SOURCE_DIR}/include PARENT_SCOPE)

set (LIBFT_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/include/libft.h
					${CMAKE_CURRENT_SOURCE_DIR}/include/get_next_line.h PARENT_SCOPE) 


set( LIBFT_FILES	ft_bzero.c ft_memset.c ft_memcmp.c ft_memccpy.c ft_memcpy.c ft_atoi.c 
					ft_memchr.c ft_strlen.c ft_strdup.c ft_strcpy.c ft_strncpy.c 
					ft_strcat.c	ft_strncat.c ft_strlcat.c ft_strchr.c ft_strrchr.c 
					ft_strstr.c	ft_strnstr.c ft_strncmp.c ft_strcmp.c ft_isdigit.c 
					ft_isspace.c ft_memmove.c ft_isalpha.c ft_isalnum.c ft_isascii.c 
					ft_isprint.c ft_toupper.c ft_tolower.c ft_memalloc.c ft_memdel.c 
					ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c 
					ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c 
					ft_strjoin.c ft_strtrim.c ft_count_symbols.c ft_count_words.c 
					ft_strsplit.c ft_itoa_base.c ft_itoa.c ft_get_size.c ft_putchar.c 
					ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c 
					ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c 
					ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_vec_cross_prod.c ft_vec_add.c 
					ft_vec_scalar.c ft_vector_init.c get_next_line.c is_directory.c ft_atod.c
					ft_remove_characters.c)

PREPEND(LIBFT_SOURCES src ${LIBFT_FILES})

add_library( libft ${LIBFT_SOURCES} )
