/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:26:12 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 15:55:26 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static t_opt	ft_init(int *i)
{
	t_opt options;

	options.l = 0;
	options.rmaj = 0;
	options.a = 0;
	options.r = 0;
	options.t = 0;
	options.f = 0;
	*i = 1;
	return (options);
}

int				find_start(int ac, char **av)
{
	int	i;
	int	cont;

	i = 1;
	cont = 1;
	while (i < ac && cont)
	{
		if (av[i][0] == '-')
			i++;
		else if (ft_strequ(av[i], "--"))
			return (i + 1);
		else
			return (i);
	}
	return (i);
}

void			check_validity(char *av)
{
	int	i;

	i = 1;
	while (av[i] != '\0')
	{
		if (av[i] != 'l' && av[i] != 'R' && av[i] != 'a' && av[i] != 'r'
				&& av[i] != 't')
		{
			ft_printf("ls: illegal option -- %c\n", av[i]);
			ft_printf("usage: ls [-lRart] [file ...]\n");
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void			norme_parsing(int i, char **av, t_opt *options)
{
	if (ft_strchr(av[i], 'l'))
		options->l = 1;
	if (ft_strchr(av[i], 'R'))
		options->rmaj = 1;
	if (ft_strchr(av[i], 'a'))
		options->a = 1;
	if (ft_strchr(av[i], 'r'))
		options->r = 1;
	if (ft_strchr(av[i], 't'))
		options->t = 1;
}

t_opt			ft_parsing(int ac, char **av)
{
	t_opt	options;
	int		i;
	int		cont;

	options = ft_init(&i);
	cont = 1;
	while (i < ac && cont && !ft_strequ(av[i], "--"))
	{
		if (av[i][0] == '-')
		{
			check_validity(av[i]);
			norme_parsing(i, av, &options);
			i++;
		}
		else
			cont = 0;
	}
	return (options);
}
