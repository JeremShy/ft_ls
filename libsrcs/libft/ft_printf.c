#include <libft.h>

static int	ft_1(const char *str, int *i)
{
	if (str[*i] != '%')
	{
		ft_putchar(str[*i]);
		(*i)++;
		return (1);
	}
	else if (str[*i + 1] == '\0')
	{
		(*i)++;
		return (1);
	}
	else if (str[*i + 1] == '%')
	{
		ft_putchar(str[*i]);
		(*i) += 2;
		return (1);
	}
	return (0);
}
static int	ft_2(const char *str, int *i, va_list list)
{
	if (str[*i + 1] == 'd')
	{
		ft_putstr(ft_itoa_base(va_arg(list, int), 10));
		*i += 2;
		return (1);
	}
	else if (str[*i + 1] == 's')
	{
		ft_putstr(va_arg(list, char *));
		*i += 2;
		return (1);
	}
	else if (str[*i + 1] == 'c')
	{
		ft_putchar(va_arg(list, int));
		*i += 2;
		return (1);
	}
	return (0);
}
int		ft_printf(const char *str, ...)
{
	va_list list;
	int i;

	i = 0;
	va_start(list, str);
	while(str[i] != '\0')
	{
		if (!ft_1(str, &i))
			if (!ft_2(str, &i, list))
				i++;
	}
	va_end(list);
	return (0);
}
