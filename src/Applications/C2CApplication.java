package Applications;

import chessgames.enums.Color;
import chessgames.games.C2CGame;
import chessgames.games.Game;
import chessgames.players.Computer;
import chessgames.players.Computer1;


public class C2CApplication extends Applications {
    public C2CApplication() {
        currentColor = Color.BLACK;
    }

    @Override
    Game newGame(int size, Color humanColor) {
        this.game = new C2CGame(size, humanColor);
        this.player1 = game.getPlayer1();
        this.player2 = game.getPlayer2();
        return game;
    }

    public static void main(String[] args) {
        for (int i = 0; i < 100; i++) {
            System.out.println("第" + i + "次游戏：");
            C2CApplication app = new C2CApplication();
            mainLogic(app);
            System.out.println();
            System.out.println();
            System.out.println();
            System.out.println();
        }
    }

    @Override
    int nextStep() {
        Color humanColor = player1.getColor();
        Color computerColor = player2.getColor();
        if (currentColor.equals(computerColor)) {
            String move = ((Computer) player2).optimalPosition(game);
            System.out.println("Computer places " + Color.intoString(computerColor) + " at " + move);
            currentColor = humanColor;
            return player2.doChess(game, move);
        } else {
            String move = ((Computer1) player1).optimalPosition(game);
            System.out.println("Human places " + Color.intoString(humanColor) + " at " + move);
            currentColor = computerColor;
            return player1.doChess(game, move);
        }
    }

    @Override
    int getSize() {
        System.out.print("Enter the board dimension: ");
        int[] r = {4, 6, 8, 10};
        int size = ((int) (Math.random() * 4) + 2) * 2;
        System.out.println(size);
        return size;
    }

    @Override
    Color getPlayer2Color() {
        System.out.print("Computer plays(X/O)：");
        Color color = Color.getByIndex("0");
        System.out.println(Color.intoString(color));
        return color;
    }
}
