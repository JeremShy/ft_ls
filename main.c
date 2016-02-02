/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/02 18:54:49 by jcamhi           ###   ########.fr       */
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

	directory = opendir(dir);
	list = NULL;
	if (!directory)
	{
		print_error(dir);
		return (0);
	}
	while ((truc = readdir(directory)))
	{
		if (truc->d_name[0] != '.' || (truc->d_name[0] == '.' && options.a))
		{
			if (list == NULL)
				list = create_elem(*truc, dir, NULL);
			else
				add_elem_end(*truc, dir, list);
		}
	}
	list = ft_sort(list, options);
	ft_print(list, options);
	if (options.rmaj)
		ft_rec(list, options, dir);
	options.r = 0;
	destroy_list(list);
	closedir(directory);
	return (1);
}

static t_dirent	*find_dirent(DIR *directory, char *name)
{
	t_dirent *truc;

	while ((truc = readdir(directory)))
		if (ft_strequ(truc->d_name, name))
			return (truc);
	return (NULL);
}

int			main(int ac, char **av)
{
	t_opt		options;
	int			start;
	t_file		*list;
	DIR			*directory;
	t_dirent	*truc;

	options = ft_parsing(ac, av);
	start = find_start(ac, av);
	list = NULL;
	if (start == ac)
	{
		directory = opendir(".");
		truc = find_dirent(directory, ".");
		list = create_elem(*truc, ".", NULL);
	}
	else
		while (start < ac)
		{
			directory = opendir(av[start]);
			truc = find_dirent(directory, ".");
			if (!list)
				list = create_elem(*truc, av[start], NULL);
			else
				add_elem_end(*truc, av[start], list);
			closedir(directory);
			start++;
		}
	while (list)
	{
		ft_printf("list: %s\n", list->name);
		list = list->next;
	}
	return (0);
}
