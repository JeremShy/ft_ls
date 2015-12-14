/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcamhi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 16:58:17 by jcamhi            #+#    #+#             */
/*   Updated: 2015/11/25 18:52:15 by jcamhi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static	int		ft_calc(int n)
{
	int len;

	len = 0;
	while (n)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char			*ft_itoa(int n)
{
	int		len[2];
	char	*str;

	len[0] = 0;
	len[1] = 0;
	if (!n)
		return ("0");
	if (n == -2147483648)
		return ("-2147483648");
	if (n < 0)
	{
		len[1] = 1;
		n *= -1;
	}
	len[0] = ft_calc(n);
	str = (char*)malloc(len[0] * sizeof(char) + 1 + len[1]);
	str[0] = len[1] ? '-' : str[0];
	str[len[0] + len[1]] = '\0';
	while (n)
	{
		str[len[0] - 1 + len[1]] = n % 10 + '0';
		n /= 10;
		len[0]--;
	}
	return (str);
}
