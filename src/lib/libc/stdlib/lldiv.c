/*
 * Copyright(C) 2011-2016 Pedro H. Penna <pedrohenriquepenna@gmail.com>
 *
 * This file is part of Nanvix.
 *
 * Nanvix is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * Nanvix is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Nanvix. If not, see <http://www.gnu.org/licenses/>.
 */

/*
 * Copyright (C) 1991, 1996 Free Software Foundation, Inc.
 *
 * This file is part of the GNU C Library.
 *
 * The GNU C Library free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The GNU C Library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/**
 * @file
 *
 * @brief lldiv() implementation.
 */

#include <stdlib.h>

/**
 * @brief Computes quotient and remainder of a long long division.
 *
 * @param numer Numerator.
 * @param denom Denominator.
 *
 * @returns A structure of type lldiv_t, comprising both the quotient and the
 *          remainder.
 */
lldiv_t lldiv (long long int numer, long long int denom)
{
	lldiv_t result;

	result.quot = numer/denom;
	result.rem = numer%denom;

	/*
	 * The ANSI standard says that |QUOT| <= |NUMER / DENOM|, where
	 * NUMER / DENOM is to be computed in infinite precision.  In
	 * other words, we should always truncate the quotient towards
	 * zero, never -infinity.  Machine division and remainer may
	 * work either way when one or both of NUMER or DENOM is
	 * negative.  If only one is negative and QUOT has been
	 * truncated towards -infinity, REM will have the same sign as
	 * DENOM and the opposite sign of NUMER; if both are negative
	 * and QUOT has been truncated towards -infinity, REM will be
	 * positive (will have the opposite sign of NUMER).  These are
	 * considered `wrong'.  If both are NUM and DENOM are positive,
	 * RESULT will always be positive.  This all boils down to: if
	 * NUMER >= 0, but REM < 0, we got the wrong answer.  In that
	 * case, to get the right answer, add 1 to QUOT and subtract
	 * DENOM from REM.
	 */
	if (numer >= 0 && result.rem < 0)
	{
		++result.quot;
		result.rem -= denom;
	}

	return (result);
}
