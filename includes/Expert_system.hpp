#ifndef EXPERT_SYSTEM_HPP
# define EXPERT_SYSTEM_HPP

# include <fstream>
# include <iostream>
# include <vector>
# include <cstring>
# include <map>

# include "Class.Elems.hpp"
# include "Class.Storage.hpp"
class Elems;

int			TreatData(std::vector<int **> vect, int *solve);
int			**function_to_add(const char *get, size_t *name);

#endif /* EXPERT_SYSTEM_HPP */
