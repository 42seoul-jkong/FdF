/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_move.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:42:40 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 20:19:40 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"
#include <math.h>

static int	_on_mouse_left(t_fdf *unit, int delta_x, int delta_y)
{
	unit->translate.x += delta_x;
	unit->translate.y += delta_y;
	return (1);
}

static int	_on_mouse_other(t_fdf *unit, int delta_x, int delta_y)
{
	unit->z_size *= pow(1.01, delta_x);
	unit->rotate.z += delta_y / 180.0 * M_PI;
	return (1);
}

static int	_on_mouse_right(t_fdf *unit, int delta_x, int delta_y)
{
	unit->rotate.y += delta_x / 180.0 * M_PI;
	unit->rotate.x += delta_y / 180.0 * M_PI;
	return (1);
}

static int	_mouse_move_hook(int x, int y, void *param)
{
	t_fdf *const	unit = param;
	const t_point2	latest = unit->input.latest;
	int				re;

	re = 0;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_LEFT))
		re |= _on_mouse_left(unit, x - latest.x, y - latest.y);
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_OTHER))
		re |= _on_mouse_other(unit, x - latest.x, y - latest.y);
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_RIGHT))
		re |= _on_mouse_right(unit, x - latest.x, y - latest.y);
	if (re)
		draw_fdf(unit);
	unit->input.latest = (t_point2){x, y};
	return (0);
}

void	enable_mouse_move_hook(t_fdf *unit)
{
	mlx_hook(unit->win_ptr, MLX_EVENT_MOUSE_MOVE, 0, &_mouse_move_hook, unit);
}
