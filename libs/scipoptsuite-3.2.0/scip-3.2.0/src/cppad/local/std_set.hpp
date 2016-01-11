// $Id: std_set.hpp 2910 2013-10-07 13:27:58Z bradbell $
# ifndef CPPAD_STD_SET_INCLUDED
# define CPPAD_STD_SET_INCLUDED

/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-12 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the 
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */

# include <cppad/local/define.hpp>

// needed before one can use CPPAD_ASSERT_FIRST_CALL_NOT_PARALLEL
# include <cppad/thread_alloc.hpp>

namespace CppAD { // BEGIN_CPPAD_NAMESPACE
/*!
\defgroup std_set_hpp std_set.hpp
\{
\file std_set.hpp
Two constant standard sets (currently used for concept checking).
*/

/*!
A standard set with one element.
*/
template <class Scalar>
const std::set<Scalar>& one_element_std_set(void)
{	CPPAD_ASSERT_FIRST_CALL_NOT_PARALLEL;
	static std::set<Scalar> one;
	if( one.empty() )
		one.insert(1);
	return one;
}  
/*!
A standard set with a two elements.
*/
template <class Scalar>
const std::set<Scalar>& two_element_std_set(void)
{	CPPAD_ASSERT_FIRST_CALL_NOT_PARALLEL;
	static std::set<Scalar> two;
	if( two.empty() )
	{	two.insert(1);
		two.insert(2);
	}
	return two;
}  

/*! \} */
} // END_CPPAD_NAMESPACE
# endif
