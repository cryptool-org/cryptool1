/**************************************************************************

  Copyright [2009] [CrypTool Team]

  This file is part of CrypTool.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

**************************************************************************/

#include "CrypToolTools.h"
#include "DialogeMessage.h"
#include "MakeNewName.h"
#include <stdlib.h>
#include <stdio.h>

#pragma warning(disable : 4996)

// used for the ShellExecuteJava function (see below)
extern char *Pfad;

BOOL CheckAlphabet( int minSize )
{
	if (theApp.TextOptions.getAlphabet().GetLength() < minSize )
	{
		Message(IDS_STRING_MSG_ON_ALPHABET, MB_ICONEXCLAMATION, minSize);
		return FALSE;
	}
	return TRUE;
}


BOOL CheckTextSize( SymbolArray &text, int Threshold )
{
	if(text.GetSize() < Threshold ) 
	{
		Message(IDS_STRING_ERR_INPUT_TEXT_LENGTH, MB_ICONEXCLAMATION, Threshold);
		return FALSE;
	}
	return TRUE;
}


void LoadText( const char *infile, SymbolArray &text )
{
	CWaitCursor WCursor;
	text.Read(infile);
	WCursor.Restore();
}


void GetNewDocTitle(const char* keyStr, const char* OldTitle, 
					int IDS_STRING_ID, char* title, long titleLength, BOOL Decrypt, int KeyType)
{
	if(Decrypt)
		LoadString(AfxGetInstanceHandle(),IDS_STRING_DECRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
	else
		LoadString(AfxGetInstanceHandle(),IDS_STRING_ENCRYPTION_OF_USING_KEY,pc_str1,STR_LAENGE_STRING_TABLE);
	

	LoadString(AfxGetInstanceHandle(),IDS_STRING_ID,pc_str,STR_LAENGE_STRING_TABLE);
    MakeNewName3(title,titleLength,pc_str1,pc_str,OldTitle,keyStr);
}

void OpenNewDoc( const char *outfile, const char* keyStr, const char* OldTitle, int IDS_STRING_ID, 
				 BOOL Decrypt, int KeyType)
{
	char title[128];
	CAppDocument *NewDoc;
	NewDoc = theApp.OpenDocumentFileNoMRU( outfile, keyStr, KeyType );
    remove(outfile);
    if(NewDoc) 
	{
		GetNewDocTitle(keyStr, OldTitle, IDS_STRING_ID, title, 128, Decrypt, KeyType);
	    NewDoc->SetTitle(title);
	}
}

char* itoa_fmt(int i_num, char *c_buffer, int i_base )
{

	char c_tmp[33];
	itoa(i_num, c_tmp, i_base );

	int l = strlen(c_tmp);
	int set_pt = (!(l % 3)) ? 3 : l % 3; 

	int i_buffer_length = l+1+l/3;
	if ( !c_buffer) 
		c_buffer = new char[i_buffer_length];

	char strPT[128];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,strPT,STR_LAENGE_STRING_TABLE);
	char c_pt = strPT[0];

	int i,j = 0;
	for (i = 0; i<l; )
	{
		c_buffer[j++] = c_tmp[i++];
		if ( i<l && i == set_pt ) { c_buffer[j++] = c_pt; set_pt += 3; }
	}
	c_buffer[j] = '\0';

	return c_buffer;
}

char* itoa_fmt(__int64 i_num, char *c_buffer, int i_base )
{
	char c_tmp[68];
	_i64toa(i_num, c_tmp, i_base );

	int l = strlen(c_tmp);
	int set_pt = (!(l % 3)) ? 3 : l % 3; 

	int i_buffer_length = l+1+l/3;
	if ( !c_buffer) 
		c_buffer = new char[i_buffer_length];

	char strPT[128];
	LoadString(AfxGetInstanceHandle(),IDS_STRING_PT,strPT,STR_LAENGE_STRING_TABLE);
	char c_pt = strPT[0];

	int i,j = 0;
	for (i = 0; i<l; )
	{
		c_buffer[j++] = c_tmp[i++];
		if ( i<l && i == set_pt ) { c_buffer[j++] = c_pt; set_pt += 3; }
	}
	c_buffer[j] = '\0';

	return c_buffer;
}



char* double_fmt(double d_num, char *c_buffer, int prec )
{
	char c_tmp[60];
	if (abs(d_num) > (double)INT_MAX)
	{
		sprintf(c_tmp, "%f", d_num);
	}
	else
	{
		int i_num = (int)floor(d_num);
		itoa_fmt(i_num, c_tmp);
		if (prec > 9) prec = 9;
		char strPrec[10];
		d_num = abs(d_num);
		d_num = d_num - floor(d_num) +1.0;
		i_num = (int)(d_num*pow(10.0, prec));
		itoa(i_num, strPrec, 10);
		char commaStr[128];
		LoadString(AfxGetInstanceHandle(),IDS_STRING_COMMA,commaStr,STR_LAENGE_STRING_TABLE);
        strPrec[0] = commaStr[0];
		strcat(c_tmp, strPrec);
	}

	if ( !c_buffer ) c_buffer = new char[strlen(c_tmp)];
	strcpy(c_buffer, c_tmp);

	return c_buffer;
}



unsigned long CT_OPEN_REGISTRY_SETTINGS	(unsigned long MODE_ACCESS, int ID_REGISTRY_PATH, const char *SUB_FOLDER )
{
	char registryPath[1024];
	LoadString(AfxGetInstanceHandle(),ID_REGISTRY_PATH,registryPath,STR_LAENGE_STRING_TABLE);

	if ( 0 == SUB_FOLDER )
	{
		return theApp.localRegistry.Open(HKEY_CURRENT_USER, registryPath, MODE_ACCESS);
	}
	else
	{
		char *path = new char[strlen(registryPath)+strlen(SUB_FOLDER)+2];
		strcpy(path, registryPath);
		strcat(path, "\\");
		strcat(path, SUB_FOLDER);
		unsigned long ret_value = theApp.localRegistry.Create(HKEY_CURRENT_USER, path, REG_NONE, REG_OPTION_NON_VOLATILE, MODE_ACCESS);
		delete []path;
		return ret_value;
	}
}

void CT_CLOSE_REGISTRY()
{
	theApp.localRegistry.Close();
}

BOOL CT_READ_REGISTRY			(unsigned long &value, const char *ID)
{
	unsigned long u_value;
	// 
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(u_value, ID))
		return FALSE;
	value = u_value;
	return TRUE;
}

BOOL CT_READ_REGISTRY			(char *value, const char *ID, unsigned long &length)
{
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(value, ID, &length))
		return FALSE;

	return TRUE;
}

BOOL CT_READ_REGISTRY_DEFAULT	(unsigned long &value, const char *ID, const unsigned long default_value)
{
	unsigned long u_value;
	// 
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(u_value, ID))
	{
		u_value = (unsigned long)default_value;
		if (ERROR_SUCCESS != theApp.localRegistry.SetValue(u_value, ID))
			return FALSE;
	}	
	value = u_value;
	return TRUE;	
}

BOOL CT_READ_REGISTRY_DEFAULT	(char *value, const char *ID, const char *default_value, unsigned long &length )
{
	if (ERROR_SUCCESS != theApp.localRegistry.QueryValue(value, ID, &length ) )
	{
		unsigned long defaultLength = strlen(default_value);
		strncpy(value, default_value, defaultLength);
		value[defaultLength]='\0';
		if (ERROR_SUCCESS != theApp.localRegistry.SetValue(value, ID))
			return FALSE;
	}	
	return TRUE;	
}

BOOL CT_WRITE_REGISTRY			(const unsigned long value, const char *ID)
{
	if (ERROR_SUCCESS != theApp.localRegistry.SetValue(value, ID))
		return FALSE;
	return TRUE;
}


BOOL CT_WRITE_REGISTRY			(const char *value,	const char *ID)
{
	if (ERROR_SUCCESS != theApp.localRegistry.SetValue(value, ID))
		return FALSE;
	return TRUE;
}

// This function returns true if the operating system on which 
// CrypTool is executed is a 64bit Windows, otherwise this function 
// returns false.
bool isWindows64Bit() {
#if defined (_WIN64)
	return true;
#elif defined(_WIN32)
	BOOL windows64bit = false;
	return IsWow64Process(GetCurrentProcess(), &windows64bit) && windows64bit;
#else
	return false;
#endif
}

// This function expects a string of KEY/VALUE pairs as follows:
// "key0: value0, key1: value1, key2: value2..."
// Taking a key as argument, the function returns the respective value 
// (if successful) or an empty string (if unsuccessful).
// ***CAUTION***: Of course you should not use this function if
// keys or values might contain separators (here: ":" or ",")
CString extractValueFromStringByKey(CString _key, CString _string) {
	CString result;
	int startKey = _string.Find(_key);
	if(startKey >= 0) {
		// determine where the value begins
		// (don't forget ":" and " ", thus the "+2")
		int startValue = startKey + _key.GetLength() + 2;
		// determine where the value ends
		// (either on a "," or it's the end of the string)
		int endValue = _string.Find(",", startValue);
		if(endValue >= 0) {
			// obviously we've separated our value successfully
			CString value = _string;
			value.Delete(endValue, _string.GetLength() - endValue);
			value.Delete(0, startValue);
			result = value;
		}
		else {
			CString value = _string;
			value.Delete(0, startValue);
			result = value;
		}
	}
	return result;
}

// This function is a very basic 'split' implemenation-- it splits the specified 
// string with regards to the specified separator and returns the results as a 
// list of strings; if no separator can be found, an empty list is returned
std::vector<CString> splitString(const CString &_string, const CString &_separator) {
	std::vector<CString> vectorStrings;
	CString inputString = _string;
	int index;
	while((index = inputString.Find(_separator)) != -1) {
		CString temporaryString = inputString;
		temporaryString.Delete(index, temporaryString.GetLength() - index);
		vectorStrings.push_back(temporaryString);
		inputString.Delete(0, index + _separator.GetLength());
	}
	if(vectorStrings.size() > 0) {
		vectorStrings.push_back(inputString);
	}
	return vectorStrings;
}

// This function simply checks whether the "%APPDATA%" environment variable 
// is defined; this check is important for various elements in CrypTool which 
// need to create temporary files; note that this function implicity dumps a 
// warning message if this variable is not defined (in other words: you don't 
// need to create any error handling stuff around the call to this function).
bool isAppDataVariableDefined() {
	const CString appDataVariable = getenv("APPDATA");
	if(appDataVariable.IsEmpty()) {
		CString errorMessage;
		errorMessage.Format(IDS_PSE_FILESTRUCT_NO_APPLICATION_DATA_PATH);
		AfxMessageBox(errorMessage, MB_ICONERROR);
		return false;
	}
	return true;
}

// This function tries to extract information about Java version installed 
// on the system. If all goes well, the extracted information is returned 
// through the output parameters. If something goes wrong, the function 
// returns false and all output parameters default to zero.
bool extractJavaInformation(int &_versionMajor, int &_versionMinor, int &_bits) {
	// initialize output parameters
	_versionMajor = 0;
	_versionMinor = 0;
	_bits = 0;
	// having a valid %APPDATA% variable is required, not just for 
	// evaluating the Java information, but for other areas as well
	if(isAppDataVariableDefined()) {
		// return structures for CreateProcess
		STARTUPINFO si;
		PROCESS_INFORMATION pi;
		// check if Java is installed (exists in %PATH% variable)
		memset(&si, 0, sizeof(si));
		memset(&pi, 0, sizeof(pi));
		if(CreateProcess(NULL, "java", NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
			// pipe the Java version output into the file
			const CString outputFileName = CString(getenv("APPDATA")) + CString("\\") + CString("__CRYPTOOL_JAVA_VERSION__");
			memset(&si, 0, sizeof(si));
			memset(&pi, 0, sizeof(pi));
			// CreateProcess doesn't know about stdout/stderr by default
			SECURITY_ATTRIBUTES sa;
			sa.nLength = sizeof(sa);
			sa.lpSecurityDescriptor = NULL;
			sa.bInheritHandle = TRUE;
			HANDLE outputFileHandle = CreateFile(outputFileName, FILE_WRITE_DATA, FILE_SHARE_WRITE | FILE_SHARE_READ, &sa, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			// initialize startup info
			si.cb = sizeof(STARTUPINFO); 
			si.dwFlags |= STARTF_USESTDHANDLES;
			si.hStdInput = NULL;
			si.hStdError = outputFileHandle;
			si.hStdOutput = outputFileHandle;
			const CString commandWriteFile = CString("java -XshowSettings:all");
			CreateProcess(NULL, (LPSTR)(LPCTSTR)(commandWriteFile), NULL, NULL, true, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);
			WaitForSingleObject(pi.hProcess, INFINITE);
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
			CloseHandle(outputFileHandle);
			// try to open the file and extract the desired information
			CStdioFile inputFile;
			if(inputFile.Open(outputFileName, CFile::modeRead)) {
				int versionMajor = 0;
				int versionMinor = 0;
				int bits = 0;
				CString line;
				while(inputFile.ReadString(line)) {
					if(line.Find("java.version") != -1) {
						CString lineVersion = line;
						lineVersion.Replace("java.version = ", "");
						std::vector<CString> elements = splitString(lineVersion, ".");
						if(elements.size() >= 2) {
							versionMajor = atoi(elements[0]);
							versionMinor = atoi(elements[1]);
						}
					}
					if(line.Find("sun.arch.data.model") != -1) {
						CString lineBits = line;
						lineBits.Replace("sun.arch.data.model = ", "");
						bits = atoi(lineBits);
					}
				}
				inputFile.Close();
				// delete the file
				DeleteFile(outputFileName);
				// if all extracted information is non-zero, we're good
				if(versionMajor != 0 && versionMinor != 0 && bits != 0) {
					_versionMajor = versionMajor;
					_versionMinor = versionMinor;
					_bits = bits;
					return true;
				}
			}
		}
	}
	return false;
}

// This function checks whether a specific Java version is available; 
// to test against a specific Java version, simply supply a string 
// like "1.3" or "1.4". Note that more sophisticated filtering is 
// not supported at the moment. Also, you don't need to create any 
// error handling stuff around the call to this function, as it 
// presents its own error message in case it returns false.
bool isJavaAvailable(const CString &_version) {
	int requestedVersionMajor = 0;
	int requestedVersionMinor = 0;
	std::vector<CString> requestedVersionElements = splitString(_version, ".");
	if(requestedVersionElements.size() >= 2) {
		requestedVersionMajor = atoi(requestedVersionElements[0]);
		requestedVersionMinor = atoi(requestedVersionElements[1]);
	}
	int availableVersionMajor = 0;
	int availableVersionMinor = 0;
	int availableBits = 0;
	extractJavaInformation(availableVersionMajor, availableVersionMinor, availableBits);
	// check whether Java is available at all
	if(availableVersionMajor == 0 || availableVersionMinor == 0 || availableBits == 0) {
		CString errorMessage;
		errorMessage.Format(IDS_STRING_JAVA_NOT_INSTALLED, _version);
		AfxMessageBox(errorMessage, MB_ICONERROR);
		return false;
	}
	// check whether the requested Java version is sufficient
	if(availableVersionMajor < requestedVersionMajor || availableVersionMajor == requestedVersionMajor && availableVersionMinor < requestedVersionMinor) {
		CString version;
		version.Format("%i.%i", availableVersionMajor, availableVersionMinor);
		CString errorMessage;
		errorMessage.Format(IDS_STRING_JAVA_REQUIREMENTS_NOT_MET, _version, version);
		AfxMessageBox(errorMessage, MB_ICONINFORMATION);
		return false;
	}
	return true;
}

// This function tries to execute a Java program (parameter 1) using 
// the supplied call (parameter 2). The first parameter ("the executable") 
// is needed for internal error management (i.e. did the Java call fail or 
// was the executable not found?). The function checks whether Java is 
// installed on the user's machine; if Java is installed, the function 
// determines if the desired program exists (thus we need parameter 1); 
// if the program exists, this function tries to execute the program 
// within a shell window
void ShellExecuteJava(const CString &_javaProgram, const CString &_javaProgramCompleteCall, const CString &_path) {
	CString javaProgram = _javaProgram;
	CString javaProgramCompleteCall = _javaProgramCompleteCall;
	CString path = _path;
	// return structures for CreateProcess
	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	// check if Java is installed (exists in %PATH% variable)
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	if(!CreateProcess(NULL, "java", NULL, NULL, false, CREATE_NO_WINDOW, NULL, NULL, &si, &pi)) {
		CString message;
		message.LoadStringA(IDS_STRING_JAVA_JRE_NOT_INSTALLED);
		AfxMessageBox(message, MB_ICONINFORMATION);
		return;
	}
	// check if Java program is there
	javaProgram.Insert(0, path);
	struct stat javaProgramFileInformation;
	if(stat(javaProgram.GetBuffer(), &javaProgramFileInformation) != 0) {
		CString message;
		message.Format(IDS_STRING_JAVA_PROGRAM_NOT_FOUND, javaProgram);
		AfxMessageBox(message, MB_ICONINFORMATION);
		return;
	}
	// try to execute the Java program
	memset(&si, 0, sizeof(si));
	memset(&pi, 0, sizeof(pi));
	CString command;
	command.Format("java %s", javaProgramCompleteCall);
	if(!CreateProcess(NULL, (LPSTR)(LPCTSTR)(command), NULL, NULL, false, CREATE_NO_WINDOW, NULL, (LPCTSTR)(path), &si, &pi)) {
		CString message;
		message.LoadStringA(IDS_STRING_JAVA_PROGRAM_EXECUTION_FAILED);
		AfxMessageBox(message, MB_ICONSTOP);
		return;
	}
}

// this function implicitly converts all lowercase letters in the key 
// to their uppercase equivalents if these are part of the alphabet 
// while the actual lowercase letters are not. 
CString adaptKeyToAlphabet(const CString _key) {
	
	CString key = _key;
	CString alphabet = "abcdefghijklmnopqrstuvwxyzäöü"; 

	for(int i=0; i<key.GetLength(); i++) {
		char characterLowercase = key[i];
		char characterUppercase = characterLowercase - (char)(32);
		// convert character to uppercase...
		// *IF* the character fits [a-z] or [ä-ü] AND
		// *IF* the character is NOT part of the CrypTool alphabet AND
		// *IF* the uppercase equivalent of the character IS part of the CrypTool alphabet
		if(alphabet.Find(characterLowercase) != -1 && theApp.TextOptions.getAlphabet().Find(characterLowercase) == -1 && theApp.TextOptions.getAlphabet().Find(characterUppercase) != -1) {
			key.SetAt(i, characterUppercase);
		}	
	}

	return key;
}

// flomar, 07/05/2010
// the following set of functions (signature: createStringNumberWithDigitGrouping) 
// adds digit groupings to a specific number with regards to the current language; 
// for example, in German the number "-23000" is converted to "-23.000", 
// whereas in English the the number "-52039.99" would lead to "-52,039.99"; 
// if we cannot successfully convert (for some reason), we return the number 
// that was passed in as argument without any changes

// this function goes into the resource file and retrieves the 
// correct integral number separator for the current language
char getIntegralNumberSeparator() {
	// get separator from resource file (language-dependent)
	CString stringIntegralNumberSeparator;
	stringIntegralNumberSeparator.Format(IDS_INTEGRAL_NUMBER_SEPARATOR);
	char integralNumberSeparator = stringIntegralNumberSeparator[0];
	return integralNumberSeparator;
}

// this function goes into the resource file and retrieves the 
// correct fractional number separator for the current language
char getFractionalNumberSeparator() {
	// get separator from resource file (language-dependent)
	CString stringFranctionalNumberSeparator;
	stringFranctionalNumberSeparator.Format(IDS_FRACTIONAL_NUMBER_SEPARATOR);
	char franctionalNumberSeparator = stringFranctionalNumberSeparator[0];
	return franctionalNumberSeparator;
}

// overloaded method: int
CString createStringNumberWithDigitGrouping(const int &_number) {
	CString stringNumber;
	// convert number to string
	stringNumber.Format("%d", _number);
	// add digit grouping and return result
	return createStringNumberWithDigitGrouping(stringNumber);
}

// overloaded method: unsigned int
CString createStringNumberWithDigitGrouping(const unsigned int &_number) {
	CString stringNumber;
	// convert number to string
	stringNumber.Format("%d", _number);
	// add digit grouping and return result
	return createStringNumberWithDigitGrouping(stringNumber);
}

// overloaded method: long
CString createStringNumberWithDigitGrouping(const long &_number) {
	CString stringNumber;
	// convert number to string
	stringNumber.Format("%d", _number);
	// add digit grouping and return result
	return createStringNumberWithDigitGrouping(stringNumber);
}

// overloaded method: unsigned long
CString createStringNumberWithDigitGrouping(const unsigned long &_number) {
	CString stringNumber;
	// convert number to string
	stringNumber.Format("%d", _number);
	// add digit grouping and return result
	return createStringNumberWithDigitGrouping(stringNumber);
}

// overloaded method: float (with extra parameter for amount of decimal places)
CString createStringNumberWithDigitGrouping(const float &_number, const unsigned int &_numberOfDecimalPlaces) {
	CString stringNumber;
	// create format string (for decimal places)
	CString stringFormat; stringFormat.Format("%d", _numberOfDecimalPlaces);
	stringFormat.Insert(0, "%.");
	stringFormat.Append("f");
	// convert number to string
	stringNumber.Format(stringFormat, _number);
	// add digit grouping and return result
	return createStringNumberWithDigitGrouping(stringNumber);
}

// overloaded method: double (with extra parameter for amount of decimal places)
CString createStringNumberWithDigitGrouping(const double &_number, const unsigned int &_numberOfDecimalPlaces) {
	CString stringNumber;
	// create format string (for decimal places)
	CString stringFormat; stringFormat.Format("%d", _numberOfDecimalPlaces);
	stringFormat.Insert(0, "%.");
	stringFormat.Append("f");
	// convert number to string
	stringNumber.Format(stringFormat, _number);
	// add digit grouping and return result
	return createStringNumberWithDigitGrouping(stringNumber);
}

// ATTENTION: to avoid confusion, this function should not be called 
// from anywhere but from within the overloaded functions defined above
CString createStringNumberWithDigitGrouping(const CString &_number) {
	CString stringNumber;

	// we expect a number to be formatted as follows:
	//  (1) optional minus sign
	//  (2) integral part
	//  (3) optional colon
	//  (4) optional fractional part
	// what we'll do now is extract the separate parts of the number string, 
	// and then put them back together to form a number with digit groupings

	CString stringMinusSign;
	CString stringIntegralPart;
	CString stringColon;
	CString stringFractionalPart;

	for(int i=0; i<_number.GetLength(); i++) {
		char character = _number[i];
		// (1) try to get the minus sign
		if(i == 0 && character == '-') {
			stringMinusSign = "-";
		}
		// (2) try to get the integral part
		else if(stringColon.GetLength() == 0 && character >= '0' && character <= '9') {
			stringIntegralPart.AppendChar(character);
		}
		// (3) try to get the colon
		else if(character == '.') {
			stringColon = ".";
		}
		// (4) try to get the fractional part
		else if(stringColon.GetLength() > 0 && character >= '0' && character <= '9') {
			stringFractionalPart.AppendChar(character);
		}
		else {
			// obviously something strange happened, thus we return the original number
			return _number;
		}
	}

	// determine amount of integral separators needed
	int amountOfIntegralSeparatorsNeeded = (stringIntegralPart.GetLength() - 1) / 3;
	int amountOfIntegralSeparatorsAdded = 0;

	// get the integral separator (language-dependent)
	char integralSeparator = getIntegralNumberSeparator();

	// insert integral separators
	for(int i=0; i<amountOfIntegralSeparatorsNeeded; i++) {
		int insertPosition = stringIntegralPart.GetLength() - (i+1) * 3 - amountOfIntegralSeparatorsAdded;
		stringIntegralPart.Insert(insertPosition, integralSeparator);
		amountOfIntegralSeparatorsAdded++;
	}

	// get the fractional separator (language-dependent)
	char fractionalSeparator = getFractionalNumberSeparator();
	if(stringColon.GetLength() > 0) {
		stringColon = "";
		stringColon.AppendChar(fractionalSeparator);
	}

	// we're through with the preliminary stuff, now we put together the result
	stringNumber = "";
	stringNumber.Append(stringMinusSign);
	stringNumber.Append(stringIntegralPart);
	stringNumber.Append(stringColon);
	stringNumber.Append(stringFractionalPart);

	return stringNumber;
}

// this function removes all non-alphabet characters from the specified string
CString removeNonAlphabetCharacters(CString &_text, const CString &_alphabet) {
	CString result;
	for(int i=0; i<_text.GetLength(); i++) {
		if(_alphabet.Find(_text[i]) != -1) {
			result.AppendChar(_text[i]);
		}
	}
	return result;
}