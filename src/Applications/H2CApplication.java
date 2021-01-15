package Applications;

import chessgames.enums.Color;
import chessgames.games.Game;
import chessgames.games.H2CGame;
import chessgames.players.Computer;
import util.DataUtil;
import util.MassageUtil;

import java.util.Scanner;

public class H2CApplication extends Applications {
    private Scanner scanner;

    public H2CApplication() {
        scanner = new Scanner(System.in);
        currentColor = Color.BLACK;
    }

    @Override
    Game newGame(int size, Color humanColor) {
        this.game = new H2CGame(size, humanColor);
        this.player1 = game.getPlayer1();
        this.player2 = game.getPlayer2();
        return game;
    }

    public static void main(String[] args) {
        H2CApplication app = new H2CApplication();
        Applications.mainLogic(app);
    }

    int nextStep() {
        Color humanColor = player1.getColor();
        Color computerColor = player2.getColor();
        if (humanColor.equals(currentColor)) {
            System.out.print("Enter move for " + Color.intoString(humanColor) + " (RowCol): ");
            String move = scanner.nextLine();
            currentColor = computerColor;
            return player1.doChess(game, move);
        } else {
            String move = ((Computer) (player2)).optimalPosition(game);
            System.out.println("Computer places " + Color.intoString(computerColor) + " at " + move);
            currentColor = humanColor;
            return player2.doChess(game, move);
        }
    }

    int getSize() {
        System.out.print("Enter the board dimension，(even between 4 and 10)：");
        String sizes = scanner.nextLine();
        int size = DataUtil.isSizeValid(sizes);
        while (size > 16) {
            System.out.println(MassageUtil.decode(size));
            System.out.print("Please re-enter：");
            sizes = scanner.nextLine();
            size = DataUtil.isSizeValid(sizes);
        }
        return size;
    }

    Color getPlayer2Color() {
        System.out.print("Computer plays(X/O/0)：");
        String colors = scanner.nextLine();
        Color color = Color.getByIndex(colors);
        while (color == null) {
            System.out.print("Invalid, Please re-enter：");
            colors = scanner.nextLine();
            color = Color.getByIndex(colors);
        }
        return color;
    }
}
