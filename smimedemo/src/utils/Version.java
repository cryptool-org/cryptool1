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