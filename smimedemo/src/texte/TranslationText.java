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
