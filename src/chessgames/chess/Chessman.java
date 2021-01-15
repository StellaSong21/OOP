package chessgames.chess;

import chessgames.enums.Color;

public class Chessman {
    private Position position;
    private Color color;

    public Chessman(Color color, Position position) {
        this.color = color;
        this.position = position;
    }

    public Chessman(Color color, int xPos, int yPos) {
        this.color = color;
        this.position = new Position(xPos, yPos);
    }

    /**
     * @return the position
     */
    public Position getPosition() {
        return position;
    }

    public Color getColor() {
        return color;
    }

    public void setColor(Color color) {
        this.color = color;
    }

    public Boolean equalColor(Color color) {
        return this.color.equals(color);
    }
}