/*
 * GNUitar
 * Biquad
 * Ciulei Bogdan /Dexterus <dexterus@hackernetwork.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * $Log: biquad.h,v $
 * Revision 1.4  2005/04/06 19:34:20  fonin
 * Code lickup
 *
 * Revision 1.3  2004/10/21 11:13:45  dexterus
 * Fixed calculus error
 * Added support for any numer of channels
 * iniline support delimited to Visual C
 *
 * Revision 1.2  2003/12/28 10:16:08  fonin
 * Code lickup
 *
 * $Id: biquad.h,v 1.4 2005/04/06 19:34:20 fonin Exp $
 */


#ifndef _BIQUAD_H_
#define _BIQUAD_H_ 1


struct Biquad {
    double          a0,
                    a1,
                    a2,
                    b1,
                    b2;		/* coefficients */
    double         *mem;	/* memory for the filter , must be
				 * alocated by the caller, 4 * number of
				 * channels */
};

/*
 * Sampling rate, Center frequency, Bandwidth, Gain (decibels) 
 */
extern void     SetEqBiquad(double Fs, double Fc, double BW, double G,
			    struct Biquad *f);

/*
 * computes one sample ; because inline declared, this will be compiled in 
 * place where called works with MS Visual C . Other compilers ? 
 */

#if defined(_MSC_VER)
/* check if the compiler is Visual C or GCC so we can use inline function in C,
 * declared here */
__inline double
doBiquad(double x, struct Biquad *f, int channel)
{				
				 
    double          y,
                   *mem;
    mem = f->mem + (channel << 2);
    y = x * f->a0 + mem[0] * f->a1 + mem[1] * f->a2 + mem[2] * f->b1 +
	mem[3] * f->b2;
    mem[1] = mem[0];
    mem[0] = x;
    mem[3] = mem[2];
    mem[2] = y;
    return y;
}
#elif defined(__GNUC__)
extern __inline double   doBiquad(double x, struct Biquad *f, int channel);
#else
/* otherwise declare a standard function */
extern double   doBiquad(double x, struct Biquad *f, int channel);
#endif


#endif
