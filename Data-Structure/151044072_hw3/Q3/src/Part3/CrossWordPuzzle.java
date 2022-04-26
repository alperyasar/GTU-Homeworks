package Part3;

import java.util.ArrayList;
import java.util.List;

public class CrossWordPuzzle {
    List<WordLinkedList> words = new ArrayList<>();

    /**
     *  Along with the given word, it also records its intersection from the list.
     * @param word is want to records in the puzzle list.
     */
    public void add(WordLinkedList word){
        if( !words.contains(word) )
            words.add(word);

        if ( word.hasCross() ) {
            List<WordLinkedList> temp = word.getWord();

            for ( int i = 0; i < temp.size() ; i++ ) {
                if( !words.contains(temp.get(i)))
                    add(temp.get(i));
            }
        }
    }

    /**
     *  Along with the given word, it also deletes its intersection from the list.
     * @param word is want to remove in the puzzle list.
     */
    public void remove(WordLinkedList word){
        if( words.contains(word) )
            words.remove(word);

        if ( word.hasCross() ) {
            List<WordLinkedList> temp = word.getWord();

            for ( int i = 0; i < temp.size() ; i++ ) {
                if(words.contains(temp.get(i)))
                    remove(temp.get(i));
            }
        }
    }

    /**
     * Displays puzzle size that how much word recorded and that words with their crossword and also indexis.
     */
    public void write () {
        for ( int i = 0; i < words.size() ; i++ ) {
            words.get(i).write();
        }
    }


}
