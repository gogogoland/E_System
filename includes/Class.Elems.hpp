/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Class.Elems.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbalea <tbalea@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/29 21:58:36 by tbalea            #+#    #+#             */
/*   Updated: 2016/03/12 12:18:59 by tbalea           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLASS_ELEMS_HPP
# define CLASS_ELEMS_HPP

# include "Interface.Elems.hpp"

/*
 *	Operator :
 *	*	-1 = No operator
 *	*	0 = operator '!'
 *	*	1 = operator '+'
 *	*	2 = operator '|'
 *	*	3 = operator '^'
 *	*	4 = operator "=>"
 *	*	5 = operator "<=>"
*/

class Elems : public InterfaceElems {
	public:
		//	Constructor
		Elems(void);
		Elems(int name);
		Elems(int name, bool state);
		Elems(int name, int op, Elems *e1, Elems *e2);
		Elems(int name, bool state, int op, Elems *e1, Elems *e2);

		//	Destructor
		~Elems(void);

		//	Copy
		Elems(Elems const & copy);
		Elems & operator=(Elems const & copy);

		//	Getter
		int					getName(void) const;
		bool				getState(void) const;
		bool				getModif(void) const;
		Elems				*getElemsOne(void) const;
		Elems				*getElemsTwo(void) const;
		int					getOperator(void) const;

		//	Setter
		void				setName(int name);
		void				setState(bool state);
		void				setModif(bool modif);
		void				setOperator(int op);
		void				setElemsOne(Elems *e1);
		void				setElemsTwo(Elems *e2);

		//	Function
		bool				applyRules(void);
		bool				setToTrue(Elems *elems);
		bool				setToFalse(Elems *elems);
	private:
		bool				applyOR(Elems *elem1, Elems *elem2);
		bool				applyXOR(Elems *elem1, Elems *elem2);
		bool				applyAND(Elems *elem1, Elems *elem2);
		bool				applyNEG(Elems *elem, Elems *v);
		bool				applyIMP(Elems *elem1, Elems *elem2);
		bool				applySSI(Elems *elem1, Elems *elem2);
		//	Variable
		typedef bool		(Elems::*rules)(Elems *, Elems *);
		static const rules	apply[];
		int					_name;
		bool				_state;
		bool				_modif;
		int					_optor;
		Elems				*_elems[2];
};
# endif
