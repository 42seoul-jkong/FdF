/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:22:15 by jkong             #+#    #+#             */
/*   Updated: 2022/04/26 22:30:06 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_point2	center_2(t_point2 pt)
{
	return ((t_point2){pt.x / 2, pt.y / 2});
}

t_point3f	zero_z_3(t_point2 pt)
{
	return ((t_point3f){pt.x, pt.y, 0});
}

t_point2	drop_z_3(t_point3 pt)
{
	return ((t_point2){pt.x, pt.y});
}

t_point3	integer_3f(t_point3f pt)
{
	return ((t_point3){pt.x, pt.y, pt.z});
}

t_point3f	negative_3f(t_point3f pt)
{
	return ((t_point3f){-pt.x, -pt.y, -pt.z});
}
