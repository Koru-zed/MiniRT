#include "get_next_line.h"

char	*ft_read_str(int fd, char *str_line)
{
	int		byte;
	char	*buff;

	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	byte = 1;
	while (!ft_strchr(str_line, '\n') && byte != 0)
	{
		byte = read (fd, buff, BUFFER_SIZE);
		if (byte == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[byte] = '\0';
		str_line = ft_strjoin_free_s1(str_line, buff);
	}
	free(buff);
	return (str_line);
}

char	*ft_re_line(char *str)
{
	int		j;
	char	*s_line;

	j = 0;
	while (str[j] && str[j] != '\n')
		j++;
	if (str[j] == '\n')
		s_line = (char *)malloc(sizeof(char) * (j + 2));
	else
		s_line = (char *)malloc(sizeof(char) * (j + 1));
	if (!s_line)
		return (NULL);
	j = 0;
	while (str[j] && str[j] != '\n')
	{
		s_line[j] = str[j];
		j++;
	}
	s_line[j] = '\0';
	return (s_line);
}

char	*ft_left(char *s, int c)
{
	int		i;
	int		j;
	char	*s_left;

	i = 0;
	while (s[i] && s[i] != (char)c)
		i++;
	if (!s[i])
	{
		free(s);
		return (NULL);
	}
	s_left = (char *)malloc(sizeof(char) * (ft_strlen(s) - i + 1));
	if (!s_left)
	{
		free(s);
		return (NULL);
	}
	i++;
	j = 0;
	while (s[i])
		s_left[j++] = s[i++];
	s_left[j] = '\0';
	free(s);
	return (s_left);
}

char	*get_next_line(int fd)
{
	char		*s_line;
	static char	*str_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str_line = ft_read_str(fd, str_line);
	if (!str_line)
		return (NULL);
	if (!str_line[0])
	{
		free(str_line);
		str_line = NULL;
		return (NULL);
	}
	s_line = ft_re_line(str_line);
	str_line = ft_left(str_line, '\n');
	return (s_line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main()
// {
//     int fd = open("../test.rt", O_RDWR);
//     printf("%s", get_next_line(fd));
// }