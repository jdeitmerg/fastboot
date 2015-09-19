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

   bootload.S

   Time-stamp: <2010-01-14 18:59:04 hcz>

   Main file of Peter Danneger's AVR bootloader for use
   with the avr-gcc tools.

   (c) 2009 H. C. Zimmerer.  You may use this file and the
   accompanying files of this project for whatever you want to do with
   them provided you don't remove this copyright notice. This
   permission covers ONLY the parts which are written/changed by me,
   leaving all original conditions untouched.
   
*/
#define __SFR_OFFSET 0

              .nolist
#include <avr/io.h>
//#include "m168def.h"
              .list

/* 
   atmel_def.h contains some definitions taken from the Atmel's def
   file (which one is defined in the Makefile).  Always keep in mind
   that flash addresses taken from there are word addresses.
*/
#undef FLASHEND
#include "atmel_def.h"
              
#define byte3(x) ((x)>>16)
#define byte2(x) ((x & 0xff00)>>8)
#define byte1(x) (x & 0xff)


/* 
   Atmel's AVR assembler is case insensitive, gcc is not.
   mangled_case.h covers the cases where the representations in the
   program mix case.
*/
#include "mangled_case.h"

/* 
   This includes the program:
*/
#include "bootload.asm"


              .global api_call
