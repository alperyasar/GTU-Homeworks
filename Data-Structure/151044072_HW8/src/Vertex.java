public class Vertex {
    private char name;

    private int row;
    private int coloumn;

    Vertex (char name, int row, int coloumn){
        this.name = name;
        this.row = row;
        this.coloumn = coloumn;
    }

    public char getName(){
        return name;
    }
    public int getRow(){
        return row;
    }
    public int getColoumn(){
        return coloumn;
    }
}
