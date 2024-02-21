/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:52:27 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/19 10:15:57 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	print_error(char *s)
{
	ft_printf("Error: %s\n", s);
}

void	free_map_matrix(char **ptr_map, t_game *ptr_game)
{
	int	i;

	i = 0;
	while (i < ptr_game->map.heigth)
	{
		free(ptr_map[i]);
		i++;
	}
	free(ptr_map);
}

int	quit_and_free(char *error, int err_type, t_game *ptr_game)
{
	if (err_type == 1)
		print_error(error);
	else if (err_type == 2)
	{
		free_map_matrix(ptr_game -> matrix, ptr_game);
		print_error(error);
	}
	else if (err_type == 3)
	{
		free_map_matrix(ptr_game -> matrix, ptr_game);
		ft_printf("%s", error);
		ft_destroy(ptr_game);
	}
	exit (0);
}

int	ft_close_x(t_game *ptr_game)
{
	quit_and_free("See U <3", 3, ptr_game);
	return (0);
}

void	ft_destroy(t_game *ptr_game)
{
	if (ptr_game->win)
		mlx_destroy_window(ptr_game->mlx, ptr_game->win);
}
