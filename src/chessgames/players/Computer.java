package chessgames.players;

import chessgames.chess.Chessman;
import chessgames.chess.Position;
import chessgames.enums.Color;
import chessgames.enums.Direction;
import chessgames.games.Game;
import util.PositionUtil;

import java.util.ArrayList;
import java.util.HashMap;

public class Computer extends Player {
    private HashMap<Direction, Position> optimal;

    public Computer(Color color) {
        super(color);
        this.optimal = new HashMap<>();
    }

    public String optimalPosition(Game game) {
        ArrayList<HashMap<Direction, Position>> paths = game.hasPath(this.getColor());
        HashMap<Direction, Position> optimal = optimal(paths);
        Position center = optimal.remove(null);
        this.optimal = optimal;
        return PositionUtil.intoString(center);
    }


    @Override //找到最优的位置，并在最优位置下棋
    public int doChess(Game game, String poss) {
        Position center = PositionUtil.intoPosition(poss);
        Chessman chessman = new Chessman(this.getColor(), center);
        return game.add(chessman, this.optimal);
    }

    private HashMap<Direction, Position> optimal(ArrayList<HashMap<Direction, Position>> paths) {
        HashMap<Direction, Position> optimal = paths.get(0);
        HashMap<Direction, Position> temp;

        for (int i = 1; i < paths.size(); i++) {
            temp = paths.get(i);
            optimal = better(optimal, temp);
        }

        return optimal;
    }

    private HashMap<Direction, Position> better(HashMap<Direction, Position> hashMap1, HashMap<Direction, Position> hashMap2) {
        Position position1 = hashMap1.get(null);
        Position position2 = hashMap2.get(null);

        int x1 = position1.getxPos();
        int x2 = position2.getxPos();
        int score1 = position1.getScore();
        int score2 = position2.getScore();
        if (score1 > score2) {
            return hashMap1;
        } else if (score2 > score1) {
            return hashMap2;
        } else {
            if (x2 < x1) {
                return hashMap2;
            } else {
                return hashMap1;
            }
        }
    }
}
