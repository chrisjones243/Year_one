import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;

public class App {

    public static void printContents(String filename) {

        try {
            BufferedReader br = new BufferedReader(new FileReader(filename));
            String line = br.readLine();
            while (line != null) {
                System.out.println(line);
                line = br.readLine();
            }
            br.close();
        } catch (Exception e) {
            System.out.println("Error reading result file");
        }
    }

    public static void main(String[] args) throws Exception {
        // Cipher ------------------
        // String decryptFile = "files/decrypt.txt";
        // String ecryptFile = "files/encrypt.txt";
        // String keyFile = "files/key.txt";


        // VigenereCipher cipher = new VigenereCipher();
        // String encrypted = cipher.encrypt(ecryptFile, keyFile);
        // System.out.println("\nEncrypted: \n" + encrypted);

        // String decrypted = cipher.decrypt(decryptFile, keyFile);
        // System.out.println("\nDecrypted: \n" + decrypted);

        // Sorting ------------------
        // CustomSort sort = new CustomSort();
        // ArrayList<Double> values = new ArrayList<>();
        // double[] vals = {9.0, 8.0, 7.0, 6.0, 5.0, 4.0, 3.0, 2.0, 1.0};
        // for (double val : vals) {
        //     values.add(val);
        // }

        // sort.setValues(values);

        // // sort.sort();

        // System.out.println(sort.getGaps());
        // System.out.println(sort.values);

        // LinkedList ------------------
    //     SortedLinkedList list = new SortedLinkedList();
        // list.add("Cha");
    //     list.add(new Node("Charlie"));
    // list.add(new Node("Alpha"));
    // list.add(new Node("Bravo"));
        
        // System.out.println("List size: " + list.size());
        // list.print();

        // System.out.println("Get index 0;" + list.get(0).getString());
        // System.out.println("Is \"d\" in list: " + list.isPresent("d"));

        // System.out.println("Remove first node: " + list.removeFirst());
        // list.print();

        // System.out.println("Remove last node: " + list.removeLast());
        // list.print();

        // System.out.println("Remove 5th node: " + list.remove(5));
        // list.print();

        // System.out.println("Remove \"d\" node: " + list.remove("d"));
        // list.print();

        // Node newNode = new Node("g");
        // list.add(newNode); // needs fixing
        // list.print();

        // list.orderDescending();
        // list.print();
        // System.out.println("-----");
        // list.orderAscending();
        // list.print();

        // PopThread ------------------
        
        ArrayList<String> filesOne = new ArrayList<String>();
        filesOne.add("1831-06-01.txt");
        filesOne.add("2003-08-27.txt");

        ArrayList<String> filesTwo = new ArrayList<String>();
        filesTwo.add("1961-04-12.txt");
        filesTwo.add("1972-12-11.txt");

        int numAttempts = 1;

        for(int i = 0; i < numAttempts; i++) {
            System.out.println("Run: " + (i+1));
            PopThread popRunnableOne = new PopThread(filesOne);
            PopThread popRunnableTwo = new PopThread(filesTwo);
            Thread threadOne = new Thread(popRunnableOne);
            Thread threadTwo = new Thread(popRunnableTwo);
            threadOne.start();
            threadTwo.start();
            try {
                threadOne.join();
                threadTwo.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            printContents("result.txt");
        }


    }
}
