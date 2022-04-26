import java.util.Objects;

public class Package implements Comparable<Package> {
    private String name;
    private String version;
    private int quantity;
    private double price;
    Package (String name, String version,  int quantity, double price){
        this.name = name;
        this.version = version;
        this.quantity = quantity;
        this.price = price;
    }
    Package (String name){
        this.name = name;
        version = null;
    }
    Package (String name, String version){
        this.version = version;
        this.name = name;
        version = null;
    }
    public String toString(){
        return (name + " " + version + ", quantity: " +
                quantity + ", price: " + price);
    }

    @Override
    public int compareTo(Package o) {
        if (o.version != null){
            return name.compareTo(o.name) + version.compareTo(o.version);
        }
        return name.compareTo(o.name);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Package aPackage = (Package) o;
        if (aPackage.version != null){
            if (compareTo(aPackage) == 0){
                return true;
            }
            else return false;
        }
        return name.contains(aPackage.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }

    public int getQuantity() {
        return quantity;
    }
    public void decreaseQuantity() {
        quantity--;
    }

    public boolean removeSize(){
        quantity--;
        if (quantity == 0)
            return true;
        return false;
    }
    public void changeName(String name) {
        this.name = name;
    }
    public void changeVersion(String version) {
        this.version = version;
    }
    public void changeQuantity(int quantity) {
        this.quantity = quantity;
    }
    public void changePrice(Double price) {
        this.price = price;
    }

}
