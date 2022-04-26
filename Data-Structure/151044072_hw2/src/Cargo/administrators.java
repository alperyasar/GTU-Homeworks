package Cargo;

import java.util.Scanner;  // Import the Scanner class
import java.util.ArrayList;
public class administrators {

    /**
     * This is for administrator page. He/She add or remove
     * @param transporters transporter employees
     * @param branchEmp branch employees
     * @param branches  branches
     */
    public static void adminSettings(ArrayList<Transporter> transporters, ArrayList<branchEmployee> branchEmp,
                                     ArrayList<Branch> branches){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        int userChoose;
        do {
            Menu();
            userChoose = inp.nextInt();
            if(userChoose == 1){
                addBranch(branches);
            }
            if(userChoose == 2){
                removeBranch(branches);
            }
            if(userChoose == 3){
                addTransporter(transporters);
            }

            if(userChoose == 4){
                removeTransporter(transporters);
            }
            if(userChoose == 5){
                addBranchEmp(branchEmp);
            }

            if(userChoose == 6){
                removeBranchEmployee(branchEmp);
            }

        }while(userChoose != 0);
    }

    /**
     * Add new branch
     * @param brc
     */
    public static void addBranch(ArrayList<Branch> brc){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the adding Branch Employee : ");
        String name = inp.nextLine();
        if( brc.size() < 1)
            brc.add(new branchEmployee(name, 0));
        else
            brc.add(new branchEmployee(name, brc.get(brc.size()-1).returnID()));

    }

    /**
     * remove special branch
     * @param brc
     */
    public static void removeBranch(ArrayList<Branch> brc){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("ID of the removing Branch Employee : ");
        int id = inp.nextInt();
        for (int i = 0; i< brc.size() ; i++){
            if(id == brc.get(i).returnID())
                brc.remove(i);
        }

    }

    /**
     * Add new branch employee
     * @param emp employee
     */
    public static void addBranchEmp(ArrayList<branchEmployee> emp){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the adding Branch Employee : ");
        String name = inp.nextLine();
        if( emp.size() < 1)
            emp.add(new branchEmployee(name, 0));
        else
            emp.add(new branchEmployee(name, emp.get(emp.size()-1).returnID()));

    }

    /**
     * Remove special employer from list
     * @param emp branch employer
     */
    public static void removeBranchEmployee(ArrayList<branchEmployee> emp){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("ID of the removing Branch Employee : ");
        int id = inp.nextInt();
        for (int i = 0; i< emp.size() ; i++){
            if(id == emp.get(i).returnID())
                emp.remove(i);
        }

    }

    /**
     * add new transporter personel
     * @param emp transperter personel
     */
    public static void addTransporter(ArrayList<Transporter> emp){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the adding Branch Employee : ");
        String name = inp.nextLine();
        if( emp.size() < 1)
            emp.add(new Transporter(name, 0));
        else
            emp.add(new Transporter(name, emp.get(emp.size()-1).returnID()));

    }

    /**
     * Remove special transporter personel
     * @param emp transporter personel
     */
    public static void removeTransporter(ArrayList<Transporter> emp){

        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("ID of the removing Branch Employee : ");
        int id = inp.nextInt();
        for (int i = 0; i< emp.size() ; i++){
            if(id == emp.get(i).returnID())
                emp.remove(i);
        }

    }


    public static void Menu(){

        System.out.print("\n\n\n----------------- ADMIN INTERFACE -----------------\n" +
                "1 - Add Branch\n" +
                "2 - Remove Branch\n" +
                "3 - Add Transportation Employee\n" +
                "4 - Remove Transportation Employee\n" +
                "5 - Add Branch Employee\n" +
                "6 - Remove Branch Employee\n" +
                "0 - Back Menu\n" +
                "choose : ");
    }

}
