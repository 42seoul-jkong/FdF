/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:43:15 by jkong             #+#    #+#             */
/*   Updated: 2022/05/02 19:02:32 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"

void	enable_key_hook(t_fdf *unit);
void	enable_mouse_hook(t_fdf *unit);
void	enable_mouse_move_hook(t_fdf *unit);

static int	_expose_hook(void *param)
{
	t_fdf *const	unit = param;

	refresh_window(unit);
	return (0);
}

static int	_close_hook(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
	return (0);
}

void	set_hook(t_fdf *unit)
{
	enable_key_hook(unit);
	enable_mouse_hook(unit);
	enable_mouse_move_hook(unit);
	mlx_expose_hook(unit->win_ptr, &_expose_hook, unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_CLOSE, 0, &_close_hook, unit);
}
