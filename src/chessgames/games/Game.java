package chessgames.games;

import chessgames.chess.Chessboard;
import chessgames.chess.Chessman;
import chessgames.chess.Position;
import chessgames.enums.Color;
import chessgames.enums.Direction;
import chessgames.players.Player;
import constant.FileConstant;
import util.FileUtil;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

public abstract class Game {
    private Chessboard chessboard;
    Player player1;
    Player player2;
    private int spec;
    private long startTime;
    private long endTime;
    private Date start;
    private int statusCode = 0x010100;
    private Chessman[][] chessmen;

    public Game(int size) {
        this.start = new Date();
        this.spec = size;
        this.chessboard = new Chessboard(size);
        this.chessmen = chessboard.getChessBoard();
        this.startTime = System.currentTimeMillis();
    }

    private int getStatus() {//continue & invalid & has no chess & full & win & has no path
        //Human gave up
        if (this.statusCode == 0x010300 || this.statusCode == 0x010301) {
            endTime = System.currentTimeMillis();
            return this.statusCode;
        }
        //board is full
        if (chessboard.getNumOfChess() == this.spec * spec) {
            this.statusCode = 0x010304;
            endTime = System.currentTimeMillis();
            return 0x010304;
        }
        //Human has no chessman
        if (this.player1.getNumOfChess() == 0) {
            if (Color.WHITE.equals(player1.getColor())) {
                this.statusCode = 0x010200;//Black wins
                endTime = System.currentTimeMillis();
                return 0x010306;
            } else {
                this.statusCode = 0x010201;//white wins
                endTime = System.currentTimeMillis();
                return 0x010305;
            }
        }
        if (this.player2.getNumOfChess() == 0) {
            if (Color.BLACK.equals(player2.getColor())) {
                this.statusCode = 0x010200;//black wins
                endTime = System.currentTimeMillis();
                return 0x010306;
            } else {
                this.statusCode = 0x010201;
                endTime = System.currentTimeMillis();
                return 0x010305;
            }
        }

        //has no path
        Boolean black = hasPath(Color.BLACK).isEmpty();
        Boolean white = hasPath(Color.WHITE).isEmpty();

        if (black && white) {
            this.statusCode = 0x010307;
            endTime = System.currentTimeMillis();
            return 0x010307;
        } else if (black) {
            this.statusCode = 0x010101;
        } else if (white) {
            this.statusCode = 0x010102;
        }

        return this.statusCode;//maybe one has no path
    }

    public void logger(String[] log) {
        FileUtil.write(log, FileConstant.LOG_CSV);
    }

    public void showBoard() {
        Chessman[][] chessBoard = chessboard.getChessBoard();
        for (int i = (int) 'a'; i < spec + 97; i++) {
            System.out.print("\t" + (char) i);
        }
        System.out.println();
        for (int i = 0; i < spec; i++) {
            System.out.print((char) (i + 97));
            for (int j = 0; j < spec; j++) {
                Chessman chessman = chessBoard[i][j];
                System.out.print("\t" + Color.intoString(chessman == null ? null : chessman.getColor()));
            }
            System.out.println();
        }
    }

    //在指定位置下棋，update 整个棋盘中的黑白棋子分布和棋子数目
    public int add(Chessman chessman, HashMap<Direction, Position> poss) {
        Color color = chessman.getColor();
        if (player1.getColor().equals(color)) {
            return addPlayer(player1, chessman, poss);
        } else if (player2.getColor().equals(color)) {
            return addPlayer(player2, chessman, poss);
        } else {
            this.statusCode = 0x010106;
            return 0x010106;
        }
    }

    //返回有效位置以及该位置的分数,返回分数最高的位置和改变的棋子数目
    public ArrayList<HashMap<Direction, Position>> hasPath(Color color) {
        ArrayList<HashMap<Direction, Position>> array = new ArrayList<>();
        int totalScore;
        for (int i = 0; i < spec; i++) {
            for (int j = 0; j < spec; j++) {
                HashMap<Direction, Position> result = isValid(new Chessman(color, i, j));
                if (result.size() == 0) {
                    continue;
                }
                totalScore = 0;
                for (Map.Entry<Direction, Position> entry : result.entrySet()) {
                    Position position = entry.getValue();
                    totalScore += position.getScore();
                }
                HashMap<Direction, Position> positions = new HashMap<>();
                positions.put(null, new Position(i, j, totalScore));
                positions.putAll(result);
                array.add(positions);
            }
        }
        return array;
    }

    //找到有效位置，并且返回该线上的终点的位置
    private HashMap<Direction, Position> isValid(Chessman chessman) {
        HashMap<Direction, Position> validPos = new HashMap<>();
        Position position = chessman.getPosition();
        int x = position.getxPos();
        int y = position.getyPos();
        Color color = chessman.getColor();
        checkAll(x, y, color, validPos);
        return validPos;
    }

    private void checkAll(int xPos, int yPos, Color color, HashMap<Direction, Position> validPos) {
        if (chessmen[xPos][yPos] != null) {
            return;
        }
        for (Direction direction : Direction.values()) {
            checkOne(xPos, yPos, color, direction, validPos);
        }
    }

    //direction参数，检查某方向上是否有变化的棋子
    private void checkOne(int xPos, int yPos, Color color, Direction direction, HashMap<Direction, Position> validPos) {
        int x = xPos;
        int y = yPos;
        int[] currentPos = {x, y};
        boolean flag = true;
        int num = -1;
        do {
            nextPos(currentPos, direction);
            x = currentPos[0];
            y = currentPos[1];
            if (x < 0 || y < 0 || x >= spec || y >= spec || chessmen[x][y] == null) {
                flag = false;
                break;
            }
            num++;
        } while (!chessmen[x][y].equalColor(color));


        if (flag && chessmen[x][y].equalColor(color) && num > 0) {
            validPos.put(direction, new Position(x, y, num));
        }
    }

    private int updateColor(Chessman chessman, HashMap<Direction, Position> posss) {
        Position center = chessman.getPosition();
        Color color = chessman.getColor();
        int score = 0;
        for (Map.Entry<Direction, Position> entry : posss.entrySet()) {
            Direction direction = entry.getKey();
            Position position = entry.getValue();
            changeColorDir(center, direction, position, color);
            score += position.getScore();
        }
        return score;
    }

    private void changeColorDir(Position start, Direction direction, Position end, Color color) {
        int x = start.getxPos();
        int y = start.getyPos();
        int ex = end.getxPos();
        int ey = end.getyPos();
        int[] currentPos = {x, y};
        while (x != ex || y != ey) {
            nextPos(currentPos, direction);
            x = currentPos[0];
            y = currentPos[1];
            chessmen[x][y].setColor(color);
        }
    }


    private int addPlayer(Player player, Chessman chessman, HashMap<Direction, Position> poss) {
        Position position = chessman.getPosition();
        if (position == null) {
            this.statusCode = 0x010300;
            return getStatus();
        }
        if (position.getxPos() >= this.spec || position.getyPos() >= this.spec) {
            this.statusCode = 0x010300;
            return getStatus();
        }

        if (poss == null) {
            poss = isValid(chessman);
            if (poss.isEmpty()) {
                this.statusCode = 0x010301;
                return getStatus();
            }
        }
        chessmen[position.getxPos()][position.getyPos()] = chessman;
        chessboard.increaseNumOfChess();
        int score = updateColor(chessman, poss);
        if (player == this.player1) {
            this.player1.increaseNumOfChess(score + 1);
            this.player2.decreaseNumOfChess(score);
        } else {
            this.player2.increaseNumOfChess(score + 1);
            this.player1.decreaseNumOfChess(score);
        }
        this.statusCode = 0x010100;
        return getStatus();
    }


    private void nextPos(int[] currentPos, Direction direction) {
        switch (direction) {
            case NORTH:
                currentPos[0]--;
                break;
            case WEST:
                currentPos[1]--;
                break;
            case EAST:
                currentPos[1]++;
                break;
            case SOUTH:
                currentPos[0]++;
                break;
            case NORTHWEST:
                currentPos[0]--;
                currentPos[1]--;
                break;
            case NORTHEAST:
                currentPos[0]--;
                currentPos[1]++;
                break;
            case SOUTHWEST:
                currentPos[0]++;
                currentPos[1]--;
                break;
            default:
                currentPos[0]++;
                currentPos[1]++;
                break;
        }
    }

    public long getStartTime() {
        return startTime;
    }

    public long getEndTime() {
        return endTime;
    }

    public Date getStart() {
        return start;
    }

    public Player getPlayer1() {
        return player1;
    }

    public Player getPlayer2() {
        return player2;
    }

    public int getSpec() {
        return spec;
    }
}
