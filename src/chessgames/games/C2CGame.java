package chessgames.games;

import chessgames.enums.Color;
import chessgames.players.Computer;
import chessgames.players.Computer1;


//Human to Computer
public class C2CGame extends Game {
    public C2CGame(int size, Color player1Color) {
        super(size);
        this.player1 = new Computer1(player1Color);
        this.player2 = new Computer(Color.another(player1Color));
    }
}
