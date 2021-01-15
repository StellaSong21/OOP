package chessgames.games;

import chessgames.enums.Color;
import chessgames.players.Computer;
import chessgames.players.Human;

//Human to Computer
public class H2CGame extends Game {

    public H2CGame(int size, Color humanColor) {
        super(size);
        this.player1 = new Human(humanColor);
        this.player2 = new Computer(Color.another(humanColor));
    }
}
