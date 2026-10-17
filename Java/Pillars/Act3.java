/*Scenario: A university wants a system that calculates fees for Regular Students, Scholarship
Students, and Graduate Students. All students have calculateFees(), but each type uses a different
calculation.
Student Tasks:
10. Create a parent class or interface named Student.
11. Create three specialized student classes.
12. Override calculateFees().
13. Use a parent reference to access different student objects.
14. Display the calculated fee for each student.
 */
abstract class Student {
    String name;
    int id;
    int units;

    Student(String name, int id, int units) {
        this.name = name;
        this.id = id;
        this.units = units;
    }

    abstract double calculateFees();
}

class Regular extends Student {
    Regular(String name, int id, int units) {
        super(name, id, units);
    }

    @Override
    double calculateFees() {
        return units * 200.00;
    }
}

class Scholar extends Student {
    Scholar(String name, int id, int units) {
        super(name, id, units);
    }

    @Override
    double calculateFees() {
        return 0.00;
    }
}

class Graduate extends Student {
    Graduate(String name, int id, int units) {
        super(name, id, units);
    }

    @Override
    double calculateFees() {
        return units * 500.00;
    }
}

public class Act3 {
    public static void main(String[] args) {
        Student[] students = {
            new Regular("Mel Chor", 738, 25),
            new Scholar("Gas Par", 482, 24),
            new Graduate("Juan Cruz", 958, 12)
        };

        for (Student student : students) {
            System.out.println( "Name: " + student.name + "\nID: " + student.id + " \nTuition Fee: " + student.calculateFees() + "\n");
        }
    }
}
/*Challenge Question: Why is polymorphism better than creating completely separate methods such as
calculateRegularFee(), calculateScholarshipFee(), and calculateGraduateFee? Explain using
flexibility, maintainability, reusability, and extensibility

Polymorphism is better than creating a new separate methods because it is flexible, maintainable,
resuable, and extensible. It is flexible because I can use different objects using a single program like
declaring an object student, but also making it regular, scholar, or graduate. It is Reusable because
I can use the same code with entirely different objects. Maintainable because changes to a specific fee 
calculation can be made inside that student subclass without modifying the other subclasses. 
It is extensible because new types of students can be added by creating another subclass that
use calculateFees(), without rewriting the existing code that processes other students.
*/