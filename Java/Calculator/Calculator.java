import javafx.animation.PauseTransition;
import javafx.application.Application;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ComboBox;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.RadioButton;
import javafx.scene.control.Tab;
import javafx.scene.control.TabPane;
import javafx.scene.control.TextField;
import javafx.scene.control.TextFormatter;
import javafx.scene.control.ToggleGroup;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.Priority;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.util.Duration;

import java.util.Arrays;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Locale;
import java.util.Map;
import java.util.Random;
import java.util.Set;
import java.util.function.Consumer;
import java.util.function.Supplier;
import java.util.function.UnaryOperator;

public class Calculator extends Application {

    private final Expression expr = new Expression();
    private final Map<String, Button> digitButtons = new HashMap<>();
    private final ObservableList<String> historyItems = FXCollections.observableArrayList();
    private final Random random = new Random();

    private double total = 0;
    private char currentOperator = '\0';
    private boolean startNewNumber = true;
    private String currentBase = "DEC";

    // --- Mixed Bases tab state ---
    private String mixedBase1 = "DEC";
    private String mixedBase2 = "DEC";
    private String mixedResultBase = "DEC";
    private double mixedResultValue = 0;
    private boolean mixedHasResult = false;
    private TextField mixedOperand1Field;
    private TextField mixedOperand2Field;
    private TextField mixedResultField;

    // Shows the operation that will run next, e.g. "12 +", while the next
    // number is being entered. Empty when nothing is pending.
    private TextField pendingField;
    // A short, fun observation about the most recent result.
    private Label funFactLabel;
    // Kept so flashDisplay()/updateFunFact() can reach the main display
    // without threading it through every method signature.
    private TextField mainDisplayRef;

    // --- Fun feature: the classic "upside-down calculator word" trick ---
    // Map each digit to the letter it resembles when the display (or the
    // digit string) is read upside down.
    private static final Map<Character, Character> UPSIDE_DOWN_MAP = new HashMap<>();
    static {
        UPSIDE_DOWN_MAP.put('0', 'O');
        UPSIDE_DOWN_MAP.put('1', 'I');
        UPSIDE_DOWN_MAP.put('2', 'Z');
        UPSIDE_DOWN_MAP.put('3', 'E');
        UPSIDE_DOWN_MAP.put('4', 'H');
        UPSIDE_DOWN_MAP.put('5', 'S');
        UPSIDE_DOWN_MAP.put('6', 'G');
        UPSIDE_DOWN_MAP.put('7', 'L');
        UPSIDE_DOWN_MAP.put('8', 'B');
    }

    private static final Set<String> FUN_WORDS = new HashSet<>(Arrays.asList(
        "BOSS", "SOS", "BIG", "BEE", "BILE", "BOIL", "BILGE", "GLOBE", "HOLE",
        "HOSE", "LOSE", "LOOSE", "GOOSE", "SHELL", "SIZE", "SLOB", "HILL",
        "SILO", "SOLE", "EGGS", "IGLOO", "HIGH", "SIGH", "OBOE", "HOBO",
        "ZOO", "BOO", "LOG", "BOG", "HOG", "LEG", "EEL", "BELL", "SELL",
        "SIS", "GEL", "LOBE"
    ));

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        TextField display = new TextField("0");
        display.setPrefHeight(60);
        display.setAlignment(Pos.CENTER_RIGHT);
        display.setEditable(false);
        display.setStyle("-fx-font-size: 20px;");
        mainDisplayRef = display;

        pendingField = new TextField("");
        pendingField.setPrefHeight(26);
        pendingField.setAlignment(Pos.CENTER_RIGHT);
        pendingField.setEditable(false);
        pendingField.setFocusTraversable(false);
        pendingField.setStyle("-fx-font-size: 13px; -fx-text-fill: gray;");

        funFactLabel = new Label("Number checker");
        funFactLabel.setWrapText(true);
        funFactLabel.setStyle("-fx-font-size: 12px; -fx-text-fill: #6a4fb3; -fx-font-style: italic;");

        HBox baseSelector = buildBaseSelector(display);

        GridPane grid = new GridPane();
        grid.setHgap(5);
        grid.setVgap(5);
        grid.setPadding(new Insets(10));

        String[] buttons = {
            "7", "8", "9", "+",
            "4", "5", "6", "-",
            "1", "2", "3", "*",
            "A", "0", "B", "/",
            "C", "D", "E", "F",
            "=", "Clear"
        };

        int row = 0;
        int col = 0;

        for (String value : buttons) {
            Button button = new Button(value);
            button.setPrefSize(70, 60);
            button.setOnAction(event -> handleButton(value, display));

            if (isDigit(value)) {
                digitButtons.put(value, button);
            }

            if (value.equals("=")) {
                grid.add(button, 0, 5, 2, 1);
            } else if (value.equals("Clear")) {
                grid.add(button, 2, 5, 2, 1);
            } else {
                grid.add(button, col, row);
                col++;

                if (col == 4) {
                    col = 0;
                    row++;
                }
            }
        }

        Button luckyButton = new Button("\uD83C\uDFB2 Randomize number");
        luckyButton.setPrefSize(300, 40);
        luckyButton.setOnAction(e -> insertRandomNumber(display));
        grid.add(luckyButton, 0, 6, 4, 1);

        updateDigitAvailability();

        VBox calculatorPane = new VBox(8);
        calculatorPane.setPadding(new Insets(10));
        calculatorPane.getChildren().addAll(baseSelector, pendingField, display, funFactLabel, grid);

        VBox historyPane = buildHistoryPane();
        VBox mixedBasesPane = buildMixedBasesPane();

        Tab calculatorTab = new Tab("Calculator", calculatorPane);
        calculatorTab.setClosable(false);

        Tab mixedBasesTab = new Tab("Mixed Bases", mixedBasesPane);
        mixedBasesTab.setClosable(false);

        Tab historyTab = new Tab("History", historyPane);
        historyTab.setClosable(false);

        TabPane tabPane = new TabPane(calculatorTab, mixedBasesTab, historyTab);

        Scene scene = new Scene(tabPane, 340, 700);

        primaryStage.setTitle("Calculator");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private VBox buildHistoryPane() {
        ListView<String> historyView = new ListView<>(historyItems);
        historyView.setPlaceholder(new Label("No calculations yet"));
        VBox.setVgrow(historyView, Priority.ALWAYS);

        Button clearHistoryButton = new Button("Clear History");
        clearHistoryButton.setOnAction(e -> historyItems.clear());

        VBox pane = new VBox(10);
        pane.setPadding(new Insets(10));
        pane.getChildren().addAll(historyView, clearHistoryButton);
        return pane;
    }

    private HBox buildBaseSelector(TextField display) {
        ToggleGroup group = new ToggleGroup();
        HBox box = new HBox(10);
        box.setPadding(new Insets(0, 10, 0, 10));

        String[] bases = {"DEC", "HEX", "OCT", "BIN"};
        for (String base : bases) {
            RadioButton radio = new RadioButton(base);
            radio.setToggleGroup(group);
            radio.setSelected(base.equals(currentBase));
            radio.setOnAction(e -> {
                String oldBase = currentBase;
                currentBase = base;
                convertDisplayBase(display, oldBase, base);
                updateDigitAvailability();
                refreshPendingDisplay();
            });
            box.getChildren().add(radio);
        }

        return box;
    }

    // --- Mixed Bases tab ---
    // Lets the user enter two operands in independently-chosen bases,
    // pick an operation, and view the result in a base of its own choosing.
    private VBox buildMixedBasesPane() {
        mixedOperand1Field = new TextField();
        mixedOperand2Field = new TextField();
        mixedResultField = new TextField();
        mixedResultField.setEditable(false);
        mixedResultField.setStyle("-fx-font-size: 16px;");

        attachBaseInputValidation(mixedOperand1Field, () -> mixedBase1);
        attachBaseInputValidation(mixedOperand2Field, () -> mixedBase2);

        HBox base1Radios = buildMixedBaseRadioGroup(mixedBase1, base -> {
            mixedBase1 = base;
            if (!isValidForBase(mixedOperand1Field.getText(), base)) {
                mixedOperand1Field.clear();
            }
        });

        HBox base2Radios = buildMixedBaseRadioGroup(mixedBase2, base -> {
            mixedBase2 = base;
            if (!isValidForBase(mixedOperand2Field.getText(), base)) {
                mixedOperand2Field.clear();
            }
        });

        HBox resultRadios = buildMixedBaseRadioGroup(mixedResultBase, base -> {
            mixedResultBase = base;
            if (mixedHasResult) {
                mixedResultField.setText(formatInBase(mixedResultValue, mixedResultBase));
            }
        });

        ComboBox<String> operatorBox = new ComboBox<>(FXCollections.observableArrayList("+", "-", "*", "/"));
        operatorBox.setValue("+");

        Button calculateButton = new Button("Calculate");
        calculateButton.setOnAction(e -> computeMixedBases(operatorBox.getValue()));

        HBox operatorRow = new HBox(10, new Label("Operation:"), operatorBox, calculateButton);
        operatorRow.setAlignment(Pos.CENTER_LEFT);

        VBox operand1Box = new VBox(5, new Label("Operand 1:"), mixedOperand1Field, base1Radios);
        VBox operand2Box = new VBox(5, new Label("Operand 2:"), mixedOperand2Field, base2Radios);
        VBox resultBox = new VBox(5, new Label("Result:"), mixedResultField, resultRadios);

        VBox pane = new VBox(18, operand1Box, operand2Box, operatorRow, resultBox);
        pane.setPadding(new Insets(15));
        return pane;
    }

    // Builds a row of DEC/HEX/OCT/BIN radio buttons in their own toggle
    // group, invoking onSelect whenever the user picks a different base.
    private HBox buildMixedBaseRadioGroup(String initialBase, Consumer<String> onSelect) {
        ToggleGroup group = new ToggleGroup();
        HBox box = new HBox(10);

        String[] bases = {"DEC", "HEX", "OCT", "BIN"};
        for (String base : bases) {
            RadioButton radio = new RadioButton(base);
            radio.setToggleGroup(group);
            radio.setSelected(base.equals(initialBase));
            radio.setOnAction(e -> onSelect.accept(base));
            box.getChildren().add(radio);
        }

        return box;
    }

    // Attaches a TextFormatter that rejects any keystroke that would make
    // the field's text invalid for its currently-selected base, popping up
    // an alert (mirroring the disabled-digit-button behavior on the main
    // Calculator tab, but for free-typed input) instead of allowing it in.
    private void attachBaseInputValidation(TextField field, Supplier<String> baseSupplier) {
        UnaryOperator<TextFormatter.Change> filter = change -> {
            String newText = change.getControlNewText();
            String base = baseSupplier.get();
            if (isValidForBase(newText, base)) {
                return change;
            }
            if (!change.getText().isEmpty()) {
                showInvalidInputAlert(change.getText(), base);
            }
            return null;
        };
        field.setTextFormatter(new TextFormatter<>(filter));
    }

    // Whether `text` could be (part of) a valid number in the given base.
    // Allows the empty string and a leading "-" so the user can type
    // incrementally, e.g. "-", "-1", "-12".
    private boolean isValidForBase(String text, String base) {
        switch (base) {
            case "BIN": return text.matches("-?[01]*");
            case "OCT": return text.matches("-?[0-7]*");
            case "HEX": return text.matches("-?[0-9A-Fa-f]*");
            default: return text.matches("-?\\d*\\.?\\d*");
        }
    }

    private void showInvalidInputAlert(String attempted, String base) {
        Alert alert = new Alert(Alert.AlertType.WARNING);
        alert.setTitle("Invalid Input");
        alert.setHeaderText(null);
        alert.setContentText("'" + attempted + "' is not a valid digit for " + base + ".");
        alert.showAndWait();
    }

    // Parses both operands in their own bases, applies the chosen
    // operator, and displays the result in whatever base is selected
    // for the Result field.
    private void computeMixedBases(String operator) {
        try {
            double v1 = parseInBase(mixedOperand1Field.getText(), mixedBase1);
            double v2 = parseInBase(mixedOperand2Field.getText(), mixedBase2);
            double result;

            switch (operator) {
                case "+":
                    result = v1 + v2;
                    break;
                case "-":
                    result = v1 - v2;
                    break;
                case "*":
                    result = v1 * v2;
                    break;
                case "/":
                    if (v2 == 0) {
                        mixedResultField.setText("Error");
                        mixedHasResult = false;
                        Alert divisionAlert = new Alert(Alert.AlertType.WARNING);
                        divisionAlert.setTitle("Invalid Input");
                        divisionAlert.setHeaderText(null);
                        divisionAlert.setContentText("Cannot divide by zero.");
                        divisionAlert.showAndWait();
                        return;
                    }
                    result = v1 / v2;
                    break;
                default:
                    return;
            }

            mixedResultValue = result;
            mixedHasResult = true;
            mixedResultField.setText(formatInBase(result, mixedResultBase));
        } catch (NumberFormatException ex) {
            mixedResultField.setText("Error");
            mixedHasResult = false;
        }
    }

    private boolean isDigit(String value) {
        return value.matches("[0-9A-F]");
    }

    private void updateDigitAvailability() {
        int maxDigitValue;
        switch (currentBase) {
            case "BIN": maxDigitValue = 1; break;
            case "OCT": maxDigitValue = 7; break;
            case "HEX": maxDigitValue = 15; break;
            default: maxDigitValue = 9; break;
        }

        for (Map.Entry<String, Button> entry : digitButtons.entrySet()) {
            int digitValue = Integer.parseInt(entry.getKey(), 16);
            entry.getValue().setDisable(digitValue > maxDigitValue);
        }
    }

    private void handleButton(String value, TextField display) {
        switch (value) {
            case "Clear":
                resetState(display);
                break;
            case "=":
                evaluate(display);
                break;
            case "+": case "-": case "*": case "/":
                applyOperator(value.charAt(0), display);
                break;
            default:
                enterDigit(value, display);
                break;
        }
    }

    private void enterDigit(String digit, TextField display) {
        if (startNewNumber) {
            display.setText(digit);
            startNewNumber = false;
        } else {
            String next = display.getText().equals("0") ? digit : display.getText() + digit;
            display.setText(next);
        }
    }

    // Fun feature: drops a random valid "seed" number onto the display,
    // respecting whichever base is currently selected.
    private void insertRandomNumber(TextField display) {
        int maxDigitValue;
        switch (currentBase) {
            case "BIN": maxDigitValue = 1; break;
            case "OCT": maxDigitValue = 7; break;
            case "HEX": maxDigitValue = 15; break;
            default: maxDigitValue = 9; break;
        }

        int length = 1 + random.nextInt(3);
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < length; i++) {
            int d = random.nextInt(maxDigitValue + 1);
            sb.append(Integer.toString(d, 16).toUpperCase());
        }
        display.setText(sb.toString());
        startNewNumber = false;
    }

    private void applyOperator(char operator, TextField display) {
        if (!startNewNumber) {
            if (!computePending(display)) {
                return;
            }
        }
        currentOperator = operator;
        startNewNumber = true;
        refreshPendingDisplay();
    }

    private void evaluate(TextField display) {
        if (currentOperator != '\0' && !startNewNumber) {
            computePending(display);
        }
        currentOperator = '\0';
        startNewNumber = true;
        refreshPendingDisplay();
    }

    private boolean computePending(TextField display) {
        double value = parseInBase(display.getText(), currentBase);

        if (currentOperator == '\0') {
            total = value;
        } else if (currentOperator == '/' && value == 0) {
            display.setText("Error");
            resetState(display, false);
            return false;
        } else {
            String prevFormatted = formatInBase(total, currentBase);
            String valueFormatted = formatInBase(value, currentBase);

            expr.num1 = total;
            expr.num2 = value;
            expr.operator = currentOperator;
            expr.calculate();
            total = expr.num1;

            String resultFormatted = formatInBase(total, currentBase);
            historyItems.add(0, prevFormatted + " " + currentOperator + " " + valueFormatted + " = " + resultFormatted);
            updateFunFact();
        }

        display.setText(formatInBase(total, currentBase));
        return true;
    }

    private double parseInBase(String text, String base) {
        if (text.isEmpty() || text.equals("Error")) {
            return 0;
        }
        switch (base) {
            case "HEX": return expr.hexToDec(text);
            case "OCT": return expr.octToDec(text);
            case "BIN": return expr.binToDec(text);
            default: return Double.parseDouble(text.replace(',', '.'));
        }
    }

    private String formatInBase(double num, String base) {
        switch (base) {
            case "HEX": return expr.decToHex((int) Math.round(num)).toUpperCase();
            case "OCT": return expr.decToOct((int) Math.round(num));
            case "BIN": return expr.decToBin((int) Math.round(num));
            default: return formatDecimal(num);
        }
    }

    // Formats a double for the decimal display: whole numbers show with no
    // decimal point, and fractional results are rounded to a sane number of
    // places and stripped of trailing zeros, so 10 / 4 shows "2.5" rather
    // than "2.5000000000" or floating-point noise like "2.4999999999999996".
    private String formatDecimal(double num) {
        if (Double.isNaN(num) || Double.isInfinite(num)) {
            return "Error";
        }
        if (num == Math.floor(num)) {
            return String.format(Locale.US, "%.0f", num);
        }
        String formatted = String.format(Locale.US, "%.8f", num);
        formatted = formatted.replaceAll("0+$", "");
        formatted = formatted.replaceAll("\\.$", "");
        return formatted;
    }

    // Re-renders whatever is currently on screen in a new base, without
    // touching the accumulator or losing progress on a pending calculation.
    private void convertDisplayBase(TextField display, String fromBase, String toBase) {
        String text = display.getText();
        if (text.isEmpty() || text.equals("Error")) {
            display.setText("0");
            return;
        }
        try {
            double decimalValue = parseInBase(text, fromBase);
            display.setText(formatInBase(decimalValue, toBase));
        } catch (NumberFormatException ex) {
            display.setText("0");
        }
    }

    // Keeps the small "next operation" field in sync with currentOperator
    // and total, in whatever base is currently selected.
    private void refreshPendingDisplay() {
        if (pendingField == null) {
            return;
        }
        if (currentOperator == '\0') {
            pendingField.setText("");
        } else {
            pendingField.setText(formatInBase(total, currentBase) + " " + currentOperator);
        }
    }

    // --- Fun facts about the latest result ---

    private void updateFunFact() {
        if (funFactLabel == null) {
            return;
        }
        if (total != Math.floor(total) || Double.isNaN(total) || Double.isInfinite(total)) {
            funFactLabel.setText("Fractional results have their own charm.");
            return;
        }

        long n = Math.round(total);
        String word = upsideDownWord(n);
        if (word != null) {
            funFactLabel.setText("\uD83D\uDE43 Turn it upside down: " + word + "!");
            flashDisplay();
        } else {
            funFactLabel.setText(funFactFor(n));
        }
    }

    // Briefly highlights the main display in gold, for the upside-down
    // word easter egg.
    private void flashDisplay() {
        if (mainDisplayRef == null) {
            return;
        }
        String originalStyle = mainDisplayRef.getStyle();
        mainDisplayRef.setStyle(originalStyle + " -fx-control-inner-background: gold;");
        PauseTransition pause = new PauseTransition(Duration.seconds(1.5));
        pause.setOnFinished(e -> mainDisplayRef.setStyle(originalStyle));
        pause.play();
    }

    // If reading this number's digits upside down spells a recognizable
    // word, returns that word; otherwise null. Classic calculator trick,
    // e.g. 5508 read upside down looks like "BOSS".
    private String upsideDownWord(long n) {
        if (n <= 0) {
            return null;
        }
        String digits = Long.toString(n);
        StringBuilder sb = new StringBuilder();
        for (int i = digits.length() - 1; i >= 0; i--) {
            Character letter = UPSIDE_DOWN_MAP.get(digits.charAt(i));
            if (letter == null) {
                return null;
            }
            sb.append(letter);
        }
        String candidate = sb.toString();
        return FUN_WORDS.contains(candidate) ? candidate : null;
    }

    private String funFactFor(long n) {
        long abs = Math.abs(n);

        if (n == 0) {
            return "Zero \u2014 the number that started it all.";
        }
        if (abs > 1_000_000_000L) {
            return "Whoa, that's a big number! (" + Long.toString(abs).length() + " digits)";
        }
        if (abs == 42) {
            return "42 \u2014 the Answer to Life, the Universe, and Everything.";
        }
        if (isPrime(abs)) {
            return abs + " is a prime number.";
        }
        if (abs >= 10 && isPalindromeNumber(abs)) {
            return abs + " reads the same backwards \u2014 a palindrome!";
        }
        if (isPerfectSquare(abs)) {
            return abs + " is a perfect square.";
        }
        if (abs > 0 && isPerfectCube(abs)) {
            return abs + " is a perfect cube.";
        }
        if (isFibonacci(abs)) {
            return abs + " appears in the Fibonacci sequence.";
        }
        if (abs >= 10 && isArmstrong(abs)) {
            return abs + " is an Armstrong number \u2014 its digits, each raised to the digit count, add back up to itself.";
        }
        return (n % 2 == 0 ? "Even" : "Odd") + " number.";
    }

    private boolean isPrime(long num) {
        if (num < 2) {
            return false;
        }
        if (num % 2 == 0) {
            return num == 2;
        }
        for (long i = 3; i * i <= num; i += 2) {
            if (num % i == 0) {
                return false;
            }
        }
        return true;
    }

    private boolean isPalindromeNumber(long num) {
        String s = Long.toString(num);
        return s.equals(new StringBuilder(s).reverse().toString());
    }

    private boolean isPerfectSquare(long num) {
        if (num < 0) {
            return false;
        }
        long root = Math.round(Math.sqrt((double) num));
        return root * root == num;
    }

    private boolean isPerfectCube(long num) {
        long root = Math.round(Math.cbrt((double) num));
        return root * root * root == num;
    }

    private boolean isFibonacci(long num) {
        return isPerfectSquare(5 * num * num + 4) || isPerfectSquare(5 * num * num - 4);
    }

    private boolean isArmstrong(long num) {
        String digits = Long.toString(num);
        int power = digits.length();
        long sum = 0;
        for (char c : digits.toCharArray()) {
            sum += (long) Math.pow(c - '0', power);
        }
        return sum == num;
    }

    private void resetState(TextField display) {
        resetState(display, true);
    }

    private void resetState(TextField display, boolean clearDisplay) {
        total = 0;
        currentOperator = '\0';
        startNewNumber = true;
        if (clearDisplay) {
            display.setText("0");
        }
        if (funFactLabel != null) {
            funFactLabel.setText("Do some math to see a fun fact!");
        }
        refreshPendingDisplay();
    }
}

class Expression {
    char operator;
    double num1;
    double num2;

    void calculate() {
        switch (operator) {
            case '+':
                num1 += num2;
                break;

            case '-':
                num1 -= num2;
                break;

            case '*':
                num1 *= num2;
                break;

            case '/':
                if (num2 != 0) {
                    num1 /= num2;
                }
                break;

            default:
                break;
        }
    }

    int binToDec(String num) {
        return Integer.parseInt(num, 2);
    }

    int hexToDec(String num) {
        return Integer.parseInt(num, 16);
    }

    int octToDec(String num) {
        return Integer.parseInt(num, 8);
    }

    String decToBin(int num) {
    if (num < 0) {
        return "-" + Integer.toBinaryString(-num);
    }
    return Integer.toBinaryString(num);
    }

    String decToHex(int num) {
        if (num < 0) {
            return "-" + Integer.toHexString(-num);
        }
        return Integer.toHexString(num);
    }
    String decToOct(int num) {
    if (num < 0) {
        return "-" + Integer.toOctalString(-num);
    }
    return Integer.toOctalString(num);
}
}