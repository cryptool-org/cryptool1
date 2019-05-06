// HomophonicSubstitution.cpp

#include "HomophonicSubstitution.h"

#include <algorithm>

#define COUNT_HOMOPHONES_MIN 1
#define COUNT_HOMOPHONES_MAX 256

HomophonicSubstitution::HomophonicSubstitution(const CString &sourceFile) :
	m_sourceFile(sourceFile),
	m_sourceFileSize(getSourceFileSize(sourceFile)),
	m_sourceAlphabet(getSourceAlphabet(sourceFile)),
	m_countHomophonesMin(COUNT_HOMOPHONES_MIN),
	m_countHomophonesMax(COUNT_HOMOPHONES_MAX),
	m_countHomophones(COUNT_HOMOPHONES_MAX) {
	
}

HomophonicSubstitution::~HomophonicSubstitution() {

}

unsigned int HomophonicSubstitution::getCountHomophonesMin() const {
	unsigned int countHomophonesMin = m_countHomophonesMin;
	countHomophonesMin = std::max<unsigned int>(countHomophonesMin, m_sourceAlphabet.size());
	countHomophonesMin = std::min<unsigned int>(countHomophonesMin, m_countHomophonesMax);
	return countHomophonesMin;
}

unsigned int HomophonicSubstitution::getCountHomophonesMax() const {
	return m_countHomophonesMax;
}

unsigned int HomophonicSubstitution::getCountHomophones() const {
	return m_countHomophones;
}

void HomophonicSubstitution::setCountHomophones(const unsigned int countHomophones) {
	const unsigned int countHomophonesOld = m_countHomophones;
	m_countHomophones = countHomophones;
	m_countHomophones = std::min<unsigned int>(m_countHomophones, getCountHomophonesMax());
	m_countHomophones = std::max<unsigned int>(m_countHomophones, getCountHomophonesMin());
	if(m_countHomophones != countHomophonesOld) {
		generateKey();
	}
}

const std::vector<HomophonicSubstitution::KeyEntry> &HomophonicSubstitution::getKeyEntries() const {
	return m_keyEntries;
}

void HomophonicSubstitution::importKeyAsString(const CString &key) {
	m_keyEntries.clear();
	m_countHomophones = 0;
	const std::vector<CString> stringsKeyEntries = splitString(key, ";");
	for(int indexKeyEntries=0; indexKeyEntries<stringsKeyEntries.size(); indexKeyEntries++) {
		const CString stringKeyEntry = stringsKeyEntries[indexKeyEntries];
		const std::vector<CString> stringsKeyEntry = splitString(stringKeyEntry, "/");
		if(stringsKeyEntry.size() == 6) {
			const CString stringKeyEntryCode = stringsKeyEntry[0];
			const CString stringKeyEntryCharacter = stringsKeyEntry[1];
			const CString stringKeyEntryCount = stringsKeyEntry[2];
			const CString stringKeyEntryFrequency = stringsKeyEntry[3];
			const CString stringKeyEntryCountHomophones = stringsKeyEntry[4];
			const CString stringKeyEntryHomophones = stringsKeyEntry[5];
			const std::vector<CString> stringsHomophones = splitString(stringKeyEntryHomophones, ",");
			if(stringsHomophones.size() == atoi(stringKeyEntryCountHomophones)) {
				KeyEntry keyEntry;
				keyEntry.code = (unsigned char)(strtol((LPCSTR)(stringKeyEntryCode), NULL, 16));
				keyEntry.character = (unsigned char)(strtol((LPCSTR)(stringKeyEntryCharacter), NULL, 16));
				keyEntry.count = (unsigned int)(strtol((LPCSTR)(stringKeyEntryCount), NULL, 10));
				keyEntry.frequency = (float)(strtod((LPCSTR)(stringKeyEntryFrequency), NULL));
				keyEntry.countHomophones = (unsigned int)(strtol((LPCSTR)(stringKeyEntryCountHomophones), NULL, 10));
				for(int indexStringsHomophones=0; indexStringsHomophones<stringsHomophones.size(); indexStringsHomophones++) {
					keyEntry.homophones.push_back((unsigned char)(strtol((LPCSTR)(stringsHomophones[indexStringsHomophones]), NULL, 16)));
					m_countHomophones++;
				}
				m_keyEntries.push_back(keyEntry);
			}
		}
	}
	sort(m_keyEntries.begin(), m_keyEntries.end(), KeyEntry::sortByCode());
}

CString HomophonicSubstitution::exportKeyAsString() const {
	CString stringKey;
	CString stringKeyEntry;
	CString stringKeyEntryCode;
	CString stringKeyEntryCharacter;
	CString stringKeyEntryCount;
	CString stringKeyEntryFrequency;
	CString stringKeyEntryCountHomophones;
	CString stringKeyEntryHomophones;
	CString stringKeyEntryHomophone;
	for(int indexKeyEntry=0; indexKeyEntry<m_keyEntries.size(); indexKeyEntry++) {
		KeyEntry keyEntry = m_keyEntries[indexKeyEntry];
		stringKeyEntryCode.Format("%02x", keyEntry.code);
		stringKeyEntryCharacter.Format("%02x", keyEntry.character);
		stringKeyEntryCount.Format("%d", keyEntry.count);
		stringKeyEntryFrequency.Format("%f", keyEntry.frequency);
		stringKeyEntryCountHomophones.Format("%d", keyEntry.countHomophones);
		stringKeyEntryHomophones.Empty();
		for(int indexHomophone=0; indexHomophone<keyEntry.homophones.size(); indexHomophone++) {
			stringKeyEntryHomophone.Format("%02x", keyEntry.homophones[indexHomophone]);
			stringKeyEntryHomophones.Append(stringKeyEntryHomophone);
			if(indexHomophone + 1 < keyEntry.homophones.size()) {
				stringKeyEntryHomophones.Append(",");
			}
		}
		stringKeyEntry.Format("%s/%s/%s/%s/%s/%s", stringKeyEntryCode, stringKeyEntryCharacter, stringKeyEntryCount, stringKeyEntryFrequency, stringKeyEntryCountHomophones, stringKeyEntryHomophones);
		stringKey.Append(stringKeyEntry);
		if(indexKeyEntry + 1 < m_keyEntries.size()) {
			stringKey.Append(";");
		}
	}
	stringKey = stringKey.MakeUpper();
	return stringKey;
}

void HomophonicSubstitution::generateKey() {
	// First, create a vector of homophones with regards to the current 
	// count of homophones, and then randomize said vector.
	std::vector<unsigned char> homophones;
	for(unsigned int homophone=0; homophone<m_countHomophones; homophone++) {
		homophones.push_back(homophone);
	}
	std::random_shuffle(homophones.begin(), homophones.end());
	// Now we go through each character of the source alphabet and create 
	// a key entry for it. Each key entry contains a code (the ASCII value), 
	// a character (displayable ASCII character, which essentially is just a 
	// duplicate of the code, though), a count (how many times the character 
	// occurs in the source file), a frequency (that's just the count divided 
	// by the size of the source file), and the randomly chosen homophones.
	m_keyEntries.clear();
	for(std::map<unsigned char, unsigned int>::const_iterator i=m_sourceAlphabet.begin(); i!=m_sourceAlphabet.end(); i++) {
		const unsigned char code = i->first;
		const unsigned int count = i->second;
		KeyEntry keyEntry;
		keyEntry.code = code;
		keyEntry.character = code;
		keyEntry.count = count;
		keyEntry.frequency = (float)(keyEntry.count) / (float)(m_sourceFileSize);
		// Note that we cannot just assign (frequency * countHomophones) homophones 
		// here as that could lead to low-frequency key entries without having a 
		// single homophone assigned. So we only assign a limited number of 
		// homophones here and assign the remaining ones in a second loop.
		const unsigned int countHomophones = std::max<unsigned int>((unsigned int)(keyEntry.frequency * (m_countHomophones - m_sourceAlphabet.size())), 1);
		for(unsigned int homophone=0; homophone<countHomophones; homophone++) {
			keyEntry.homophones.push_back(homophones.back());
			homophones.pop_back();
		}
		keyEntry.countHomophones = countHomophones;
		m_keyEntries.push_back(keyEntry);
	}
	// At this point all key entries have been created, but we're not 
	// necessarily done: There might be some homophones left which have 
	// not been assigned yet. We assign them by order of frequency, or 
	// in other words: We sort the key entries by their count and then 
	// loop over them, adding one homophone at a time, until all of the 
	// homophones are assigned.
	std::sort(m_keyEntries.begin(), m_keyEntries.end(), KeyEntry::sortByCount());
	if(m_keyEntries.size() > 0) {
		while(homophones.size() > 0) {
			for(int indexKeyEntry=0; indexKeyEntry<m_keyEntries.size(); indexKeyEntry++) {
				if(homophones.size() == 0) {
					break;
				}
				KeyEntry keyEntry = m_keyEntries[indexKeyEntry];
				keyEntry.homophones.push_back(homophones.back());
				keyEntry.countHomophones += 1;
				homophones.pop_back();
				m_keyEntries[indexKeyEntry].homophones = keyEntry.homophones;
				m_keyEntries[indexKeyEntry].countHomophones = keyEntry.countHomophones;
			}
		}
	}
	// Sort key entries by their code.
	std::sort(m_keyEntries.begin(), m_keyEntries.end(), KeyEntry::sortByCode());
}

bool HomophonicSubstitution::executeEncryption(const CString &sourceFile, const CString &targetFile) const {
	// Prepare the key entries for quicker access: Instead of sifting 
	// through all available key entries for each cleartext character, 
	// we're creating a temporary look-up table with the following 
	// mapping: cleartext character -> key entry index.
	std::map<unsigned char, int> lookUpTable;
	for(int indexKeyEntry=0; indexKeyEntry<m_keyEntries.size(); indexKeyEntry++) {
		const KeyEntry keyEntry = m_keyEntries[indexKeyEntry];
		lookUpTable[keyEntry.code] = indexKeyEntry;
	}
	// Try to open the source file and the target file. If everything 
	// goes well, execute the encryption byte for byte. Cleartext bytes 
	// not contained in the key are ignored.
	CFile infile;
	CFile outfile;
	if(!infile.Open(sourceFile, CFile::modeRead | CFile::typeBinary)) {
		return false;
	}
	if(!outfile.Open(targetFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
		return false;
	}
	const unsigned int bufferSize = 4096;
	unsigned char buffer[bufferSize];
	while(true) {
		const unsigned int bytesRead = infile.Read(buffer, bufferSize);
		if(bytesRead == 0) {
			break;
		}
		// TODO/FIXME: Yes, writing bytes one-at-a-time is extremely 
		// slow, but it gets the job done. Whoever sees this comment 
		// and has some spare time: feel free to fix it.
		for(unsigned int i=0; i<bytesRead; i++) {
			const unsigned char byteCleartext = buffer[i];
			if(lookUpTable.find(byteCleartext) != lookUpTable.end()) {
				const int indexKeyEntry = lookUpTable[byteCleartext];
				const KeyEntry keyEntry = m_keyEntries[indexKeyEntry];
				const unsigned char byteCiphertext = keyEntry.homophones[rand() % keyEntry.homophones.size()];
				outfile.Write(&byteCiphertext, 1);
			}
		}
	}
	infile.Close();
	outfile.Close();
	return true;
}

bool HomophonicSubstitution::executeDecryption(const CString &sourceFile, const CString &targetFile) const {
	// Prepare the key entries for quicker access: Instead of sifting 
	// through all available key entries for each ciphertext character, 
	// we're creating a temporary look-up table with the following 
	// mapping: ciphertext character -> cleartext character.
	std::map<unsigned char, unsigned char> lookUpTable;
	for(int indexKeyEntry=0; indexKeyEntry<m_keyEntries.size(); indexKeyEntry++) {
		const KeyEntry keyEntry = m_keyEntries[indexKeyEntry];
		for(int indexHomophone=0; indexHomophone<keyEntry.homophones.size(); indexHomophone++) {
			const unsigned char homophone = keyEntry.homophones[indexHomophone];
			lookUpTable[homophone] = keyEntry.code;
		}
	}
	// Try to open the source file and the target file. If everything 
	// goes well, execute the decryption byte for byte. Ciphertext bytes 
	// not contained in the key are ignored.
	CFile infile;
	CFile outfile;
	if(!infile.Open(sourceFile, CFile::modeRead | CFile::typeBinary)) {
		return false;
	}
	if(!outfile.Open(targetFile, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)) {
		return false;
	}
	const unsigned int bufferSize = 4096;
	unsigned char buffer[bufferSize];
	while(true) {
		const unsigned int bytesRead = infile.Read(buffer, bufferSize);
		if(bytesRead == 0) {
			break;
		}
		// TODO/FIXME: Yes, writing bytes one-at-a-time is extremely 
		// slow, but it gets the job done. Whoever sees this comment 
		// and has some spare time: feel free to fix it.
		for(unsigned int i=0; i<bytesRead; i++) {
			const unsigned char byteCiphertext = buffer[i];
			if(lookUpTable.find(byteCiphertext) != lookUpTable.end()) {
				const unsigned char byteCleartext = lookUpTable[byteCiphertext];
				outfile.Write(&byteCleartext, 1);
			}
		}
	}
	infile.Close();
	outfile.Close();
	return true;
}

unsigned int HomophonicSubstitution::getSourceFileSize(const CString &sourceFile) const {
	CFile infile;
	if(infile.Open(sourceFile, CFile::modeRead | CFile::typeBinary)) {
		return (unsigned int)(infile.GetLength());
	}
	return 0;
}

std::map<unsigned char, unsigned int> HomophonicSubstitution::getSourceAlphabet(const CString &sourceFile) const {
	std::map<unsigned char, unsigned int> sourceAlphabet;
	const unsigned int bufferSize = 4096;
	unsigned char buffer[bufferSize];
	CFile infile;
	if(infile.Open(sourceFile, CFile::modeRead | CFile::typeBinary)) {
		while(true) {
			const unsigned int bytesRead = infile.Read(buffer, bufferSize);
			if(bytesRead == 0) {
				break;
			}
			for(unsigned int i=0; i<bytesRead; i++) {
				const unsigned char byte = buffer[i];
				if(sourceAlphabet.find(byte) == sourceAlphabet.end()) {
					sourceAlphabet[byte] = 1;
				}
				else {
					const unsigned int count = sourceAlphabet[byte];
					sourceAlphabet[byte] = count + 1;
				}
			}
		}
	}
	return sourceAlphabet;
}
