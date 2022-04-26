package Cargo;

import java.util.Scanner;  // Import the Scanner class
import java.util.ArrayList;
public class User {
    /**
     * User send new package or can check where is package
     * with tracking number
     * @param paket package
     */
    public void SendingPack(ArrayList<shipments> paket){
        /*user menu*/
        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        Menu();
        int userChoose = inp.nextInt();

        if(userChoose == 1){        //check traking number
            System.out.print("Please enter treaking number : ");
            int trakingNumber = inp.nextInt();
            int j = 0;
            for (int i = 0 ; i< paket.size() ; i++) {
                if(paket.get(i).trackingNumber == trakingNumber){
                    paket.get(i).printShipments();
                    j++;
                }
            }
            if (j<1)
                System.out.println("Wrong traking number");
        }
        //add new package
        if(userChoose == 2){
            if(paket.size() < 1)
                paket.add(new shipments(0));

            else
                paket.add(new shipments(paket.get(paket.size()-1).trackingNumber));

        }
    }
    public static void Menu(){
        System.out.print("\n\n\n----------------- CUSTOMER INTERFACE -----------------\n" +
                "1 - Shipment Tracking\n" +
                "2 - Send Package\n" +
                "Choose : ");

    }
}
