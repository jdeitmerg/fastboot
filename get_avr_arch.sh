#!/bin/sh

#  This file is part of fastboot, an AVR serial bootloader.
#  Copyright (C) 2010 Heike C. Zimmerer <hcz@hczim.de>
# 
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
# 
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
# 
#  You should have received a copy of the GNU General Public License
#  along with this program.  If not, see <http://www.gnu.org/licenses/>.



# Get AVR architecture
#
# 2010-08-19: now runs gawk instead of awk.  WinAVR only knows about gawk.
 
usage(){
    echo "\
Usage: $pname -mmcu=<mcutype> <objfile.o>
Function: return AVR architecture (the
  architecture which avr-gcc uses for linking) as
  string on stdout.  
  <mcutype> may be any mcu type accepted by avr-gcc.
  <objfile.o> must exist but may be empty.
Opts: 
  -x   Script debug (set -x)"
    exit
}

pname="${0##*/}"
while getopts m:-:hx argv; do
    case $argv in
	m) mcu="$OPTARG";;
	x) set -x;;
	*) usage;;
    esac
done
shift $((OPTIND-1))

case "$#" in
    0) echo >&2 "$pname: missing object file"; exit 1;;
    1) ;;
    *) echo >&2 "$pname: Too many arguments: $*"; exit 1;;
esac

magic=";#magic1295671ghkl-."
# call gcc, asking it for the command line which it would use for
# linking:
set -- $(avr-gcc -m"$mcu" -### "$1" -o "$magic" 2>&1 \
         | gawk '/^avr-gcc:/||/ld.*'"$magic"'.*"-lgcc"/')

if [ "$1" = "avr-gcc:" ]; then
    # we have an error message from gcc:
    echo "$*"
    exit 1
fi

# retrieve architecture argument from gcc's commandline (the argument
# which follows '"-m"'):
while [ -n "$2" ]; do
    if [ "$1" = '"-m"' ]; then
	eval echo $2		# eval: remove quotes
	exit 0
    fi
    shift
done
echo >&2 "\
$pname: Could not find an architecture in avr-gcc's internal ld command line"
exit 1
