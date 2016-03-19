#ifndef CLASS_STORAGE_HPP
# define CLASS_STORAGE_HPP

# include "Expert_system.hpp"

class Storage {
	public:
		Storage(void);
		Storage(std::vector<std::string> array);
		Storage(Storage const &copy);
		Storage &operator=(Storage const &copy);

		~Storage(void);

		int						Check(void);
		std::vector<std::string>	getArray(void) const;

	private:
		std::vector<std::string> 	_Array;
		std::vector<int**>			_Val;
		int							**_Keys;
};

#endif
