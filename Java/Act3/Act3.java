// This packages allows us to use File handling
import java.io.File;
import java.io.FileWriter;
import java.io.FileReader;
import java.io.BufferedReader;

// package to handle erros;
import java.io.IOException;

//package to get the user's input
import java.util.Scanner;

public class Act3{
    
    public static void main(String[] args){
        // creating objects for each class will run the code inside their constructors
        Scanner scanner = new Scanner(System.in);
        while(true){
            int choice;
            System.out.println("FILE HANDLING MENU:");
            System.out.println("[1] Create/Check file if exists");
            System.out.println("[2] Write in the file");
            System.out.println("[3] Read File");
            System.out.println("[4] Delete File");
            System.out.println("[5] Exit");
            System.out.println("Select your choice: ");
            choice = scanner.nextInt();
            scanner.nextLine();
            switch(choice){
                case 1:
                    // this object will create the file or tell us if it already exists 
                    CreateNewFile create = new CreateNewFile();
                    System.out.println("Press Enter to continue...");
                    scanner.nextLine();
                    break;
                case 2:
                    // this object let us write in the File
                    WriteinFile write = new WriteinFile();
                    System.out.println("Press Enter to continue...");
                    scanner.nextLine();
                    break;
                
                case 3:
                    // this object let us read the file
                    ReadFiles read = new ReadFiles();
                    System.out.println("Press Enter to continue...");
                    scanner.nextLine();
                    break;

                case 4:
                    // this object let us delete the file
                    DeleteFile delete = new DeleteFile();
                    System.out.println("Press Enter to continue...");
                    scanner.nextLine();
                    break;

                case 5:
                    return;
                
                default:
                    System.out.println("Invalid choice!");
                    System.out.println("Press Enter to continue...");
                    scanner.nextLine();
            }
        }
    }
    
}


// this class creates and check if a file already exist 
class CreateNewFile{
    
    CreateNewFile(){
        // try catch block are for errors that occur when handling files
        try{
            // the File is a type of class that is used for file handling so we make an object to access the methods
            File obj = new File("File.txt");
            if (obj.createNewFile()){
                System.out.println("File created!: " + obj.getName());
            }
            else{
                System.out.println("File already exists");
            }
        }
        catch (IOException e){
            System.out.println("Error handling file");
            e.printStackTrace(); // error details 
        }
    }
}

// this class writes text into the file
class WriteinFile{
    
    WriteinFile(){
        // try catch block are for errors that occur when handling files
        try{
            // FileWriter is the class used to write text into a file
            FileWriter writer = new FileWriter("File.txt");

            // Scanner lets us get input from the user
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter text to write into the file: ");
            String userInput = sc.nextLine();

            // this actually writes the text into the file
            writer.write(userInput);
            writer.close(); // always close the writer to save the changes
            System.out.println("Successfully wrote to the file!");
        }
        catch (IOException e){
            System.out.println("Error writing to file");
            e.printStackTrace(); // error details
        }
    }
}

// this class reads and displays whats inside the file
class ReadFiles{

    ReadFiles(){
        // try catch block are for errors that occur when handling files
        try{
            // BufferedReader lets us read the file line by line
            FileReader fr = new FileReader("File.txt");
            BufferedReader br = new BufferedReader(fr);

            String line;
            System.out.println("Reading file: ");
            // this loop keeps reading until there are no more lines left
            while ((line = br.readLine()) != null){
                System.out.println(line);
            }

            br.close(); // always close the reader when done
        }
        catch (IOException e){
            System.out.println("Error reading file");
            e.printStackTrace(); // error details
        }
    }
}

// this class deletes the file
class DeleteFile{

    DeleteFile(){
        // File object is needed to access the delete method
        File obj = new File("File.txt");

        // delete() returns true or false depending if it worked
        if (obj.delete()){
            System.out.println("Deleted the file: " + obj.getName());
        }
        else{
            System.out.println("Failed to delete the file");
        }
    }
}

// reference: https://www.w3schools.com/java/java_files.asp