/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*   File....: source.c                                                      */
/*   Name....: Source Code Printing Function                                 */
/*   Author..: Thorsten Koch                                                 */
/*   Copyright by Author, All rights reserved                                */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*
 * Copyright (C) 2001-2015 by Thorsten Koch <koch@zib.de>
 * 
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "bool.h"
#include "mshell.h"
#include "ratlptypes.h"
#include "numb.h"
#include "elem.h"
#include "tuple.h"
#include "mme.h"

void show_source(FILE* fp, const char* text, int column)
{
   int len;
   int beg;
   int end;
      
   assert(fp     != NULL);
   assert(text   != NULL);
   assert(column >= 0);

   if (column > 0)
      column--;
   
   len = strlen(text);
   beg = column - 30;
   end = column + 30;

   if (beg < 0)
   {
      end -= beg;
      beg = 0;
   }
   if (end > len)
   {
      beg -= end - len;
      end  = len;      
   }
   if (beg < 0)
      beg = 0;

   assert(beg >= 0);
   assert(end <= len);
   assert(beg <= end);

   fprintf(fp, "*** %-*s\n", end - beg, &text[beg]);
   fprintf(fp, "*** %*s^^^\n", column - beg, ""); 
}




