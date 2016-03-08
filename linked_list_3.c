/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 15:27:36 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 16:12:21 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void	links(t_file *list, t_opt opt)
{
	while (list)
	{
		if (list->rights[0] == 'l')
		{
			if (!opt.l)
				list->path_to_lnk = NULL;
			else if (list->av_name[ft_strlen(list->av_name) - 1] == '/')
				list->path_to_lnk = NULL;
		}
		list = list->next;
	}
}

void	sort_n_print(t_file *list, t_opt options, int print_total, char *dir)
{
	list = ft_sort(list, options);
	ft_print(list, options, print_total);
	if (options.rmaj)
		ft_rec(list, options, dir);
	options.r = 0;
	destroy_list(list);
}

t_file	*create_printable_list(char *dir, t_file *list,
		DIR *directory, t_opt options)
{
	t_dirent *truc;

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
	return (list);
}

int		check_error(DIR *directory, char *name_pr, char *dir)
{
	if (!directory && errno != 20)
	{
		if (name_pr)
			ft_printf("%s:\n", name_pr);
		print_error(dir);
		return (1);
	}
	return (0);
}

t_file	*folder_is_file(char *lnk, char *dir, int *print_total, int *is_file)
{
	t_file *list;

	list = NULL;
	if (errno == 20 || lnk)
	{
		list_file(dir, &list);
		*is_file = 1;
		*print_total = 0;
	}
	return (list);
}
