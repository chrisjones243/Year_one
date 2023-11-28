import java.util.ArrayList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.BufferedWriter;
import java.io.PrintWriter;
import java.io.File;


class PopThread implements Runnable {

    private ArrayList<String> files;

    public PopThread (ArrayList<String> files) {
        this.files = files;

        File file = new File("result.txt");
        if (file.exists()) {
            file.delete();
        }
        try {
            file.createNewFile();
        } catch (Exception e) {
            System.out.println("Error creating file");
        }
    }
    
    public void run() {

        ArrayList<Thread> threads = new ArrayList<Thread>();

        for (int i = 0; i < this.files.size() ; i++) {
            threads.add(new Thread(new PushThread(this.files.get(i))));
            // PushThread pushThread = new PushThread(this.files.get(i));
            // Thread thread = new Thread(threads.get(i));
            threads.get(i).start();
        }

        for (int i = 0; i < this.files.size() ; i++) {
            try {
                threads.get(i).join();
            } catch (Exception e) {
                // System.out.println("Error sleeping");
            }
        }
    }

}

class PushThread implements Runnable {

    private String fileName = "";
    private String lastLine;

    public PushThread (String fileName) {
        this.fileName = fileName;  
    }

    private String readString (String filename) {
        String message = "";

        try {
            BufferedReader br = new BufferedReader(new FileReader("files/" + filename));
            String line = br.readLine();
            while (line != null) {
                message += line;
                message += "\n";
                this.lastLine = line;
                line = br.readLine();
            }
            br.close();
            message = message.substring(0, message.length() - 1);
        } catch (Exception e) {
            // System.out.println("Error reading file");
        }

        return (message);
    }

    private int getCurrentIndex () {
        String line = this.lastLine;
        line = line.substring(1, 4);
        int index = Integer.parseInt(line) - 1;
        return index;
    }

    // private int getNumFiles () {
    //     String line = this.lastLine;
    //     line = line.substring(5, 8);
    //     int numFiles = Integer.parseInt(line);
    //     return numFiles;
    // }

    private void writeToResult (String message) {
        File file = new File("result.txt");
        if (!file.exists()) {
            try {
                file.createNewFile();
            } catch (Exception e) {
                // System.out.println("Error creating file");
            }
        }
        try {
            FileWriter fw = new FileWriter("result.txt", true); // true = append
            BufferedWriter bw = new BufferedWriter(fw);
            PrintWriter out = new PrintWriter(bw);

            out.println(message); // write to file
            out.close(); // close file
        } catch (Exception e) {
            // System.out.println("Error writing to file");
        }
    }

    public void run() {

        // System.out.println("Reading: " + this.fileName);
        String message = readString(this.fileName); 
        int currentIndex = getCurrentIndex();
        // int numFiles = getNumFiles();

        int sleepTime = 1 * currentIndex; // sleep time is proportional to the index of the file

        try {
            Thread.sleep(sleepTime);
            this.writeToResult(message);
        } catch (Exception e) {
            // System.out.println("Error sleeping");
        }
    }

}