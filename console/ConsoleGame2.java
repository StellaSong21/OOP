package oop.lab1.console;

import oop.lab1.Color;
import oop.lab1.Computer;
import oop.lab1.Session;

/*
 * class BoardConsole{
 * 		void display(Board board);
 * }
 */
public class ConsoleGame2 {

	public static void main(String[] args) {

		Session s = new Session(6, 6, new Computer(Color.BLACK), new Computer(Color.WHITE));
//		s.play();

	}

}