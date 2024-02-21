/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:52:27 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 13:01:46 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_ber_file(char *path, t_game *ptr_game)
{
	int	len;

	len = ft_strlen(path);
	if (path[len - 1] == 'r' && path[len - 2] == 'e'
		&& path[len - 3] == 'b' && path[len - 4] == '.')
	{
		ptr_game->map.map_path = path;
		return (1);
	}
	else
		return (quit_and_free("Invalid file extension", 1, ptr_game));
}

int	check_char(char c)
{
	if (c == '0' || c == '1' || c == 'P' || c == 'E' || c == 'C' || c == 'N')
		return (1);
	return (0);
}

int	matrix_complete_checker(t_game *ptr_game)
{
	if (!p_e_c_n_count(ptr_game))
		return (0);
	else if (!check_map_and_set_tyle(ptr_game))
		return (0);
	else if (!check_path(ptr_game))
		return (0);
	else
		return (1);
}

void	set_tile_location(t_game *ptr_game, char asset, int x, int y)
{
	if (asset == 'P')
	{
		ptr_game -> map.player.tile_type = asset;
		ptr_game -> map.player.x_axis = x;
		ptr_game -> map.player.y_axis = y;
	}
	else if (asset == 'E')
	{
		ptr_game -> map.exit.tile_type = asset;
		ptr_game -> map.exit.x_axis = x;
		ptr_game -> map.exit.y_axis = y;
	}
	else if (asset == 'N')
	{
		ptr_game -> map.enemy.tile_type = asset;
		ptr_game -> map.enemy.x_axis = x;
		ptr_game -> map.enemy.y_axis = y;
	}
	else if (asset == 'C')
	{
		ptr_game -> map.collect[ptr_game -> map.n_coin].tile_type = asset;
		ptr_game -> map.collect[ptr_game -> map.n_coin].x_axis = x;
		ptr_game -> map.collect[ptr_game -> map.n_coin].y_axis = y;
		ptr_game -> map.n_coin++;
	}
}
