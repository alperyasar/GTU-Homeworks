public class branch{

    int branchEmployeeSize;
    int transportationEmployeeSize;
    String [] branchEmployee;
    String [] transportationEmployee;
    branch (){
        this.branchEmployeeSize = 0;
        this.transportationEmployeeSize = 0;
    }
    public branch(branch temp){
/**
 * This constructor for assing branch object
 * to another branch object.
 * @return branch object for assign.
 */
        this.branchEmployeeSize = temp.branchEmployeeSize;
        this.transportationEmployeeSize = temp.transportationEmployeeSize;
        this.branchEmployee = temp.branchEmployee;
        this.transportationEmployee = temp.transportationEmployee;

    }
    public void branchPage(){
/**
 * This method is used to print user interface.
 * Select which user will use the program.
 */
        System.out.print("\n\n\n\n\n\n----------------- BRANCH INTERFACE -----------------\n" +
                "1 - Info abaout package\n" +
                "2 - Delete package\n" +
                "0 - Exit\n" +
                "choose : ");
    }
}