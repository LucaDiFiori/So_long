/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 18:04:22 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 11:45:46 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_time_coin(t_game *p_g)
{
	struct timeval	current_e;
	int				ret;

	gettimeofday(&current_e, NULL);
	ret = (((current_e.tv_sec * 1000) + (current_e.tv_usec / 1000))
			- (((p_g->time_coin.tv_sec * 1000))
				+ (p_g->time_coin.tv_usec / 1000)));
	if (ret >= 200)
		p_g->time_coin = current_e;
	return (ret);
}

static int	ft_time_enemy(t_game *p_g)
{
	struct timeval	current_n;
	int				ret;

	gettimeofday(&current_n, NULL);
	ret = (((current_n.tv_sec * 1000) + (current_n.tv_usec / 1000))
			- (((p_g->time_enemy.tv_sec * 1000))
				+ (p_g->time_enemy.tv_usec / 1000)));
	if (ret >= 1000)
		p_g->time_enemy = current_n;
	return (ret);
}

static void	coin_update(t_game *g, int i)
{
	mlx_put_image_to_window(g->mlx,
		g->win, g->map.ground.img[0],
		(g->map.collect[i].y_axis) * 64,
		(g->map.collect[i].x_axis) * 64);
	mlx_put_image_to_window(g->mlx,
		g->win, g->map.collect[0].img[g->coin_mov],
		(g->map.collect[i].y_axis) * 64,
		(g->map.collect[i].x_axis) * 64);
}

int	loop_coin(t_game *g)
{
	int	i;

	i = -1;
	if (ft_time_coin(g) >= 200)
	{
		if (g->map.c_take != g->map.n_coin)
		{
			if (g->coin_mov == 4)
				g->coin_mov = 0;
			if (g->coin_mov != 4)
				g->coin_mov++;
			while (++i <= g->map.n_coin)
			{
				if (g->matrix[g->map.collect[i].x_axis]
					[g->map.collect[i].y_axis] == 'C')
					coin_update(g, i);
			}
		}
		else
			mlx_put_image_to_window(g->mlx, g->win, g->map.exit.img[1],
				(g->map.exit.y_axis) * 64, (g->map.exit.x_axis) * 64);
	}
	return (1);
}

int	loop_enemy(t_game *p_g)
{
	loop_coin(p_g);
	if (ft_time_enemy(p_g) >= 1000)
		is_alive(p_g);
	return (0);
}
