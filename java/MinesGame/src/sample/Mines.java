package sample;

import java.util.ArrayList;
import java.util.Random;

public class Mines {
    private boolean showAll;
    private int height;
    private int width;
    private int numMines;
    private static ArrayList<ArrayList<Cell>> field;

    public Mines(int height, int width, int numMines) {
        field = new ArrayList<ArrayList<Cell>>();

        for (int i = 0; i < height; i++) {
            ArrayList<Cell> row = new ArrayList<Cell>();
            for (int j = 0; j < width; j++) {
                row.add(new Cell(i, j));
            }
            field.add(row);
        }
        this.height = height;
        this.width = width;
        this.numMines = numMines;
        showAll = false;

        Random newRandomVal = new Random();
        for (int c = 0; c < this.numMines; c++) {
            int a, b;
            a = newRandomVal.nextInt(height);
            if (a == 0)
                a++;
            b = newRandomVal.nextInt(width);
            if (b == 0)
                b++;
            if (!addMine(a, b))
                c--;
        }
        for (ArrayList<Cell> i : field) {
            for (Cell j : i)
                j.setNeighbor();
        }
    }

    public boolean addMine(int i, int j) {
        if (!field.get(i).get(j).getMine()) {
            field.get(i).get(j).setMine();
            return true;
        } else
            return false;
    }

    public static ArrayList<ArrayList<Cell>> getField() {
        return field;
    }

    public boolean open(int i, int j) {
        if (field.get(i).get(j).openCell() && field.get(i).get(j).checkNeighbors()) {
            for (Cell k : field.get(i).get(j).getNeighbors()) {
                open(k.getX(), k.getY());
            }
            return true;
        }
        else if(field.get(i).get(j).getMine()) {
            field.get(i).get(j).openCell();
            return true;
        }
        return false;
    }

    public void toggleFlag(int x, int y) {
        field.get(x).get(y).setFlag();
    }

    public boolean isDone() {
        int count = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                if (field.get(i).get(j).getOpened() && !field.get(i).get(j).getMine()
                        || !field.get(i).get(j).getOpened() && field.get(i).get(j).getFlag())
                    count++;
        }
        if (count == (height * width) - numMines)
            return true;
        return false;
    }

    public String get(int i, int j) {
        if (!showAll) {
            if (!field.get(i).get(j).getOpened() && !field.get(i).get(j).getFlag())
                return ".";
            else if (!field.get(i).get(j).getOpened() && field.get(i).get(j).getFlag())
                return "F";
            else if (field.get(i).get(j).getOpened() && field.get(i).get(j).getMine())
                return "X";
            else if (field.get(i).get(j).getOpened() && !field.get(i).get(j).getMine()) {
                String str = "";
                int num = field.get(i).get(j).getMinedNeighbors();
                if (num > 0)
                    return str + num;
                else
                    return " ";
            }
            return " ";
        } else {
            if (field.get(i).get(j).getFlag())
                return "F";
            else if (field.get(i).get(j).getMine())
                return "X";
            else if (!field.get(i).get(j).getMine()) {
                String str = "";
                int num = field.get(i).get(j).getMinedNeighbors();
                if (num > 0)
                    return str + num;
                else return " ";
            }
            return " ";
        }
    }

    public void setShowAll(boolean showAll) {
        this.showAll = showAll;
    }

    public String toString() {
        String toRet = "";
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++)
                toRet += get(i, j);
            toRet += "\n";
        }
        return toRet;
    }
}
