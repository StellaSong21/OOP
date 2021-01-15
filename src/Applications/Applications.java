package Applications;

import chessgames.enums.Color;
import chessgames.games.Game;
import chessgames.players.Player;
import util.MassageUtil;

import java.text.SimpleDateFormat;
import java.util.Date;

public abstract class Applications {
    Game game;
    Color currentColor;
    Player player1;
    Player player2;

    public static void mainLogic(Applications app) {
        int size = app.getSize();
        Color computerColor = app.getPlayer2Color();
        Game game = app.newGame(size, Color.another(computerColor));
        int status = 0x010100;
        boolean endFlag = false;
        while (!endFlag) {
            switch (status) {
                case 0x010300://放弃
                case 0x010301:
                    System.out.println(MassageUtil.decode(status));
                    endFlag = true;
                    status = 0x010303;
                    break;
                case 0x010304://棋盘已满
                case 0x010305://X没有棋子
                case 0x010306://O没有棋子
                case 0x010307://双方无路可走
                    game.showBoard();
                    System.out.println(MassageUtil.decode(status));
                    endFlag = true;
                    break;
                case 0x010101:
                    game.showBoard();
                    if (app.currentColor.equals(Color.BLACK)) {
                        System.out.println(MassageUtil.decode(status));
                        app.currentColor = Color.another(app.currentColor);
                    }
                    status = app.nextStep();
                    break;
                case 0x010102:
                    game.showBoard();
                    if (app.currentColor.equals(Color.WHITE)) {
                        System.out.println(MassageUtil.decode(status));
                        app.currentColor = Color.another(app.currentColor);
                    }
                    status = app.nextStep();
                    break;
                default:
                    game.showBoard();
                    status = app.nextStep();
            }
        }
        app.end(status);
        game.logger(app.getLog(game.getStart(), game.getStartTime(), game.getEndTime(), status));
    }

    abstract Game newGame(int size, Color player1Color);

    private void end(int status) {
        int[] score = getScore();
        int blackNum = score[0];
        int whiteNum = score[1];
        if (status != 0x010303) {
            System.out.println("X : O =" + blackNum + " : " + whiteNum);
            if (blackNum > whiteNum) {
                System.out.println("X player wins.");
            } else if (blackNum == whiteNum) {
                System.out.println("Draw!");
            } else {
                System.out.println("O player wins.");
            }
        } else {
            System.out.println("Game Over");
            System.out.println(Color.intoString(player2.getColor()) + " player wins.");
        }
    }

    private int[] getScore() {
        int whiteNum;
        int blackNum;
        if (player1.getColor().equals(Color.WHITE)) {
            whiteNum = player1.getNumOfChess();
            blackNum = player2.getNumOfChess();
        } else {
            whiteNum = player2.getNumOfChess();
            blackNum = player1.getNumOfChess();
        }
        return new int[]{blackNum, whiteNum};
    }

    private String[] getLog(Date date, long startTime, long endTime, int status) {
        String[] log = new String[6];
        SimpleDateFormat dateFormat = new SimpleDateFormat("yyyyMMdd HH:mm:ss");
        log[0] = dateFormat.format(date);
        log[1] = (endTime - startTime) / 1000 + "";
        log[2] = game.getSpec() + "*" + game.getSpec();
        if (player1.getColor().equals(Color.WHITE)) {
            log[3] = "Computer";
            log[4] = "Human";
        } else {
            log[4] = "Computer";
            log[3] = "Human";
        }
        int[] score = getScore();
        log[5] = status == 0x010303 ? "Human gave up" : (score[0] + " to " + score[1]);
        return log;
    }

    abstract int nextStep();

    abstract int getSize();

    abstract Color getPlayer2Color();
}
