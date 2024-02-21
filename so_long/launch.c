/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:42:13 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 11:39:38 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	set_var_to_zero(t_game *ptr_t_game)
{
	ptr_t_game -> mlx = NULL;
	ptr_t_game -> win = NULL;
	ptr_t_game -> map.map_path = NULL;
	ptr_t_game -> map.heigth = 0;
	ptr_t_game -> map.width = 0;
	ptr_t_game -> matrix = NULL;
	ptr_t_game -> map.n_coin = 0;
	ptr_t_game -> map.c_take = 0;
	ptr_t_game -> n_move = 0;
	ptr_t_game -> map.count.count_c = 0;
	ptr_t_game -> map.count.count_e = 0;
	ptr_t_game -> map.count.count_n = 0;
	ptr_t_game -> map.count.count_p = 0;
	ptr_t_game -> map.img_height = 64;
	ptr_t_game -> map.img_width = 64;
	ptr_t_game ->coin_mov = 0;
	gettimeofday(&(ptr_t_game->time_coin), NULL);
	gettimeofday(&(ptr_t_game->time_enemy), NULL);
	return (1);
}

int	launch_game(t_game *ptr_t_game)
{
	ptr_t_game -> mlx = mlx_init();
	if (!ptr_t_game -> mlx)
		quit_and_free("MLX initialization failed", 1, ptr_t_game);
	ptr_t_game -> win = mlx_new_window(ptr_t_game -> mlx,
			(ptr_t_game->map.width) * 64,
			(ptr_t_game->map.heigth) * 64, "So Long");
	if (!ptr_t_game->win)
		quit_and_free("Windows initialization failed", 1, ptr_t_game);
	init_images(ptr_t_game);
	on_screen(ptr_t_game);
	if (ft_strncmp(ptr_t_game->map.map_path, "maps/bonusmap.ber") == 0
		|| ft_strncmp(ptr_t_game->map.map_path, "maps/bonusmap2.ber") == 0)
		mlx_loop_hook(ptr_t_game -> mlx, *loop_enemy, ptr_t_game);
	else
		mlx_loop_hook(ptr_t_game -> mlx, *loop_coin, ptr_t_game);
	mlx_key_hook(ptr_t_game->win, *inputs, ptr_t_game);
	mlx_hook(ptr_t_game->win, 17, 0, *ft_close_x, ptr_t_game);
	mlx_loop(ptr_t_game -> mlx);
	return (1);
}
