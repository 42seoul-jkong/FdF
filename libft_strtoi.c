/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_strtoi.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 13:19:54 by jkong             #+#    #+#             */
/*   Updated: 2022/04/21 21:58:19 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	_isspace(int c)
{
	return ((011 <= c && c <= 015) || c == ' ');
}

static int	_get_digit(int c, const char *base)
{
	int	i;

	if ('a' <= c && c <= 'z')
		c = 'A' + (c - 'a');
	i = 0;
	while (base[i] && base[i] != c)
		i++;
	return (i);
}

static int	_atoi_base(int sign, const char *str, const char *base)
{
	int	unit;
	int	number;
	int	digit;

	unit = _get_digit('\0', base);
	number = 0;
	while (*str)
	{
		digit = _get_digit(*str++, base);
		if (digit == unit)
			break ;
		number = unit * number + (1 - (sign << 1)) * digit;
	}
	return (number);
}

static int	_strtoi(const char *str)
{
	int			sign;
	const char	*base;

	sign = 0;
	if (*str == '+' || *str == '-')
		sign = *str++ == '-';
	if (*str == '0')
	{
		str++;
		if (*str == 'x' || *str == 'X')
		{
			str++;
			base = "0123456789ABCDEF";
		}
		else
			base = "01234567";
	}
	else
		base = "0123456789";
	return (_atoi_base(sign, str, base));
}

int	ft_strtoi(const char *str)
{
	while (_isspace(*str))
		str++;
	return (_strtoi(str));
}
