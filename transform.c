/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:20:43 by jkong             #+#    #+#             */
/*   Updated: 2022/04/26 18:54:06 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <math.h>

void	translate(t_point3f *pt, t_point3f delta)
{
	pt->x += delta.x;
	pt->y += delta.y;
	pt->z += delta.z;
}

void	scale(t_point3f *pt, double k)
{
	pt->x *= k;
	pt->y *= k;
	pt->z *= k;
}

void	rotate_yaw(t_point3f *pt, double yaw)
{
	const double	x = pt->x;
	const double	y = pt->y;

	pt->x = x * cos(yaw) - y * sin(yaw);
	pt->y = x * sin(yaw) + y * cos(yaw);
}

void	rotate_pitch(t_point3f *pt, double pitch)
{
	const double	y = pt->y;
	const double	z = pt->z;

	pt->y = y * cos(pitch) - z * sin(pitch);
	pt->z = y * sin(pitch) + z * cos(pitch);
}

void	rotate_roll(t_point3f *pt, double roll)
{
	const double	z = pt->z;
	const double	x = pt->x;

	pt->z = z * cos(roll) - x * sin(roll);
	pt->x = z * sin(roll) + x * cos(roll);
}
