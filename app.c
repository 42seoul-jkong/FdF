/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:28:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/21 22:35:56 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "fdf.h"
#include "get_next_line.h"

#include <math.h>

#include <stdio.h>

/*
static void	_draw_line(t_fdf *unit, int x1, int y1, int x2, int y2, int color)
{
	//TODO: ...
	(void)x2, (void)y2;
	mlx_pixel_put(unit->mlx_ptr, unit->win_ptr, x1, y1, color);
}
*/

static void	_on_key(t_fdf *unit, int flag, int keycode)
{
	//Test:
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_C)
	{
		printf("Window Cleared\n");
		mlx_clear_window(unit->mlx_ptr, unit->win_ptr);
		unit->input.pointed.x = 0;
		unit->input.pointed.y = 0;
	}
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_V)
	{
		printf("Pos Setted\n");
		unit->input.pointed.x = unit->input.latest.x;
		unit->input.pointed.y = unit->input.latest.y;
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
	{
		printf("Key Down %d With %04X\n", keycode, unit->input.pressed);
		_on_key(unit, unit->input.pressed, keycode);
	}
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
	else
	{
		printf("Key Up %d With %04X\n", keycode, unit->input.pressed);
	}
	return (0);
}

static int	_get_mouse_flag(int button)
{
	if (button == MLX_MB_LEFT)
		return (MLX_MOD_MOUSE_LEFT);
	else if (button == MLX_MB_RIGHT)
		return (MLX_MOD_MOUSE_RIGHT);
	else if (button == MLX_MB_OTHER)
		return (MLX_MOD_MOUSE_OTHER);
	return (MLX_NO_MOD);
}

static int	_mouse_down_hook(int button, int x, int y, void *param)
{
	t_fdf *const	unit = param;
	const int		flag = _get_mouse_flag(button);

	if (x < 0 || x >= unit->win_dim.x || y < 0 || y >= unit->win_dim.y)
		return (0);
	printf("Mouse Down %d, %d, %d\n", button, x, y);
	if (flag != MLX_NO_MOD)
		set_flag(&unit->input.pressed, flag);
	return (0);
}

static int	_mouse_up_hook(int button, int x, int y, void *param)
{
	t_fdf *const	unit = param;
	const int		flag = _get_mouse_flag(button);

	printf("Mouse Up %d, %d, %d\n", button, x, y);
	if (flag != MLX_NO_MOD)
		reset_flag(&unit->input.pressed, flag);
	return (0);
}

static int	_mouse_move_hook(int x, int y, void *param)
{
	t_fdf *const	unit = param;
	int				color;

	//printf("Mouse Move Hook %d, %d\n", x, y);
	if (x < 0 || x >= unit->win_dim.x || y < 0 || y >= unit->win_dim.y)
		return (0);
	unit->input.latest.x = x;
	unit->input.latest.y = y;
	color = 0;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_LEFT))
		color |= 0xFF0000;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_OTHER))
		color |= 0x00FF00;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_RIGHT))
		color |= 0x0000FF;
	mlx_pixel_put(unit->mlx_ptr, unit->win_ptr, x, y, color);
	return (0);
}

static int	_close_hook(void *param)
{
	(void)param;
	exit(EXIT_SUCCESS);
	return (0);
}

static int	_create_window(void *mlx_ptr, t_fdf *unit)
{
	int		width;
	int		height;
	char	*title;

	width = 800;
	height = 600;
	title = unit->map.path;
	unit->mlx_ptr = mlx_ptr;
	unit->win_dim.x = width;
	unit->win_dim.y = height;
	unit->win_ptr = mlx_new_window(unit->mlx_ptr, width, height, title);
	if (unit->win_ptr == NULL)
		return (0);
	mlx_clear_window(unit->mlx_ptr, unit->win_ptr);
	mlx_hook(unit->win_ptr, MLX_EVENT_KEY_DOWN, 0, &_key_down_hook, unit);
	mlx_key_hook(unit->win_ptr, &_key_up_hook, unit);
	mlx_mouse_hook(unit->win_ptr, &_mouse_down_hook, unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_MOUSE_UP, 0, &_mouse_up_hook, unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_MOUSE_MOVE, 0, &_mouse_move_hook, unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_CLOSE, 0, &_close_hook, unit);
	return (1);
}

int	main(int argc, char *argv[])
{
	void		*mlx_ptr;
	t_fdf		*fdf_arr;
	int			begin;
	int			i;

	if (argc < 2)
	{
		return (EXIT_FAILURE);
	}
	mlx_ptr = mlx_init();
	if (mlx_ptr == NULL)
		return (EXIT_FAILURE);
	begin = 1;
	fdf_arr = ft_calloc(argc - begin, sizeof(*fdf_arr));
	i = 0;
	while (i < argc - begin)
	{
		fdf_read_map(&fdf_arr[i].map, argv[begin + i]);
		_create_window(mlx_ptr, &fdf_arr[i]);
		i++;
	}
	printf("%lf ; %lf\n", sin(M_PI / 2), cos(M_PI / 2));
	mlx_loop(mlx_ptr);
	free(fdf_arr);
	return (EXIT_SUCCESS);
}
