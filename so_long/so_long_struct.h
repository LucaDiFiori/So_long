/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_struct.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:34:01 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 13:02:13 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_STRUCT_H
# define SO_LONG_STRUCT_H

# define NUM_COLLECTABLE 5
# define MAX_XPM 5

typedef struct s_tile
{
	char	tile_type;
	int		x_axis;
	int		y_axis;
	void	*img[MAX_XPM];	
}			t_tile;

typedef struct s_count
{
	int	count_p;
	int	count_e;
	int	count_c;
	int	count_n;
}	t_count;

typedef struct s_map
{
	char	*map_path;
	int		heigth;
	int		width;
	t_count	count;
	t_tile	player;
	t_tile	enemy;
	t_tile	exit;
	t_tile	wall;
	t_tile	ground;
	t_tile	score;
	t_tile	collect[NUM_COLLECTABLE];
	int		n_coin;
	int		c_take;
	int		img_width;
	int		img_height;
}		t_map;

typedef struct s_game
{
	void			*mlx;
	void			*win;
	t_map			map;
	char			**matrix;
	int				n_move;
	struct timeval	time_coin;
	struct timeval	time_enemy;
	int				coin_mov;
}				t_game;

#endif