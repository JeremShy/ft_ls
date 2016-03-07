/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: JeremShy <JeremShy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/21 22:19:38 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/07 11:36:51 by jcamhi           ###   ########.fr       */
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

int			list_folder(t_opt options, char *dir, char *name_pr, char *lnk)
{
	DIR			*directory;
	t_file		*list;
	int		print_total;
	int		is_file;

	is_file = 0;
	print_total = 1;
	errno = 0;
	directory = opendir(dir);
	list = NULL;
	if (check_error(directory, name_pr, dir))
		return (0);
	list = folder_is_file(lnk, dir, &print_total, &is_file);
	if (errno != 20 && !lnk)
		list = create_printable_list(dir, list, directory, options);
	if (name_pr && !is_file)
		ft_printf("%s:\n", name_pr);
	sort_n_print(list, options, print_total, dir);
	if (errno != 20)
		closedir(directory);
	return (!is_file);
}

int			main(int ac, char **av)
{
	t_opt		options;
	int			start;
	t_file		*list;
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
	while_main(list, ac, start, options);
	destroy_list(list);
	return (0);
}