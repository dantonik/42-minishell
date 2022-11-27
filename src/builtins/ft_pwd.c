/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cboubour <cboubour@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:03:54 by cboubour          #+#    #+#             */
/*   Updated: 2022/11/22 21:06:24 by cboubour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	*pwd;
	int		len;

	pwd = getcwd(NULL, MAXPATHLEN);
	if (pwd != NULL)
	{
		len = ft_strlen(pwd);
		write(1, pwd, len);
		write(1, "\n", 1);
		free(pwd);
		return (0);
	}
	return (1);
}
