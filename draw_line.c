/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:39 by jkong             #+#    #+#             */
/*   Updated: 2022/04/26 20:43:38 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static long	_abs_diff(long a, long b)
{
	if (a < b)
		return (b - a);
	else
		return (a - b);
}

void	draw_line(t_fdf *unit, t_point2 a, t_point2 b, t_color color)
{
	const t_point2	dst = {_abs_diff(a.x, b.x), _abs_diff(a.y, b.y)};
	const t_point2	sgn = {((a.x < b.x) << 1) - 1, ((a.y < b.y) << 1) - 1};
	long			err;
	t_point2		t;

	err = dst.x - dst.y;
	put_pixel(unit, a.x, a.y, color.begin);
	while (a.x != b.x || a.y != b.y)
	{
		t.x = (2 * err - dst.x) < 0;
		t.y = (2 * err + dst.y) > 0;
		if (t.y)
		{
			err -= dst.y;
			a.x += sgn.x;
		}
		if (t.x)
		{
			err += dst.x;
			a.y += sgn.y;
		}
		put_pixel(unit, a.x, a.y, color.end);
	}
}
