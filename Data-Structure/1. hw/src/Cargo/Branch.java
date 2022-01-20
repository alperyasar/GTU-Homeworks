package Cargo;

public class Branch {
    protected String name;
    protected int id;
    /**
     * Constructer for branch employee
     * @param NAME name
     * @param ID id
     */
    public Branch(String NAME, int ID){
        name = NAME;
        id = id+1;
    }
    public int returnID(){
        return id;
    }
    /**
     * print id and name of branch employer
     */
    public void print(){
        System.out.println(id + " " + name);
    }
}
