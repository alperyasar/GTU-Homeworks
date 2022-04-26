package Part2;

/**
 * <h1>HW3 Part 2 !</h1>
 * The text is represented by a list of characters in your class.
 * read in a text file and construct the text.
 * adds one or more characters (given as a string) at the specified position
 * returns the start index of the first occurrence of the searched group of characters.
 * replaces all occurrences of a character with another character.
 *
 *
 * @author  Alper YASAR
 * @version 1.0
 * @since   2020-03-31
 */

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.logging.FileHandler;
import java.util.logging.Logger;
import java.util.logging.SimpleFormatter;


public class MAIN {

    public static void main(String[] args) throws IOException {
        Logger logger = Logger.getLogger("MyLog");
        FileHandler fh;

        try {

// This block configure the logger with handler and formatter
            fh = new FileHandler("MyLogFile.log");
            logger.addHandler(fh);
            SimpleFormatter formatter = new SimpleFormatter();
            fh.setFormatter(formatter);

// the following statement is used to log any messages
            logger.info("My first log");

        } catch (SecurityException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        SimpleTextEditor deneme = new SimpleTextEditor();
        deneme.ReadFile();
        deneme.add("alper",0);
        deneme.add(" yasar" , 5);
        deneme.search("became");
        deneme.replace('^',' ');


        deneme.ReadFileLoop();
        deneme.addLoop("Zeki", 12);
        deneme.addLoop("TEKIRDAG", 110);
        deneme.searchLoop("became");
        deneme.replace('^',' ');

    }
}
