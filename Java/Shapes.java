
import java.util.Scanner;

class Shape {
String shapeName;
double area;
 

Shape(double radius) {
shapeName = "Circle";
area = Math.PI * radius * radius;
}


Shape(int length, int width) {
shapeName = "Rectangle";
area = length * width;
}

Shape(int side) {
shapeName = "Square";
area = side * side;
}

Shape(double base, double height){
    shapeName = "Triangle";
    area = (base * height) / 2;
}

void display() {
System.out.println("Shape: " + shapeName);
System.out.println("Area: " + area);
System.out.println();
}
}


public class Shapes {

public static void main(String[] args) {
boolean running = true;
Scanner sc = new Scanner(System.in);
while(running){
    int choice, length, width;
    float radius, base, height;
    choice = 0;
    System.out.println("MENU");
    System.out.println("[1]Calculate shapes");
    System.out.println("[2] Exit");
    System.out.println("Input choice: ");
    choice = sc.nextInt();
    switch(choice){
        case 1:
            System.out.println("Select Shapes");
            System.out.println("[1] Squares");
            System.out.println("[2] Rectangle");
            System.out.println("[3] Circle");
            System.out.println("[4] Triangle");
            System.out.println("[5] Exit");
            System.out.println("Select choice: ");
            choice = sc.nextInt();

            switch(choice){
                case 1:
                    System.out.println("Enter side length: ");
                    length = sc.nextInt();
                    Shape shape1 = new Shape(length);
                    shape1.display();
                    break;
                case 2:
                    System.out.println("Enter  length: ");
                    length = sc.nextInt();
                    System.out.println("Enter  width: ");
                    width = sc.nextInt();
                    Shape shape2 = new Shape(length, width);
                    shape2.display();
                    break;
                case 3:
                    System.out.println("Enter  radius: ");
                    radius = sc.nextFloat();
                    Shape shape3 = new Shape(radius);
                    shape3.display();
                    break;
                case 4:
                    System.out.println("Enter  base: ");
                    base = sc.nextFloat();
                    System.out.println("Enter  height: ");
                    height = sc.nextFloat();
                    Shape shape4 = new Shape(base, height);
                    shape4.display();
                    break;
                case 5: 
                    running = false;
                    break;
                default:
                    System.out.print("Invalid choice!");
            }
            break;
            
        case 2:
            running = false;
            break;

        default:
            System.out.print("Invalid choice!");
    }
}
}
}

