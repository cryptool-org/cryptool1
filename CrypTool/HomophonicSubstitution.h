// HomophonicSubstitution.h

#ifndef _HOMOPHONICSUBSTITUTION_H_
#define _HOMOPHONICSUBSTITUTION_H_

#include <afxwin.h>

#include <map>
#include <set>
#include <vector>

#include "CrypToolTools.h"

class HomophonicSubstitution {
public:
	struct KeyEntry {
		unsigned char code;
		unsigned char character;
		unsigned int count;
		float frequency;
		std::vector<unsigned char> homophones;
		unsigned int countHomophones;
		struct sortByCode {
			inline bool operator()(const KeyEntry &keyEntryA, const KeyEntry &keyEntryB) {
				return keyEntryA.code < keyEntryB.code;
			}
		};
		struct sortByCount {
			inline bool operator()(const KeyEntry &keyEntryA, const KeyEntry &keyEntryB) {
				return keyEntryA.count > keyEntryB.count;
			}
		};
	};
public:
	HomophonicSubstitution(const CString &sourceFile);
	virtual ~HomophonicSubstitution();
public:
	unsigned int getCountHomophonesMin() const;
	unsigned int getCountHomophonesMax() const;
	unsigned int getCountHomophones() const;
	void setCountHomophones(const unsigned int countHomophones);
public:
	const std::vector<KeyEntry> &getKeyEntries() const;
	void importKeyAsString(const CString &key);
	CString exportKeyAsString() const;
	void generateKey();
public:
	bool executeEncryption(const CString &sourceFile, const CString &targetFile) const;
	bool executeDecryption(const CString &sourceFile, const CString &targetFile) const;
private:
	unsigned int getSourceFileSize(const CString &sourceFile) const;
	std::map<unsigned char, unsigned int> getSourceAlphabet(const CString &sourceFile) const;
private:
	const CString m_sourceFile;
	const unsigned int m_sourceFileSize;
	const std::map<unsigned char, unsigned int> m_sourceAlphabet;
private:
	const unsigned int m_countHomophonesMin;
	const unsigned int m_countHomophonesMax;
private:
	unsigned int m_countHomophones;
private:
	std::vector<KeyEntry> m_keyEntries;
};

#endif
