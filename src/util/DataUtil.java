package util;

public class DataUtil {
    public static int maxAbs(int x, int y) {
        int xAbs = Math.abs(x);
        int yAbs = Math.abs(y);
        return xAbs > yAbs ? xAbs : yAbs;
    }

    public static int isSizeValid(String sizes) {
        try {
            int size = Integer.parseInt(sizes);
            if (size < 4 || size > 10) {
                return 0x010501;
            }
            if (size % 2 != 0) {
                return 0x010502;
            }
            return size;
        } catch (IllegalArgumentException e) {
            return 0x010503;
        }
    }
}
