import java.util.Arrays;
import java.util.Random;
import java.util.Scanner;

public class NumberGuessingGame {
    private static final int ARRAY_SIZE = 4;
    private static final int TRIES = 7;
    private static int leftTries = TRIES;
    private static int[] digitsArray = new int[ARRAY_SIZE];
    private static String arrayToStr;

    private static void resetArray() {
        Arrays.fill(digitsArray, -1);
    }

    private static void printArray() {
        System.out.print("Digits array: ");
        for (int digit : digitsArray) {
            System.out.print(digit + " ");
        }
        System.out.println();
    }

    private static boolean doesContain(int digit) {
        for (int i = 0; i < ARRAY_SIZE; i++) {
            if (digitsArray[i] == digit) {
                return true;
            }
        }
        return false;
    }

    private static void generateRandomNumber() {
        int digitsIndex = 0;
        do {
            int randomDigit = new Random().nextInt(9) + 1;
            if (!doesContain(randomDigit)) {
                digitsArray[digitsIndex] = randomDigit;
                digitsIndex++;
            }
        } while (digitsIndex != ARRAY_SIZE);
    }

    private static boolean containsOnlyDigits(String str) {
        for (int i = 0; i < str.length(); i++) {
            if (!Character.isDigit(str.charAt(i))) {
                return false;
            }
        }
        return true;
    }

    private static boolean checkIfGood(String guessNumberStr) {
        if (guessNumberStr.length() != ARRAY_SIZE) {
            System.out.println("Incorrect length.");
            return false;
        }
        if (!containsOnlyDigits(guessNumberStr)) {
            System.out.println("Only digits are allowed.");
            return false;
        }
        return true;
    }

    private static String arrayToStr() {
        StringBuilder str = new StringBuilder();
        for (int digit : digitsArray) {
            str.append(digit);
        }
        return str.toString();
    }

    private static int calcCorrectDigits(String str) {
        int count = 0;
        for (int i = 0; i < str.length(); i++) {
            if (arrayToStr.indexOf(str.charAt(i)) != -1) {
                count++;
            }
        }
        return count;
    }

    private static int calcCorrectPosition(String str) {
        int count = 0;
        for (int i = 0; i < str.length(); i++) {
            if (arrayToStr.indexOf(str.charAt(i)) == i) {
                count++;
            }
        }
        return count;
    }

    public static void main(String[] args) {
        Random random = new Random();
        generateRandomNumber();
        arrayToStr = arrayToStr();

        Scanner scanner = new Scanner(System.in);
        System.out.print("DEBUG: ");
        printArray();
        String guessNumberStr;
        boolean guessed = false;

        do {
            guessNumberStr = scanner.next();
            if (checkIfGood(guessNumberStr)) {
                leftTries--;
                System.out.println("Tries left: " + leftTries);
                int calcCorrectDigits = calcCorrectDigits(guessNumberStr);
                int calcCorrectPositions = calcCorrectPosition(guessNumberStr);
                System.out.println("Correct digits: " + calcCorrectDigits);
                System.out.println("Correct positions: " + calcCorrectPositions);
                if (calcCorrectPositions == 4) {
                    guessed = true;
                }
            } else {
                System.out.println("Bad.");
            }
        } while (leftTries > 0 && !guessed);

        if (guessed) {
            System.out.println("You guessed it!");
        } else {
        System.out.println("L bozo.");
        }
    }
}