package chessgames.chess;

import chessgames.enums.Color;

public class Chessboard {
    //check if spec is even or not at the front end
    private int spec;
    private int numOfChess;
    private Chessman[][] chessBoard;

    public Chessboard(int spec) {
        this.spec = spec;
        chessBoard = new Chessman[spec][spec];
        int mid = spec / 2;
        //设定初始棋子的位置
        chessBoard[mid - 1][mid - 1] = new Chessman(Color.WHITE, mid - 1, mid - 1);
        chessBoard[mid][mid] = new Chessman(Color.WHITE, mid, mid);
        chessBoard[mid - 1][mid] = new Chessman(Color.BLACK, mid - 1, mid);
        chessBoard[mid][mid - 1] = new Chessman(Color.BLACK, mid, mid - 1);
        this.numOfChess = 4;
    }

    /**
     * @return the spec
     */
    public int getSpec() {
        return spec;
    }

    /**
     * @return the numOfchess
     */
    public int getNumOfChess() {
        return numOfChess;
    }

    /**
     * @return the chessBoard
     */
    public Chessman[][] getChessBoard() {
        return chessBoard;
    }

    public void increaseNumOfChess() {
        numOfChess++;
    }
}