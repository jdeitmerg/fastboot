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
;------------------------------	check, if watchdog active ----------------
	wdr
	xin	a0, WDTCSR
	ori	a0, 1<<WDCE				; change enable
	ldi	a1, 1<<WDE^1<<WDP2^1<<WDP1^1<<WDP0	; 2s
	xout	WDTCSR, a0
	sbrc	a0, WDE
	xout	WDTCSR, a1
;-------------------------------------------------------------------------

