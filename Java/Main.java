class Student {
int id;
String name;
String course;
// Constructor 1: Only name
Student(String name) {
this.name = name;
}

// Constructor 2: ID and name

Student(int id, String name) {

this.id = id;
this.name = name;
}

// Constructor 3: ID, name, and course
Student(int id, String name, String course) {
this.id = id;
this.name = name;
this.course = course;
}

void display() {
System.out.println(id + " " + name + " " + course);
}
}
public class Main {

public static void main(String[] args) {
Student s1 = new Student("Ariel");
Student s2 = new Student(101, "John");
Student s3 = new Student(102, "Maria", "BSIT");

s1.display();
s2.display();
s3.display();
}
}

