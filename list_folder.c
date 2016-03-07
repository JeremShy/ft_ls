/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_folder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JeremShy <JeremShy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 11:00:48 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/07 11:36:01 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char  *list_file(char *dir, char **path, t_file **list)
{
	char	*name;

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
	(*path) = ft_strsub(dir, 0, name - dir);
	(*list) = create_elem(*path, NULL, name);
	return (name);
}
