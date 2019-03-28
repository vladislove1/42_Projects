/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knikanor <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:47:46 by knikanor          #+#    #+#             */
/*   Updated: 2017/11/23 14:39:44 by knikanor         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct			s_tetrim
{
	int					x;
	int					y;
}						t_tetrim;

typedef struct			s_list
{
	int					num;
	char				l;
	struct s_tetrim		tetrimin[4];
	struct s_tetrim		place[4];
	struct s_list		*next;
}						t_list;

typedef struct			s_fillit
{
	int					count_t;
	int					chars;
	int					lines;
	int					count_ch;
	struct s_list		*list;
}						t_fillit;

int						check_open(char *file, t_fillit *a);
int						check_file(int	fd, char *temp, t_fillit *a);
int						validate(char **tetrimino, t_fillit *a);
void					delete_arr(char **arr, t_fillit *a);
char					**create_arr(char *file, t_fillit *a);
char					**create_map(int *side, t_fillit *main);
void					algoritm(t_list *lst, t_fillit *main);
t_tetrim				find_free(char **map, int *s, int size);
void					print(char **map);
int						find_solution(t_list *lst, char **map, int side);
int						place(char **map, t_list *lst, int side, int *skip);
void					freemap(char **map, int side);
void					tet_delete(char **map, t_list *lst);
t_tetrim				place_v2(char **map, t_list *lst, int side, int *skip);
void					ft_putstr(char const *s);

#endif
