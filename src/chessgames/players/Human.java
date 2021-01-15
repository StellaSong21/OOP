package chessgames.players;

import chessgames.chess.Chessman;
import chessgames.chess.Position;
import chessgames.enums.Color;
import chessgames.games.Game;
import util.PositionUtil;

public class Human extends Player {

    public Human(Color color) {
        super(color);
    }

    @Override
    public int doChess(Game game, String poss) {
        Position position = PositionUtil.intoPosition(poss);
        Chessman chessman = new Chessman(this.getColor(), position);
        return game.add(chessman,  null);
    }
}
