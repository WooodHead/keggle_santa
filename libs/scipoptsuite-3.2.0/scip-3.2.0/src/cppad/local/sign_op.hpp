/* $Id: sign_op.hpp 2910 2013-10-07 13:27:58Z bradbell $ */
# ifndef CPPAD_SIGN_OP_INCLUDED
# define CPPAD_SIGN_OP_INCLUDED

/* --------------------------------------------------------------------------
CppAD: C++ Algorithmic Differentiation: Copyright (C) 2003-13 Bradley M. Bell

CppAD is distributed under multiple licenses. This distribution is under
the terms of the 
                    Eclipse Public License Version 1.0.

A copy of this license is included in the COPYING file of this distribution.
Please visit http://www.coin-or.org/CppAD/ for information on other licenses.
-------------------------------------------------------------------------- */


namespace CppAD { // BEGIN_CPPAD_NAMESPACE
/*!
\defgroup sign_op_hpp sign_op.hpp
\{
\file sign_op.hpp
Forward and reverse mode calculations for z = sign(x).
*/

/*!
Compute forward mode Taylor coefficient for result of op = SignOp.

The C++ source code corresponding to this operation is
\verbatim
	z = sign(x)
\endverbatim

\copydetails forward_unary1_op
*/
template <class Base>
inline void forward_sign_op(
	size_t q           ,
	size_t p           ,
	size_t i_z         ,
	size_t i_x         ,
	size_t nc_taylor   , 
	Base*  taylor      )
{
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(SignOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(SignOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( i_x < i_z );
	CPPAD_ASSERT_UNKNOWN( p < nc_taylor );
	CPPAD_ASSERT_UNKNOWN( q <= p );

	// Taylor coefficients corresponding to argument and result
	Base* x = taylor + i_x * nc_taylor;
	Base* z = taylor + i_z * nc_taylor;

	if( q == 0 )
	{	z[0] = sign(x[0]);
		q++;
	}
	for(size_t j = q; j <= p; j++)
		z[j] = Base(0.);
}

/*!
Compute zero order forward mode Taylor coefficient for result of op = SignOp.

The C++ source code corresponding to this operation is
\verbatim
	z = sign(x)
\endverbatim

\copydetails forward_unary1_op_0
*/
template <class Base>
inline void forward_sign_op_0(
	size_t i_z         ,
	size_t i_x         ,
	size_t nc_taylor   , 
	Base*  taylor      )
{

	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(SignOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(SignOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( i_x < i_z );
	CPPAD_ASSERT_UNKNOWN( 0 < nc_taylor );

	// Taylor coefficients corresponding to argument and result
	Base x0 = *(taylor + i_x * nc_taylor);
	Base* z = taylor + i_z * nc_taylor;

	z[0] = sign(x0);
}
/*!
Compute reverse mode partial derivatives for result of op = SignOp.

The C++ source code corresponding to this operation is
\verbatim
	z = sign(x)
\endverbatim

\copydetails reverse_unary1_op
*/

template <class Base>
inline void reverse_sign_op(
	size_t      d            ,
	size_t      i_z          ,
	size_t      i_x          ,
	size_t      nc_taylor    , 
	const Base* taylor       ,
	size_t      nc_partial   ,
	Base*       partial      )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(SignOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(SignOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( i_x < i_z );
	CPPAD_ASSERT_UNKNOWN( d < nc_taylor );
	CPPAD_ASSERT_UNKNOWN( d < nc_partial );

	// nothing to do because partials of sign are zero
	return;
}

/*! \} */
} // END_CPPAD_NAMESPACE
# endif
