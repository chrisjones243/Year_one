

public class App {
    public static void main(String[] args) throws Exception {
        String decryptFile = "files/decrypt.txt";
        String ecryptFile = "files/encrypt.txt";
        String keyFile = "files/key.txt";


        VigenereCipher cipher = new VigenereCipher();
        String encrypted = cipher.encrypt(ecryptFile, keyFile);
        System.out.println("\nEncrypted: \n" + encrypted);

        String decrypted = cipher.decrypt(decryptFile, keyFile);
        System.out.println("\nDecrypted: \n" + decrypted);


    }
}
