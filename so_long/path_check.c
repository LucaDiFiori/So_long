/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 12:54:44 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 12:49:14 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**matrix_duplicator(t_game *ptr_game)
{
	char	**mat_duplicate;
	int		i;

	i = -1;
	mat_duplicate = (char **)malloc(sizeof(char *)
			* ptr_game -> map.heigth);
	while (++i < ptr_game->map.heigth)
		mat_duplicate[i] = ft_strdup(ptr_game -> matrix[i]);
	return (mat_duplicate);
}

void	trace_all_path(t_game *g, int x, int y, char **t_p)
{
	if (x >= 0 && x < g -> map.heigth - 1 && y >= 0 && y < g->map.width - 1
		&& (g -> matrix[x][y] == '0' || g -> matrix[x][y] == 'C'
		|| g -> matrix[x][y] == 'E') && t_p[x][y] != '1' && t_p[x][y] != 'N')
		t_p[x][y] = '1';
	if (t_p[x + 1][y] != '1' && t_p[x + 1][y] != 'P')
		trace_all_path(g, x + 1, y, t_p);
	if (t_p[x][y + 1] != '1' && t_p[x][y + 1] != 'P')
		trace_all_path(g, x, y + 1, t_p);
	if (t_p[x - 1][y] != '1' && t_p[x - 1][y] != 'P')
		trace_all_path(g, x - 1, y, t_p);
	if (t_p[x][y - 1] != '1' && t_p[x][y - 1] != 'P')
		trace_all_path(g, x, y - 1, t_p);
}

static int	check_coin(t_game *ptr_game, char **trace_path)
{
	int	i;

	i = -1;
	while (++i < ptr_game->map.n_coin)
	{
		if (trace_path[ptr_game->map.collect[i].x_axis]
			[ptr_game->map.collect[i].y_axis] != '1')
			return (0);
	}
	return (1);
}

int	check_path(t_game *ptr_game)
{
	char	**traced_path;

	traced_path = matrix_duplicator(ptr_game);
	trace_all_path(ptr_game, ptr_game -> map.player.x_axis,
		ptr_game -> map.player.y_axis, traced_path);
	if (!check_coin(ptr_game, traced_path))
	{
		free_map_matrix(traced_path, ptr_game);
		quit_and_free("Path not valid", 2, ptr_game);
	}
	if (traced_path[ptr_game->map.exit.x_axis]
		[ptr_game->map.exit.y_axis] != '1')
	{
		free_map_matrix(traced_path, ptr_game);
		quit_and_free("Path not valid", 2, ptr_game);
	}
	free_map_matrix(traced_path, ptr_game);
	return (1);
}
