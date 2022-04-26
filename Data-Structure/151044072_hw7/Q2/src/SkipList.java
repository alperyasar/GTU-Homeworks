import java.util.Stack;

public class SkipList {
    /** Node max size     */
    private int order;
    /** The reference to the root. */
    private Node root;

    public class Node {
        int location;
        /**   A node can contain a maximum of order - 1 keys.      */
        int key[] = new int[2 * order - 1];
        /**A node (except root node) should contain a minimum of ⌈m/2⌉ - 1 keys. */
        Node child[] = new Node[2 * order];
        boolean leaf = true;

        /**
         * find location
         * @param key finding key
         * @return location
         */
        public int Find(int key) {
            for (int i = 0; i < this.location; i++) {
                if (this.key[i] == key) {
                    return i;
                }
            }
            return -1;
        }
    }
    /**
     * Construct a B-tree with a specified order
     * @param order - the size of a node
     */
    public SkipList(int order) {
        this.order = order;
        root = new Node();
        root.location = 0;
        root.leaf = true;
    }


    /**
     * Search the key
     * @param root finding node
     * @param key finding key
     * @return node
     */
    private Node Search(Node root, int key) {
        int i;
        //If key = the first key of the node, return the node and the index.
        if (root == null)
            return root;
        //search the left child of this key recursively.
        for (i = 0; i < root.location; i++) {
            if (key < root.key[i]) {
                break;
            }
            if (key == root.key[i]) {
                return root;
            }
        }
        if (root.leaf) {
            return null;
        } else {
            return Search(root.child[i], key);
        }
    }

    // Split function

    /**
     * Split node
     * @param root root
     * @param key key
     * @param child child
     */
    private void Split(Node root, int key, Node child) {
        Node z = new Node();
        z.leaf = child.leaf;
        //Push the median key upwards and make the left keys as a left child
        z.location = order - 1;
        for (int j = 0; j < order - 1; j++) {
            z.key[j] = child.key[j + order];
        }
        if (!child.leaf) {
            for (int j = 0; j < order; j++) {
                z.child[j] = child.child[j + order];
            }
        }
        //right keys as a right child.
        child.location = order - 1;
        for (int j = root.location; j >= key + 1; j--) {
            root.child[j + 1] = root.child[j];
        }
        root.child[key + 1] = z;

        for (int j = root.location - 1; j >= key; j--) {
            root.key[j + 1] = root.key[j];
        }
        root.key[key] = child.key[order - 1];
        root.location = root.location + 1;
    }

    /**
     * insert key
     * @param key key
     */
    public void insert(int key) {
        Node root = this.root;
        //If the tree is empty, allocate a root node and insert the key.
        if (root.location == 2 * order - 1) {
            Node temp = new Node();
            this.root = temp;
            temp.leaf = false;
            temp.location = 0;
            temp.child[0] = root;
            Split(temp, 0, root);
            insert(temp, key);
        } else {
            insert(root, key);
        }
    }

    /**
     * Recursive insert an key into the Tree. Inserted
     * item must implement the Comparable interface
     * @param root The local root
     * @param key The item to be inserted
     */
    private void insert(Node root, int key) {

        if (root.leaf) {        // 4.	If the node is not full
            int i;
            for (i = root.location - 1; i >= 0 && key < root.key[i]; i--) {
                root.key[i + 1] = root.key[i];
            }   // 5.	Insert the elements in increasing order.
            root.key[i + 1] = key;
            root.location = root.location + 1;
        } else { // If the node is full
            int i = 0;
            for (i = root.location - 1; i >= 0 && key < root.key[i]; i--) ;
            i++;
            Node tmp = root.child[i];
            if (tmp.location == 2 * order - 1) {    // Insert the elements in increasing order.
                Split(root, i, tmp); //split at the median.
                if (key > root.key[i]) {
                    i++;
                }
            }   // insert to node child
            insert(root.child[i], key);
        }

    }

    /**
     * print all nodes
     */
    public void print() {
        print(root);
    }

    /**
     * Remove an key from the tree.
     * @param tempNode - The root of tree
     * @param key The key to be removed
     */
    private void Remove(Node tempNode, int key) {
        int pos = tempNode.Find(key); // finde key exist
        if (pos != -1) {
            if (tempNode.leaf) {    //check leaf
                int i = 0;
                //The deletion of the key does not violate the property of
                //the minimum number of keys a node should hold.
                for (i = 0; i < tempNode.location && tempNode.key[i] != key; i++) ;
                for (; i < tempNode.location; i++) {
                    if (i != 2 * order - 2) {
                        tempNode.key[i] = tempNode.key[i + 1];
                    }
                }
                tempNode.location--;
                return;
            }
            if (!tempNode.leaf) {
                 /*The deletion of the key violates the property of the
                  minimum number of keys a node should hold.             */

                Node pred = tempNode.child[pos];
                int predKey = 0;
                if (pred.location >= order) {
                    //borrow a key from its immediate neighboring
                    // sibling node in the order of left to right.
                    for (; ; ) {
                        if (pred.leaf) {
                            //If the left sibling node has more than a
                            // minimum number of keys, then borrow a key from this node.
                            System.out.println(pred.location);
                            predKey = pred.key[pred.location - 1];
                            break;
                        } else {
                            pred = pred.child[pred.location];
                        }
                    }
                    Remove(pred, predKey);
                    tempNode.key[pos] = predKey;
                    return;
                }

                Node nextNode = tempNode.child[pos + 1];
                if (nextNode.location >= order) {
                    //check to borrow from the immediate right sibling node.
                    int nextKey = nextNode.key[0];
                    if (!nextNode.leaf) {
                        nextNode = nextNode.child[0];
                        for (; ; ) {
                            if (nextNode.leaf) {
                                nextKey = nextNode.key[nextNode.location - 1];
                                break;
                            } else {
                                nextNode = nextNode.child[nextNode.location];
                            }
                        }
                    }
                    Remove(nextNode, nextKey);
                    tempNode.key[pos] = nextKey;
                    return;
                }
                //merge the node with either the left sibling node or the right sibling node.
                int temp = pred.location + 1;
                pred.key[pred.location++] = tempNode.key[pos];
                //left
                for (int i = 0, j = pred.location; i < nextNode.location; i++) {
                    pred.key[j++] = nextNode.key[i];
                    pred.location++;
                }

                for (int i = 0; i < nextNode.location + 1; i++) {
                    pred.child[temp++] = nextNode.child[i];
                }
                //right
                tempNode.child[pos] = pred;
                for (int i = pos; i < tempNode.location; i++) {
                    if (i != 2 * order - 2) {
                        tempNode.key[i] = tempNode.key[i + 1];
                    }
                }
                for (int i = pos + 1; i < tempNode.location + 1; i++) {
                    if (i != 2 * order - 1) {
                        tempNode.child[i] = tempNode.child[i + 1];
                    }
                }
                tempNode.location--;
                if (tempNode.location == 0) {
                    if (tempNode == root) {
                        root = tempNode.child[0];
                    }
                    tempNode = tempNode.child[0];
                }
                Remove(pred, key);
                return;
            }
        } else {    //If the key to be deleted lies in the
            // internal node, the following cases occur.
            for (pos = 0; pos < tempNode.location; pos++) {
                if (tempNode.key[pos] > key) {
                    break;
                }
            }

            Node tmp = tempNode.child[pos];
            if (tmp.location >= order) {
                Remove(tmp, key);
                return;
            }

            if (true) {
                Node nb = null;
                int devider = -1;
                //The internal node, which is deleted, is replaced by an inorder predecessor
                // if the left child has more than the minimum number of keys.
                if (pos != tempNode.location && tempNode.child[pos + 1].location >= order) {
                    devider = tempNode.key[pos];
                    nb = tempNode.child[pos + 1];
                    tempNode.key[pos] = nb.key[0];
                    tmp.key[tmp.location++] = devider;
                    tmp.child[tmp.location] = nb.child[0];
                    for (int i = 1; i < nb.location; i++) {
                        nb.key[i - 1] = nb.key[i];
                    }
                    for (int i = 1; i <= nb.location; i++) {
                        nb.child[i - 1] = nb.child[i];
                    }
                    nb.location--;
                    Remove(tmp, key);
                    return;
                    //The internal node, which is deleted, is replaced by an inorder successor
                    // if the right child has more than the minimum number of keys.
                } else if (pos != 0 && tempNode.child[pos - 1].location >= order) {

                    devider = tempNode.key[pos - 1];
                    nb = tempNode.child[pos - 1];
                    tempNode.key[pos - 1] = nb.key[nb.location - 1];
                    Node child = nb.child[nb.location];
                    nb.location--;

                    for (int i = tmp.location; i > 0; i--) {
                        tmp.key[i] = tmp.key[i - 1];
                    }
                    tmp.key[0] = devider;
                    for (int i = tmp.location + 1; i > 0; i--) {
                        tmp.child[i] = tmp.child[i - 1];
                    }
                    tmp.child[0] = child;
                    tmp.location++;
                    Remove(tmp, key);
                    return;
                    //If either child has exactly a minimum number
                    // of keys then, merge the left and the right children
                } else {
                    Node lt = null;
                    Node rt = null;
                    boolean last = false;
                    if (pos != tempNode.location) {
                        devider = tempNode.key[pos];
                        lt = tempNode.child[pos];
                        rt = tempNode.child[pos + 1];
                    } else {
                        devider = tempNode.key[pos - 1];
                        rt = tempNode.child[pos];
                        lt = tempNode.child[pos - 1];
                        last = true;
                        pos--;
                    }
                    for (int i = pos; i < tempNode.location - 1; i++) {
                        tempNode.key[i] = tempNode.key[i + 1];
                    }
                    for (int i = pos + 1; i < tempNode.location; i++) {
                        tempNode.child[i] = tempNode.child[i + 1];
                    }
                    tempNode.location--;
                    lt.key[lt.location++] = devider;

                    for (int i = 0, j = lt.location; i < rt.location + 1; i++, j++) {
                        if (i < rt.location) {
                            lt.key[j] = rt.key[i];
                        }
                        lt.child[j] = rt.child[i];
                    }
                    lt.location += rt.location;
                    if (tempNode.location == 0) {
                        if (tempNode == root) {
                            root = tempNode.child[0];
                        }
                        tempNode = tempNode.child[0];
                    }
                    Remove(lt, key);
                    return;
                }
            }
        }
    }


    /**
     * Removes an instance of the given item
     * @param key The item to remove
     * @return true if the item is removed, false if the item is not in the list
     */
    public boolean remove(int key) {
        Node x = Search(root, key);
        if (x == null) {
            return false;
        }
        Remove(root, key);
        return true;
    }

    // Show the node
    private void print(Node x) {
        assert (x == null);
        for (int i = 0; i < x.location; i++) {
            System.out.print(x.key[i] + " ");
        }
        if (!x.leaf) {
            for (int i = 0; i < x.location + 1; i++) {
                print(x.child[i]);
            }
        }
    }
}