package chessgames.players;

import chessgames.enums.Color;
import chessgames.games.Game;

public abstract class Player {
    //black,white
    private Color color;
    private int numOfChess = 2;

    public Player(Color color) {
        this.color = color;
    }

    //下棋
    public abstract int doChess(Game game, String poss);

    public Color getColor() {
        return color;
    }

    public int getNumOfChess() {
        return numOfChess;
    }

    public void increaseNumOfChess(int num) {
        this.numOfChess += num;
    }

    public void decreaseNumOfChess(int num) {
        this.numOfChess -= num;
    }
}