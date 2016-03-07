/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 02:26:14 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/07 20:35:04 by jcamhi           ###   ########.fr       */
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
	char	f;
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
	char			*av_name;
	int				major;
	int				minor;
	struct s_file	*next;
	int				is_file;
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
	int				major;
	int				minor;
	int				sec;
}						t_max;

t_opt					ft_parsing(int ac, char **av);
int						find_start(int ac, char **av);
void					print_error(char *dir);
t_file					*create_elem(char *path,
							t_file *suivant, char *name);
void					add_elem_end(char *path,
							t_file *list, char *name);
void					add_elem_end_av(char *path,
							t_file *list, char *name, char *av);
void					add_elem_start(char *path,
							t_file **list, char *name);
t_max					find_max(t_file *list);
int						len(int nbr);
t_file					*ft_sort(t_file *list, t_opt opt);
void					ft_rec(t_file *list, t_opt options, char *dir);
int						list_folder(t_opt options, char *dir, char *name_pr, char *lnk);
t_file					*set_own_grp(t_stat structure, t_file *ret);
void					destroy_list(t_file *list);
void					ft_print(t_file *list, t_opt options, int print_total);
t_file					*create_dir_list(t_opt options, int start, char **av, int ac);
void					print_error_fp(char *dir);
void					list_file(char *dir, t_file **list);
char					rights_3(mode_t mode);
char					rights_6(mode_t mode);
char					rights_9(mode_t mode);
void					links(t_file *list, t_opt opt);
void					sort_n_print(t_file *list, t_opt options, int print_total, char *dir);
t_file					*create_printable_list(char *lnk, t_file *list, DIR *directory, t_opt options);
int						check_error(DIR *directory, char *name_pr, char *dir);
t_file					*folder_is_file(char *lnk, char *dir, int *print_total, int *is_file);
void					while_main(t_file *list, int ac, int start, t_opt options);
t_file					*create_2(t_file *ret, t_stat structure, char *name, char *path);
t_file					*create_link(t_stat structure, t_file *ret, char *join);
void					get_rights(t_file *ret, mode_t mode);
char					*find_name(char *dup, char **av, int start);
t_file					*create_fake_list(char **av, int start, int ac);
void					add_list_with_name(t_file *list, char *name, char *path, int size);
t_opt					init_opt(void);
t_file					*create_real_list(t_file *list, t_file *list2);
long long				(*init_tab(t_opt opt))(t_file *, t_file *, t_opt);
long long				ft_rights(t_file *elem1, t_file *elem2, t_opt opt);
long long				ft_lexic(t_file *elem1, t_file *elem2, t_opt opt);
long long				ft_lexic_inv(t_file *elem1, t_file *elem2, t_opt opt);
long long				ft_mod(t_file *elem1, t_file *elem2, t_opt opt);
long long				ft_mod_inv(t_file *elem1, t_file *elem2, t_opt opt);
#endif
