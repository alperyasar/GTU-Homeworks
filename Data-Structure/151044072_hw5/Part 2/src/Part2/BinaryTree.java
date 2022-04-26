package Part2;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.Serializable;
import java.util.Scanner;

public class BinaryTree<E> implements Serializable {
    protected Node<E> root;

    public BinaryTree() { root = null; }

    protected BinaryTree(Node<E> root) {
        this.root = root;
    }

    public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree) {
        this.root = new BinaryTree.Node(data);
        if (leftTree != null) {
            this.root.left = leftTree.root;
        } else {
            this.root.left = null;
        }

        if (rightTree != null) {
            this.root.right = rightTree.root;
        } else {
            this.root.right = null;
        }

    }

    public BinaryTree<E> getLeftSubtree() {
        return root != null && root.left != null ? new BinaryTree(root.left) : null;
    }

    public BinaryTree<E> getRightSubtree() {
        return root != null && root.right != null ? new BinaryTree(root.right) : null;
    }

    public E getData() {
        return root != null ? root.data : null;
    }

    public boolean isLeaf() {
        return root.left == null && root.right == null;
    }

    public String toString() {
        System.out.println(root);
        StringBuilder sb = new StringBuilder();
        this.preOrderTraverse(root, 1, sb);
        return sb.toString();
    }


    private void preOrderTraverse(Node<E> node, int depth, StringBuilder sb) {
        for(int var = 1; var < depth; ++var) {
            sb.append("  ");
        }

        if (node == null) {
            sb.append("null\n");
        } else {
            sb.append(node.toString());
            sb.append("\n");
            this.preOrderTraverse(node.left, depth + 1, sb);
            this.preOrderTraverse(node.right, depth + 1, sb);
        }

    }

    public String toString2() {
        StringBuilder sb = new StringBuilder();
        this.postOrderTraverse(this.root, 1, sb);
        return sb.toString();
    }

    private void postOrderTraverse(Node<E> node, int depth, StringBuilder sb) {
        for(int var4 = 1; var4 < depth; ++var4) {
        }

        if (node != null) {
            this.postOrderTraverse(node.left, depth + 1, sb);
            this.postOrderTraverse(node.right, depth + 1, sb);
            sb.append(node.toString());
            sb.append("\n");
        }

    }

 /*   private void inOrderTraverse(BinaryTree.Node<E> var1, int var2, StringBuilder var3) {
        for(int var4 = 1; var4 < var2; ++var4) {
        }

        if (var1 != null) {
            this.inOrderTraverse(var1.left, var2 + 1, var3);
            var3.append(var1.toString());
            var3.append("\n");
            this.inOrderTraverse(var1.right, var2 + 1, var3);
        }

    }
*/
    public BinaryTree<String> readBinaryTree(Scanner Scan) {
        String data = Scan.next();
        if (data.equals("null")) {
            return null;
        } else {
            BinaryTree<String> leftTree = readBinaryTree(Scan);
            BinaryTree<String> rightTree = readBinaryTree(Scan);
            return new BinaryTree<String>(data, leftTree, rightTree);
        }
    }

    protected static class Node<E> implements Serializable {
        public E data;
        public Node<E> left;
        public Node<E> right;

        public Node(E var1) {
            this.data = var1;
            this.left = null;
            this.right = null;
        }

        public String toString() {
            return data.toString();
        }
    }
}
