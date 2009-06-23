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
package mail;

import java.util.Date;

public class Mail {
	/** Absender */ 
	private String absender;
	/** Empfänger */
	private String empfaenger;
	/** Betreff */
	private String betreff;
	/** Text */
	private byte[] text;
	/** Absendedatum */
	private Date absendeDatum;
	/** MIME-Type */
	private String[] mailTypes;
	
	
	/**
	 * Konstruktor
	 */
	public Mail(){
		
		// init
		absendeDatum = new Date();
		absender = "";
		empfaenger = "";
		betreff = "";
		text = new byte[0];
		mailTypes = new String[0];
	}
	

	/**
	 * Konstruktor
	 * @param absender
	 * @param empfänger
	 * @param betreff
	 * @param text
	 * @param mailTypes
	 */
	public Mail(String absender, String empfaenger, String betreff, 
			byte[] text, String[] mailTypes) {
		this.absender = absender;
		this.empfaenger = empfaenger;
		this.betreff = betreff;
		this.text = text;
		this.mailTypes = mailTypes;
	}


	/**
	 * @return the absender
	 */
	public String getAbsender() {
		return absender;
	}


	/**
	 * @param absender the absender to set
	 */
	public void setAbsender(String absender) {
		this.absender = absender;
	}


	/**
	 * @return the betreff
	 */
	public String getBetreff() {
		return betreff;
	}


	/**
	 * @param betreff the betreff to set
	 */
	public void setBetreff(String betreff) {
		this.betreff = betreff;
	}


	/**
	 * @return the empfaenger
	 */
	public String getEmpfaenger() {
		return empfaenger;
	}


	/**
	 * @param empfaenger the empfaenger to set
	 */
	public void setEmpfaenger(String empfaenger) {
		this.empfaenger = empfaenger;
	}


	/**
	 * @return the text
	 */
	public byte[] getText() {
		return text;
	}


	/**
	 * @param text the text to set
	 */
	public void setText(byte[] text) {
		this.text = text;
	}

	/**
	 * @return the absendeDatum
	 */
	public Date getAbsendeDatum() {
		return absendeDatum;
	}

	/**
	 * @param absendeDatum the absendeDatum to set
	 */
	public void setAbsendeDatum(Date absendeDatum) {
		this.absendeDatum = absendeDatum;
	}

	/**
	 * @return the mailTypes
	 */
	public String[] getMailTypes() {
		return mailTypes;
	}


	/**
	 * @param mailTypes the mailTypes to set
	 */
	public void setMailTypes(String[] mailTypes) {
		this.mailTypes = mailTypes;
	}
	
	
	/* (non-Javadoc)
	 * @see java.lang.Object#toString()
	 */
	public String toString(){
		return "From=" + absender + "; To=" + empfaenger 
				+ "; Subject=" + betreff;
	}
	
	
}
