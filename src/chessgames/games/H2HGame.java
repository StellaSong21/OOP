package chessgames.games;

import chessgames.enums.Color;
import chessgames.players.Human;

public class H2HGame extends Game {
    public H2HGame(int size, Color player1Color) {
        super(size);
        this.player1 = new Human(player1Color);
        this.player2 = new Human(Color.another(player1Color));
    }
}
