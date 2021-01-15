package chessgames.players;

import chessgames.chess.Chessman;
import chessgames.chess.Position;
import chessgames.enums.Color;
import chessgames.enums.Direction;
import chessgames.games.Game;
import util.PositionUtil;

import java.util.ArrayList;
import java.util.HashMap;

public class Computer1 extends Player {
    private HashMap<Direction, Position> optimal;

    public Computer1(Color color) {
        super(color);
        this.optimal = new HashMap<>();
    }

    public String optimalPosition(Game game) {
        ArrayList<HashMap<Direction, Position>> paths = game.hasPath(this.getColor());
        HashMap<Direction, Position> optimal = random(paths);
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

    private HashMap<Direction, Position> random(ArrayList<HashMap<Direction, Position>> paths) {
        int r = (int) (Math.random() * paths.size());
        return paths.get(r);
    }
}
