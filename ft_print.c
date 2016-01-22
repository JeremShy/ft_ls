/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/22 14:39:55 by jcamhi            #+#    #+#             */
/*   Updated: 2016/01/22 15:54:37 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

void			ft_print_with_l(t_file *list)
{
	t_max	max;

	max = find_max(list);
	while(list != NULL)
	{
		ft_printf("%s ", list->rights);
	}
}
