package sample;

import java.util.LinkedList;
import java.util.List;

public class Cell {
    private boolean flagged;
    private boolean mine;
    private boolean opened;
    private List<Cell> neighbors;
    private int x;
    private int y;

    public Cell(int x, int y) {
        this.x = x;
        this.y = y;
        flagged = false;
        opened = false;
        mine = false;
        neighbors = new LinkedList<Cell>();
    }

    public Cell getCell(){
        return this;
    }

    public void setNeighbor() {
        for (int i = x - 1; i <= x + 1; i++) {
            for (int j = y - 1; j <= y + 1; j++) {
                if (i == x && j == y)
                    continue;
                else {
                    try {
                        neighbors.add(Mines.getField().get(i).get(j));
                    } catch (IndexOutOfBoundsException e) {
                        continue;
                    }
                }
            }
        }
    }

    public int getMinedNeighbors() {
        int minedNeighbors = 0;
        for (Cell k : neighbors) {
            if (k.getMine())
                minedNeighbors++;
        }
        return minedNeighbors;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public boolean checkNeighbors() {
        for (Cell i : neighbors)
            if (i.getMine())
                return false;
        return true;
    }

    public List<Cell> getNeighbors() {
        return neighbors;
    }

    public void setMine() {
        mine = true;
    }

    public boolean getMine() {
        return mine;
    }

    public boolean getFlag() {
        return flagged;
    }

    public boolean setFlag() {
        if (flagged) {
            flagged = false;
        } else
            flagged = true;
        return flagged;
    }

    public boolean openCell() {
        if (!opened && !mine)
            return opened = true;
        if(!opened&& mine){
            return opened = true;
        }
        return false;

    }

    public boolean getOpened() {
        return opened;
    }

}
