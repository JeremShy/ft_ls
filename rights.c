/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/07 14:16:09 by jcamhi            #+#    #+#             */
/*   Updated: 2016/03/08 15:49:18 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	rights_3(mode_t mode)
{
	if (mode & S_ISUID && !(mode & S_IXUSR))
		return ('S');
	else if (mode & S_ISUID && (mode & S_IXUSR))
		return ('s');
	else if (!(mode & S_ISUID) && (mode & S_IXUSR))
		return ('x');
	else
		return ('-');
}

char	rights_6(mode_t mode)
{
	if (mode & S_ISGID && !(mode & S_IXGRP))
		return ('S');
	else if (mode & S_ISGID && (mode & S_IXGRP))
		return ('s');
	else if (!(mode & S_ISGID) && (mode & S_IXGRP))
		return ('x');
	else
		return ('-');
}

char	rights_9(mode_t mode)
{
	if (mode & S_ISVTX && !(mode & S_IXOTH))
		return ('T');
	else if (mode & S_ISVTX && (mode & S_IXOTH))
		return ('t');
	else if (!(mode & S_ISVTX) && (mode & S_IXOTH))
		return ('x');
	else
		return ('-');
}
