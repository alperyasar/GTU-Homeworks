/**
 * <h1>CARGO COMPANY!</h1>
 * The automation system for a cargo company has users such as
 * administrators, branch employees, transportation personnel
 * and customers.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-03-02
 */

package Cargo;

import java.util.Scanner;  // Import the Scanner class
import java.util.ArrayList;

public class MAIN {

    /**
     * Menu for First Page
     */
    public static void Menu(){

        System.out.print("\n\n\n----------------- USER INTERFACE -----------------\n" +
                "1 - Administrator\n" +
                "2 - Branch Employee\n" +
                "3 - Transportation Employee\n" +
                "4 - Customer\n" +
                "0 - Exit\n" +
                "choose : ");
    }

    /**
     *User types are determined and the operations that he/she wants to do according to the individual menus are selected.
     * @param args
     */
    public static void main(String[] args) {

        administrators adm = new administrators();
        User user = new User();
        ArrayList<Branch> brc = new ArrayList<Branch>();
        ArrayList<branchEmployee> brcEmployee = new ArrayList<branchEmployee>();
        ArrayList<Transporter> transporters = new ArrayList<Transporter>();
        ArrayList<String> scanString = new ArrayList<String>(); // Create an ArrayList object
        ArrayList<shipments> pack = new ArrayList<shipments>();

        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        Scanner inp2 = new Scanner(System.in);  // Create a Scanner object

        int userChoose;  // Read user input
        int adminChoose;
        do{
            Menu();
            userChoose = inp.nextInt();

            if(userChoose == 1){
                adm.adminSettings(transporters, brcEmployee, brc);

                for (int i = 0 ; i<brcEmployee.size(); i++)
                    brcEmployee.get(i).print();
                for (int i = 0 ; i<transporters.size(); i++)
                    transporters.get(i).print();

            }

            if(userChoose == 2){
                // Branch Employee menu
                System.out.print("Enter branch ID : ");
                int i = inp.nextInt();
                int k = 0;
                for (int j = 0 ; j < brcEmployee.size(); j++){
                    if(brcEmployee.get(j).returnID() == i){
                        brcEmployee.get(j).BranchSettings(pack);
                        k++;
                    }
                }
                if(k<=0)
                    System.out.println("There is no personel with this ID");
            }

            if(userChoose == 3){
                System.out.print("Enter branch ID : ");
                int i = inp.nextInt();
                int k = 0;
                for (int j = 0 ; j < transporters.size(); j++){
                    if(transporters.get(j).returnID() == i){
                        transporters.get(j).TransporterSettings(pack);
                        k++;
                    }
                }
                if(k<=0)
                    System.out.println("There is no personel with this ID");
            }

            if(userChoose == 4){
                user.SendingPack(pack);
            }
        }while(userChoose != 0);
    }



}