;  This file is part of fastboot, an AVR serial bootloader.
;  Copyright (C) 2008 Peter Dannegger
;  Copyright (C) 2010 Heike C. Zimmerer <hcz@hczim.de>
;
;  This program is free software: you can redistribute it and/or modify
;  it under the terms of the GNU General Public License as published by
;  the Free Software Foundation, either version 3 of the License, or
;  (at your option) any later version.
;
;  This program is distributed in the hope that it will be useful,
;  but WITHOUT ANY WARRANTY; without even the implied warranty of
;  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;  GNU General Public License for more details.
;
;  You should have received a copy of the GNU General Public License
;  along with this program.  If not, see <http://www.gnu.org/licenses/>.
;
;-------------------------------------------------------------------------
;				Send Messages
;-------------------------------------------------------------------------
;input: a0 = number of message 0 .. 3
;
SendMessage:
#if FLASHEND > 0x7FFF
	ldi	zx, hh8(/* 2* */Messages)
	out	RAMPZ, zx
#endif
	ldi	zl, lo8(/* 2* */Messages)
	ldi	zh, hi8(/* 2* */Messages)
	ldi	yl, 0
_sme1:
	add	zl, yl			; add offset to next message
	adc	zh, zerol
	XLPM	yl, z
	subi	a0, 1			; count down until message found
	brcc	_sme1
	ldi	a0, ANSWER		; first byte of message
_sme2:
	rcall	putchar
	XLPM	a0, z+
	subi	yl, 1
	brcc	_sme2
	rjmp	main_ok
;-------------------------------------------------------------------------
