/*
 * This file is part of fastboot, an AVR serial bootloader.
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
 
#define  SIGNATURE_000 0x1e
#define  SIGNATURE_001 0x93
#define  SIGNATURE_002 0x07
#define  BOOTRST 0	// Select Reset Vector
#define  BOOTSZ0 1	// Select Boot Size
#define  BOOTSZ1 2	// Select Boot Size
#define  FLASHEND 0x0fff	// Note: Word address
#define  SRAM_START 0x0060
#define  SRAM_SIZE 1024
; ***** BOOTLOADER DECLARATIONS ******************************************
#define  PAGESIZE 32
#define  FIRSTBOOTSTART 0xf80
#define  SECONDBOOTSTART 0xf00
#define  THIRDBOOTSTART 0xe00
#define  FOURTHBOOTSTART 0xc00
#define  SMALLBOOTSTART FIRSTBOOTSTART
#define  LARGEBOOTSTART FOURTHBOOTSTART
