package utils;

import java.util.Date;

/**
 * Informationen zur Versionsnummer und zum Datum des Builds 
 */
public abstract class Version {

	// Version
	public static final String version = "v1.0";
	
	// Datums des Build
	public static final String builddate = "20090423";
	
	
	/**
	 * Gibt die Version plus das Datum des Build als String zurück.
	 * @return
	 */
	public static String getVersionInfo(){
		return version + " - " + builddate; 
	}
	
	/**
	 * @return
	 */
	public static String getVersionwithCurrentDate(){
		return version + " - " + new Date().toString();
	}
}