/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*   File....: conname.h                                                     */
/*   Name....: Constraint Names                                              */
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
#ifndef _CONNAME_H_
#define _CONNAME_H_

#ifndef _BOOL_H_
#error "Need to include bool.h before conname.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

enum con_name_format { CON_FORM_MAKE, CON_FORM_NAME, CON_FORM_FULL };

typedef enum con_name_format     ConNameForm;

extern void        conname_format(ConNameForm format);
extern void        conname_free(void);
/*lint -sem(       conname_set, nulterm(1), 1p) */
extern Bool        conname_set(const char* prefix);
/*lint -sem(       conname_set, @p && nulterm(@)) */
extern const char* conname_get(void);
extern void        conname_next(void);

#ifdef __cplusplus
}
#endif
#endif /* _CONNAME_H_ */
