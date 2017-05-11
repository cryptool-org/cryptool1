BUILD INSTRUCTIONS FOR APFLOAT (2.41)
=====================================

1) You need a Microsoft IDE, VS2008 was successfully tested.

2) Download the following packages from "http://apfloat.org":
* the apfloat base package (i.e. "apf241.zip")
* the files for Windows GUI (i.e. "32_vc_a.zip")
* the files for Windows threading support (i.e. "win32_ta.zip")

3) Now, extract all ZIP files in the same directory (i.e. "apfloat").

NOTE: Follow the instructions on the apfloat site; it is important HOW and IN WHICH ORDER you extract the ZIP files, see option "-o" of your ZIP program.

4) Open the file "apfloat/makefile" and make changes as follows:
*Find the "OPTS" parameter, and replace the option "/GX" with "/EHsc", according to MS this option is deprecated.
*Furthermore, add the option "/MTd" if you want to build a DEBUG library, and "/MT" if you want to build a RELEASE library, respectively.

5) Now you're ready to build. Go into the "apfloat" directory and call "NMAKE" to compile the library.

6) When done building the libraries, put the libraries into the following locations:
* trunk/apfloat/apfloat-vs2008/apfloatd.lib (VS2008, debug)
* trunk/apfloat/apfloat-vs2008/apfloat.lib (VS2008, release)

I hope this helped. Send an email to florian(at)marchal(dot)de if you run into any problems.

Florian Marchal, 2017/05/09
