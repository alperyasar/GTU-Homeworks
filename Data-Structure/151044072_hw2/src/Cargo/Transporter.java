package Cargo;

import java.util.ArrayList;
import java.util.Scanner;

public class Transporter extends Branch {
    /**
     * Constructer for branch employee
     * @param NAME name
     * @param ID id
     */
    public Transporter(String NAME, int ID){
        super(NAME,ID);
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

    /**
     * Transporter personel can change info about package
     * delivered or not
     * @param pack
     */
    public void TransporterSettings(ArrayList<shipments> pack){
        int userChoose;
        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Enter Package trackingNumber : ");
        int i = inp.nextInt();
        int l = 0;
        for (int k = 0 ; k< pack.size() ; k++) {
            if(pack.get(k).trackingNumber == i){
                Menu();
                int j = inp.nextInt();
                pack.get(k).changeInfo(j);
                l++;
            }
        }
        if(l<0)
            System.out.println("There is no package with this tracking number");
    }
    /**
     * This method is used to print user interface.
     * Select which user will use the program.
     */
    public void Menu(){

        System.out.print("\n\n\n----------------- TRANSPORTER INTERFACE -----------------\n" +
                "4 - Delivered\n" +
                "2 - Not Delivered\n" +
                "0 - Exit\n" +
                "choose : ");
    }
}
