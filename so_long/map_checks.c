/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 11:16:34 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 12:09:50 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_mapsize(t_game *ptr_game, char *m_path)
{
	int		fd;
	int		width_map;
	char	*map_line;

	check_ber_file(m_path, ptr_game);
	fd = open(m_path, O_RDONLY);
	if (fd < 0)
		return (quit_and_free("file opening error", 1, ptr_game));
	map_line = get_next_line(fd);
	if (!map_line[0] || !map_line)
		return (quit_and_free("Empty map file", 1, ptr_game));
	ptr_game->map.width = ft_strlen(map_line) - 1;
	while (map_line && ++ptr_game -> map.heigth)
	{
		width_map = ft_strlen(map_line);
		if (map_line[width_map - 1] == '\n')
			width_map--;
		free(map_line);
		if (width_map != ptr_game->map.width)
			return (quit_and_free("invalid map shape", 1, ptr_game));
		map_line = get_next_line(fd);
	}
	close(fd);
	return (1);
}

static int	p_e_c_n_support(t_game *game)
{
	if (game->map.count.count_p != 1)
		return (quit_and_free("invalid number of player", 2, game));
	else if ((ft_strncmp(game->map.map_path, "maps/bonusmap.ber") == 0)
		&& (game->map.count.count_n != 1))
		return (quit_and_free("invalid number of enemy", 2, game));
	else if (game->map.count.count_e != 1)
		return (quit_and_free("invalid number of exit", 2, game));
	else if (game->map.count.count_c > NUM_COLLECTABLE)
		return (quit_and_free("to many collectables on map", 2, game));
	else
		return (1);
}

int	p_e_c_n_count(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->map.heigth)
	{
		j = -1;
		while (++j < game->map.width)
		{
			if (game->matrix[i][j] == 'P')
				game->map.count.count_p++;
			else if (game -> matrix[i][j] == 'E')
				game->map.count.count_e++;
			else if (game->matrix[i][j] == 'C')
				game->map.count.count_c++;
			else if (game->matrix[i][j] == 'N')
				game->map.count.count_n++;
		}
	}
	return (p_e_c_n_support(game));
}

int	check_map_and_set_tyle(t_game *g)
{
	int	i;
	int	j;

	i = -1;
	while (++i < g->map.heigth)
	{
		j = -1;
		while (++j < g->map.width)
		{
			if (g -> matrix[i][j] != '1' && (i == 0 || j == 0
				|| i == g -> map.heigth - 1 || j == g -> map.width - 1))
				return (quit_and_free("Invalid Map Walls", 2, g));
			else if (!check_char(g -> matrix[i][j]))
				return (quit_and_free("Invalid Character On Map", 2, g));
			else if (g -> matrix[i][j] == 'P')
				set_tile_location(g, 'P', i, j);
			else if (g -> matrix[i][j] == 'E')
				set_tile_location(g, 'E', i, j);
			else if (g -> matrix[i][j] == 'C')
				set_tile_location(g, 'C', i, j);
			else if (g -> matrix[i][j] == 'N')
				set_tile_location(g, 'N', i, j);
		}
	}
	return (1);
}

int	matrix_generator(t_game *ptr_game, char *m_path)
{
	int		fd;
	int		i;
	char	*map_line;

	if (!check_mapsize(ptr_game, m_path))
		return (0);
	ptr_game->matrix = (char **)malloc(sizeof(char *) * ptr_game->map.heigth);
	if (!ptr_game->matrix)
		return (quit_and_free("Matrix allocation failed", 1, ptr_game));
	fd = open(m_path, O_RDONLY);
	if (!fd)
		return (quit_and_free("File non found", 1, ptr_game));
	map_line = get_next_line(fd);
	if (!map_line)
		return (quit_and_free("Function get_next_line failure", 1, ptr_game));
	i = -1;
	while (map_line)
	{
		map_line[ptr_game->map.width] = '\0';
		ptr_game->matrix[++i] = map_line;
		map_line = get_next_line(fd);
	}
	close(fd);
	return (matrix_complete_checker(ptr_game));
}
