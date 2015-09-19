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
;		 		Verify User Flash
;-------------------------------------------------------------------------
;
_ver1:
#if FLASHEND > 0x7FFF
	out	RAMPZ, zx
	elpm	r0, z
	adiw	zl, 1
	adc	zx, zerol		; 24 bit addition
#else
	lpm	r0, z+
#endif
#ifndef FirstBootStart
	cpi	zl, 3
	cpc	zh, zerol
	brcs	VerifyFlash		; exclude jump to bootloader
#endif
	cpse	r0, a0
	set
VerifyFlash:
	rcall	getchar
	brne	_ver1			; not COMMAND ?
	rcall	getchar
	subi	a0, ESC_SHIFT
	brne	_ver1			; COMMMAND + not COMMAND = End
	brts	main_error		; error, Flash not equal
	rjmp	main_ok
;-------------------------------------------------------------------------
