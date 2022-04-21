/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 13:35:26 by jkong             #+#    #+#             */
/*   Updated: 2022/04/21 22:22:11 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdlib.h>

typedef struct s_str_list
{
	char				*str;
	struct s_str_list	*next;
}	t_str_list;

typedef struct s_map_loader
{
	t_str_list	*head;
	size_t		count;
}	t_map_loader;

typedef struct s_point2
{
	int	x;
	int	y;
}	t_point2;

typedef struct s_point2z
{
	size_t	x;
	size_t	y;
}	t_point2z;

typedef struct s_fdf_point
{
	int	value;
	int	color;
}	t_fdf_point;

typedef struct s_fdf_map
{
	size_t		*ref_count;
	const char	*path;
	t_fdf_point	*arr;
	t_point2z	dim;
}	t_fdf_map;

typedef struct s_input_sys
{
	int			pressed;
	t_point2	latest;
	t_point2	pointed;
}	t_input_sys;

typedef struct s_fdf
{
	void		*mlx_ptr;
	t_fdf_map	map;
	t_point2	win_dim;
	void		*win_ptr;
	t_input_sys	input;
}	t_fdf;

/*
 * Reference: 
 * /
 * Library/
 * Developer/
 * CommandLineTools/
 * SDKs/MacOSX.sdk/
 * System/Library/
 * Frameworks/
 * Carbon.framework/
 * Versions/
 * A/
 * Frameworks/
 * HIToolbox.framework/
 * Versions/
 * A/
 * Headers/
 * Events.h
 */

/*
 *  Summary:
 *    Virtual keycodes
 *  
 *  Discussion:
 *    These constants are the virtual keycodes defined originally in
 *    Inside Mac Volume V, pg. V-191. They identify physical keys on a
 *    keyboard. Those constants with "ANSI" in the name are labeled
 *    according to the key position on an ANSI-standard US keyboard.
 *    For example, kVK_ANSI_A indicates the virtual keycode for the key
 *    with the letter 'A' in the US keyboard layout. Other keyboard
 *    layouts may have the 'A' key label on a different physical key;
 *    in this case, pressing 'A' will generate a different virtual
 *    keycode.
 */
enum e_vk
{
	kVK_ANSI_A = 0x00,
	kVK_ANSI_S = 0x01,
	kVK_ANSI_D = 0x02,
	kVK_ANSI_F = 0x03,
	kVK_ANSI_H = 0x04,
	kVK_ANSI_G = 0x05,
	kVK_ANSI_Z = 0x06,
	kVK_ANSI_X = 0x07,
	kVK_ANSI_C = 0x08,
	kVK_ANSI_V = 0x09,
	kVK_ANSI_B = 0x0B,
	kVK_ANSI_Q = 0x0C,
	kVK_ANSI_W = 0x0D,
	kVK_ANSI_E = 0x0E,
	kVK_ANSI_R = 0x0F,
	kVK_ANSI_Y = 0x10,
	kVK_ANSI_T = 0x11,
	kVK_ANSI_1 = 0x12,
	kVK_ANSI_2 = 0x13,
	kVK_ANSI_3 = 0x14,
	kVK_ANSI_4 = 0x15,
	kVK_ANSI_6 = 0x16,
	kVK_ANSI_5 = 0x17,
	kVK_ANSI_Equal = 0x18,
	kVK_ANSI_9 = 0x19,
	kVK_ANSI_7 = 0x1A,
	kVK_ANSI_Minus = 0x1B,
	kVK_ANSI_8 = 0x1C,
	kVK_ANSI_0 = 0x1D,
	kVK_ANSI_RightBracket = 0x1E,
	kVK_ANSI_O = 0x1F,
	kVK_ANSI_U = 0x20,
	kVK_ANSI_LeftBracket = 0x21,
	kVK_ANSI_I = 0x22,
	kVK_ANSI_P = 0x23,
	kVK_ANSI_L = 0x25,
	kVK_ANSI_J = 0x26,
	kVK_ANSI_Quote = 0x27,
	kVK_ANSI_K = 0x28,
	kVK_ANSI_Semicolon = 0x29,
	kVK_ANSI_Backslash = 0x2A,
	kVK_ANSI_Comma = 0x2B,
	kVK_ANSI_Slash = 0x2C,
	kVK_ANSI_N = 0x2D,
	kVK_ANSI_M = 0x2E,
	kVK_ANSI_Period = 0x2F,
	kVK_ANSI_Grave = 0x32,
	kVK_ANSI_KeypadDecimal = 0x41,
	kVK_ANSI_KeypadMultiply = 0x43,
	kVK_ANSI_KeypadPlus = 0x45,
	kVK_ANSI_KeypadClear = 0x47,
	kVK_ANSI_KeypadDivide = 0x4B,
	kVK_ANSI_KeypadEnter = 0x4C,
	kVK_ANSI_KeypadMinus = 0x4E,
	kVK_ANSI_KeypadEquals = 0x51,
	kVK_ANSI_Keypad0 = 0x52,
	kVK_ANSI_Keypad1 = 0x53,
	kVK_ANSI_Keypad2 = 0x54,
	kVK_ANSI_Keypad3 = 0x55,
	kVK_ANSI_Keypad4 = 0x56,
	kVK_ANSI_Keypad5 = 0x57,
	kVK_ANSI_Keypad6 = 0x58,
	kVK_ANSI_Keypad7 = 0x59,
	kVK_ANSI_Keypad8 = 0x5B,
	kVK_ANSI_Keypad9 = 0x5C
};

/*
 * keycodes for keys that are independent of keyboard layout
 */
enum e_vk_i
{
	kVK_Return = 0x24,
	kVK_Tab = 0x30,
	kVK_Space = 0x31,
	kVK_Delete = 0x33,
	kVK_Escape = 0x35,
	kVK_Command = 0x37,
	kVK_Shift = 0x38,
	kVK_CapsLock = 0x39,
	kVK_Option = 0x3A,
	kVK_Control = 0x3B,
	kVK_RightShift = 0x3C,
	kVK_RightOption = 0x3D,
	kVK_RightControl = 0x3E,
	kVK_Function = 0x3F,
	kVK_F17 = 0x40,
	kVK_VolumeUp = 0x48,
	kVK_VolumeDown = 0x49,
	kVK_Mute = 0x4A,
	kVK_F18 = 0x4F,
	kVK_F19 = 0x50,
	kVK_F20 = 0x5A,
	kVK_F5 = 0x60,
	kVK_F6 = 0x61,
	kVK_F7 = 0x62,
	kVK_F3 = 0x63,
	kVK_F8 = 0x64,
	kVK_F9 = 0x65,
	kVK_F11 = 0x67,
	kVK_F13 = 0x69,
	kVK_F16 = 0x6A,
	kVK_F14 = 0x6B,
	kVK_F10 = 0x6D,
	kVK_F12 = 0x6F,
	kVK_F15 = 0x71,
	kVK_Help = 0x72,
	kVK_Home = 0x73,
	kVK_PageUp = 0x74,
	kVK_ForwardDelete = 0x75,
	kVK_F4 = 0x76,
	kVK_End = 0x77,
	kVK_F2 = 0x78,
	kVK_PageDown = 0x79,
	kVK_F1 = 0x7A,
	kVK_LeftArrow = 0x7B,
	kVK_RightArrow = 0x7C,
	kVK_DownArrow = 0x7D,
	kVK_UpArrow = 0x7E
};

/*
 * Reference: mlx_window.swift#eventFuncts
 */
enum e_mlx_event_index
{
	MLX_EVENT_KEY_DOWN = 2,
	MLX_EVENT_KEY_UP = 3,
	MLX_EVENT_MOUSE_DOWN = 4,
	MLX_EVENT_MOUSE_UP = 5,
	MLX_EVENT_MOUSE_MOVE = 6,
	MLX_EVENT_EXPOSURE = 12,
	MLX_EVENT_CLOSE = 17,
	MLX_EVENT_ACCEPT_MOUSE_MOVE = 32
};

/*
 * Reference: mlx_window.swift#get_mouse_button
 */
enum e_mlx_mouse_button
{
	MLX_MB_UNKNOWN,
	MLX_MB_LEFT,
	MLX_MB_RIGHT,
	MLX_MB_OTHER,
	MLX_MB_WHEEL_DOWN,
	MLX_MB_WHEEL_UP,
	MLX_MB_WHEEL_RIGHT,
	MLX_MB_WHEEL_LEFT
};

/*
 * Reference: mlx_window.swift#flagsChanged
 * 
 * DO NOT USE VALUES FOLLOWING BELOW
 *   MLX_MOD_UNKNOWN = 8,
 *   MLX_MOD_RCONTROL = 13,
 *   MLX_MOD_CAPSLOCK = 16,
 *   MLX_MOD_FUNCTION = 23
 * 
 * Initially (MLX_MOD_UNKNOWN) is returned unconditionally.
 * So after (NO_MLX_MOD_KEY), using as different meaning.
 */
enum e_modifiers
{
	MLX_MOD_LCONTROL,
	MLX_MOD_LSHIFT,
	MLX_MOD_RSHIFT,
	MLX_MOD_LCMD,
	MLX_MOD_RCMD,
	MLX_MOD_LOPTION,
	MLX_MOD_ROPTION,
	NO_MLX_MOD_KEY,
	MLX_MOD_MOUSE_LEFT,
	MLX_MOD_MOUSE_RIGHT,
	MLX_MOD_MOUSE_OTHER,
	MLX_NO_MOD
};

int		fdf_read_map(t_fdf_map *map, const char *path);
int		fdf_load_map(t_fdf_map *map, t_map_loader *loader);

size_t	ft_strlen(const char *s);
void	*ft_memset(void *b, int c, size_t len);
void	*ft_memcpy(void *dst, const void *src, size_t n);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);

size_t	ft_split_count(const char *s, const char *set);
char	**ft_split_free(char **ptr);
char	**ft_split(const char *s, const char *set);

int		ft_strtoi(const char *str);

void	set_flag(int *ptr, int index);
void	reset_flag(int *ptr, int index);
int		has_flag(int flags, int index);

void	*malloc_safe(size_t size);
void	*calloc_safe(size_t count, size_t size);

#endif
