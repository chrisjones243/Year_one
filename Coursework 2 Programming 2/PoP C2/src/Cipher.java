import java.util.ArrayList;
import java.io.*;

public interface Cipher {
	
	/**
	* Encrypts a message using a key.
	*
	* @param  message_filename		the filename of the message to be encrypted
	* @param  key_filename			the filename of the key to be used to encrypt the message
	* @return       The encrypted message
	*/
	public String encrypt(String message_filename, String key_filename);
	
	/**
	* Decrypts a message using a key.
	*
	* @param  message_filename		the filename of the message to be decrypted
	* @param  key_filename			the filename of the key to be used to decrypt the message
	* @return       The decrypted message
	*/
	public String decrypt(String message_filename, String key_filename);
}

class VigenereCipher implements Cipher {

    private String extendString(int num, String text) {
        int textLen = text.length();
        String extendedText = "";
        for (int i = 0; i < num; i++) {
            extendedText += text.charAt(i % textLen);
        }
        return extendedText;
    }


    private ArrayList<String> readString(String filename) {
        ArrayList<String> messages = new ArrayList<String>();

        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line = br.readLine();
            while (line != null) {
                messages.add(line.toUpperCase());
                messages.add("\n");
                line = br.readLine();
            }
            br.close();
        } catch (Exception e) {
            System.out.println("Error reading file");
        }

        return (messages);
    }


    @Override
    public String encrypt(String message_filename, String key_filename) {
        ArrayList<String> messages = readString(message_filename);
        ArrayList<String> keys = readString(key_filename);

        String key = keys.get(0);

        String encryptedMessage = "";

        int messageLength = 0;
        for (String message : messages) {
            messageLength += message.length();
        }

        String keyStream = extendString(messageLength, key);

        String messageTogether = "";
        for (String message : messages) {
            messageTogether += message;
        }

        for (int i = 0; i < messageTogether.length(); i++) {
            if (messageTogether.charAt(i) >= 'A' && messageTogether.charAt(i) <= 'Z') {
                // if message is a letter
                encryptedMessage += (char) (65 + (messageTogether.charAt(i) + keyStream.charAt(i) + 26) % 26);
            } else {
                encryptedMessage += messageTogether.charAt(i);
            }
        }

        // remove last newline
        if (encryptedMessage != null && encryptedMessage.length() > 0 && encryptedMessage.charAt(encryptedMessage.length() - 1) == '\n') {
            encryptedMessage = encryptedMessage.substring(0, encryptedMessage.length() - 1);
        }

        return encryptedMessage;
    }


    @Override
    public String decrypt(String message_filename, String key_filename) {
        ArrayList<String> ciphers = readString(message_filename);
        ArrayList<String> keys = readString(key_filename);

        String key = keys.get(0);

        String decryptedMessage = "";

        int cipherLength = 0;
        for (String cipher : ciphers) {
            cipherLength += cipher.length();
        }

        String keyStream = extendString(cipherLength, key);

        String cipherTogether = "";
        for (String cipher : ciphers) {
            cipherTogether += cipher;
        }

        for (int i = 0; i < cipherTogether.length(); i++) {
            if (cipherTogether.charAt(i) >= 'A' && cipherTogether.charAt(i) <= 'Z') {
                // if message is a letter
                decryptedMessage += (char) (65 + (cipherTogether.charAt(i) - keyStream.charAt(i) + 26) % 26);
            } else {
                decryptedMessage += cipherTogether.charAt(i);
            }
        }

        // remove last newline
        if (decryptedMessage != null && decryptedMessage.length() > 0 && decryptedMessage.charAt(decryptedMessage.length() - 1) == '\n') {
            decryptedMessage = decryptedMessage.substring(0, decryptedMessage.length() - 1);
        }

        return decryptedMessage;
    }
    
}
