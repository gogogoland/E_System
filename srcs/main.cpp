/***********************************************************************************
	______                     __ _____            __                    __ __ ___
   / ____/  ______  ___  _____/ // ___/__  _______/ /____  ____ ___     / // /|__ \
  / __/ | |/_/ __ \/ _ \/ ___/ __|__ \/ / / / ___/ __/ _ \/ __ `__ \   / // /___/ /
 / /____>  </ /_/ /  __/ /  / /____/ / /_/ (__  ) /_/  __/ / / / / /  /__  __/ __/
/_____/_/|_/ .___/\___/_/   \__/____/\__, /____/\__/\___/_/ /_/ /_/     /_/ /____/
		 /_/                       /____/
***********************************************************************************/

#include "Expert_system.hpp"

std::vector<std::string>	parsing_file_into_table(std::vector<std::string> array)
{
	bool						first = false;
	std::string					cpy;

	for(auto it = array.begin();  it != array.end() ; it++)
	{
		//REMOVE ALL SPACES / TABs
		it->erase(remove(it->begin(), it->end(), '\t'), it->end());
		it->erase(remove(it->begin(), it->end(), ' '), it->end());
		
		//UPPER Character
		for (auto & c: *it) c = toupper(c);
	
		//CHECK IF IT'S EMPTY AND IF # IS THE FIRST CHARACTER
		if (it->empty() || (*it)[0] == '#')
		{
			if (it != array.begin())
			{
				it = array.erase(it);
				it--;
			}
			else
				first = true;
		}
		for (size_t i = 0; (*it)[i]; i++)
		{
			if ((*it)[i] == '#')
				(*it).resize(i);
		}
	}
	if (first == true)
		array.erase(array.begin());
	return (array);
}

void		read_file(char *file)
{
	std::ifstream 				fd(file);
	std::string 				line;
	std::vector<std::string>	array;
	
	if (fd.is_open())
	{	
		while (std::getline (fd, line))
			array.push_back(line);
		fd.close();
		if ((array = parsing_file_into_table(array)).size() < 2)
		{
			std::cout << "ERROR : bad format." << std::endl;
			exit(0);
		}
		// Use my class to check if the input and format are correct else EXIT
		Storage parse_input(array);
		parse_input.Check(); // it will throw an error and exit else nothing..
	}
	else
	{
		std::cout << "ERROR : Unable to open this file." << std::endl;
		return ;
	}
}

int		main(int ac, char **av)
{
	int	res;

	if (ac != 2)
	{
		std::cout << "Usage : ./Expert_system <your input file>" << std::endl;
		return (0);
	}
	read_file(av[1]);
/*
 * CheckData function put data files in table of Elems AND print result
 * TO TEST
 * Argument for CheckData
 *   Size = number of facts + number of rules
 *   data = table of int facts and rules
 *     data[x][0] = name of fact or rule (in int)
 *     data[x][1] = -1 if fact, else type of operator
 * 	     (0 = '!', 1 = '+', 2 = '|', 3 = '^', 4 = "=>", 5 = "<=>")
 *     data[x][2] = name of rules or fact for elemsOne (0 if fact)
 *     data[x][3] = name of rules or fact for elemsTwo (0 if fact or '!' operator)
 *   look = string of int of fact to look if true or false at th end
*/
	res = 1;
//	res = CheckData(data);
//	std::out
//		<< res == -1 ? "missing data"
//		: res ? "incoherence in rules" : "Cool, Cool-cool-cool"
//		<< std::endl;
	return (res > 0 ? 1 : 0);
}
/*
	Elems	*elms[9];
	//	TEST
	//	*	create fact
	elms[0] = new Elems (85);
	elms[1] = new Elems (86);
	elms[2] = new Elems (87);
	elms[3] = new Elems (88);
	elms[4] = new Elems (89);
	//	*	create rule
	elms[5] = new Elems (100, 1, elms[0], elms[1]);
	elms[6] = new Elems (101, 4, elms[5], elms[2]);
	elms[7] = new Elems (102, 1, elms[5], elms[2]);
	elms[8] = new Elems (103, 4, elms[7], elms[4]);
	//	*	check consistance
	if (!CheckConsistenceRules(elms, 9))
	{
		std::cout << "Inconsistence" << std::endl;
		return (0);
	}
	//	*	set facts true or false
	elms[0]->setState(true);
	elms[0]->setModif(true);
	elms[1]->setState(true);
	elms[1]->setModif(true);
	//	*	Check facts
	if (!CheckConsistenceFacts(elms, 9))
	{
		std::cout << "Inconsistence fact" << std::endl;
		return (0);
	}
	//	*	answer
	std::cout << "89 is" << std::endl;
	std::cout << (elms[4]->getState() ? "true" : "false") << std::endl;
	//	TEST
*/
