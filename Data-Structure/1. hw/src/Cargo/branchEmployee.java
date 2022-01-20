package Cargo;

import java.util.Scanner;  // Import the Scanner class
import java.util.ArrayList;

public class branchEmployee extends Branch {
    /**
     * Constructer for branch employee
     * @param NAME name
     * @param ID id
     */
    public branchEmployee(String NAME, int ID){
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
     * Branch employer can change info about package
     * @param pack deliver
     */
    public void BranchSettings(ArrayList<shipments> pack){
        int userChoose;
        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        do {
            Menu();
            userChoose = inp.nextInt();

            if(userChoose == 1){
                System.out.print("Enter Package trackingNumber : ");
                int i = inp.nextInt();
                int l = 0;
                for (int k = 0 ; k< pack.size() ; k++) {
                    if(pack.get(k).trackingNumber == i){
                        System.out.println("Enter 2 for Arrive to branch\n" +
                                "enter 3 for Leave from branch\n" +
                                "Choose : ");
                        int j = inp.nextInt();
                        pack.get(k).changeInfo(j);
                        l++;
                    }
                }
                if(l<0)
                    System.out.println("There is no package with this tracking number");

            }
            if (userChoose == 2){
                System.out.print("Enter Tracking number for delete : ");
                int i = inp.nextInt();
                int l = 0;
                for (int k = 0 ; k< pack.size() ; k++) {
                    if(pack.get(k).trackingNumber == i){
                        pack.remove(k);
                        l++;
                    }
                }
                if(l<0)
                    System.out.println("There is no package with this tracking number");

            }
        }while (userChoose != 0);
    }
    /**
     * This method is used to print user interface.
     * Select which user will use the program.
     */
    public void Menu(){

        System.out.print("\n\n\n----------------- BRANCH INTERFACE -----------------\n" +
                "1 - Info abaout package\n" +
                "2 - Delete package\n" +
                "0 - Exit\n" +
                "choose : ");
    }

}
