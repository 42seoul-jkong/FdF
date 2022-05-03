/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_input_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 18:32:52 by jkong             #+#    #+#             */
/*   Updated: 2022/05/03 20:28:58 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"

static void	_on_key(t_fdf *unit, int flag, int keycode)
{
	if (keycode == kVK_Escape)
	{
		exit(EXIT_SUCCESS);
		return ;
	}
	if (has_flag(flag, MLX_MOD_LCONTROL) && keycode == kVK_ANSI_C)
	{
		exit(EXIT_FAILURE);
		return ;
	}
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_C)
	{
		unit->scale = unit->default_scale;
		unit->z_size = unit->default_z_size;
		unit->translate = unit->default_translate;
		unit->rotate = unit->default_rotate;
		draw_fdf(unit);
	}
}

static int	_key_down_hook(int keycode, void *param)
{
	t_fdf *const	unit = param;

	if (keycode > 0xFF)
	{
		keycode -= 0x100;
		if (keycode < NO_MLX_MOD_KEY)
			set_flag(&unit->input.pressed, keycode);
	}
	else
		_on_key(unit, unit->input.pressed, keycode);
	return (0);
}

static int	_key_up_hook(int keycode, void *param)
{
	t_fdf *const	unit = param;

	if (keycode > 0xFF)
	{
		keycode -= 0x100;
		if (keycode < NO_MLX_MOD_KEY)
			reset_flag(&unit->input.pressed, keycode);
	}
	return (0);
}

void	enable_key_hook(t_fdf *unit)
{
	mlx_hook(unit->win_ptr, MLX_EVENT_KEY_DOWN, 0, &_key_down_hook, unit);
	mlx_key_hook(unit->win_ptr, &_key_up_hook, unit);
}
