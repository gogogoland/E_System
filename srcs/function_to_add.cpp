/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function_to_add.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/16 22:14:54 by tbalea            #+#    #+#             */
/*   Updated: 2016/03/15 18:38:43 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>
#include <cctype>
#include "Expert_system.hpp"
//	1) To simplify everything, change char *str to int *str;
//	2) Check priority and replace value;

//	Delete one elem of table of int
static void	delelem(int *str, int i)
{
	while (str[i] > -3)
	{
		str[i] = str[i + 1];
		i++;
	}
}

//	All operator other than "=>" and "<=>"
static int	opall(int *str, int **tab, int b, int e, size_t *name, int org, int val)
{
	int	sup;

	sup = 0;
	while (b < e && str[b] != -3)
	{
		if (str[b] == val)
		{
			//	Add rule
			tab[(*name - org)] = new int[4];
			tab[(*name - org)][0] = *name + 91;
			tab[(*name - org)][1] = val;
			tab[(*name - org)][2] = str[b + 1];
			tab[(*name - org)][3] = str[b - 1];
			//	Replace rule by rule value
			str[b] = *name + 91;
			(*name)++;
			delelem(str, b + 1);
			sup++;
			e--;
			if (val)
			{
				delelem(str, b - 1);
				e--;
				b--;
			}
		}
		b++;
	}
	return (sup);
}

//	Operator "<=>" and "=>"
static int	opres(int *str, int **tab, int b, int e, size_t *name, int org)
{
	while (b < e && (str[b] < 3 || str[b] > 6) && str[b] != -3)
		b++;
	if (str[b] > 3 && str[b] < 6)
	{
		//	Add rule
		tab[(*name - org)] = new int[4];
		tab[(*name - org)][0] = *name + 91;
		tab[(*name - org)][1] = str[b];
		tab[(*name - org)][2] = str[b - 1];
		tab[(*name - org)][3] = str[b + 1];
		//	Replace rule by rule value
		str[b] = *name + 91;
		(*name)++;
		delelem(str, b + 1);
		delelem(str, b - 1);
		return (1);
	}
	return (0);
}

//	Parenthese priority
static void	parenthese(int *str, int **tab, int b, size_t *name, int org)
{
	int i;

	i = b;
	while (str[++i] != -2)
	{
		if (str[i] == -1)
			parenthese(str, tab, i, name, org);
	}
	//	Add in tab '!' rules and delete them from str between "()"
	i -= opall(str, tab, b, i, name, org, 0);
	//	Add in tab '+' rules and delete them from str between "()"
	i -= 2 * opall(str, tab, b, i, name, org, 1);
	//	Add in tab '|' rules and delete them from str between "()"
	i -= 2 * opall(str, tab, b, i, name, org, 2);
	//	Add in tab '^' rules and delete them from str between "()"
	i -= 2 * opall(str, tab, b, i, name, org, 3);
	delelem(str, i);
	delelem(str, b);
}

//	Extract data in str to table of table of int
static int	**getdata(int *str, size_t *name, int size)
{
	int	i;
	int	org;
	int	**tab = NULL;

	i = 0;
	org = *name;
	tab = new int*[size + 3];
	//	Get rules by priority
	//	'()' priority;
	while (str[i] > -3)
	{
		if (str[i] == -1)
			parenthese(str, tab, i, name, org);
		i++;
	}
	i = 0;
	while (str[i] > -3)
		i++;
	//	Add in tab '!' rules and delete them from str
	opall(str, tab, 0, i, name, org, 0);
	//	Add in tab '+' rules and delete them from str
	opall(str, tab, 0, i, name, org, 1);
	//	Add in tab '|' rules and delete them from str
	opall(str, tab, 0, i, name, org, 2);
	//	Add in tab '^' rules and delete them from str
	opall(str, tab, 0, i, name, org, 3);
	//	Add in tab "=>" or "<=>" rules and delete them from str
	opres(str, tab, 0, i, name, org);
	tab[(*name - org)] = new int[4];
	tab[*name - org][0] = -2;
	tab[*name - org][1] = -2;
	tab[*name - org][2] = -2;
	tab[*name - org][3] = -2;
	tab[*name - org + 1] = NULL;
	return (tab);
}

//	Transform string char into table of int
static int	*strtoints(char *str)
{
	int	*istr = new int[strlen(str) + 1];
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
			i++;
		if (str[i] == '(')
			istr[j] = -1;
		else if (str[i] == ')')
			istr[j] = -2;
		else if (str[i] == '!')
			istr[j] = 0;
		else if (str[i] == '+')
			istr[j] = 1;
		else if (str[i] == '|')
			istr[j] = 2;
		else if (str[i] == '^')
			istr[j] = 3;
		else if (str[i] == '=' && ((i - 1) > -1 && str[i - 1] != '<'))
			istr[j] = 4;
		else if (str[i] == '=' && ((i - 1) > -1 && str[i - 1] == '<'))
			istr[j] = 5;
		else
			istr[j] = (int)str[i];
		i++;
		j++;
	}
	istr[j] = -3;
	return (istr);
}

int			**function_to_add(const char *get, size_t *name)
{
	int 	*istr;
	int		i;
	int		size;
	char	*str = NULL;

	str = strdup(get);
	i = 0;
	size = 0;
	//	Transform char * into int*
	istr = strtoints(str);
	//	Get number of operator
	while (str[++i] != '\0')
	{
		if (!isalpha(str[i]) && str[i] != '(' && str[i] != ')' && str[i] != '<' && str[i] != '>')
			size++;
	}
	return (getdata(istr, name, size));
}
