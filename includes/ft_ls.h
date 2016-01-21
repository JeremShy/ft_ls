#ifndef FT_LS_H
# define FT_LS_H

# include <libft.h>
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

typedef struct	dirent t_dirent;

typedef struct	s_opt
{
	int		l;
	int		R;
	int		a;
	int		r;
	int		t;
	char	folder[];
}				t_opt;

typedef struct	s_file
{
	char			name[256 + 1];
	ino_t			fileno;
	__uint16_t		name_len;
	struct s_file	*next;
}				t_file;

t_opt			ft_parsing(int ac, char **av);
#endif
