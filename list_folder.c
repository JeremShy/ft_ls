/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_folder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:00:48 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/07 19:50:49 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void  list_file(char *dir, t_file **list)
{
	char	*name;
	char	*path;

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
	(*list) = create_elem(path, NULL, name);
	free(path);
}

void	while_main(t_file *list, int ac, int start, t_opt options)
{
	char	*tmp;
	int		printed_nl;

	printed_nl = 2;
	while (list)
	{
		(!(start != ac - 1 && start != ac)) ? list->av_name = NULL : 0;
		if (!printed_nl && list->rights[0] == 'd')
		{
			printed_nl = 0;
			ft_printf("\n");
		}
		else if (printed_nl == 2)
			printed_nl = 0;
		tmp = ft_strequ(list->name, "") ? ft_strdup(list->path):
			ft_strjoinaf1(ft_strjoin(list->path, list->name), "/");
		if (list_folder(options, tmp, list->av_name, list->path_to_lnk) &&
				start != ac - 1 && start != ac && list->next != NULL)
		{
			ft_printf("\n");
			printed_nl = 1;
		}
		free(tmp);
		list = list->next;
	}
}
