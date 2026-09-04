import java.util.Scanner;
import java.util.Random;


class Account {
Random random = new Random();
int accNum;
String name;
float balance;

Account(String name) {
this.name = name;
accNum = random.nextInt(1_000_000);
balance = 5000;
}


Account(int accNum, String name) {
this.accNum = accNum;
this.name = name;
balance = 5000;
}

Account(int accNum, String name, float balance) {
this.accNum = accNum;
this.name = name;
this.balance = balance;
}

void display() {
System.out.println("Name:" + name );
System.out.printf("Account number: %06d%n ", accNum);  
System.out.println("Balance: " + balance);
}
}


public class Bank {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String name;
        float balance;
        int accNum;

        System.out.println("Input User 1 Name only: ");
        name = scanner.nextLine();
        Account s1 = new Account(name);

        System.out.println("Input User 2 Name: ");
        name = scanner.nextLine();
        System.out.println("Input User 2 accNum: ");
        accNum = scanner.nextInt();
        scanner.nextLine();
        Account s2 = new Account(accNum, name);

        System.out.println("Input User 3 Name: ");
        name = scanner.nextLine();
        System.out.println("Input User 3 accNum: ");
        accNum = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Input User 2 balance: ");
        balance = scanner.nextFloat();
        Account s3 = new Account(accNum, name, balance);

        s1.display();
        s2.display();
        s3.display();
    }
}

