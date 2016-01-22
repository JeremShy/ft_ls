/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/22 04:40:08 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		print_error(char *dir)
{
	char	*message;

	dir = ft_strchr(dir, '/');
	message = ft_strjoin("ls: ", dir);
	perror(message);
	free(message);
}



static void	ft_print_with_l(t_file *list)
{

	while(list != NULL)
	{
		ft_printf("%s ", list->rights);

	}
}

int			list(t_opt options, char *dir)
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
		if (list == NULL)
			list = create_elem(*truc, dir, NULL);
		else
			add_elem_end(*truc, dir, list);
	}
	if (options.l)
		ft_print_with_l(list);
	options.r = 0;
	closedir(directory);
	return (1);
}

int			main(int ac, char **av)
{
	t_opt	options;
	int		start;

	options = ft_parsing(ac, av);
//	ft_printf("options.l = %d\noptions.R = %d\noptions.a = %d\noptions.r = %d\noptions.t = %d\n", options.l, options.R, options.a, options.r, options.t);
	start = find_start(ac, av);
	if (start == ac)
		list(options, ".");
	else if (start == ac - 1)
		list(options, av[start]);
	else
		while (start < ac)
		{
			list(options, av[start]);
			start++;
		}
	return (0);
}
