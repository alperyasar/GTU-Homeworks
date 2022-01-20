#include <stdio.h>
#include <stdlib.h>
 
#define FALSE  0
#define TRUE  1
 
typedef struct {
    int info;
} DATA;
 
typedef struct node {
    DATA data;
    struct node* prev;
} NODE;
 
void init(NODE** top) {/* set top of stack as empty */
    *top = NULL;
}
 
/* Returns new TOS
 * [In ] Current TOS
 * [In ] Data node to push
 */
NODE* push(NODE* top, DATA data) {
    NODE* tmp = (NODE*) malloc(sizeof (NODE));
    if (tmp == NULL) { // no memory available
        exit(0);
    }
    tmp->data = data;
    tmp->prev = top;
    top = tmp;
    return top;
}
 
/*  Returns new TOS
 * [In] TOS 
 * [Out] Data node to pop
 */
NODE* pop(NODE *top, DATA *element) {
    NODE* tmp = top;
    *element = top->data;
    top = top->prev;
    free(tmp);
    return top;
}
 
DATA* top_of_stack(NODE *top) {
    return &top->data;
}
 
NODE * push_from_other_stack(NODE *stack_to_push,
        NODE *stack_to_pop) {
    DATA elementBuf;
 
    //stack_to_push = top_of_stack(stack_to_pop);
    stack_to_pop = pop(stack_to_pop, &elementBuf);
    stack_to_push = push(stack_to_push, elementBuf);
 
    return stack_to_push;
}
 
/*
 * Return 1 if empty
 */
int is_empty(NODE* top) {
    return (top == NULL) ? 1 : 0;
}
 
int main() {
    NODE * top, * second_stack;
    NODE * arr[4];
    DATA element;
    int i, size, counter = 0;
 
    /* stack size is dynamic and specified at runtime */
    printf("Enter stack size:");
    scanf("%d", &size);
 
    printf("Push elements to stack\n");
    init(&top);
    while (counter < size) {
        element.info = rand();
        printf("push element %d into stack\n", element.info);
        top = push(top, element);
        counter++;
    }
    printf("\nTop Of stack %d\n", top_of_stack(top)->info);
 
    init(&second_stack);
  /*  element.info = 333333;
    second_stack = push(second_stack, element);
    top = push_from_other_stack(top, second_stack);*/
 
    printf("Pop elements from stack\n");
    while (0 == is_empty(top)) {
        top = pop(top, &element);
        printf("pop element %d from stack\n", element.info);
    }
 
    //Array of Stacks
    printf("\nPush Elements to Stack - Array Syntax\n");
    for (i = 0; i < 3; i++) {
        init(&arr[i]);
    }
 
    for (i = 0; i < 3; i++) {
        element.info = rand() % 30;
        printf("Push Element %3d Into Stack\n", element.info);
        arr[1] = push(arr[1], element);
    }
    while (0 == is_empty(arr[1])) {
        arr[1] = pop(arr[1], &element);
        printf("Pop  Element %3d From Stack\n", element.info);
    }
    return (EXIT_SUCCESS);
}

/*
#include <stdio.h>
#include <string.h>

int main () {
   FILE *fp;
   char c[] = "this is tutorialspoint";
   char buffer[100];

   /* Open file for both reading and writing */
//   fp = fopen("file.txt", "w+");

   /* Write data to the file */
  // fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
  // fseek(fp, 0, SEEK_SET);

   /* Read and display data */
 /*  fread(buffer, strlen(c)+1, 1, fp);
   printf("%s\n", buffer);
   fclose(fp);
   
   return(0);
}
*/
