/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/04 15:55:14 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void		print_error(char *dir)
{
	char	*message;
	char	*ptr;
	char	*dup;

	dup = ft_strdup(dir);
	ptr = ft_strrchr(dup, '/');
	if (ptr && ptr != dup)
	{
		*ptr = '\0';
		ptr = ft_strrchr(dup, '/');
	}
	if (ptr)
		ptr++;
	else
		ptr = dup;
	message = ft_strjoin("ls: ", ptr);
	perror(message);
	free(message);
	free(dup);
}

void		print_error_fp(char *dir)
{

	char *message;

	message = ft_strjoin("ls: ", dir);
	perror(message);
	free(message);

}

int			list_folder(t_opt options, char *dir, int print_name,
			char *name_pr)
{
	DIR			*directory;
	t_dirent	*truc;
	t_file		*list;
	char		*name;
	char		*path;
	int		print_total;
	int		is_file;

	is_file = 0;;
	errno = 0;
	print_total = 1;
	directory = opendir(dir);
	list = NULL;
	if (!directory && errno != 20)
	{
		if (print_name)
			ft_printf("%s:\n", name_pr);
		print_error(dir);
		return (0);
	}
	if (errno == 20)
	{
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
		list = create_elem(path, NULL, name);
		is_file = 1;
		print_total = 0;
		print_name = 0;
	}
	while (errno != 20 && (truc = readdir(directory)))
	{
		if (truc->d_name[0] != '.' || (truc->d_name[0] == '.' && options.a))
		{
			if (list == NULL)
				list = create_elem(dir, NULL, truc->d_name);
			else
				add_elem_end(dir, list, truc->d_name);
		}
	}
	list = ft_sort(list, options);
	if (print_name)
		ft_printf("%s:\n", name_pr);
	ft_print(list, options, print_total);
	if (options.rmaj)
		ft_rec(list, options, dir);
	options.r = 0;
	destroy_list(list);
	if (errno != 20)
		closedir(directory);
	errno = 0;
	return (!is_file);
}

int			main(int ac, char **av)
{
	t_opt		options;
	int			start;
	t_file		*list;
	char		*tmp;
	int		print_name;

	print_name = 0;
	options = ft_parsing(ac, av);
	start = find_start(ac, av);
	list = NULL;
	if (start == ac)
		list = create_elem(ft_strdup("./"), NULL, ft_strdup(""));
	else
		list = create_dir_list(options, start, av, ac);
	options.f = 1;
	list = ft_sort(list, options);
	options.f = 0;
	while (list)
	{
		if (start != ac - 1 && start != ac)
			print_name = 1;
		tmp = ft_strequ(list->name, "") ? ft_strdup(list->path):
					ft_strjoinaf1(ft_strjoin(list->path, list->name), "/");
		if (list_folder(options, tmp, print_name, list->av_name) &&
			start != ac - 1 && start != ac && list->next != NULL)
			ft_printf("\n");
		free(tmp);
		list = list->next;
	}
	destroy_list(list);
	return (0);
}
