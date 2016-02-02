/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/02 12:31:48 by jcamhi           ###   ########.fr       */
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
	if (options.l)
		ft_print_with_l(list);
	if (options.rmaj)
		ft_rec(list, options, dir);
	options.r = 0;
	destroy_list(list);
	closedir(directory);
	return (1);
}

int			main(int ac, char **av)
{
	t_opt	options;
	int		start;

	options = ft_parsing(ac, av);
	start = find_start(ac, av);
	if (start == ac)
		list_folder(options, ".");
	else if (start == ac - 1)
		list_folder(options, av[start]);
	else
		while (start < ac)
		{
			list_folder(options, av[start]);
			start++;
		}
	return (0);
}
