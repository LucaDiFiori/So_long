/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 17:03:26 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/15 17:14:32 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	check(t_game *p_g, int x, int y)
{
	if (p_g->matrix[x][y] == '1')
		return (0);
	if (p_g->matrix[x][y] == 'N')
	{
		printf(" *******\n*********\n* o * o *\n****A****\n  |!!!| \n");
		quit_and_free("YOU DIED", 3, p_g);
		return (0);
	}
	if (p_g->matrix[x][y] == 'C')
	{
		ft_printf("It's free if nobody sees ;)\n");
		p_g->map.c_take++;
	}
	if (p_g->matrix[x][y] == 'E' && p_g->map.c_take != p_g->map.n_coin)
	{
		ft_printf("You've forgotten something\n");
		return (0);
	}
	else if (p_g->matrix[x][y] == 'E' && p_g->map.c_take == p_g->map.n_coin)
	{
		ft_printf("You complete the game in %d moves\n", ++p_g->n_move);
		quit_and_free("\n()()\n( ..)\n*(')(')\nBYE!\n", 3, p_g);
	}
	ft_printf("Moves: %d\n", ++p_g->n_move);
	return (1);
}

static void	move(t_game *p_g, int n_x, int n_y, int fr_bk)
{
	p_g->matrix[p_g->map.player.x_axis][p_g->map.player.y_axis] = '0';
	p_g->matrix[n_x][n_y] = 'P';
	mlx_put_image_to_window(p_g->mlx, p_g->win, p_g->map.ground.img[0],
		(p_g->map.player.y_axis) * 64, (p_g->map.player.x_axis) * 64);
	if (fr_bk == 1)
		mlx_put_image_to_window(p_g->mlx, p_g->win,
			p_g->map.player.img[1], n_y * 64, n_x * 64);
	else if (fr_bk == 0)
		mlx_put_image_to_window(p_g->mlx, p_g->win,
			p_g->map.player.img[0], n_y * 64, n_x * 64);
	else if (fr_bk == -1)
		mlx_put_image_to_window(p_g->mlx, p_g->win,
			p_g->map.player.img[0], n_y * 64, n_x * 64);
	d_score(p_g);
}

int	check_and_move(t_game *p_g, int key, int x, int y)
{
	if ((key == 13 || key == 126) && check(p_g, x - 1, y))
	{
		move(p_g, x - 1, y, -1);
		return (1);
	}
	else if ((key == 1 || key == 125) && check(p_g, x + 1, y))
	{
		move(p_g, x + 1, y, -1);
		return (1);
	}
	else if ((key == 2 || key == 124) && check(p_g, x, y + 1))
	{
		move(p_g, x, y + 1, 0);
		return (1);
	}
	else if ((key == 0 || key == 123) && check(p_g, x, y - 1))
	{
		move(p_g, x, y - 1, 1);
		return (1);
	}
	return (0);
}

int	inputs(int key, t_game *ptr_game)
{
	int	x;
	int	y;

	x = ptr_game->map.player.x_axis;
	y = ptr_game->map.player.y_axis;
	if (key == 53)
		ft_close_x(ptr_game);
	if ((key == 13 || key == 126) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.x_axis--;
	if ((key == 1 || key == 125) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.x_axis++;
	if ((key == 2 || key == 124) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.y_axis++;
	if ((key == 0 || key == 123) && check_and_move(ptr_game, key, x, y))
		ptr_game->map.player.y_axis--;
	return (0);
}
