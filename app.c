/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:28:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/20 22:43:08 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

#include "fdf.h"
#include "get_next_line.h"

#include <math.h>

#include <stdio.h>

static void	_draw_line(t_fdf *app, int x1, int y1, int x2, int y2, int color)
{
	//TODO: ...
	mlx_pixel_put(app->mlx_ptr, app->win_ptr, x1, y1, color);
}

static int	_key_down_hook(int keycode, void *param)
{
	t_fdf *const	app = param;
	int *const		flag = &app->input.pressed;

	if (keycode > 0xFF)
	{
		keycode -= 0x100;
		if (keycode < NO_MLX_MOD_KEY)
			set_flag(flag, keycode);
	}
	else
	{
		printf("Key Down %d With %04X\n", keycode, app->input.pressed);

		//Test:
		if (has_flag(*flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_C)
		{
			printf("Window Cleared\n");
			mlx_clear_window(app->mlx_ptr, app->win_ptr);
			app->input.pointed_x = 0;
			app->input.pointed_y = 0;
		}
		if (has_flag(*flag, MLX_MOD_LCMD) && keycode == kVK_ANSI_V)
		{
			printf("Pos Setted\n");
			app->input.pointed_x = app->input.latest_x;
			app->input.pointed_y = app->input.latest_y;
		}
	}
	return (0);
}

static int	_key_up_hook(int keycode, void *param)
{
	t_fdf *const	app = param;

	if (keycode > 0xFF)
	{
		keycode -= 0x100;
		if (keycode < NO_MLX_MOD_KEY)
			reset_flag(&app->input.pressed, keycode);
	}
	else
	{
		printf("Key Up %d With %04X\n", keycode, app->input.pressed);
	}
	return (0);
}

static int _get_mouse_flag(int button)
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
	t_fdf *const	app = param;
	const int		flag = _get_mouse_flag(button);

	if (x < 0 || x >= app->win_width || y < 0 || y >= app->win_height)
		return (0);
	printf("Mouse Down %d, %d, %d\n", button, x, y);
	if (flag != MLX_NO_MOD)
		set_flag(&app->input.pressed, flag);
	else
	{
		//Wheel position bug
		y = (app->win_height - 1) - y;
	}
	return (0);
}

static int	_mouse_up_hook(int button, int x, int y, void *param)
{
	t_fdf *const	app = param;
	const int		flag = _get_mouse_flag(button);

	printf("Mouse Up %d, %d, %d\n", button, x, y);
	if (flag != MLX_NO_MOD)
		reset_flag(&app->input.pressed, flag);
	return (0);
}

static int	_mouse_move_hook(int x, int y, void *param)
{
	t_fdf *const	app = param;
	int				color;

	//printf("Mouse Move Hook %d, %d\n", x, y);
	if (x < 0 || x >= app->win_width || y < 0 || y >= app->win_height)
		return (0);
	app->input.latest_x = x;
	app->input.latest_y = y;
	color = 0;
	if (has_flag(app->input.pressed, MLX_MOD_MOUSE_LEFT))
		color |= 0xFF0000;
	if (has_flag(app->input.pressed, MLX_MOD_MOUSE_OTHER))
		color |= 0x00FF00;
	if (has_flag(app->input.pressed, MLX_MOD_MOUSE_RIGHT))
		color |= 0x0000FF;
	mlx_pixel_put(app->mlx_ptr, app->win_ptr, x, y, color);
	return (0);
}

static int	_expose_hook(void *param)
{
	t_fdf *const	app = param;

	(void)app;
	printf("Expose\n");
	return (0);
}

static int	_close_hook(void *param)
{
	t_fdf *const	app = param;

	(void)app;
	printf("Close\n");
	//exit_hook();
	exit(EXIT_SUCCESS);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_fdf	app;

	if (argc != 2)
	{
		return (EXIT_FAILURE);
	}
	ft_memset(&app, 0, sizeof(app));
	app.map_path = argv[1];
	app.mlx_ptr = mlx_init();
	if (app.mlx_ptr == NULL)
		return (EXIT_FAILURE);
	app.win_width = 800;
	app.win_height = 600;
	app.win_ptr = mlx_new_window(app.mlx_ptr, app.win_width, app.win_height, "Test");
	if (app.win_ptr == NULL)
		return (EXIT_FAILURE);
	printf("%lf ; %lf\n", sin(M_PI / 2), cos(M_PI / 2));
	mlx_clear_window(app.mlx_ptr, app.win_ptr);
	mlx_pixel_put(app.mlx_ptr, app.win_ptr, 400, 300, 0x00FFFFFF);
	mlx_hook(app.win_ptr, MLX_EVENT_KEY_DOWN, 0, &_key_down_hook, &app);
	mlx_key_hook(app.win_ptr, &_key_up_hook, &app);
	mlx_mouse_hook(app.win_ptr, &_mouse_down_hook, &app);
	mlx_hook(app.win_ptr, MLX_EVENT_MOUSE_UP, 0, &_mouse_up_hook, &app);
	mlx_hook(app.win_ptr, MLX_EVENT_MOUSE_MOVE, 0, &_mouse_move_hook, &app);
	mlx_expose_hook(app.win_ptr, &_expose_hook, &app);
	mlx_hook(app.win_ptr, MLX_EVENT_CLOSE, 0, &_close_hook, &app);
	mlx_loop(app.mlx_ptr);
	return (EXIT_SUCCESS);
}
