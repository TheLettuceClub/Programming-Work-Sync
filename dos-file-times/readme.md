Project overview:
The goal of this program is to determine the most recently modified file on a given filesystem. Despite the use of C++17 headers, it is actually targeted at retro systems via DJGPP.


Installation Instructions:
Download the relevant executable for your planned operating system.
    For modern Windows: fsmod-w10.exe
    For Windows 9x/3.x and DOS: fsmodw9x.exe
    For DOS: also download CWSDPMI.exe, this is required.
    For other OSes: See compiliation instructions, below
Place the executable into the directory you wish to scan
run the program, see usage instructions.


Usage Instructions:
running the executable with no arguments makes it print the relative path and modification time (in computer format) of every file it scans. If this is not desired, pass the "-m" parameter and such output will be muted.
Whenever the program finds a new "most recent" file, its relative path and modification time (in human readable format) is printed. This is not mutable.
At the end of the scan, it will print the most recent file's info, to make sure you see it :)
IMPORTANT NOTE: This program will scan every file in every folder it can see from where its ran. This will take a lot of time, and put a decent amount of stress on the system. Don't use this on a hard drive thats about to kick the bucket!


Compilation instructions:
On modern Windows/other OSes:
    Compile it with your favorite compiler in whatever way you see fit. Compiler must support C++17.

On Windows 9x:
    1) install DJGPP
        a) from any DJGPP mirror (available via http://www.delorie.com/djgpp/getting.html), download the following
            v2/djdev205.zip
            v2/faq230b.zip
            v2gnu/bnu2351b.zip
            v2gnu/gcc122b.zip
            v2gnu/gpp122b.zip
            v2gnu/mak44b.zip
        b) setup DJGPP according to its instructions, I recommend following the instructions of the ZIP picker page (http://www.delorie.com/djgpp/zip-picker.html)
    2) compile the program using gxx in a standard DOS box

On DOS/Windows 3.x:
Unfortunately compiling on DOS and Windows 3 isn't supported at the moment. This is due to those OSes not supporting Long File Names (introduced in win95). These are unfortunately required to properly preprocess the file. If you know a workaround, please let me know!!

Handy "can I <>" chart:
        Run?    CWSDPMI?    Compile?
DOS:     y          y           n
win 3.x: y          n*          n
win 9x:  y          n*          y
win NT:  ?          n?          ?
*nix:    y?         n           y
*: windows provides DPMI, removing the need for CWS, this only applies in a Windows dos box though

