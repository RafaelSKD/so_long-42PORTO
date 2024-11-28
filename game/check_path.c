/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:43:34 by rafaefer          #+#    #+#             */
/*   Updated: 2024/10/07 15:43:35 by rafaefer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../so_long.h"

static void	visiting(t_idk *game, int height, int width, int **visited)
{
	if (visited[height][width] || game->map[height][width] == '1'
		|| game->map[height][width] == 'E')
	{
		if (game->map[height][width] == 'E')
			game->exit_visit = 1;
		return ;
	}
	if (game->map[height][width] == 'C')
		game->collectables_check++;
	visited[height][width] = 1;
	visiting(game, height + 1, width, visited);
	visiting(game, height - 1, width, visited);
	visiting(game, height, width + 1, visited);
	visiting(game, height, width - 1, visited);
}

static int	check_valid(t_idk *game, int height, int **visited)
{
	int	path;
	int	width;

	path = 1;
	while (height < game->heightmap)
	{
		width = 0;
		while (width < game->widthmap)
		{
			if ((game->map[height][width] == 'C')
				&& !visited[height][width])
			{
				path = 0;
				break ;
			}
			width ++;
		}
		height++;
	}
	if ((game->exit_visit == 1 && game->collectables_check
			< game->collectables) || game->exit_visit == 0)
		path = 0;
	return (path);
}

int	check_path(t_idk *game)
{
	int			height;
	static int	**visited;

	visited = ft_calloc(game->heightmap, sizeof(int *));
	height = 0;
	while (height < game->heightmap)
		visited[height++] = ft_calloc(game->widthmap, sizeof(int));
	visiting(game, game->j, game->i, visited);
	height = 0;
	if (!check_valid(game, height, visited))
	{
		height = 0;
		while (height < game->heightmap)
			free(visited[height++]);
		free(visited);
		ft_printf("Error\nNot all collectables or exits are reachable!\n");
		return (0);
	}
	height = 0;
	while (height < game->heightmap)
		free(visited[height++]);
	free(visited);
	return (1);
}
