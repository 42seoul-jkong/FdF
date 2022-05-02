/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   depth.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 21:55:55 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 19:56:57 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	clear_depth(t_fdf *unit)
{
	const size_t	s = unit->win_dim.x * unit->win_dim.y;

	ft_memset(unit->depth, 0x88, s * sizeof(*unit->depth));
}

void	put_pixel_depth(t_fdf *unit, t_point3 pos, int color)
{
	if (pos.x < 0 || pos.x >= unit->win_dim.x)
		return ;
	if (pos.y < 0 || pos.y >= unit->win_dim.y)
		return ;
	if (pos.z > unit->depth[pos.x + pos.y * unit->win_dim.x])
	{
		put_pixel(unit, pos.x, pos.y, color);
		unit->depth[pos.x + pos.y * unit->win_dim.x] = pos.z;
	}
}
