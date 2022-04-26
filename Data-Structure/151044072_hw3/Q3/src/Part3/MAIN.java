package Part3;
import java.util.*;

public class MAIN {

    public static void main(String[] args) {

        WordLinkedList puz = new WordLinkedList("PUZZLES");
        WordLinkedList fun = new WordLinkedList("FUN");
        WordLinkedList cw = new WordLinkedList("CROSSWORD");
        WordLinkedList are = new WordLinkedList("ARE");

        WordLinkedList tek = new WordLinkedList("TEKIRDAG");
        WordLinkedList ist = new WordLinkedList("ISTANBUL");
        WordLinkedList koe = new WordLinkedList("KOCAELI");
        WordLinkedList krk = new WordLinkedList("KIRKLARELİ");

        puz.add(1,fun);
        puz.add(6,cw);
        cw.add(1,are);
        cw.add(7,tek);
        tek.add(3,ist);
        ist.add(3,koe);
        koe.add(0,krk);

        CrossWordPuzzle crossWords = new CrossWordPuzzle();
        crossWords.add(puz);

        crossWords.write();

        System.out.println("After remove :");
        //crossWords.remove(are);

        crossWords.write();






    }
}
