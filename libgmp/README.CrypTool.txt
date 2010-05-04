HOW TO UPDATE LIB GMP/MPIR

Optain the current release from http://www.mpir.org/#release

Follow the build instructions in the source directory: build.vc9\readme.txt

Using mpir.sln build 
	lib_mpir_p4 and lib_mpir_cxx
in Debug and Release configuration.

Copy the following files:

PIR source					CrypTool source
----------------------------------------------------------------
build.vc9\lib\Win32\Debug\*.h		->	libgmp\
build.vc9\lib\Win32\Debug\mpir.lib	->	libgmp\Debug\
build.vc9\lib\Win32\Debug\mpir.pdb	->	libgmp\Debug\
build.vc9\lib\Win32\Release\mpir.lib	->	libgmp\Release\
build.vc9\lib\Win32\Release\mpir.pdb	->	libgmp\Release\

