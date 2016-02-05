/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 02:26:14 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/04 18:32:17 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
# include <ft_printf.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <time.h>
# include <stdlib.h>
# include <stdio.h>
# include <errno.h>
# include <limits.h>

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct tm		t_tm;
typedef struct timespec	t_timespec;

typedef struct			s_opt
{
	int		l;
	int		rmaj;
	int		a;
	int		r;
	int		t;
	char	folder[];
}						t_opt;

typedef struct			s_file
{
	int				blocks;
	char			name[PATH_MAX + 1];
	int				name_len;
	char			rights[11];
	int				nlinks;
	char			*owner_name;
	char			*group_name;
	int				nbytes;
	char			*mounth;
	char			*day_name;
	char			*day_nbr;
	char			*hour;
	char			*min;
	char			*sec;
	t_timespec		m_time;
	char			*path;
	char			*path_to_lnk;
	struct s_file	*next;
}						t_file;

typedef struct			s_max
{
	int				name;
	int				rights;
	int				nlinks;
	int				owner_name;
	int				group_name;
	int				nbytes;
	int				mounth;
	int				day;
	int				hour;
	int				sec;
}						t_max;

t_opt					ft_parsing(int ac, char **av);
int						find_start(int ac, char **av);
void					print_error(char *dir);
t_file					*create_elem(const char *path,
							t_file *suivant, char *name);
void					add_elem_end(const char *path,
							t_file *list, char *name);
void					add_elem_start(const char *path,
							t_file **list, char *name);
t_max					find_max(t_file *list);
int						len(int nbr);
t_file					*ft_sort(t_file *list, t_opt opt);
void					ft_rec(t_file *list, t_opt options, char *dir);
int						list_folder(t_opt options, char *dir);
t_file					*set_own_grp(t_stat structure, t_file *ret);
void					destroy_list(t_file *list);
void					ft_print(t_file *list, t_opt options);
t_file					*create_dir_list(t_opt options, int start, char **av, int ac);
#endif
