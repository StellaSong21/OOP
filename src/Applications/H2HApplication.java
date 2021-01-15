package Applications;

import chessgames.enums.Color;
import chessgames.games.Game;
import chessgames.games.H2HGame;
import util.DataUtil;
import util.MassageUtil;

import java.util.Scanner;

public class H2HApplication extends Applications {
    private Scanner scanner;

   public H2HApplication() {
        scanner = new Scanner(System.in);
        currentColor = Color.BLACK;
    }

    public static void main(String[] args) {
        H2HApplication app = new H2HApplication();
        Applications.mainLogic(app);
    }


    @Override
    Game newGame(int size, Color player1Color) {
        this.game = new H2HGame(size, player1Color);
        this.player1 = game.getPlayer1();
        this.player2 = game.getPlayer2();
        return game;
    }

    @Override
    int nextStep() {
        Color player1Color = player1.getColor();
        Color player2Color = player2.getColor();
        if (player1Color.equals(currentColor)) {
            System.out.print("Player1: Enter move for " + Color.intoString(player1Color) + " (RowCol): ");
            String move = scanner.nextLine();
            currentColor = player2Color;
            return player1.doChess(game, move);
        } else {
            System.out.print("Player2: Enter move for " + Color.intoString(player2Color) + " (RowCol): ");
            String move = scanner.nextLine();
            currentColor = player1Color;
            return player2.doChess(game, move);
        }
    }

    @Override
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

    @Override
    Color getPlayer2Color() {
        System.out.print("Player2 plays(X/O/0)：");
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
