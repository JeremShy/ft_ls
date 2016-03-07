/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rec.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/02 11:38:02 by jcamhi            #+#    #+#             */
/*   Updated: 2016/02/13 07:37:42 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	ft_rec(t_file *list, t_opt options, char *dir)
{
	char *path;

	while (list != NULL)
	{
		if ((list->rights)[0] == 'd' && !ft_strequ(list->name, ".") &&
				!ft_strequ(list->name, ".."))
		{
			path = ft_strjoinaf1(ft_strjoin(dir, list->name), "/");
			ft_printf("\n%s:\n", path);
			list_folder(options, path, NULL, NULL);
			free(path);
		}
		list = list->next;
	}
}
