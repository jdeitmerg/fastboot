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
 
/*

        bootload.template.x and bootload.x

         Time-stamp: <2010-01-14 21:22:26 hcz>

        Linker script for Peter Dannegger's bootloader.  Always make
        sure you edit bootload.template.x.  Any changes made to
        bootload.x will be overwritten during the next make.

        Symbols enclosed in @ will be replaced when bootload.x is
        generated (see sed part in Makefile).

*/


OUTPUT_FORMAT("elf32-avr","elf32-avr","elf32-avr")
OUTPUT_ARCH(@ARCH@)
MEMORY
{
  text      (rx)   : ORIGIN = @LOADER_START@, LENGTH = @STUB_OFFSET@ + 2
  bss       (rw!x) : ORIGIN = 0x8000000 + @RAM_START@, LENGTH = @RAM_SIZE@
}


/* PHDRS { stub PT_LOAD ; } */
SECTIONS
{
  .bss : { *(.bss) } > bss 
  . = @LOADER_START@ ;
  .text : { 
    bootload.o(.text) 
    /* place a jump to api_call at the very end: */
    . = @STUB_OFFSET@ ;
    stub.o(.text)
  }

 /* Stabs and DWARF debugging sections, taken from 'avr-ld --verbose'  */
  .stab 0 : { *(.stab) }
  .stabstr 0 : { *(.stabstr) }
  .stab.excl 0 : { *(.stab.excl) }
  .stab.exclstr 0 : { *(.stab.exclstr) }
  .stab.index 0 : { *(.stab.index) }
  .stab.indexstr 0 : { *(.stab.indexstr) }
  .comment 0 : { *(.comment) }
  /* DWARF debug sections.
     Symbols in the DWARF debugging sections are relative to the beginning
     of the section so we begin them at 0.  */
  /* DWARF 1 */
  .debug          0 : { *(.debug) }
  .line           0 : { *(.line) }
  /* GNU DWARF 1 extensions */
  .debug_srcinfo  0 : { *(.debug_srcinfo) }
  .debug_sfnames  0 : { *(.debug_sfnames) }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  0 : { *(.debug_aranges) }
  .debug_pubnames 0 : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     0 : { *(.debug_info) *(.gnu.linkonce.wi.*) }
  .debug_abbrev   0 : { *(.debug_abbrev) }
  .debug_line     0 : { *(.debug_line) }
  .debug_frame    0 : { *(.debug_frame) }
  .debug_str      0 : { *(.debug_str) }
  .debug_loc      0 : { *(.debug_loc) }
  .debug_macinfo  0 : { *(.debug_macinfo) }
}
