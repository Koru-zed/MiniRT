

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../libft/libft.h"

# define BUFFER_SIZE 42


char	*get_next_line(int fd);
char	*ft_read_str(int fd, char *str_line);
char	*ft_re_line(char *str);
char	*ft_left(char *s, int c);

#endif      
