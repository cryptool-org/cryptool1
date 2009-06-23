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
 * 
 */
package texte;

/**
 * Kapselt einen Anzeigetext jeweils in deutsch und englisch.
 */
public class TranslationText {

	private String deutsch;
	private String englisch;
	
	
	/**
	 * Konstruktor
	 */
	public TranslationText() {
		
	}


	public TranslationText(String deutsch, String englisch) {
		this.deutsch = deutsch;
		this.englisch = englisch;
	}


	
	/**
	 * Gibt den deutschen Text wieder.
	 * @return
	 */
	public String getDeutsch() {
		return deutsch;
	}


	/**
	 * Setzt den deutschen Text.
	 * @param deutsch
	 */
	public void setDeutsch(String deutsch) {
		this.deutsch = deutsch;
	}


	/**
	 * Gibt den englischen Text wieder.
	 * @return
	 */
	public String getEnglisch() {
		return englisch;
	}


	/**
	 * Setzt den englischen Text.
	 * @param englisch
	 */
	public void setEnglisch(String englisch) {
		this.englisch = englisch;
	}
	
	/**
	 * Gibt den Übersetzungstext abhängig von der Sprache an.
	 * @param language
	 * @return
	 */
	public String getText(String language){
		if (language.toUpperCase().equals("DE")){
			return getDeutsch();
		} else if (language.toUpperCase().equals("EN")){
			return getEnglisch();
		} 
		//default	
		else return getEnglisch();
	}
	
}
