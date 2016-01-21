/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:26:12 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/21 22:26:34 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static t_opt   ft_init(int *i)
{
	t_opt options;

	options.l = 0;
	options.R = 0;
	options.a = 0;
	options.r = 0;
	options.t = 0;
	*i = 1;
	return (options);
}

t_opt   ft_parsing(int ac, char **av)
{
	t_opt   options;
	int     i;
	int     cont;

	options = ft_init(&i);
	cont = 1;
	while(i < ac && cont)
		if (av[i][0] == '-')
		{
			if (ft_strchr(av[i], 'l'))
				options.l = 1;
			if (ft_strchr(av[i], 'R'))
				options.R = 1;
			if (ft_strchr(av[i], 'a'))
				options.a = 1;
			if (ft_strchr(av[i], 'r'))
				options.r = 1;
			if (ft_strchr(av[i], 't'))
				options.t = 1;
			i++;
		}
		else
			cont = 0;
	return (options);
}
