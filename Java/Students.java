
import java.util.Scanner;;

class Student {
int id;
String name;
String program;

Student(String name) {
this.name = name;
}


Student(int id, String name) {

this.id = id;
this.name = name;
}

Student(int id, String name, String program) {
this.id = id;
this.name = name;
this.program = program;
}

void display() {
System.out.println("ID: " + id + ", Name: " + name + ", Program: " + program);
}
}


public class Students {

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String name, program;
        int id;

        System.out.println("Input student 1 Name only: ");
        name = scanner.nextLine();
        Student s1 = new Student(name);

        System.out.println("Input student 2 Name: ");
        name = scanner.nextLine();
        System.out.println("Input student 2 ID: ");
        id = scanner.nextInt();
        scanner.nextLine();
        Student s2 = new Student(id, name);

        System.out.println("Input student 3 Name: ");
        name = scanner.nextLine();
        System.out.println("Input student 3 ID: ");
        id = scanner.nextInt();
        scanner.nextLine();
        System.out.println("Input student 2 Program: ");
        program = scanner.nextLine();
        Student s3 = new Student(id, name, program);

        s1.display();
        s2.display();
        s3.display();
    }
}

