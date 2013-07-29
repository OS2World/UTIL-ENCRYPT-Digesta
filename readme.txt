DIGEST (c) 2005, 2006 Axel Meiss

Disclaimer
The program is provided "as is" with no warranty. Use only at your own risk.


Description

The DIGEST program is a utility for creating message digests for files.
ITs main purpose is that it can be extended for new message digest algorithms
by simply creating a special Dynamic Link Library. Currently included are
the popular MD5 and SHA-1 so OS/2 users now have a native program for SHA-1.
The idea is based on JACKSUM (www.jonelo.de) which is a Java program for many
message digests. DIGEST.EXE is for use with Warp3 and does not support large
files (> 2 GB). DIGESTL.EXE is for use with Warp 4.5 which supports large
files.

Syntax
The program is called from command line this way
digest.exe  [case] <method> <file name>
digestl.exe [case] <method> <file name>

[case] is optional and will cause DIGEST to display the message digest in
lower case.
<file name> is a regular file name or the dash '-' when input will be taken
from standard input


Copyright notice

The program and its sources may be distributed freely as long as this
README.TXT and Copyright notices in the sources are preserved.


Developer notes

DIGEST and DIGESTL actually contain of two parts
1. the main program which handles file access
2. the supporting DLL which does create the message digest

The message digest calculation is done in a DLL which must follow naming
rules as this:
MD5 becomes DMD5.DLL
SHA-1 becomes DSHA1.DLL

The DLL must contain the following entry names
DIGESTINIT
DIGESTUPDATE
DIGESTRESULT

DIGESTINIT performs initialisation for the calculation
DIGESTUPDATE performs the calculation

DIGESTRESULT performs final calculations and returns the message digest as
a string consisting of hexadecimal letters

The Dynamic Link Libraries are not suited for calculating message digests
in different threads in the same process.

The program has been compiled with OpenWatcom 1.1 which is part of eComStation
version 1.1.
For compiling DIGESTL.EXE the file OS2386.LIB in library directory LIB386\OS2
must be replaced by OS2386.LIB of the Warp 4.5 Toolkit.


Questions and complaints may be sent to
toriani@hotmail.com
or
redbill@os2ecs.org



