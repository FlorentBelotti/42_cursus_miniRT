/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jedurand <jedurand@student.42perpignan.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:24:18 by jedurand          #+#    #+#             */
/*   Updated: 2024/09/09 16:24:19 by jedurand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

char	*construct_scene_path(const char *filename)
{
	const char	*scene_dir;
	size_t		len;
	char		*filepath;

	scene_dir = "Scene/";
	len = ft_strlen(scene_dir) + ft_strlen(filename) + 1;
	filepath = malloc(len);
	if (filepath)
	{
		ft_strlcpy(filepath, scene_dir, len);
		ft_strlcat(filepath, filename, len);
	}
	return (filepath);
}

void	init_scene_data(t_data *data)
{
	data->ambient.ratio = -1;
	data->camera.fov = -1;
	data->light = NULL;
}

int	parse_scene_file(int fd, t_data *data)
{
	char	*line;
	int		result;

	result = 0;
	line = get_next_line(fd);
	while (line != NULL)
	{
		result = parse_line(line, data);
		free(line);
		if (result)
		{
			while (line)
			{
				line = get_next_line(fd);
				free(line);
			}
			return (1);
		}
		line = get_next_line(fd);
	}
	return (0);
}

int	check_mandatory_elements(t_data *data)
{
	if (data->ambient.ratio == -1 || data->camera.fov == -1
		|| data->light == NULL || data->light->brightness == -1)
	{
		ft_printf("Error: Missing mandatory scene elements\n");
		return (1);
	}
	return (0);
}

int	validate_filename(const char *filename)
{
	const char	*extension;
	size_t		len;
	size_t		ext_len;

	extension = ".rt";
	len = ft_strlen(filename);
	ext_len = ft_strlen(extension);
	if (len < ext_len)
	{
		ft_printf("Error: Invalid file extension. Expected .rt\n");
		return (1);
	}
	if (ft_strcmp((char *)(filename + len - ext_len), (char *)extension) != 0)
	{
		ft_printf("Error: Invalid file extension. Expected .rt\n");
		return (1);
	}
	return (0);
}
