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

package krypto;

import java.io.InputStream;
import java.security.KeyStore;

/**
 * Bietet Methoden rund um den KeyStore an.
 *
 */
public class KeyStoreUtils {

	
	/**
	 * @return
	 * @throws Exception
	 */
	public static KeyStore createKeyStore() throws Exception {
		
		KeyStore store = KeyStore.getInstance("PKCS12", "BC");
		store.load(null, null);
		
		return store;
	}
	
	/**
	 * Lädt einen Keystore.
	 * @param input
	 * @param passwort
	 * @return
	 * @throws Exception
	 */
	public static KeyStore createKeyStore(InputStream input, String passwort) 
			throws Exception {
		
		KeyStore store = KeyStore.getInstance("PKCS12", "BC");
		store.load(input, passwort.toCharArray());
		
		return store;
	}
}
