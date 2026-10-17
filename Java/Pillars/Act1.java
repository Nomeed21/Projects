class Calculator{
    int multiply(int num1, int num2){
        return num1 * num2;
    }

    int multiply(int num1, int num2, int num3){
        return num1 * num2 * num3;
    }

    double multiply(double num1, double num2){
        return num1 * num2;
    }
}

public class Act1{
    public static void main(String[] args) {
        Calculator expression = new Calculator();

        System.out.println("Product of 2 integers: " + expression.multiply(10, 5));
        System.out.println("Product of 3 integers: " + expression.multiply(10, 5, 40));
        System.out.println("Product of 2 decimal numbers: " + expression.multiply(3.5, 5.5));
    }
    
}