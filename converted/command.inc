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
;				Receive commands
;-------------------------------------------------------------------------
;00	get bootloader revision
;01	get buffer size
;02	get target signature
;03	get user flash size
;04	program flash
;05	start application
;06	check crc
;07	verify flash
;-------------------------------------------------------------------------
main_ok:
	ldi	a0, SUCCESS
_cex1:
	rcall	putchar
_cex2:
	rcall	getchar
	brne	_cex2			; ignore until COMMAND
_cex3:
	rcall	getchar
	breq	_cex3			; ignore further COMMAND
#if FLASHEND > 0x7FFF
	ldi	zx, 0
#endif
	movw	zl, zerol      ; Z = 0x0000,
	clt				; T = 0 (for program, verify)
	cpi	a0, 4
	brcs	SendMessage		; command 0 ... 3
	breq	program			; command 4
	cpi	a0, 5
	breq	timeout			; command 5
	cpi	a0, 7
#if VERIFY
	breq	VerifyFlash		; command 7
#endif
	ldi	a0, BADCOMMAND
;-------------------------------------------------------------------------
#if CRC
	brcc	_cex1			; command >7
;-------------------------------------------------------------------------
CheckCRC:				; command 6
	rcall	getchar			; read CRC low
	rcall	getchar			; read CRC high
	or	crcl, crch		; now CRC = 0x0000 ?
	breq	main_ok			; yes
	movw	crcl, zerol	; clear CRC
#else
	rjmp	_cex1
#endif
;-------------------------------------------------------------------------
main_error:
	ldi	a0, FAIL
	rjmp	_cex1
;-------------------------------------------------------------------------
timeout:				; command 5
	out	STX_DDR, zerol
	out	STX_PORT, zerol
#if SRX_PORT != STX_PORT
	out	SRX_PORT, zerol
#endif
#if FlashEnd > 0x0fff
        jmp Application
#else
	rjmp	Application		; run application
#endif
;-------------------------------------------------------------------------
#include "message.inc" // command 0 ... 3
;-------------------------------------------------------------------------
#if VERIFY
#include "verify.inc" // command 7
#endif
;-------------------------------------------------------------------------
#ifdef FirstBootStart
#include "progmega.inc" // mega with bootstart fuse set
#else
#include "progtiny.inc" // tiny, mega without RWW section
#endif
;-------------------------------------------------------------------------
