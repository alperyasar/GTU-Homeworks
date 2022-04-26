package Part1;


public class MAIN {
    public static void main(String[] args) {
        FileSystemTree myFileSystem = new FileSystemTree();

        myFileSystem.addDir("root/first_directory");
        myFileSystem.addDir("root/second_directory");
        myFileSystem.addFile("root/first_directory/new_file.txt");
        myFileSystem.addDir("root/second_directory/new_directory");
        myFileSystem.addFile("root/second_directory/new_directory/new_file.doc");

        System.out.println("\nAll Element in Tree");
        myFileSystem.printFileSystem();

        System.out.print("\nSearch file or directory names including 'new' ");
        myFileSystem.search("new");
        System.out.println("\n");
        //Remove files or directories
        if ( !myFileSystem.remove("root/first_directory/new_file.txt") ){
            System.out.println("The path cannot be found!");
        }
        if ( !myFileSystem.remove("root/second_directory/new_directory") ){
            System.out.println("The path cannot be found!");
        }


        System.out.println("\n All Element in Tree");
        myFileSystem.printFileSystem();

    }
}
