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

/**
 * 22.02.2008
 */
package main;

/**
 * Kapselt Konfigurationseinstellungen.
 */
public class Config {

	public static final String BASE64 = "base64";
	public static final String QP = "quoted-printable";
	public static final String RSA = "RSA";
	public static final String DSA = "DSA";
	public static final String SHA1 = "SHA-1";
	public static final String MD5 = "MD5";
	public static final String MPS = "Multipart/signed";
	public static final String CMSSD = "CMS signed-data";
	
	
	private boolean internesCertificate;
	
	private int hash;
	private int sigAlg;
	private int transCode;
	private int encrAlg;
	private int mimeTyp;
	
	private String sprache;
	
	private String filename;
	
	private String filenamePSE;
	private String aliasPSE;
	
	private boolean isTest = false;
	
	/**
	 * Standardkonstruktor 
	 */
	public Config(){
		
	}
	
	
	/**
	 * Konstruktor
	 * @param hash
	 * @param sigAlg
	 * @param transCode
	 * @param encrAlg
	 * @param mimeTyp
	 */
	public Config(int hash, int sigAlg, int transCode, int encrAlg, int mimeTyp) {
		super();
		this.hash = hash;
		this.sigAlg = sigAlg;
		this.transCode = transCode;
		this.encrAlg = encrAlg;
		this.mimeTyp = mimeTyp;
		this.sprache = "DE";
	}

	/**
	 * Konstruktor mit Standardspracheinstellung deutsch.
	 * @param hash
	 * @param sigAlg
	 * @param transCode
	 * @param encrAlg
	 * @param mimeTyp
	 */
	public Config(int hash, int sigAlg, int transCode, int encrAlg, int mimeTyp, String sprache) {
		super();
		this.hash = hash;
		this.sigAlg = sigAlg;
		this.transCode = transCode;
		this.encrAlg = encrAlg;
		this.mimeTyp = mimeTyp;
		this.sprache = sprache.toUpperCase();
	}

	
	/**
	 * Übersetzung Hashfunktionen.
	 * @return
	 */
	public String getHashDescription(){
		
		if (hash == 0){
			return SHA1;
		} else if (hash == 1){
			return MD5;
		} else return "";
	}
	
	/**
	 * Übersetzung Signaturalgorithmus. Mögliche Werte:<br>
	 * * RSA<br>
	 * * DSA
	 * @return
	 */
	public String getSigAlgDescription(){
		if (sigAlg == 1)
			return DSA;
		else 
			return RSA;
	}
	
	/**
	 * Übersetzung Transfercodierung. Mögliche Rückgabewerte: <br>
	 * * BASE64<br>
	 * * quoted-printable<br>
	 * @return
	 */
	public String getTranscodeDescription(){
		if (transCode == 0){
			return BASE64;
		} else if (transCode == 1){
			return QP;
		} else return "";
	}

	/**
	 * Übersetzung Verschlüsselungsalgorithmus.
	 * @return
	 */
	public String getEncodingDescription(){
		if (encrAlg == 0){
			return "DESEDE";
		} else if (encrAlg == 1){
			return "AES";
		} else return "";
	}
	
	/**
	 * Übersetzung MIME-Type.
	 * @return
	 */
	public String getMIMETypeDescription(){
		if (mimeTyp == 0){
			return MPS;
		} else if (mimeTyp == 1){
			return CMSSD;
		} else return "";

	}

	
	/**
	 * Übersetzung 
	 * @return the encrAlg
	 */
	public int getEncrAlg() {
		return encrAlg;
	}

	/**
	 * @param encrAlg the encrAlg to set
	 */
	public void setEncrAlg(int encrAlg) {
		this.encrAlg = encrAlg;
	}

	/**
	 * Gibt das zu verwendende Hashverfahren zurück. <br>
	 * 0 = SHA-1 <br>
	 * 1 = MD5
	 * @return the hash
	 */
	public int getHash() {
		return hash;
	}

	/**
	 * @param hash the hash to set
	 */
	public void setHash(int hash) {
		this.hash = hash;
	}

	/**
	 * Gibt den zu verwendenden MIME-Typ zurück.<br>
	 * 0 = Multipart/signed <br>
	 * 1= CMS/signeddata
	 * @return the mimeTyp
	 */
	public int getMimeTyp() {
		return mimeTyp;
	}

	/**
	 * @param mimeTyp the mimeTyp to set
	 */
	public void setMimeTyp(int mimeTyp) {
		this.mimeTyp = mimeTyp;
	}

	/**
	 * @return the sigAlg
	 */
	public int getSigAlg() {
		return sigAlg;
	}

	/**
	 * @param sigAlg the sigAlg to set
	 */
	public void setSigAlg(int sigAlg) {
		this.sigAlg = sigAlg;
	}

	/**
	 * @return the transCode
	 */
	public int getTransCode() {
		return transCode;
	}

	/**
	 * @param transCode the transCode to set
	 */
	public void setTransCode(int transCode) {
		this.transCode = transCode;
	}

	/**
	 * @return the sprache
	 */
	public String getSprache() {
		return sprache;
	}

	/**
	 * @param sprache the sprache to set
	 */
	public void setSprache(String sprache) {
		this.sprache = sprache;
	}


	/**
	 * @return the filename
	 */
	public String getFilename() {
		return filename;
	}


	/**
	 * @param filename the filename to set
	 */
	public void setFilename(String filename) {
		this.filename = filename;
	}


	/**
	 * @return the internesCertificate
	 */
	public boolean isInternesCertificate() {
		return internesCertificate;
	}


	/**
	 * @param internesCertifivate the internesCertificate to set
	 */
	public void setInternesCertificate(boolean internesCertificate) {
		this.internesCertificate = internesCertificate;
	}


	/**
	 * @return the filenamePSE
	 */
	public String getFilenamePSE() {
		return filenamePSE;
	}


	/**
	 * @param aliasPSE the aliasPSE to set
	 */
	public void setAliasPSE(String aliasPSE) {
		this.aliasPSE = aliasPSE;
	}
	
	/**
	 * @return the aliasPSE
	 */
	public String getAliasPSE() {
		return aliasPSE;
	}


	/**
	 * @param filenamePSE the filenamePSE to set
	 */
	public void setFilenamePSE(String filenamePSE) {
		this.filenamePSE = filenamePSE;
	}


	/**
	 * @return the isTest
	 */
	public boolean isTest() {
		return isTest;
	}


	/**
	 * @param isTest the isTest to set
	 */
	public void setTest(boolean isTest) {
		this.isTest = isTest;
	}
	
	
	
}
