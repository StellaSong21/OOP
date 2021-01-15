package chessgames.chess;

public class Position {
    private int xPos;
    private int yPos;
    private int score = 0;

    public Position(int x, int y) {
        this.xPos = x;
        this.yPos = y;
    }

    public Position(int x, int y, int score) {
        this.xPos = x;
        this.yPos = y;
        this.score = score;
    }

    public int getxPos() {
        return xPos;
    }

    public int getyPos() {
        return yPos;
    }

    public int getScore() {
        return score;
    }
}
