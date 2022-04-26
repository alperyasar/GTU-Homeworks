import java.util.*;

public class Books {
    //<author name, < book name, <location,status>>>
        Map<String,Map<String,Set<String>>> map =
            new HashMap<String, Map<String, Set<String>>>();

    /**
     * first crate library for search
     */
    Books (){
        add("Sigmund Freud","Amator Psikanaliz");
        add("Aldous Huxley","Cesur Yeni Dünya");
        add("Grigory Petrov","Beyaz Zambaklar Ülkesinde");
        add("Jack London","Beyaz Diş");
        add("Yusuf Atılgan","Anayurt Oteli");
        add("Sabahattin Ali","İcimizdeki Seytan");
        add("Lev N. Tolstoy","İnsan Neyle Yaşar");
        add("Friedrich Nietzsche","Böyle Söyledi Zerdüşt ");
        add("Thomas More","Utopia");
        add("Jose Mauro De Vasconcelos","Seker Portakalı");
        add("Gabriel Garcia Marquez","Kırmızı Pazartesi");
        add("Franz Kafka","Dönüşüm");
        add("Yusuf Atılgan","Aylak Adam");
        add("Stefan Zweig","Olağanüstü Bir Gece");
        add("Oscar Wilde","Dorian Gray'in Portresi");
        add("Isidor Feinstein Stone","Sokrates'in Yargılanması\n");
        add("Jose Mauro De Vasconcelos","Seker Portakalı");
        add("Gabriel Garcia Marquez","Kırmızı Pazartesi");
        add("Franz Kafka","Dönüşüm");
        add("Yusuf Atılgan","Aylak Adam");
        add("Stefan Zweig","Olağanüstü Bir Gece");
        add("Gabriel Garcia Marquez","Kırmızı Pazartesi");
        add("Franz Kafka","Dönüşüm");
        add("Gabriel Garcia Marquez","Kırmızı Pazartesi");
        add("Franz Kafka","Aylak Adam");
    }

    /**
     * add new book to library (map)
     * @param author author of book
     * @param nameOfBook name of book
     */
    protected void add(String author, String nameOfBook){
        Random rand = new Random();
        //random location
        String location = "c" + rand.nextInt(30) + "s" + (rand.nextInt(8) + 1)
                + "." +rand.nextInt(256);
        Set<String> set;
        // if library has this author books check has same book in library
        if (map.get(author) != null){
            Map<String,Set<String>> temp = map.get(author);
            //if same book is found
            if (temp.get(nameOfBook) != null){
                // check locations
                set = temp.get(nameOfBook);
                if (set == null) {
                    set = new HashSet<String>();
                }
            }
            else {
                set = new HashSet<String>();
            }
            set.add(location);
            temp.put(nameOfBook,set);
        }
        // if library has not this author books so creat ne
        else {
            set = new HashSet<String>();
            set.add(location);
            Map<String,Set<String>> temp = new HashMap<String,Set<String>>();
            temp.put(nameOfBook,set);
            map.put(author,temp);
        }

    }

    /**
     * search book name in library and print all information
     * with location
     * @param name name of book
     */
    public void SearchBook(String name){
        for (Map.Entry<String, Map<String,Set<String>>> entry : map.entrySet()) {
            String author = entry.getKey();
            Map<String,Set<String>> entry2 = entry.getValue();
            Set<String> set = entry2.get(name);
            if (set != null){
                for (String s : set) {
                    System.out.println("author : "+author + "  -  name : " + name + "  Location : " + s);
                }
            }
        }
    }

    /**
     *  When searching by author name, all books of the author in the library will be listed on the screen.
     * Then, whichever book the user chooses, the location(s) of that book will be displayed.
     * @param name author
     */
    public void SearchAuthor(String name){
        Map<String,Set<String>> entry= map.get(name);
        if (entry != null){
            for (Map.Entry<String,Set<String>> entry2: entry.entrySet()){
                String nameOfBook = entry2.getKey();
                Set<String> set = entry2.getValue();
                for (String s : set) {
                    System.out.println("author : "+ name + "  -  name : " + nameOfBook);
                }
            }
        }
        System.out.print("Book name : ");
        Scanner scanner = new Scanner(System.in);
        String books = scanner.nextLine();  // Read user input
        SearchBook(books);
    }

    /**
     * print all books in library
     */
    void print(){
        for (Map.Entry<String, Map<String,Set<String>>> entry : map.entrySet()) {
            String author = entry.getKey();
            Map<String,Set<String>> entry2 = entry.getValue();
            for (Map.Entry<String,Set<String>> entry3: entry2.entrySet()){
                String nameOfBook = entry3.getKey();
                Set<String> set = entry3.getValue();
                for (String s : set) {
                    System.out.println("author : "+author + "  -  name : " + nameOfBook + "  Location : " + s);
                }
            }
        }
    }
}
