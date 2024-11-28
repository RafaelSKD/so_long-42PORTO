/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:53 by rafaefer          #+#    #+#             */
/*   Updated: 2024/10/07 16:50:27 by rafaefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	destroy_images(t_idk *game)
{
	if (game && game->mlx && game->floor)
		mlx_destroy_image(game->mlx, game->floor);
	if (game->wall)
		mlx_destroy_image(game->mlx, game->wall);
	if (game->player1)
		mlx_destroy_image(game->mlx, game->player1);
	if (game->collectable)
		mlx_destroy_image(game->mlx, game->collectable);
	if (game->exit)
		mlx_destroy_image(game->mlx, game->exit);
}

int	exit_game(t_idk *game)
{
	int	line;

	line = 0;
	if (game && game->mlx)
		destroy_images(game);
	if (game && game->mlx)
		mlx_destroy_window(game->mlx, game->window);
	if (game && game->mlx)
		mlx_destroy_display(game->mlx);
	free(game->mlx);
	while (line < game->heightmap)
		free(game->map[line++]);
	free(game->map);
	exit(0);
}

static void	functions(t_idk game)
{
	game.mlx = mlx_init();
	game.window = mlx_new_window(game.mlx, (game.widthmap * 100),
			(game.heightmap * 100), "So long");
	if (!put_imgs_to_variables(&game))
	{
		ft_printf("Error\nSome images missing\n");
		exit_game(&game);
	}
	put_img_in_game(&game);
	mlx_key_hook(game.window, controls, &game);
	mlx_hook(game.window, 17, 0, exit_game, &game);
	mlx_loop(game.mlx);
}

int	main(int argc, char **argv)
{
	t_idk	game;

	if (argc != 2)
	{
		ft_printf("Error\n Maybe you forgot the map\n");
		return (0);
	}
	game.moves = 0;
	ft_memset(&game, 0, sizeof(t_idk));
	map_reading(&game, argv);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".ber", 4)
		|| !check_errors(&game))
	{
		ft_printf("Error\nThe map is bad formated\n");
		exit_game(&game);
	}
	functions(game);
}
