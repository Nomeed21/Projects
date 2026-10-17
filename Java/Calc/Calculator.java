import java.util.Scanner;

public class Calculator {

    private static final Expression expr = new Expression();

    private static String display = "0";
    private static int accumulator = 0;
    private static char pendingOperator = '\0';
    private static String currentBase = "DEC";

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        boolean running = true;

        System.out.println("========================");
        System.out.println("====  CALCULATOR  ======");
        System.out.println("========================\n");

        while (running) {
            System.out.println("Value (" + currentBase + "): " + display);
            if (pendingOperator != '\0') {
                System.out.println("(" + display + " " + pendingOperator + " ? )");
            }
            System.out.println("[d]ecimal  [b]inary  [h]ex  [o]ctal   + - * /   =   [e]xit");
            System.out.println("(hex digits B/D/E must be typed uppercase to tell them apart from the menu letters)");
            System.out.print("Input: ");

            String input = sc.nextLine().trim();
            if (input.isEmpty()) {
                continue;
            }

            switch (input) {
                case "e":
                    running = false;
                    continue;

                case "d":
                    switchBase("DEC");
                    break;

                case "b":
                    switchBase("BIN");
                    break;

                case "h": case "H":
                    switchBase("HEX");
                    break;

                case "o": case "O":
                    switchBase("OCT");
                    break;

                case "+": case "-": case "*": case "/":
                    applyOperator(input.charAt(0));
                    break;

                case "=":
                    evaluate();
                    break;

                default:
                    enterNumber(input);
                    break;
            }

            System.out.println();
        }

        System.out.println("Goodbye!");
        sc.close();
    }

    private static void enterNumber(String input) {
        try {
            parseInBase(input, currentBase); // validate before committing
            display = input.toUpperCase();
        } catch (NumberFormatException ex) {
            System.out.println("\"" + input + "\" isn't a valid " + currentBase + " number.");
        }
    }

    private static void applyOperator(char operator) {
        if (!foldDisplayIntoAccumulator()) {
            return; // an error (e.g. divide by zero) was already reported
        }
        pendingOperator = operator;
    }

    private static void evaluate() {
        if (pendingOperator != '\0') {
            foldDisplayIntoAccumulator();
        }
        pendingOperator = '\0';
    }

    /**
     * Combines the current display value into the accumulator using pendingOperator.
     * Returns false if the operation couldn't be completed (bad input, divide by zero).
     */
    private static boolean foldDisplayIntoAccumulator() {
        int value;
        try {
            value = parseInBase(display, currentBase);
        } catch (NumberFormatException ex) {
            System.out.println("\"" + display + "\" isn't a valid " + currentBase + " number.");
            return false;
        }

        if (pendingOperator == '\0') {
            accumulator = value;
        } else if (pendingOperator == '/' && value == 0) {
            System.out.println("Cannot divide by zero.");
            pendingOperator = '\0';
            return false;
        } else {
            expr.num1 = accumulator;
            expr.num2 = value;
            expr.operator = pendingOperator;
            expr.calculate();
            accumulator = expr.num1;
        }

        display = formatInBase(accumulator, currentBase);
        return true;
    }

    // Re-renders the current display value in a new base, keeping the number itself.
    private static void switchBase(String newBase) {
        try {
            int value = parseInBase(display, currentBase);
            currentBase = newBase;
            display = formatInBase(value, newBase);
        } catch (NumberFormatException ex) {
            currentBase = newBase;
            display = "0";
        }
    }

    private static int parseInBase(String text, String base) {
        switch (base) {
            case "HEX": return expr.hexToDec(text);
            case "OCT": return expr.octToDec(text);
            case "BIN": return expr.binToDec(text);
            default: return Integer.parseInt(text);
        }
    }

    private static String formatInBase(int num, String base) {
        switch (base) {
            case "HEX": return expr.decToHex(num).toUpperCase();
            case "OCT": return expr.decToOct(num);
            case "BIN": return expr.decToBin(num);
            default: return Integer.toString(num);
        }
    }
}

class Expression {
    char operator;
    String str1;
    String str2;
    int num1;
    int num2;

    Expression() {
        operator = '\0';
        num1 = 0;
        num2 = 0;
        str1 = "0";
        str2 = "0";
    }

    Expression(String num1, String num2, char operator) {
        this.str1 = num1;
        this.str2 = num2;
        this.operator = operator;
    }

    void calculate() {
        switch (operator) {
            case '+':
                num1 += num2;
                break;

            case '-':
                num1 -= num2;
                break;

            case 'x', '*':
                num1 *= num2;
                break;

            case '/':
                if (num2 == 0) System.out.println("Cannot be divided by zero");
                else num1 /= num2;
                break;

            default:
                System.out.println("Invalid operator");
                break;
        }
    }

    int binToDec(String num) {
        num1 = Integer.parseInt(num, 2);
        return num1;
    }

    int hexToDec(String num) {
        num1 = Integer.parseInt(num, 16);
        return num1;
    }

    int octToDec(String num) {
        num1 = Integer.parseInt(num, 8);
        return num1;
    }

    String decToBin(int num) {
        str1 = Integer.toBinaryString(num);
        return str1;
    }

    String decToHex(int num) {
        str1 = Integer.toHexString(num);
        return str1;
    }

    String decToOct(int num) {
        str1 = Integer.toOctalString(num);
        return str1;
    }
}