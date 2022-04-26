/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 20:45:10 by jkong             #+#    #+#             */
/*   Updated: 2022/04/26 22:16:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned char	*_t(int *color)
{
	return (&((unsigned char *)color)[3]);
}

static unsigned char	*_r(int *color)
{
	return (&((unsigned char *)color)[2]);
}

static unsigned char	*_g(int *color)
{
	return (&((unsigned char *)color)[1]);
}

static unsigned char	*_b(int *color)
{
	return (&((unsigned char *)color)[0]);
}

int	get_color(t_color *range, double rate)
{
	const double	inverse_rate = 1.0 - rate;
	int				result;

	*_t(&result) = inverse_rate * *_t(&range->begin) + rate * *_t(&range->end);
	*_r(&result) = inverse_rate * *_r(&range->begin) + rate * *_r(&range->end);
	*_g(&result) = inverse_rate * *_g(&range->begin) + rate * *_g(&range->end);
	*_b(&result) = inverse_rate * *_b(&range->begin) + rate * *_b(&range->end);
	return (result);
}
