package util;

import chessgames.chess.Position;

public class PositionUtil {
    private static final char A = 'a';
    private static final int DIMENTION = 2;

    public static Position intoPosition(String position) {
        //转换为小写
        char[] positionc = position.toLowerCase().toCharArray();

        //tips: 如果用户输入的多于2位如何处理？取前两位还是返回错误？大写和小写都可以
        if (positionc.length != DIMENTION) {
            return null;
        }
        int[] coordinate = new int[DIMENTION];
        for (int i = 0; i < DIMENTION; i++) {
            if (positionc[i] < 'a' || positionc[i] > 'z') {
                return null;
            }
            coordinate[i] = positionc[i] - A;
        }

        return new Position(coordinate[0], coordinate[1]);
    }

    public static String intoString(Position position) {
        if (position == null) {
            return null;
        }
        char[] poschr = {(char) (position.getxPos() + A), (char) (position.getyPos() + A)};
        return String.valueOf(poschr);
    }
}
