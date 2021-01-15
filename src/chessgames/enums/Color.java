package chessgames.enums;

public enum Color {
    WHITE, BLACK;

    public static Color another(Color color) {
        if (WHITE.equals(color)) {
            return BLACK;
        } else {
            return WHITE;
        }
    }

    private static Color random() {
        int r = (int) (Math.random() * Color.values().length);
        return Color.values()[r];
    }

    public static Color getByIndex(String indexs) {
        if (indexs.length() > 1) {
            return null;
        }
        String indexLower = indexs.toUpperCase();
        //todo revert
        if ("0".equals(indexs)) {
            return random();
        }
        if ("X".equals(indexLower)) {
            return BLACK;
        }
        if ("O".equals(indexLower)) {
            return WHITE;
        }
        return null;
    }

    public static String intoString(Color color) {
        if (BLACK.equals(color)) {
            return "X";
        }
        if (WHITE.equals(color)) {
            return "O";
        }
        return ".";
    }
}
