/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalamarn <jalamarn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 17:00:00 by jalamarn          #+#    #+#             */
/*   Updated: 2026/05/07 17:00:00 by jalamarn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*append_expand_str(char *dst, const char *src)
{
	char	*joined;

	if (!src)
		src = "";
	if (!dst)
		return (ft_strdup(src));
	joined = ft_strjoin(dst, src);
	free(dst);
	return (joined);
}

char	*append_expand_char(char *dst, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (append_expand_str(dst, tmp));
}

char	*status_to_str(int status)
{
	char	buffer[12];
	char	tmp;
	int		i;
	int		j;

	if (status == 0)
		return (ft_strdup("0"));
	i = 0;
	while (status > 0)
	{
		buffer[i++] = (status % 10) + '0';
		status = status / 10;
	}
	buffer[i] = '\0';
	j = 0;
	while (j < i / 2)
	{
		tmp = buffer[j];
		buffer[j] = buffer[i - j - 1];
		buffer[i - j - 1] = tmp;
		j++;
	}
	return (ft_strdup(buffer));
}
