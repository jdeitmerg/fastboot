/*
 * This file is part of fastboot, an AVR serial bootloader.
 * Copyright (C) 2008 Peter Dannegger
 * Copyright (C) 2010 Heike C. Zimmerer <hcz@hczim.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
/*

  mangled_case.h

  Time-stamp: <2010-01-14 15:59:07 hcz>

   (c) 2009 H. C. Zimmerer.  You may use this file and the
   accompanying files of this project for whatever you want to do with
   them provided you don't remove this copyright notice. This
   permission covers ONLY the parts which are written/changed by me,
   leaving all original conditions untouched.

*/

#define Flashend FLASHEND
#define FlashEnd FLASHEND
#define RamEnd RAMEND
#define ProgBuff PROGBUFF
#define ProgbuffEnd PROGBUFFEND
#define PageSize PAGESIZE
#define Version VERSION
#define program Program
#ifdef FIRSTBOOTSTART
# define FirstBootStart FIRSTBOOTSTART
#endif
#ifdef SECONDBOOTSTART
# define SecondBootStart SECONDBOOTSTART
#endif


#define xl r26
#define xh r27
#define yl r28
#define yh r29
#define zl r30
#define zh r31
