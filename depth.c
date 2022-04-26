/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:55:55 by jkong             #+#    #+#             */
/*   Updated: 2022/04/26 22:16:28 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_depth(t_fdf *unit)
{
	const size_t	s = unit->win_dim.x * unit->win_dim.y;

	ft_memset(unit->depth, 0, s * sizeof(*unit->depth));
}

void	put_pixel_depth(t_fdf *unit, t_point3 pos, int color)
{
	if (-pos.z < unit->depth[pos.x * pos.y * unit->win_dim.x])
	{
		put_pixel(unit, pos.x, pos.y, color);
		unit->depth[pos.x * pos.y * unit->win_dim.x] = -pos.z;
	}
}

void	draw_line_depth(t_fdf *unit, t_point3 a, t_point3 b, t_color color)
{
	if (-a.z < unit->depth[a.x * a.y * unit->win_dim.x])
	{
		draw_line(unit, drop_z_3(a), drop_z_3(b), color);
		unit->depth[a.x * a.y * unit->win_dim.x] = -a.z;
	}
}
