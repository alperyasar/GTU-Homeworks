import java.util.Scanner;  // Import the Scanner class

public class administrators {

    public branch branchSetting(branch sube,int userChoose){
/**
 * This method for admin page. The admin can add or
 * remove branch, branch employee and transportation
 * personnel. He/She chosing what he/she will do.
 * @param sube is a branch that taken from main and
 * the admin making a decide what will do in this branch.
 * @param userChoose is decision of admin.
 * @return branch what happened in this branch with
 * @param brc .
 */
        branch brc = new branch();
        Scanner inp = new Scanner(System.in);  // Create a Scanner object
        if(sube.transportationEmployeeSize != 0 || sube.branchEmployeeSize != 0 ){
            brc = sube;
        }

        while(userChoose != 0 ){
            if(userChoose == 3){
                ++brc.transportationEmployeeSize;
                brc.transportationEmployee = addTransportalPersonal(brc.transportationEmployeeSize, brc.transportationEmployee);
            }

            if(userChoose == 4){
                brc.transportationEmployeeSize--;
                brc.transportationEmployee = removeTransportalPersonal(brc.transportationEmployeeSize, brc.transportationEmployee);
            }
            if(userChoose == 5){
                ++brc.branchEmployeeSize;
                brc.branchEmployee = addBranchEmployee(brc.branchEmployeeSize, brc.branchEmployee);
            }

            if(userChoose == 6){
                brc.branchEmployeeSize--;
                brc.branchEmployee = removeBranchEmployee(brc.branchEmployeeSize, brc.branchEmployee);
            }
            adminMenu();
            userChoose = inp.nextInt();
        }


        return brc;
    }
    public static void adminMenu(){
/**
 * This method is used to print admin interface.
 * Select which admin will use the program.
 */
        System.out.print("\n\n\n\n\n\n----------------- ADMIN INTERFACE -----------------\n" +
                "1 - Add Branch\n" +
                "2 - Remove Branch\n" +
                "3 - Add Transportation Employee\n" +
                "4 - Remove Transportation Employee\n" +
                "5 - Add Branch Employee\n" +
                "6 - Remove Branch Employee\n" +
                "0 - Back Menu\n" +
                "choose : ");
    }

    public String [] addTransportalPersonal(int numb,String [] employee){
/**
 *	This method for add transportation personnel to
 *	branch.
 *	@param numb is how many transportation personnel working
 *	this branch.
 *	@param employee is transportation personnel.
 *	@param name is new personel.
 *	@return string array.
 */
        String [] temp = new String[numb];
        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the adding Branch Employee : ");
        String name = inp.nextLine();

        if(numb > 1){
            for(int i = 0; i< numb-1; i++){
                temp[i] = employee[i];
            }
            temp[numb-1] = name;

        }
        else{
            temp = new String[1];
            temp[0] = name;
        }
        return temp;
    }
    public String [] removeTransportalPersonal(int numb,String [] employee){
/**
 *	This method for remove transportation personnel to
 *	branch.
 *	@param numb is how many transportation personnel working
 *	this branch.
 *	@param employee is transportation personnel.
 *	@param name is leaving personel.
 *	@return string array.
 */
        String [] temp = new String[numb];
        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the removing Branch Employee : ");
        String name = inp.nextLine();

        int j = 0;
        for(int i = 0; i< numb+1; i++){
            if( !(employee[i].equalsIgnoreCase(name)) ){
                temp[j] = employee[i];
                j++;
            }

        }

        return temp;
    }


    public String [] addBranchEmployee(int numb,String [] employee){
/**
 *	This method for add Branch employee to
 *	branch.
 *	@param numb is how many Branch employee working
 *	this branch.
 *	@param employee is Branch employee.
 *	@param name is new employee.
 *	@return string array.
 */
        String [] temp = new String[numb];
        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the adding Branch Employee : ");
        String name = inp.nextLine();

        if(numb > 1){
            for(int i = 0; i< numb-1; i++){
                temp[i] = employee[i];
            }
            temp[numb-1] = name;

        }
        else{
            temp = new String[1];
            temp[0] = name;
        }
        return temp;
    }
    public String [] removeBranchEmployee(int numb,String [] employee){
/**
 *	This method for Remove Branch employee to
 *	branch.
 *	@param numb is how many Branch employee working
 *	this branch.
 *	@param employee is Branch employee.
 *	@param name is leaving employee.
 *	@return string array.
 */
        String [] temp = new String[numb];
        Scanner inp = new Scanner(System.in);  // Create a Scanner object

        System.out.print("Name of the removing Branch Employee : ");
        String name = inp.nextLine();

        int j = 0;
        for(int i = 0; i< numb+1; i++){
            if( !(employee[i].equalsIgnoreCase(name)) ){
                temp[j] = employee[i];
                j++;
            }

        }

        return temp;
    }

}