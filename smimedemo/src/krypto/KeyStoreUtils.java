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
