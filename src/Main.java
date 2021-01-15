import Applications.Applications;
import Applications.H2CApplication;
import Applications.C2CApplication;
import Applications.H2HApplication;

import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("请选择模式：");
        String input = scanner.nextLine();
        Applications app = new H2CApplication();
        if ("1".equals(input)) {
            app = new H2CApplication();
        } else if ("2".equals(input)) {
            app = new C2CApplication();
        } else if ("3".equals(input)) {
            app = new H2HApplication();
        }

        Applications.mainLogic(app);

    }
}