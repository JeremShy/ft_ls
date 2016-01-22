/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/21 22:57:55 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int	main(int ac, char **av)
{
	t_opt	options;
	DIR		*directory;

	directory = opendir("/dev/");
	t_dirent *truc;
	while ((truc = readdir(directory)))
	{
		ft_putendl(truc->d_name);
	}
	closedir(directory);
	options = ft_parsing(ac, av);
	ft_printf("options.l = %d\noptions.R = %d\noptions.a = %d\noptions.r = %d\noptions.t = %d\n", options.l, options.R, options.a, options.r, options.t);
	return (0);
}
