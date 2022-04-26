package Part2;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class SimpleTextEditor {
    private MyLinkedList dataLinkedList = new MyLinkedList();
    private MyArrayList dataArrayList = new MyArrayList();
    char newData;
    /**
     * read file from input.txt
     * @throws IOException if file doesn't exist
     */
    public void ReadFile() throws IOException {
        File file = new File("input");
        FileReader fileReader = new FileReader(file);
        BufferedReader reader = new BufferedReader(fileReader);

        int c = 0;
        while ( ( c = reader.read() ) != -1 ) {
            char data = (char) c;
            dataLinkedList.add(data);
        }
    }

    /**
     * read file from input.txt
     * @throws IOException if file doesn't exist
     */
    public void ReadFileLoop() throws IOException {
        File file = new File("input");
        FileReader fileReader = new FileReader(file);
        BufferedReader reader = new BufferedReader(fileReader);

        int c = 0;
        while ( ( c = reader.read() ) != -1 ) {
            char data = (char) c;
            dataArrayList.add(data);
        }
    }
    /**
     * add character to specific location
     * @param item adding character
     * @param index specific location
     */
    public void add(String item,int index){
        dataLinkedList.add(item,index);
    }

    /**
     * add character to specific location
     * @param item adding character
     * @param index specific location
     */
    public void addLoop(String item,int index){
        dataArrayList.add(item,index);
    }

    /**
     * Search group of characters and write where founded
     * @param letter gruop of characters which searching
     */
    public void search(String letter){
        int foundation = dataLinkedList.locationFound(letter);
        if(foundation == -1){
            System.out.println("Word not found in input.txt");
        }
        else{
            System.out.println("\n\'" + letter + "\' is found in " + foundation);
        }
    }

    /**
     * Search group of characters and write where founded
     * @param letter gruop of characters which searching
     */
    public void searchLoop(String letter){
        int foundation = dataArrayList.locationFound(letter);
        if(foundation == -1){
            System.out.println("Word not found in input.txt");
        }
        else{
            System.out.println("\n\'" + letter + "\' is found in " + foundation);
        }
    }
    /**
     *  replaces all occurrences of a character with another character
     * @param newChar new character added
     * @param oldChar old character changing
     */
    public void replace(char newChar, char oldChar){
        dataLinkedList.replace(newChar,oldChar);
        dataLinkedList.write();
    }
    /**
     *  replaces all occurrences of a character with another character
     * @param newChar new character added
     * @param oldChar old character changing
     */
    public void replaceLoop(char newChar, char oldChar){
        dataArrayList.replace(newChar,oldChar);
        dataArrayList.write();
    }
}
