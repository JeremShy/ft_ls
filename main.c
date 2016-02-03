/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/03 20:06:22 by jcamhi           ###   ########.fr       */
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
	printf("errno = %d\n", errno);
	perror(message);
	free(message);
}

int			list_folder(t_opt options, char *dir)
{
	DIR			*directory;
	t_dirent	*truc;
	t_file		*list;

	errno = 0;
	directory = opendir(dir);
	list = NULL;
	if (!directory)
	{
		if (errno == 20)
		{
			list = create_elem(dir, NULL, dir);
			errno = 0;
			return (1);
		}
		print_error(dir);
		return (0);
	}
	while ((truc = readdir(directory)))
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
		list = create_elem(".", NULL, truc->d_name);
	}
	else
		list = create_dir_list(options, start, av, ac);
	while (list)
	{
		list_folder(options, list->path);
		list = list->next;
	}
	return (0);
}
