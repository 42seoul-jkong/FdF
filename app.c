/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:28:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/27 21:43:33 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include "mlx.h"

//Test
#include <math.h>
#include <stdio.h>

static void	_draw_fdf(t_fdf *unit)
{
	fill_image(unit, 0xAA);
	for (long i = 0; i < unit->map.dim.x; i++)
	{
		for (long j = 0; j < unit->map.dim.y; j++)
		{
			t_fdf_point *const	pos = get_pos(&unit->map, i, j);
			t_point3f			pt;
			t_point3f			center;

			pt = (t_point3f){i, j, pos->value};
			//center = zero_z_2(center_2(unit->map.dim));
			center = (t_point3f){unit->map.dim.x / 2, unit->map.dim.y / 2, 0};
			scale(&pt, unit->scale);
			scale(&center, unit->scale);
			translate(&pt, negative_3f(center));
			rotate_pitch(&pt, unit->rotate.x);
			rotate_roll(&pt, unit->rotate.y);
			rotate_yaw(&pt, unit->rotate.z);
			translate(&pt, center);
			translate(&pt, unit->translate);
			pos->coord = integer_3f(pt);
		}
	}
	clear_depth(unit);
	for (long i = 0; i < unit->map.dim.x; i++)
	{
		for (long j = 0; j < unit->map.dim.y; j++)
		{
			t_fdf_point *const	pos = get_pos(&unit->map, i, j);
			t_fdf_point			*pos_px;
			t_fdf_point			*pos_py;

			if (i > 0)
				pos_px = get_pos(&unit->map, i - 1, j);
			else
				pos_px = NULL;
			if (j > 0)
				pos_py = get_pos(&unit->map, i, j - 1);
			else
				pos_py = NULL;
			if (pos_px)
				draw_line(unit, pos_px->coord, pos->coord, (t_color){pos_px->color, pos->color});
			if (pos_py)
				draw_line(unit, pos_py->coord, pos->coord, (t_color){pos_py->color, pos->color});
			put_pixel(unit, pos->coord.x, pos->coord.y, pos->color);
		}
	}
	refresh_window(unit);
}

static void	_on_key(t_fdf *unit, int flag, int keycode)
{
	//Test:
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_X)
	{
		printf("Window Cleared\n");
		fill_image(unit, 0xCC);
		unit->input.pointed.x = 0;
		unit->input.pointed.y = 0;
		refresh_window(unit);
	}
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_C)
	{
		printf("Pos Setted\n");
		unit->input.pointed.x = unit->input.latest.x;
		unit->input.pointed.y = unit->input.latest.y;
	}
	if (has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_V)
	{
		int	color;

		color = 0;
		if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_LEFT))
			color |= 0x990000;
		if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_OTHER))
			color |= 0x009900;
		if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_RIGHT))
			color |= 0x000099;
		//old: draw_line(unit, unit->input.pointed, unit->input.latest, (t_color){color, color / 3});
		refresh_window(unit);
	}
	if (keycode == kVK_ANSI_Q)
		unit->rotate.x += M_PI / 90;
	else if (keycode == kVK_ANSI_A)
		unit->rotate.x -= M_PI / 90;
	else if (keycode == kVK_ANSI_E)
		unit->rotate.y += M_PI / 90;
	else if (keycode == kVK_ANSI_D)
		unit->rotate.y -= M_PI / 90;
	else if (keycode == kVK_ANSI_W)
		unit->rotate.z += M_PI / 90;
	else if (keycode == kVK_ANSI_S)
		unit->rotate.z -= M_PI / 90;
	else if (keycode == kVK_UpArrow)
		unit->translate.x += 30;
	else if (keycode == kVK_DownArrow)
		unit->translate.x -= 30;
	else if (keycode == kVK_LeftArrow)
		unit->translate.y += 30;
	else if (keycode == kVK_RightArrow)
		unit->translate.y -= 30;
	else if (keycode == kVK_ANSI_Z)
		unit->translate.z += 30;
	else if (keycode == kVK_ANSI_X)
		unit->translate.z -= 30;
	else if (keycode == kVK_ANSI_Equal)
		unit->scale *= 2;
	else if (keycode == kVK_ANSI_Minus)
		unit->scale *= 0.5;
	else if (!(has_flag(flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_Z))
		return ;
	_draw_fdf(unit);
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
	unit->input.latest.x = x;
	unit->input.latest.y = y;
	color = 0;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_LEFT))
		color |= 0xFF0000;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_OTHER))
		color |= 0x00FF00;
	if (has_flag(unit->input.pressed, MLX_MOD_MOUSE_RIGHT))
		color |= 0x0000FF;
	put_pixel(unit, x, y, color);
	refresh_window(unit);
	return (0);
}

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

static int	_create_window(void *mlx_ptr, t_fdf *unit)
{
	int		width;
	int		height;
	char	*title;

	width = 800;
	height = 600;
	unit->scale = 1.0;
	title = unit->map.path;
	unit->mlx_ptr = mlx_ptr;
	unit->win_dim.x = width;
	unit->win_dim.y = height;
	unit->win_ptr = mlx_new_window(unit->mlx_ptr, width, height, title);
	if (!unit->win_ptr)
		return (0);
	unit->img_ptr = mlx_new_image(unit->mlx_ptr, width, height);
	if (!unit->img_ptr)
		return (0);
	unit->depth = calloc_safe(width * height, sizeof(*unit->depth));
	clear_depth(unit);
	fill_image(unit, 0xCC);
	refresh_window(unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_KEY_DOWN, 0, &_key_down_hook, unit);
	mlx_key_hook(unit->win_ptr, &_key_up_hook, unit);
	mlx_mouse_hook(unit->win_ptr, &_mouse_down_hook, unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_MOUSE_UP, 0, &_mouse_up_hook, unit);
	mlx_hook(unit->win_ptr, MLX_EVENT_MOUSE_MOVE, 0, &_mouse_move_hook, unit);
	mlx_expose_hook(unit->win_ptr, &_expose_hook, unit);
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
		return (EXIT_FAILURE);
	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		return (EXIT_FAILURE);
	begin = 1;
	fdf_arr = ft_calloc(argc - begin, sizeof(*fdf_arr));
	i = 0;
	while (i < argc - begin)
	{
		if (fdf_read_map(&fdf_arr[i].map, argv[begin + i]))
			_create_window(mlx_ptr, &fdf_arr[i]);
		else
			printf("Map Error %d\n", i);
		i++;
	}
	mlx_loop(mlx_ptr);
	free(fdf_arr);
	return (EXIT_SUCCESS);
}
