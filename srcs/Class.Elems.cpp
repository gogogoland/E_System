/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Class.Elems.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 21:58:36 by tbalea            #+#    #+#             */
/*   Updated: 2016/03/16 00:18:07 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "Class.Elems.hpp"

//	Variable
const Elems::rules Elems::apply[] = {
	&Elems::applyNEG,
	&Elems::applyAND,
	&Elems::applyOR,
	&Elems::applyXOR,
	&Elems::applyIMP,
	&Elems::applySSI
};

//	Constructor
Elems::Elems(void) :
	_name(0),
	_state(false),
	_modif(false),
	_optor(-1)
{
	_elems[0] = NULL;
	_elems[1] = NULL;
}

Elems::Elems(int name) :
	_name(name),
	_state(false),
	_modif(false),
	_optor(-1)
{
	_elems[0] = NULL;
	_elems[1] = NULL;
}

Elems::Elems(int name, bool state) :
	_name(name),
	_state(state),
	_modif(state),
	_optor(-1)
{
	_elems[0] = NULL;
	_elems[1] = NULL;
}

Elems::Elems(int name, int op, Elems *e1, Elems *e2) :
	_name(name),
	_state(false),
	_modif(false),
	_optor(op)
{
	_elems[0] = e1;
	_elems[1] = e2;
}

Elems::Elems(int name, bool state, int op, Elems *e1, Elems *e2) :
	_name(name),
	_state(state),
	_modif(state),
	_optor(op)
{
	_elems[0] = e1;
	_elems[1] = e2;
}

//	Destructor
Elems::~Elems(void)
{
	if (this->_elems[0])
		delete this->_elems[0];
	if (this->_elems[1])
		delete this->_elems[1];
}

//	Copy
Elems::Elems(Elems const & copy)
{
	*this = copy;
}

Elems & Elems::operator=(Elems const & copy)
{
	if (this != & copy)
	{
		this->_name = copy.getName();
		this->_state = copy.getState();
		this->_modif = copy.getModif();
		this->_optor = copy.getOperator();
		this->_elems[0] = copy.getElemsOne();
		this->_elems[1] = copy.getElemsTwo();
	}
	return *this;
}

//	Getter
int		Elems::getName(void) const
{
	return (this->_name);
}

bool	Elems::getState(void) const
{
	return (this->_state);
}

bool	Elems::getModif(void) const
{
	return (this->_modif);
}

Elems	*Elems::getElemsOne(void) const
{
	return (this->_elems[0]);
}

Elems	*Elems::getElemsTwo(void) const
{
	return (this->_elems[1]);
}

int		Elems::getOperator(void) const
{
	return (this->_optor);
}

//	Setter
void	Elems::setName(int name)
{
	this->_name = name;
}

void	Elems::setState(bool state)
{
	this->_state = state;
}

void	Elems::setModif(bool modif)
{
	this->_modif = modif;
}

void	Elems::setOperator(int op)
{
	this->_optor = op;
}

void	Elems::setElemsOne(Elems *e1)
{
	this->_elems[0] = e1;
}

void	Elems::setElemsTwo(Elems *e2)
{
	this->_elems[1] = e2;
}

//	Functions
//	*	Verify Elems and Apply rule
bool	Elems::applyRules(void)
{
	if (this->_optor < 0)
		return (true);
	if (this->_elems[0]
			&& this->_elems[0]->getName() > 90
			&& !this->_elems[0]->getModif())
	{
		if (!this->_elems[0]->applyRules())
			return (false);
	}
	if (this->_optor != 4
			&& this->_elems[1]
			&& this->_elems[1]->getName() > 90
			&& !this->_elems[1]->getModif())
	{
		if (!this->_elems[1]->applyRules())
			return (false);
	}
	return ((this->*(this->apply[this->_optor]))(this->_elems[0], this->_elems[1]));
}

//	Functions
//	Set Elems to false (used for "!")
bool	Elems::setToFalse(Elems *elems)
{
	//	if !OR or !XOR
	if (elems->getOperator() == 2 || elems->getOperator() == 3)
	{
		if (!setToFalse(elems->getElemsTwo()))
			return (false);
		if (!setToFalse(elems->getElemsOne()))
			return (false);
	}
	//	if !OR or !AND
	if (elems->getOperator() == 2 || elems->getOperator() == 1)
	{
		if (!setToFalse(elems->getElemsTwo()) || !setToFalse(elems->getElemsOne()))
			return (false);
	}
	//	if !XOR to do ?
	//	if !NEG
	if (elems->getOperator() == 0)
	{
		if (elems->getElemsOne()->getState())
			return (false);
		elems->getElemsOne()->setModif(true);
		if (setToTrue(elems->getElemsOne()))
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

//	*	Set Elems to true
bool	Elems::setToTrue(Elems *elems)
{
	//	if OR or XOR
	if (elems->getOperator() == 2 || elems->getOperator() == 3)
	{
		if (!setToTrue(elems->getElemsTwo()))
			return (false);
		if (!setToTrue(elems->getElemsOne()))
			return (false);
	}
	//	if OR or AND
	if (elems->getOperator() == 2 || elems->getOperator() == 1)
	{
		if (!setToTrue(elems->getElemsTwo()) || !setToTrue(elems->getElemsOne()))
			return (false);
	}
	//	if NEG
	if (elems->getOperator() == 0)
	{
		if (elems->getElemsOne()->getState())
			return (false);
		elems->getElemsOne()->setModif(true);
		if (!setToFalse(elems->getElemsOne()))
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

//	*	List of operator
//	*	*	operator '|'
bool	Elems::applyOR(Elems *f1, Elems *f2)
{
	if (f1->getState() || f2->getState())
	{
		if (!this->_state && this->_modif)
			return (false);
		this->_state = true;
		this->_modif = true;
	}
	else
	{
		this->_state = false;
		if (this->_modif)
			return (false);
	}
	return (true);
}

//	*	*	operator '^'
bool	Elems::applyXOR(Elems *f1, Elems *f2)
{
	if (f1->getState() != f2->getState())
	{
		if (!this->_state && this->_modif)
			return (false);
		this->_state = true;
		this->_modif = true;
	}
	else
	{
		this->_state = false;
		if (this->_modif)
			return (false);
	}
	return (true);
}

//	*	*	operator '&'
bool	Elems::applyAND(Elems *f1, Elems *f2)
{
	if (f1->getState() && f2->getState())
	{
		if (!this->_state && this->_modif)
			return (false);
		this->_state = true;
		this->_modif = true;
	}
	else
	{
		this->_state = false;
		if (this->_modif)
			return (false);
	}
	return (true);
}

//	*	*	operator '!'
bool	Elems::applyNEG(Elems *f, Elems *v)
{
	(void)v;

	if ((f->getState() && this->_state)
			|| (!f->getState() && !this->_state && this->_modif))
		return (false);
	if (!f->getState())
		this->_state = true;
	this->_modif = true;
	return (true);
}

//	*	*	operator "=>"
bool	Elems::applyIMP(Elems *f1, Elems *f2)
{
	if (f1->getState())
	{
		if (!f2->getState() && f2->getModif())
			return (false);
		if (!setToTrue(f2))
			return (false);
		f2->setModif(true);
		this->_modif = true;
		this->_state = true;
	}
	return (true);
}

//	*	*	operator "<=>"
bool	Elems::applySSI(Elems *f1, Elems *f2)
{
	if (f1->getState() == f2->getState())
	{
		this->_modif = true;
		this->_state = true;
		return (true);
	}
	else if (f1->getModif() != f2->getModif())
	{
		this->_modif = true;
		this->_state = false;
		if (f1->getModif())
		{
			if (!setToTrue(f2))
				return (false);
			this->_state = true;
			return (true);
		}
		else if (f2->getModif())
		{
			if (!setToTrue(f1))
				return (false);
			this->_state = true;
			return (true);
		}
	}
	return (false);
}
