/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: pminialg <pminialg@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/11/08 17:08:32 by pminialg      #+#    #+#                 */
/*   Updated: 2023/11/20 10:40:18 by pminialg      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_free(char **string)
{
	free(*string);
	*string = NULL;
	return (NULL);
}

char	*next_line_data(char *buffer, char **line_data)
{
	char	*line_next;
	char	*temp_ptr;
	int		length;

	temp_ptr = ft_strchr(buffer, '\n');
	if (!temp_ptr)
	{
		line_next = NULL;
		return (ft_free(&buffer));
	}
	else
		length = (temp_ptr - buffer) + 1;
	if (!buffer[length])
		return (ft_free(&buffer));
	line_next = ft_substr(buffer, length, ft_strlen(buffer) - length);
	ft_free(&buffer);
	if (!line_next)
		return (ft_free(line_data));
	return (line_next);
}

char	*get_line_from_buffer(char *buffer)
{
	char	*line_data;
	char	*temp_ptr;
	int		length;

	temp_ptr = ft_strchr(buffer, '\n');
	length = (temp_ptr - buffer) + 1;
	line_data = ft_substr(buffer, 0, length);
	if (!line_data)
		return (NULL);
	return (line_data);
}

char	*read_data_from_file(char **result, int fd)
{
	char	*buffer;
	int		bytes_read;

	bytes_read = 1;
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(result));
	buffer[0] = '\0';
	while (bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read > 0)
		{
			buffer[bytes_read] = '\0';
			*result = ft_strjoin(*result, buffer);
			if (!result)
				return (ft_free(&buffer));
		}
	}
	free(buffer);
	if (bytes_read == -1)
		return (ft_free(result));
	return (*result);
}

char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line_data;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	if ((buffer[fd] && !ft_strchr(buffer[fd], '\n')) || !buffer[fd])
		buffer[fd] = read_data_from_file(&buffer[fd], fd);
	if (!buffer[fd])
		return (NULL);
	line_data = get_line_from_buffer(buffer[fd]);
	if (!line_data)
		return (ft_free(&buffer[fd]));
	buffer[fd] = next_line_data(buffer[fd], &line_data);
	return (line_data);
}
