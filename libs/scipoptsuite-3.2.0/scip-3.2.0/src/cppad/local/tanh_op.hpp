/* $Id: tanh_op.hpp 2910 2013-10-07 13:27:58Z bradbell $ */
# ifndef CPPAD_TANH_OP_INCLUDED
# define CPPAD_TANH_OP_INCLUDED

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
\defgroup tanh_op_hpp tanh_op.hpp
\{
\file tanh_op.hpp
Forward and reverse mode calculations for z = tanh(x).
*/


/*!
Compute forward mode Taylor coefficient for result of op = TanOp.

The C++ source code corresponding to this operation is
\verbatim
	z = tanh(x)
\endverbatim
The auxillary result is
\verbatim
	y = tanh(x)^2
\endverbatim
The value of y, and its derivatives, are computed along with the value
and derivatives of z.

\copydetails forward_unary2_op
*/
template <class Base>
inline void forward_tanh_op(
	size_t q           ,
	size_t p           ,
	size_t i_z         ,
	size_t i_x         ,
	size_t nc_taylor   , 
	Base*  taylor      )
{	
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(TanOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(TanOp) == 2 );
	CPPAD_ASSERT_UNKNOWN( i_x + 1 < i_z );
	CPPAD_ASSERT_UNKNOWN( p < nc_taylor );
	CPPAD_ASSERT_UNKNOWN( q <= p );

	// Taylor coefficients corresponding to argument and result
	Base* x = taylor + i_x * nc_taylor;
	Base* z = taylor + i_z * nc_taylor;
	Base* y = z      -       nc_taylor;

	size_t k;
	if( q == 0 )
	{	z[0] = tanh( x[0] );
		y[0] = z[0] * z[0];
		q++;
	}
	for(size_t j = q; j <= p; j++)
	{	Base base_j = static_cast<Base>(j);

		z[j] = x[j];
		for(k = 1; k <= j; k++)
			z[j] -= Base(k) * x[k] * y[j-k] / base_j;

		y[j] = z[0] * z[j];
		for(k = 1; k <= j; k++)
			y[j] += z[k] * z[j-k];
	}
}


/*!
Compute zero order forward mode Taylor coefficient for result of op = TanOp.

The C++ source code corresponding to this operation is
\verbatim
	z = tanh(x)
\endverbatim
The auxillary result is
\verbatim
	y = cos(x)
\endverbatim
The value of y is computed along with the value of z.

\copydetails forward_unary2_op_0
*/
template <class Base>
inline void forward_tanh_op_0(
	size_t i_z         ,
	size_t i_x         ,
	size_t nc_taylor   , 
	Base*  taylor      )
{
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(TanOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(TanOp) == 2 );
	CPPAD_ASSERT_UNKNOWN( i_x + 1 < i_z );
	CPPAD_ASSERT_UNKNOWN( 0 < nc_taylor );

	// Taylor coefficients corresponding to argument and result
	Base* x = taylor + i_x * nc_taylor;
	Base* z = taylor + i_z * nc_taylor;  // called z in documentation
	Base* y = z      -       nc_taylor;  // called y in documentation

	z[0] = tanh( x[0] );
	y[0] = z[0] * z[0];
}

/*!
Compute reverse mode partial derivatives for result of op = TanOp.

The C++ source code corresponding to this operation is
\verbatim
	z = tanh(x)
\endverbatim
The auxillary result is
\verbatim
	y = cos(x)
\endverbatim
The value of y is computed along with the value of z.

\copydetails reverse_unary2_op
*/

template <class Base>
inline void reverse_tanh_op(
	size_t      d            ,
	size_t      i_z          ,
	size_t      i_x          ,
	size_t      nc_taylor    , 
	const Base* taylor       ,
	size_t      nc_partial   ,
	Base*       partial      )
{
	// check assumptions
	CPPAD_ASSERT_UNKNOWN( NumArg(TanOp) == 1 );
	CPPAD_ASSERT_UNKNOWN( NumRes(TanOp) == 2 );
	CPPAD_ASSERT_UNKNOWN( i_x + 1 < i_z );
	CPPAD_ASSERT_UNKNOWN( d < nc_taylor );
	CPPAD_ASSERT_UNKNOWN( d < nc_partial );

	// Taylor coefficients and partials corresponding to argument
	const Base* x  = taylor  + i_x * nc_taylor;
	Base* px       = partial + i_x * nc_partial;

	// Taylor coefficients and partials corresponding to first result
	const Base* z  = taylor  + i_z * nc_taylor; // called z in doc
	Base* pz       = partial + i_z * nc_partial;

	// Taylor coefficients and partials corresponding to auxillary result
	const Base* y  = z  - nc_taylor; // called y in documentation
	Base* py       = pz - nc_partial;

	size_t j = d;
	size_t k;
	Base base_two(2);
	while(j)
	{
		px[j]   += pz[j];
		pz[j]   /= Base(j);
		for(k = 1; k <= j; k++)
		{	px[k]   -= pz[j] * y[j-k] * Base(k);
			py[j-k] -= pz[j] * x[k] * Base(k);
		}
		for(k = 0; k < j; k++)
			pz[k] += py[j-1] * z[j-k-1] * base_two;
	
		--j;
	}
	px[0] += pz[0] * (Base(1) - y[0]);
}

/*! \} */
} // END_CPPAD_NAMESPACE
# endif
