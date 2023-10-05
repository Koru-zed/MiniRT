/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mait-jao <mait-jao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 16:03:32 by mait-jao          #+#    #+#             */
/*   Updated: 2022/12/08 16:03:33 by mait-jao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include "../Libft/libft.h"

# define BUFFER_SIZE 42

char	*get_next_line(int fd);
char	*ft_read_str(int fd, char *str_line);
char	*ft_re_line(char *str);
char	*ft_left(char *s, int c);

#endif      
