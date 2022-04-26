package Part1;
/**
 * <h1>HW5 Part 1 </h1>
 * In this homework implemented 2 class:
 * First class to handle a file system hierarchy in a general tree
 * structure.
 * Second class to handle the nodes of the tree.
 *
 * A node can be created either for a file or a directory.
 *
 * Add directories or files to the file system. The path of the
 * new directory (or file) will be given as a parameter to the method.
 *
 * Remove a directory (or a file) from the file system. The path of the
 * directory (or the file) will be given as a parameter to the method. The method will warn the
 * user if the path cannot be found. If the directory includes some other directories (or files),
 * method will list the contents and ask the user whether to remove or not.
 *
 * Search the entire file system for a directory or a file including the given
 * search characters in its name. The search characters will be given as the parameter of the
 * method.
 *
 * Print the whole tree.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-04-22
 */

import java.util.Scanner;

public class FileSystemTree {
    private FileNode node;
    private boolean result;

    //FileNode class to handle the nodes of the tree
    public class FileNode {
        //file or directory name
        private String name;
        //previous directory
        private FileNode top;
        //first element in directory
        private FileNode left;
        //other files or directories in directory
        private FileNode right;
        //hold what is file (file or directory)
        private String type;

        //A constructor to create a file system with a root directory.
        FileNode(String name){
            this.name = name;
            right = null;
            left = null;
            this.type = "root";
        }

        //A constructor to insert a file or directory to system.
        FileNode(String name,String type,FileNode top){
            this.name = name;
            this.top = top;
            this.right = null;
            this.left = null;
            this.type = type;
        }
    }
    //constructor
    FileSystemTree(){
        node = new FileNode("root");
    }

    /**
     * add directory to specified directory
     * @param name directory name
     */
    public void addDir(String name){
        String[] arr = name.split("/");
        node = add(arr,node,0,"dir",node);
    }

    /**
     * add file to specified directory
     * @param name file name
     */
    public void addFile(String name){
        String[] arr = name.split("/");
        node = add(arr,node,0,"file",node);
    }

    /**
     * find the location recursively and insert file
     * @param name file path
     * @param iter search location
     * @param index array index
     * @param type file or dir
     * @param top previous directory of files
     * @return inserting node
     */
    public FileNode add(String [] name, FileNode iter, int index,String type,FileNode top){
        if (index == name.length-1 && iter == null){
            return new FileNode(name[index],type,top);
        }
        else if (name[index].compareTo(iter.name) == 0){
            iter.left = add(name,iter.left,++index,type,iter);
        }
        else {
            iter.right = add(name,iter.right,index,type,iter.top);
        }
        return iter;

    }

    /**
     * file or directory given path
     * @param name file or directory name with path
     * @return true if deleted or false is not found
     */
    public boolean remove(String name){
        this.result = false;
        String[] arr = name.split("/");
        remove(arr[arr.length-1],node);
        return this.result;
    }

    /**
     * find location from given path and deleted given name
     *  If the directory includes some other directories (or files),
     * method will list the contents and ask the user whether to remove or not.
     * @param name directory or file
     * @param iter search location
     */
    public void remove(String name,FileNode iter){
        if (iter != null)
        {
            // check if directory or file is first element in directory
            // and assign the next file to directory left
            if (iter.left != null && iter.left.name.equals(name)){
                this.result = true;
                if(iter.left.left != null){
                    System.out.println("In " + iter.left.name);
                    printFileSystem(iter.left.left);
                    System.out.println("Do you want to delete this directory? \n1 - Yes \n2 - No");
                    Scanner sc = new Scanner(System.in);
                    int i = sc.nextInt();
                    if (i == 1){
                        iter.left = iter.left.right;
                    }
                }
                else{
                    iter.left = iter.left.right;
                }
            }
            // if deleting element not first element
            else if(iter.right != null && iter.right.name == name) {
                this.result = true;
                if(iter.right.left != null){
                    System.out.println("In " + iter.right.name);
                    printFileSystem(iter.right.left);
                    System.out.println("Do you want to delete this directory? \n1 - Yes \n2 - No");
                    Scanner sc = new Scanner(System.in);
                    int i = sc.nextInt();
                    if (i == 1){
                        iter.right = iter.right.right;
                    }
                }
            }

            remove(name,iter.left);
            remove(name,iter.right);
        }
    }

    /**
     * search string
     * @param name searching name
     */
    public void search(String name){
        search(name,node);
    }

    /**
     * control files and directories has name
     * if has given name send searchFound and write
     * all path recursively
     * @param name searching name
     * @param iter iteration
     */
    public void search(String name,FileNode iter){
        if (iter != null)
        {
            if(iter.name.contains(name)) {
                System.out.print( "\n" + iter.type + " - ");
                searchFound(iter);
            }

            search(name,iter.left);
            search(name,iter.right);
        }
    }

    /**
     * Write path of found file or directory
     * @param top top directory
     */
    public void searchFound(FileNode top){
        if(top.name == "root"){
            System.out.print(top.name);
        }
        else {
            searchFound(top.top);
            System.out.print("/" + top.name);
        }
    }

    /**
     * print all files and directory
     */
    public void printFileSystem(){
        printFileSystem(node);
    }
    public void printFileSystem(FileNode iter){
        if (iter != null)
        {
            System.out.println(iter.name);
            printFileSystem(iter.left);
            printFileSystem(iter.right);
        }
    }


}
