/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/10 19:12:31 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		print_error(char *dir)
{
	char	*message;
	char	*ptr;

	ptr = ft_strchr(dir, '/');
	if (ptr)
		ptr++;
	else
		ptr = dir;
	message = ft_strjoin("ls: ", ptr);
	perror(message);
	free(message);
}

int			list_folder(t_opt options, char *dir)
{
	DIR			*directory;
	t_dirent	*truc;
	t_file		*list;
	char		*name;
	char		*path;

	errno = 0;
	directory = opendir(dir);
	list = NULL;
	if (!directory && errno != 20)
	{
		print_error(dir);
		return (0);
	}
	if (errno == 20)
	{
		name = ft_strrchr(dir, (int)'/');
		if (!name)
			name = dir;
		else if (*(name + 1) == '\0' && name != dir)
		{
			*name = '\0';
			name = ft_strrchr(dir, (int)'/');
			if (!name)
				name = dir;
			else
				name++;
		}
		else
			name++;
		path = ft_strsub(dir, 0, name - dir);
		list = create_elem(path, NULL, name);
		free(path);
	}
	while (errno != 20 && (truc = readdir(directory)))
	{
		if (truc->d_name[0] != '.' || (truc->d_name[0] == '.' && options.a))
		{
			if (list == NULL)
				list = create_elem(dir, NULL, truc->d_name);
			else
				add_elem_end(dir, list, truc->d_name);
		}
	}
	list = ft_sort(list, options);
	ft_print(list, options);
	if (options.rmaj)
		ft_rec(list, options, dir);
	options.r = 0;
	destroy_list(list);
	free(dir);
	if (errno != 20)
		closedir(directory);
	errno = 0;
	return (1);
}

int			main(int ac, char **av)
{
	t_opt		options;
	int			start;
	t_file		*list;

	options = ft_parsing(ac, av);
	start = find_start(ac, av);
	list = NULL;
	if (start == ac)
		list = create_elem("./", NULL, "");
	else
		list = create_dir_list(options, start, av, ac);
	options.f = 1;
	list = ft_sort(list, options);
	options.f = 0;
	while (list)
	{
		if (start != ac - 1 && start != ac)
			ft_printf("%s:\n", list->name);
		list_folder(options, (ft_strequ(list->name, "") ? ft_strdup(list->path):
					ft_strjoinaf1(ft_strjoin(list->path, list->name), "/")));
		if (start != ac - 1 && start != ac && list->next != NULL)
			ft_printf("\n");
		list = list->next;
	}
	return (0);
}
