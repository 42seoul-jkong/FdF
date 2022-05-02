/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:05:39 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 19:41:40 by jkong            ###   ########.fr       */
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

static double	_rate(const t_point3 *c, const t_point3 *a, const t_point3 *b)
{
	long	val_c;
	long	val_a;
	long	val_b;

	if (_abs_diff(a->x, b->x) > _abs_diff(a->y, b->y))
	{
		val_c = c->x;
		val_a = a->x;
		val_b = b->x;
	}
	else
	{
		val_c = c->y;
		val_a = a->y;
		val_b = b->y;
	}
	if (val_a != val_b)
		return ((double)(val_c - val_a) / (double)(val_b - val_a));
	else
		return (1.0);
}

static void	_put_z(t_point3 *c, const t_point3 *a, const t_point3 *b)
{
	long	val_c;
	long	val_a;
	long	val_b;
	double	m;

	if (_abs_diff(a->x, b->x) > _abs_diff(a->y, b->y))
	{
		val_c = c->x;
		val_a = a->x;
		val_b = b->x;
	}
	else
	{
		val_c = c->y;
		val_a = a->y;
		val_b = b->y;
	}
	if (val_a != val_b)
	{
		m = (double)(b->z - a->z) / (double)(val_b - val_a);
		c->z = m * (double)(val_c - val_a) + a->z;
	}
	else
		c->z = a->z;
}

void	draw_line(t_fdf *unit, t_point3 a, t_point3 b, t_color color)
{
	const t_point2	dst = {_abs_diff(a.x, b.x), _abs_diff(a.y, b.y)};
	const t_point2	sgn = {((a.x < b.x) << 1) - 1, ((a.y < b.y) << 1) - 1};
	long			err;
	t_point2		t;
	t_point3		c;

	err = dst.x - dst.y;
	c = a;
	put_pixel_depth(unit, c, get_color(&color, _rate(&c, &a, &b)));
	while (c.x != b.x || c.y != b.y)
	{
		t = (t_point2){(2 * err - dst.x) < 0, (2 * err + dst.y) > 0};
		if (t.y)
		{
			err -= dst.y;
			c.x += sgn.x;
		}
		if (t.x)
		{
			err += dst.x;
			c.y += sgn.y;
		}
		_put_z(&c, &a, &b);
		put_pixel_depth(unit, c, get_color(&color, _rate(&c, &a, &b)));
	}
}
