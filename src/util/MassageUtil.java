package util;

public class MassageUtil {
    public static String decode(int code) {
        switch (code) {
            case 0x010100:
                return "Continue...";
            case 0x010101:
                return "X player has no valid move!";
            case 0x010102:
                return "O player has no valid move!";

            case 0x010200:
                return "X player wins!";
            case 0x010201:
                return "O player wins!";

            case 0x010300:
                return "Invalid position!";
            case 0x010301:
                return "Invalid move!";
            case 0x010302:
                return "Unknown player type!";
            case 0x010303:
                return "Human gave up!\nGame over!";//
            case 0x010304:
                return "Board has been full!\nGame over!";//
            case 0x010305:
                return "X player has no chessman!\nGame over!";//
            case 0x010306:
                return "O player has no chessman!\nGame over!";//
            case 0x010307:
                return "Both players have no valid move.\nGame over!";//

            case 0x010400:
                return "Move success";

            case 0x010501:
                return "not in the legal range";
            case 0x010502:
                return "not an even";
            case 0x010503:
                return "not an integer number";
        }
        return "Unknown error!";
    }

}
