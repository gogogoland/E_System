/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Class.Storage.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: croy <croy@student.42.fr>         	        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/06 14:24:28 by croy              #+#    #+#             */
/*   Updated: 2016/03/16 02:36:13 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Class.Storage.hpp"
#include "Expert_system.hpp"

/*
 ** ~ Canonical Form
 */

Storage::Storage(void){}

Storage::Storage(std::vector<std::string> array): _Array(array){}

Storage::~Storage(void){}

Storage::Storage(Storage const & copy) { *this = copy;}


Storage & Storage::operator=(Storage const & copy)
{
	if (this != & copy)
	{
		this->_Array = copy.getArray();
	}
	return *this;
}

/*
 ** Getter
 */

std::vector<std::string>	Storage::getArray(void) const { return (this->_Array); }

/*
 ** ~ Methods
 */

int						Storage::Check(void)
{
	std::pair<std::map<char,int>::iterator,bool>	ret;
	std::map<char,int>								Value;
	size_t											error = 0, result = 0, equal = 0, index = 1, P_L = 0, P_R = 0, R_1 = 0, R_2 = 0;
	int												mal = 0;
	int												*solve = NULL;

	for (auto it = this->_Array.begin(); it != this->_Array.end() ; it++, ++index)
	{
		if ((*it)[0] == '=')
			equal = equal + 1;

		if ((*it)[0] == '?')
			result = result + 1;

		if (equal > 1 || result > 1)
		{
			std::cout << "ERROR : Line." << index <<  " Bad syntax (more than one = or ?)." << std::endl;
			error++;
		}

		for (size_t i = 0; (*it)[i]; i++)
		{
			if ((*it)[i - 1] != '<' && (*it)[i] == '=' && (*it)[i + 1] == '>')
			{
				if (P_L != P_R)
				{
					std::cout << "ERROR : Line." << index << " Bad syntax with parenthesis." << std::endl;
					error++;
				}
				R_1 += 1;
			}
			else if ((*it)[i] == '<' && (*it)[i + 1] == '=' && (*it)[i + 2] == '>')
			{
				if (P_L != P_R)
				{
					std::cout << "ERROR : Line." << index << " Bad syntax with parenthesis." << std::endl;
					error++;
				}
				R_2 += 1;
			}

			if ((*it)[0] != '?' && (*it)[0] != '=')
			{
				//CHECK FOR PAIR OF PARENTHESE
				if ((*it)[i] == '(')
					P_L += 1;
				if ((*it)[i] == ')')
					P_R += 1;

				//CHECK IF IT'S ALPHA
				if ((*it)[i] == '!' && (!isalpha((*it)[i + 1]) && (*it)[i + 1] != '('))
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbols: !)." << std::endl;
					error++;
				}
				//CHECK IF IT'S ! ALPHA ^ or (
				else if ((*it)[i] == '+' && (!isalpha((*it)[i + 1]) && (*it)[i + 1] != '!' && (*it)[i + 1] != '(') && (*it)[i + 1] != '^')
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbols: '+')." << std::endl;
					error++;
				}

				//CHECK IF IT'S ALPHA or !
				else if ((*it)[i] == '(' && (!isalpha((*it)[i + 1]) && (*it)[i + 1] != '!' && (*it)[i + 1] != '('))
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbols: '(')." << std::endl;
					error++;
				}

				//CHECK FOR PARENTHESE
				else if ((*it)[i] == ')' && ((*it)[i + 1] != '+') && (*it)[i + 1] != '<' && (*it)[i + 1] != '=' && (*it)[i + 1] != '|' &&  (*it)[i + 1] != '^' && (*it)[i + 1] != ')' && (*it)[i + 1] != '\0')
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbols: ')')." << std::endl;
				}

				//CHECK IF IT'S ALPHA OR !
				else if ((*it)[i] == '^' && (!isalpha((*it)[i + 1]) && (*it)[i + 1] != '!') && (*it)[i + 1] != '(')
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbols: '^')." << std::endl;
					error++;
				}

				//CHECK FOR IMPLIES
				else if ((*it)[i] == '>' && (!isalpha((*it)[i + 1]) && (*it)[i + 1] != '!' && (*it)[i + 1] != '('))
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbols: '>')." << std::endl;
					error++;
				}

				//CHECK FOR SYNTAX
				else if (isalpha((*it)[i]) != true && (*it)[i] != '=' && (*it)[i] != '>' && (*it)[i] != '+' && (*it)[i] != '^' && (*it)[i] != '|' && (*it)[i] != '(' && (*it)[i] != ')' && (*it)[i] != '<' && (*it)[i] != '!')
				{
					std::cout << "ERROR : Line." << index << " Bad syntax." << std::endl;
					error++;
				}
				else if ((*it)[i] == '=' && (*it)[i + 1] != '>')
				{
					std::cout << "ERROR : Line." << index << " Bad syntax (symbol '=')." << std::endl;
					error++;
				}

				// INSERT INTO DICTIONNARY
				if (isalpha((*it)[i]) == true && (*it)[0] != '=')
					Value.insert(std::pair<char, int>((*it)[i], 0));
			}
			else if ((*it)[0] == '?' || (*it)[0] == '=')
			{
				if (isalpha((*it)[i]) != true && i > 0)
				{
					std::cout << "ERROR : Line." << index << " Bad syntax." << std::endl;
					error++;
				}

				if ((*it)[0] == '=' && i > 0 && isalpha((*it)[i]) == true)
					Value[(*it)[i]] = 1;

				if ((*it)[0] == '?' && i > 0)
				{
					ret = Value.insert(std::pair<char, int>((*it)[i], true));
					mal += 1;
					if (ret.second == true)
					{
						std::cout << "ERROR : Line." << index << " '" << (*it)[i] << "' doesn't exist." << std::endl;
						error++;
					}
				}
			}
		}
		if ((R_1 >= 1 && R_2 >= 1) || (R_1 > 1) || (R_2 > 1))
		{
			std::cout << "ERROR : Line." << index << " bad syntax." << std::endl;
			error++;
		}
		R_1 = 0;
		R_2 = 0;
		if (P_R != P_L)
		{
			std::cout << "ERROR : Line." << index << " '(' need ')'" << std::endl;
			P_R = 0;
			P_L = 0;
			error++;
		}
	}
	if (error > 0)
	{
		std::cout << error << " error(s) found(s)."<< std::endl;
		exit(0);
	}
	index = 0;
	this->_Keys = new int *[(int)Value.size() + 1];
	for (auto i : Value) {
		this->_Keys[index] = new int[4];
		this->_Keys[index][0] = (int)i.first;
		this->_Keys[index][1] = i.second;
		this->_Keys[index][2] = 0;
		this->_Keys[index][3] = 0;
		index++;
	}
	this->_Keys[index] = new int[4];
	this->_Keys[index][0] = -2;
	this->_Keys[index][1] = -2;
	this->_Keys[index] = NULL;
	this->_Val.push_back(this->_Keys);
	index = 0;
	for (auto it = this->_Array.begin(); it != this->_Array.end() ; it++)
	{
		if ((*it).c_str()[0] == '=')
			break ;
		this->_Val.push_back(function_to_add((*it).c_str(), &index));
	}
	solve = new int[mal + 1];
	for (auto it = this->_Array.begin(); it != this->_Array.end() ; it++)
	{
		if ((*it)[0] == '?')
		{
			for (int i = 1; (*it)[i]; i++)
				solve[i - 1] = (int)(*it)[i];
			solve[mal] = -2;
		}
	}
	return (TreatData(this->_Val, solve));
}
