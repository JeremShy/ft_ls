/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/22 02:13:25 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static void	print_error(char *dir)
{
	char *message;

	message = ft_strjoin("ls: ", dir);
	perror(message);
	free(message);
}

int			list(t_opt options, char *dir)
{
	DIR		*directory;
	t_dirent *truc;

	directory = opendir(dir);
	if (!directory)
	{
		print_error(dir);
		return (0);
	}
	while ((truc = readdir(directory)))
	{
		ft_putendl(truc->d_name);
	}
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
	else
		while (start < ac)
		{
			ft_printf("%s:\n\n", av[start]);
			list(options, av[start]);
			start++;
		}
	return (0);
}
