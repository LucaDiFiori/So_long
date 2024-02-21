/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 16:19:03 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 17:12:56 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ch(t_game *p_g, int x, int y)
{
	if (p_g->matrix[x][y] == 'E')
		return (0);
	if (p_g->matrix[x][y] == 'C')
		return (0);
	else if (p_g->matrix[x][y] == 'P')
	{
		printf(" *******\n*********\n* o * o *\n****A****\n  |!!!| \n");
		quit_and_free("YOU DIED", 3, p_g);
		return (0);
	}
	if (p_g->matrix[x][y] == '0')
		return (1);
	return (0);
}

static void	mv(t_game *p_g, int n_x, int n_y, int fr_bk)
{
	p_g->matrix[p_g->map.enemy.x_axis][p_g->map.enemy.y_axis] = '0';
	p_g->matrix[n_x][n_y] = 'N';
	mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.ground.img[0],
		(p_g->map.enemy.y_axis) * 64, (p_g->map.enemy.x_axis) * 64);
	if (fr_bk == 1)
		mlx_put_image_to_window(p_g->mlx, p_g->win,
			p_g->map.enemy.img[1], n_y * 64, n_x * 64);
	else if (fr_bk == 0)
		mlx_put_image_to_window(p_g->mlx, p_g->win,
			p_g->map.enemy.img[0], n_y * 64, n_x * 64);
	else if (fr_bk == -1)
		mlx_put_image_to_window(p_g->mlx, p_g->win,
			p_g->map.enemy.img[0], n_y * 64, n_x * 64);
}

static int	ch_if_alv(t_game *p_g, int rand_n, int x, int y)
{
	if (rand_n == 0 && ch(p_g, x - 1, y))
	{
		mv(p_g, x - 1, y, -1);
		return (1);
	}
	else if (rand_n == 1 && ch(p_g, x + 1, y))
	{
		mv(p_g, x + 1, y, -1);
		return (1);
	}
	else if (rand_n == 2 && ch(p_g, x, y + 1))
	{
		mv(p_g, x, y + 1, 0);
		return (1);
	}
	else if (rand_n && ch(p_g, x, y - 1))
	{
		mv(p_g, x, y - 1, 1);
		return (1);
	}
	return (0);
}

int	is_alive(t_game *p_g)
{
	int	rand_n;
	int	x;
	int	y;

	rand_n = random_n(0, 3);
	x = p_g->map.enemy.x_axis;
	y = p_g->map.enemy.y_axis;
	if (rand_n == 0 && p_g->matrix[x - 1][y] != '1'
			&& p_g->matrix[x - 1][y] != 'C' && ch_if_alv(p_g, rand_n, x, y))
		p_g->map.enemy.x_axis--;
	else if (rand_n == 1 && p_g->matrix[x + 1][y] != '1'
			&& p_g->matrix[x + 1][y] != 'C' && ch_if_alv(p_g, rand_n, x, y))
		p_g->map.enemy.x_axis++;
	else if (rand_n == 2 && p_g->matrix[x][y + 1] != '1'
			&& p_g->matrix[x][y + 1] != 'C' && ch_if_alv(p_g, rand_n, x, y))
		p_g->map.enemy.y_axis++;
	else if (rand_n == 3 && p_g->matrix[x][y - 1] != '1'
			&& p_g->matrix[x][y - 1] != 'C' && ch_if_alv(p_g, rand_n, x, y))
		p_g->map.enemy.y_axis--;
	return (0);
}
