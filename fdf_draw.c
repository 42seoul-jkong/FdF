/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 16:20:57 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 22:25:27 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	_ensure_rect(t_rect *rect, t_fdf_point *pt, int force)
{
	if (force || pt->coord.x < rect->left)
		rect->left = pt->coord.x;
	if (force || pt->coord.x > rect->right)
		rect->right = pt->coord.x;
	if (force || pt->coord.y < rect->top)
		rect->top = pt->coord.y;
	if (force || pt->coord.y > rect->bottom)
		rect->bottom = pt->coord.y;
}

static int	_in(t_fdf *unit, t_fdf_point *p, t_fdf_point *px, t_fdf_point *py)
{
	const t_rect	win_rect = {0, unit->win_dim.x, 0, unit->win_dim.y};
	t_rect			rect;

	_ensure_rect(&rect, p, 1);
	if (px)
		_ensure_rect(&rect, px, 0);
	if (py)
		_ensure_rect(&rect, py, 0);
	if (win_rect.left <= rect.right && rect.left < win_rect.right)
		return (1);
	if (win_rect.top <= rect.bottom && rect.top < win_rect.bottom)
		return (1);
	return (0);
}

static void	_transform_fdf(t_fdf *unit, long x, long y)
{
	t_fdf_point *const	pos = get_pos(&unit->map, x, y);
	t_point3f			pt;
	t_point3f			center;

	pt = (t_point3f){x, y, unit->z_size * pos->value};
	center = zero_z_2(center_2(unit->map.dim));
	translate(&pt, negative_3f(center));
	rotate_pitch(&pt, unit->rotate.x);
	rotate_roll(&pt, unit->rotate.y);
	rotate_yaw(&pt, unit->rotate.z);
	translate(&pt, center);
	scale(&pt, unit->scale);
	translate(&pt, unit->translate);
	pos->coord = integer_3f(pt);
}

static void	_pixel_fdf(t_fdf *unit, long x, long y)
{
	t_fdf_point *const	pos = get_pos(&unit->map, x, y);
	t_fdf_point			*pos_px;
	t_fdf_point			*pos_py;
	t_color				color;

	pos_px = NULL;
	pos_py = NULL;
	if (x > 0)
		pos_px = get_pos(&unit->map, x - 1, y);
	if (y > 0)
		pos_py = get_pos(&unit->map, x, y - 1);
	if (_in(unit, pos, pos_px, pos_py))
	{
		if (pos_px)
		{
			color = (t_color){pos_px->color, pos->color};
			draw_line(unit, pos_px->coord, pos->coord, color);
		}
		if (pos_py)
		{
			color = (t_color){pos_py->color, pos->color};
			draw_line(unit, pos_py->coord, pos->coord, color);
		}
		put_pixel_depth(unit, pos->coord, pos->color);
	}
}

void	draw_fdf(t_fdf *unit)
{
	long	i;

	fill_image(unit, 0xCC);
	i = 0;
	while (i < unit->map.dim.x * unit->map.dim.y)
	{
		_transform_fdf(unit, i % unit->map.dim.x, i / unit->map.dim.x);
		i++;
	}
	clear_depth(unit);
	i = 0;
	while (i < unit->map.dim.x * unit->map.dim.y)
	{
		_pixel_fdf(unit, i % unit->map.dim.x, i / unit->map.dim.x);
		i++;
	}
	refresh_window(unit);
}
