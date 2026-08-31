//this package allows us to use file handling
public class Student {
    private String name;
    private int id;
    private double grade;

    // Constructor
    public Student(String name, int id, double grade) {
        this.name = name;
        this.id = id;
        this.grade = grade;
    }

    // Getters and Setters
    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public double getGrade() {
        return grade;
    }

    public void setGrade(double grade) {
        this.grade = grade;
    }

    // Method to print student details
    @Override
    public String toString() {
        return "Student [name=" + name + ", id=" + id + ", grade=" + grade + "]";
    }
}
