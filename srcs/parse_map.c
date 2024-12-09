/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vagarcia <vagarcia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:31:12 by vagarcia          #+#    #+#             */
/*   Updated: 2024/11/26 13:00:39 by vagarcia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || \
	c == '\v' || c == '\f' || c == '\r');
}

void	is_valid(char *s)
{
	int	i;

	if (!s)
		get_err(INVALID_MAP_ERR);
	i = 0;
	i += (s[i] == '-');
	while (s[i] && s[i] != ',')
	{
		if (!ft_isdigit(s[i]) && !ft_isspace(s[i]))
			get_err(INVALID_MAP_ERR);
		i++;
	}
	if (!s[i] || s[i] == ' ')
		return ;
	i += 1;
	if (ft_strlen(s + i) < 3)
		get_err(INVALID_MAP_ERR);
	while (s[i])
	{
		if (!in_string("0123456789abcdef", to_lower(s[i])))
			get_err(INVALID_MAP_ERR);
		i++;
	}
}

int	get_points_from_line(char *line, t_dot **matrix_of_points, int y)
{
	char	**points;
	int		x;

	if (!line)
		get_err(INVALID_MAP_ERR);
	points = ft_split(line, ' ');
	if (!points)
		return (ft_free(points), get_err(MALLOC_ERR), 0);
	x = 0;
	while (points[x])
	{
		is_number_valid(points[x]);
		matrix_of_points[y][x].z = ft_atoi(points[x]);
		matrix_of_points[y][x].x = x;
		matrix_of_points[y][x].y = y;
		matrix_of_points[y][x].color = get_color_from_line(*(points + x));
		matrix_of_points[y][x].is_last = 0;
		free(points[x++]);
	}
	free(points);
	matrix_of_points[y][--x].is_last = 1;
	return (x);
}

t_dot **alloc_new(t_dot **new, int y, int x)
{
	new = (t_dot **)malloc(sizeof(t_dot *) * (++y + 1));
	if (!new)
		return (NULL);
	while (y > 0)
	{
		new[--y] = (t_dot *)malloc(sizeof(t_dot) * (x + 1));
		if (!new[y])
			free_matrix(new);
	}
	return (new);
}

t_dot	**alloc_all_points(char *file_name)
{
	t_dot	**new;
	int		x;
	int		y;
	int		fd;
	char	*line;

	fd = open_file(file_name, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		get_err(INVALID_MAP_ERR);
	}
	x = ft_wdcounter(line, ' ');
	y = 0;
	while (line)
	{
		y++;
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	close(fd);
	new = alloc_new(new, y, x);
	if (!new)
		return (free_matrix(new), get_err(MALLOC_ERR), NULL);
	return (new);
}

t_dot	**parse_map(char *file_name)
{
	t_dot	**matrix_of_points;
	int		y;
	int		fd;
	char	*line;

	matrix_of_points = alloc_all_points(file_name);
	if (!matrix_of_points)
		return (free_matrix(matrix_of_points), NULL);
	fd = open_file(file_name, O_RDONLY);
	y = 0;
	line = get_next_line(fd);
	if (!line)
	{
		close(fd);
		get_err(INVALID_MAP_ERR);
	}
	while (line)
	{
		get_points_from_line(line, matrix_of_points, y++);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	if (matrix_of_points[y])
		free(matrix_of_points[y]);
	matrix_of_points[y] = NULL;
	return (close(fd),matrix_of_points);
}
