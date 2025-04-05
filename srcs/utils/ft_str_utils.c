/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 18:16:51 by hoskim            #+#    #+#             */
/*   Updated: 2025/04/05 17:39:41 by hoskim           ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

/**
 * @brief Measures the length of string.
 * @note Only used for 'ft_strjoin()' in the current file
 * @return The length of the string (int)
 */
int	ft_strlen(char *str)
{
	int	len_of_str;

	len_of_str = 0;
	while (str[len_of_str])
		len_of_str++;
	return (len_of_str);
}

/**
 * @brief Combines s1 and s2 in a string
 */
char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		i;
	int		j;
	int		len_s1;
	int		len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	result = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < len_s1)
		result[i] = s1[i];
	j = 0;
	while (j < len_s2)
	{
		result[i + j] = s2[j];
		j++;
	}
	result[i + j] = '\0';
	return (result);
}

/**
 * @brief Converts an integer to a string
 */
char	*ft_itoa(int n)
{
	char	*str;
	int		len;
	int		temp;

	len = 1;
	temp = n;
	while (temp / 10)
	{
		len++;
		temp /= 10;
	}
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = '0' + (n % 10);
		n /= 10;
	}
	return (str);
}
