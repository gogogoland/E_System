/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TreatData.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 14:24:28 by tbalea            #+#    #+#             */
/*   Updated: 2016/03/19 18:21:07 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Expert_system.hpp"

static bool	CheckConsistenceRules(Elems **elm_lst, int size);
static bool	CheckConsistenceFacts(Elems **elm_lst, int size, bool fact);
static bool	setToTrue(Elems *elems, Elems **elm_lst, int size);
static bool	setToFalse(Elems *elems, Elems **elm_lst, int size);

//	Reset Elems to false
static void	resetELM(Elems *elems)
{
	elems->setState(false);
	elems->setModif(false);
	if (elems->getOperator() >= 0)
	{
		resetELM(elems->getElemsOne());
		if (elems->getOperator() > 0)
			resetELM(elems->getElemsTwo());
	}
}

//	Reset All Elems
static void	resetAllELM(Elems **elems, int size)
{
	while (--size >= 0)
		resetELM(elems[size]);
}

//	Set Elems to false (used for "!")
static bool	setToFalse(Elems *elems, Elems **elm_lst, int size)
{
	bool	orXor;

	orXor = false;
	//	if !OR or !XOR
	if (elems->getOperator() == 2 || elems->getOperator() == 3)
	{
		if (setToFalse(elems->getElemsTwo(), elm_lst, size))
		{
			orXor = true;
			if (!CheckConsistenceFacts(elm_lst, size, false))
				return (false);
		}
//		resetELM(elems->getElemsTwo());
		resetAllELM(elm_lst, size);
		if (setToFalse(elems->getElemsOne(), elm_lst, size))
		{
			if (!CheckConsistenceFacts(elm_lst, size, false))
				return (false);
		}
		else if (!orXor)
			return (false);
//		resetELM(elems->getElemsOne());
//		resetAllELM(elm_lst, size);
	}
	//	if !OR or !AND
	if (elems->getOperator() == 2 || elems->getOperator() == 1)
	{
		if (!setToFalse(elems->getElemsTwo(), elm_lst, size)
				|| !setToFalse(elems->getElemsOne(), elm_lst, size))
			return (false);
	}
	//	if !XOR (only) to do ?
	//	if !NEG
	if (elems->getOperator() == 0)
	{
		if (elems->getElemsOne()->getState())
			return (false);
		elems->getElemsOne()->setModif(true);
		if (!setToTrue(elems->getElemsOne(), elm_lst, size))
			return (false);
	}
	//	if !FACT
	if (elems->getName() < 91)
	{
		if (elems->getState() && elems->getModif())
			return (false);
		elems->setState(false);
		elems->setModif(true);
	}
	return (true);
}

//	Set Elems to true
static bool	setToTrue(Elems *elems, Elems **elm_lst, int size)
{
	bool	orXor;

	orXor = false;
	//	if OR or XOR
	if (elems->getOperator() == 2 || elems->getOperator() == 3)
	{
		if (setToTrue(elems->getElemsTwo(), elm_lst, size))
		{
			orXor = true;
			if (!CheckConsistenceFacts(elm_lst, size, false))
				return (false);
		}
		resetAllELM(elm_lst, size);
//		resetELM(elems->getElemsTwo());
		if (setToTrue(elems->getElemsOne(), elm_lst, size))
		{
			if (!CheckConsistenceFacts(elm_lst, size, false))
				return (false);
		}
		else if (!orXor)
			return (false);
//		resetAllELM(elm_lst, size);
//		resetELM(elems->getElemsOne());
	}
	//	if OR or AND
	if (elems->getOperator() == 2 || elems->getOperator() == 1)
	{
		if (!setToTrue(elems->getElemsTwo(), elm_lst, size)
				|| !setToTrue(elems->getElemsOne(), elm_lst, size))
			return (false);
	}
	//	if XOR (only) to do ?
	//	if NEG
	if (elems->getOperator() == 0)
	{
		if (elems->getElemsOne()->getState())
			return (false);
		elems->getElemsOne()->setModif(true);
		if (!setToFalse(elems->getElemsOne(), elm_lst, size))
			return (false);
	}
	//	if FACT
	if (elems->getName() < 91)
	{
		if (!elems->getState() && elems->getModif())
			return (false);
		elems->setState(true);
		elems->setModif(true);
	}
	return (true);
}

//	Verify rules elems
static bool	CheckConsistenceRules(Elems **elm_lst, int size)
{
	int		i;
	bool	orXor;

	i = 0;
	orXor = false;
	while (i < size)
	{
		if (elm_lst[i]->getOperator() == 2 || elm_lst[i]->getOperator() == 3)
			orXor = true;
		//	if IMP or SSI
		if (elm_lst[i]->getOperator() >= 4)
		{
			if (!setToTrue(elm_lst[i]->getElemsOne(), elm_lst, size))
				return (false);
			//	if SSI
			if (elm_lst[i]->getOperator() == 5)
			{
				if (!setToTrue(elm_lst[i]->getElemsTwo(), elm_lst, size))
					return (false);
			}
			if (!orXor)
			{
				if (!CheckConsistenceFacts(elm_lst, size, false))
					return (false);
			}
			orXor = false;
			resetAllELM(elm_lst, size);
		}
		i++;
	}
	return (true);
}

//	Verify facts elems
static bool	CheckConsistenceFacts(Elems **elm_lst, int size, bool fact)
{
	int		i;
	bool	modif;
	bool	tmp;

	modif = true;
	while (modif)
	{
		modif = false;
		i = 0;
		while (i < size)
		{
			tmp = elm_lst[i]->getState();
			if (elm_lst[i]->getName() > 90)
//			if (elm_lst[i]->getOperator() > 3)
			{
				if (!elm_lst[i]->applyRules())
				{
					if (!fact
							&& elm_lst[i]->getOperator() == 3
							&& elm_lst[i]->getElemsOne()->getModif() == false
							&& elm_lst[i]->getElemsTwo()->getModif() == false)
						fact ? std::cout << "XOR unknow in "
							<< elm_lst[i]->getName()
							<< std::endl : std::cout;
					else
					{
						std::cout << "For rule " << elm_lst[i]->getName() << std::endl;
						return (false);
					}
				}
			}
			if (tmp != elm_lst[i]->getState())
				modif = true;
			i++;
		}
	}
	return (true);
}

//	Verify rules and facts and print result (to separate)
static int	CheckData(Elems **elm, int i, int **data, int *solve)
{
	int	j;

	if (!CheckConsistenceRules(elm, i))
	{
		std::cout << "Error in rules" << std::endl;
		return (0);
	}
	j = -1;
	while (data[++j][0] < 91 && data[j][0] > 0)
	{
		elm[j]->setState(data[j][1] ? true : false);
		elm[j]->setModif(data[j][1] ? true : false);
	}
	if (!CheckConsistenceFacts(elm, i, true))
	{
		std::cout << "Error in facts" << std::endl;
		return (0);
	}
	i = 0;
	while (solve && solve[i] && solve[i] > 0)
	{
		j = 0;
		while (elm[j] && elm[j]->getName() != solve[i])
			j++;
		if (!elm[j])
			break ;
		std::cout << (char)solve[i] << " is " << (elm[j]->getState() ? "true." : "false.") << std::endl;
		i++;
	}
	delete [] solve;
//	Elems **elm, *e1, *e2 to free
	return (1);
}

//	Transfer data from vector of int** to simple int**
static int	**getData(std::vector<int **> vect)
{
	int					j;
	int					size;
	int					**data;

	size = 0;
	for (auto it = vect.begin(); it != vect.end(); it++)
	{
		j = 0;
		while ((*it)[j] && (*it)[j][0] > -2)
			j++;
		size += j + 1;
	}
	data = new int *[size + 3];
	size = 0;
	for (auto it = vect.begin(); it != vect.end(); it++)
	{
		j = 0;
		while ((*it)[j] && (*it)[j][0] > -2)
		{
			data[size] = new int [4];
			data[size][0] = (*it)[j][0];
			data[size][1] = (*it)[j][1];
			data[size][2] = (*it)[j][2];
			data[size][3] = (*it)[j][3];
			size++;
			j++;
		}
	}
	data[size] = new int [4];
	data[size][0] = -2;
	data[size][1] = -2;
	data[size][2] = -2;
	data[size][3] = -2;
	data[size + 1] = NULL;
	return (data);
}

//	Put readed files data in table of elems
int			TreatData(std::vector<int **> vect, int *solve)
{
	int		**data;
	Elems	**elm;
	Elems	*e1;
	Elems	*e2;
	int		i;
	int		j;

	data = getData(vect);
	i = 0;
	//	Set size of Elems **elm
	while (data[i][0] && data[i][1] > -2)
		i++;
	elm = new Elems*[(i + 1)];
	//	Put int **data to Elems **elm
	i = 0;
	while (data[i][0] && data[i][1] > -2)
	{
		//	Facts
		if (data[i][0] < 91)
			elm[i] = new Elems (data[i][0]);
		//	Rules
		else
		{
			e2 = NULL;
			j = i - 1;
			//	Research Elems *e1;
			while (j >= 0 && elm[j]->getName() != data[i][2])
				j--;
			if (j < 0)
				return (-1);
			e1 = elm[j];
			if (data[i][1] > 0)
			{
				j = i - 1;
				//	Research Elems *e2 (except for '!')
				while (j >= 0 && elm[j]->getName() != data[i][3])
					j--;
				if (j < 0)
					return (-1);
				e2 = elm[j];
			}
			elm[i] = new Elems (data[i][0], data[i][1], e1, e2);
		}
		i++;
	}
	return (CheckData(elm, i, data, solve));
}
