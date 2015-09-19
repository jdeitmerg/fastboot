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
;				Check password
;-------------------------------------------------------------------------
	ldi	yl, 10			; try it 10 times
#if FLASHEND > 0x7FFF
	ldi	a0, hh8(/* 2* */Password)
	out	RAMPZ, a0
#endif
checkpwd:
	ldi	zl, lo8(/* 2* */Password)
	ldi	zh, hi8(/* 2* */Password)
_cpw2:
	XLPM	r0, z+
	tst	r0
	breq	_cpw3			; end if zero byte
	rcall	getchar
	cp	r0, a0
	breq	_cpw2			; compare next byte
	dec	yl			; count down wrong compares
	breq	timeout
	rjmp	checkpwd		; try again
_cpw3:
;-------------------------------------------------------------------------
