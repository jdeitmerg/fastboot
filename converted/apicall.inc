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
;------------------------------------------------------------------------
;		API-Call to program Flash from application 
;------------------------------------------------------------------------
;
;input:	 R22 = command		a0 = r22
;	 X = source
;	 R21, Z = destination	zx = r21
;output: R22 = return code
;use:    R0, R1, R21, R22, R23, X, Z
;
api_call:
	in	a1, SREG
	cli
	cpi	a0, API_PROG_PAGE
	ldi	a0, API_ERR_FUNC
	brne	_apc1
	rcall	prog_page
	ldi	a0, API_SUCCESS
	brcs	_apc1			; CY = 1: o.k.
	ldi	a0, API_ERR_RANGE
_apc1:
	out	SREG, a1
	ret
;-------------------------------------------------------------------------
/* 	.org	Flashend */  ; removed by _conv.awk
/* 	rjmp	api_call */  ; removed by _conv.awk
;-------------------------------------------------------------------------

