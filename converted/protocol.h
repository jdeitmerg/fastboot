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
 
//*************************************************************************
//				Protocol definitions
//-------------------------------------------------------------------------
#define	COMMAND		0xA5		// Command sequence start
#define ESCAPE		COMMAND

#define	CONNECT		0xA6		// connection established
#define	BADCOMMAND	0xA7		// command not supported
#define	ANSWER		0xA8		// followed by length byte
#define	CONTINUE	0xA9
#define	SUCCESS		0xAA
#define	FAIL		0xAB

#define	ESC_SHIFT	0x80		// offset escape char
#define	PROGEND		ESC_SHIFT
//-------------------------------------------------------------------------
//				APICALL definitions
//-------------------------------------------------------------------------
#define API_PROG_PAGE	0x81		// copy one Page from SRAM to Flash

#define API_SUCCESS	0x80		// success
#define API_ERR_FUNC	0xF0		// function not supported
#define API_ERR_RANGE	0xF1		// address inside bootloader
#define API_ERR_PAGE	0xF2		// address not page aligned
//-------------------------------------------------------------------------
