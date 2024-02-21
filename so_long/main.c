/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldi-fior <ldi-fior@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:47:12 by ldi-fior          #+#    #+#             */
/*   Updated: 2024/02/16 11:49:30 by ldi-fior         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	main(int argc, char **argv)
{
	static t_game	game;

	if (argc != 2)
	{
		ft_printf("Error1: invalid number of parameters");
		return (1);
	}
	set_var_to_zero(&game);
	if (matrix_generator(&game, argv[1]) != 0)
		launch_game(&game);
}
