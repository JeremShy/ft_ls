/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <jcamhi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 02:52:25 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 15:44:37 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

static char	handle_type(mode_t mode)
{
	if ((mode & S_IFMT) == S_IFREG)
		return ('-');
	else if ((mode & S_IFMT) == S_IFIFO)
		return ('p');
	else if ((mode & S_IFMT) == S_IFCHR)
		return ('c');
	else if ((mode & S_IFMT) == S_IFDIR)
		return ('d');
	else if ((mode & S_IFMT) == S_IFBLK)
		return ('b');
	else if ((mode & S_IFMT) == S_IFLNK)
		return ('l');
	else if ((mode & S_IFMT) == S_IFSOCK)
		return ('s');
	else
		return ('-');
}

void		get_rights(t_file *ret, mode_t mode)
{
	ret->rights[0] = handle_type(mode);
	ret->rights[1] = (mode & S_IRUSR ? 'r' : '-');
	ret->rights[2] = (mode & S_IWUSR ? 'w' : '-');
	ret->rights[3] = rights_3(mode);
	ret->rights[4] = (mode & S_IRGRP ? 'r' : '-');
	ret->rights[5] = (mode & S_IWGRP ? 'w' : '-');
	ret->rights[6] = rights_6(mode);
	ret->rights[7] = (mode & S_IROTH ? 'r' : '-');
	ret->rights[8] = (mode & S_IWOTH ? 'w' : '-');
	ret->rights[9] = rights_9(mode);
	ret->rights[10] = '\0';
}

void		add_elem_end(char *path, t_file *list, char *name)
{
	t_file *elem;

	if (!(elem = create_elem(path, NULL, name)))
		return ;
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
}

void		add_elem_end_av(char *path, t_file *list, char *name, char *av)
{
	t_file *elem;

	if (!(elem = create_elem(path, NULL, name)))
		return ;
	elem->av_name = ft_strdup(av);
	while (list->next != NULL)
		list = list->next;
	list->next = elem;
}

void		add_elem_start(char *path, t_file **list, char *name)
{
	t_file	*elem;

	elem = create_elem(path, *list, name);
	*list = elem;
}
