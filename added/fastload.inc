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

  fastload.inc

  Written by Peter Dannegger, modified by H. C. Zimmerer

   Time-stamp: <2010-01-14 21:16:21 hcz>

   You may use my modifications here and in the accompanying files of
   this project for whatever you want to do with them provided you
   don't remove this copyright notice.


*/
;*************************************************************************
;*									 *
;*				AVR universal Bootloader		 *
;*									 *
;*			Author: Peter Dannegger				 *
;*									 *
;*************************************************************************
#include "fastload.h"
.list
init:
#ifndef FIRSTBOOTSTART
;        .equ    Application,init-2
#endif
	cli				; no interrupts allowed
	ldi	a0, lo8(RamEnd)	; initialize stack
	out	SPL, a0
#ifdef SPH
	ldi	a0, hi8(RamEnd)
	out	SPH, a0
#endif
	clr	zerol			; for faster clear
	clr	zeroh

#if WDTRIGGER
#include "watchdog.inc"
#endif

	IOPortInit
#if CRC
	ldi	polynoml, 0x01
	ldi	polynomh, 0xA0
#endif
;-------------------------------------------------------------------------
#include "abaud.inc" // measure baudrate
#include "password.inc" // check password
;-------------------------------------------------------------------------
connected:
	ldi	a0, CONNECT		; password recognized
#if ONEWIRE
	rcall	syncputchar		; avoid message garbage
#else
	rcall	putchar
#endif
	rcall	getchar
	brne	connected		; until COMMAND received
;-------------------------------------------------------------------------
#include "command.inc" // execute commands
#include "uart.inc" // UART subroutines
;-------------------------------------------------------------------------
Password:
.ascii "Peda", "\0", "\0" ; 'a' was recognized by ABAUD

.list
Messages:
.byte           3
.byte           VERSION>>8
.byte           VERSION&0xff
.byte  	        3
.byte           ((2*BufferSize)>>8)
.byte           ((2*BufferSize) & 0xff)
.byte  	        4
.byte           SIGNATURE_000
.byte           SIGNATURE_001
.byte           SIGNATURE_002
              .byte 4
              .byte UserFlash>>16
              .byte (UserFlash>>8) & 0xff
              .byte UserFlash & 0xff
              .align 1
;-------------------------------------------------------------------------
#if APICALL
#include "apicall.inc" // program Flash from application
#endif
;-------------------------------------------------------------------------
