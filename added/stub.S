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

   stub.i

   Put a jmp stub at the end of flash.  This is moved from APICALL.INC
   into this file which is assembled separately so the linker can take
   care of poitioning it unto the last flash word.

 */

#include <avr/io.h>
#undef FLASHEND
#include "atmel_def.h"
#include "mangled_case.h"
              .section .text
              .global stub          ; so it shows up in the symbol table
stub:
#ifdef FirstBootStart
              rjmp  api_call
#else   /* no APICALL, so just return */
              ret
#endif
              .end
