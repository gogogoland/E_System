/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Elems.Interface.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 17:01:35 by tbalea            #+#    #+#             */
/*   Updated: 2016/02/09 21:14:34 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ELEMS_INTERFACE_HPP
# define ELEMS_INTERFACE_HPP

# include "Expert_system.hpp"

class Elems;

class	InterfaceElems {
	public:
		//	Destructor
		virtual ~InterfaceElems() {};
		//	Getter
		virtual int		getName(void) const = 0;
		virtual bool	getModif(void) const = 0;
		virtual bool	getState(void) const = 0;
		virtual int		getOperator(void) const = 0;
		virtual Elems	*getElemsOne(void) const = 0;
		virtual Elems	*getElemsTwo(void) const = 0;
		//	Setter
		virtual void	setName(int name) = 0;
		virtual void	setModif(bool modif) = 0;
		virtual void	setState(bool state) = 0;
		virtual void	setOperator(int optor) = 0;
		virtual void	setElemsOne(Elems *elem1) = 0;
		virtual void	setElemsTwo(Elems *elem2) = 0;
		//	Function
		virtual bool	applyRules(void) = 0;
	protected:
		//	Function
		//	*	for applyRules
		virtual bool	applyNEG(Elems *elem1, Elems *v) = 0;
		virtual bool	applyAND(Elems *elem1, Elems *elem2) = 0;
		virtual bool	applyOR(Elems *elem1, Elems *elem2) = 0;
		virtual bool	applyXOR(Elems *elem1, Elems *elem2) = 0;
		virtual bool	applyIMP(Elems *elem1, Elems *elem2) = 0;
		virtual bool	applySSI(Elems *elem1, Elems *elem2) = 0;
};

#endif
