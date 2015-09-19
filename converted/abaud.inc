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
;			automatic baud rate detection
;-------------------------------------------------------------------------
;
; recognize any byte,
; which contain 1 * bit time low, followed by 4 * bit times low
;                      ____    __    __ __             ____
;e.g. recognize 0x0D:      |__|  |__|  |  |__|__|__|__|
;                          0  1  2  3     5           9
;                                1*T               4*T
;
#define  TOLERANCE 3
#define  MINTIME 90
;
abaud:
	ldi	a0, byte3(BootDelay / 6)
_aba1:
	movw	zl, zerol	; cause first try invalid
_aba2:
	movw	yl, zl
	movw	zl, zerol	; z = 0x0000
_aba3:
	sbiw	twl, 1		;2
	sbci	a0, 0			;1
	SKIP_RXD_0			;1	wait until RXD = 0
	brne	_aba3			;2 = 6
	breq	timeout
_aba4:
	sbiw	yl, 1		;2
	adiw	zl, 4		;2	count bit time
	brcs	timeout			;1	time to long
	SKIP_RXD_1			;1 	wait until RXD = 1
	rjmp	_aba4			;2 = 8
;------------------------------ correction for USB dongle !!! ------------
	mov	r0, zh
_aba5:
	asr	yl			; shift signed !
	lsr	r0
	brne	_aba5
;-------------------------------------------------------------------------
	sbiw	yl, TOLERANCE
	adiw	yl, 2 * TOLERANCE
	brcc	_aba2			; outside tolerance
	cpi	zl, MINTIME
	cpc	zh, zerol
	brcs	_aba2			; time to short
	sbiw	zl, 2*UartLoop-1	; rounding, -loop time
	lsr	zh			; /2
	ror	zl
	movw	baudl, zl
;inlined	ret
;-------------------------------------------------------------------------
