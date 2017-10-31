#include<stdlib.h>
#include<stdio.h>

struct bin_tree
{
char data;
int label;
struct bin_tree *right, *left;

};
typedef struct bin_tree node;

int R[]={1,0};
int top=1;
char *op;


void insertnode(node **tree,char val)
{
node *temp = NULL;

if(!(*tree))
    {
        temp = (node *)malloc(sizeof(node));
        temp->left = temp->right = NULL;
        temp->data = val;
        temp->label=-1;
        *tree = temp;
    }
}

void insert(node **tree,char val)
{
   
    char l,r;
    int numofchildren;

    insertnode(tree, val);

   // printf("\nEnter character to be entered:");
   // scanf("%c",&val);

   

    printf("\nEnter number of children of %c:",val);
    scanf("%d",&numofchildren);

  if(numofchildren==2)
   {
    printf("\nEnter Left Child of %c:",val);
    scanf("%s",&l);
    insertnode(&(*tree)->left,l);

    printf("\nEnter Right Child of %c:",val);
    scanf("%s",&r);
    insertnode(&(*tree)->right,r);
  

    //if(&(*tree)->left != NULL)
    insert(&(*tree)->left,l);
    insert(&(*tree)->right,r);
   }
   

}


void findleafnodelabel(node *tree,int val)
{

if(tree->left != NULL && tree->right !=NULL)
{
findleafnodelabel(tree->left,1);
findleafnodelabel(tree->right,0);
}

else
{
tree->label=val;
}

}

void findinteriornodelabel(node *tree)
{
if(tree->left->label==-1)
{
findinteriornodelabel(tree->left);
}

else if(tree->right->label==-1)
{
findinteriornodelabel(tree->right);
}

else
{

if(tree->left != NULL && tree->right !=NULL)
{

if(tree->left->label == tree->right->label)
{

tree->label=(tree->left->label)+1;
}

else
{

if(tree->left->label > tree->right->label)
{
tree->label=tree->left->label;
}
else
{
tree->label=tree->right->label;
}

}


}
}

}



void print_inorder(node * tree)
{
    if (tree)
    {
        print_inorder(tree->left);
        printf("%c with Label %d\n",tree->data,tree->label);
        print_inorder(tree->right);
    }
}

void swap()
{
int temp;
temp=R[0];
R[0]=R[1];
R[1]=temp;
}

int pop()
{
int temp=R[top];
top--;
return temp;
}

void push(int temp)
{
top++;
R[top]=temp;
}

char* nameofoperation(char temp)
{
switch(temp)
{
case '+': return "ADD"; break;
case '-': return "SUB"; break;
case '*': return "MUL"; break;
case '/': return "DIV"; break;
}
}

void gencode(node * tree)
{

if(tree->left != NULL && tree->right != NULL)
{
if(tree->left->label== 1 && tree->right->label ==0)
{
printf("MOV %c,R[%d]\n",tree->left->data,R[top]);
op=nameofoperation(tree->data);
printf("%s %c,R[%d]\n",op,tree->right->data,R[top]);
}


else if(tree->left->label < tree->right->label)
{
int temp;
swap();
gencode(tree->right);
temp=pop();
gencode(tree->left);
push(temp);
swap();
op=nameofoperation(tree->data);
printf("%s R[%d],R[%d]\n",op,R[top-1],R[top]);
}

else if(tree->left->label >= tree->right->label)
{
int temp;
gencode(tree->left);
temp=pop();
gencode(tree->right);
push(temp);
op=nameofoperation(tree->data);
printf("%s R[%d],R[%d]\n",op,R[top-1],R[top]);
}

}

else if(tree->left == NULL && tree->right == NULL && tree->label == 1)
{
printf("MOV %c,R[%d]\n",tree->data,R[top]);
}

}






void deltree(node * tree)
{
    if (tree)
    {
        deltree(tree->left);
        deltree(tree->right);
        free(tree);
    }
}


void main()
{
    node *root;
    node *tmp;
    char val;
  

    root = NULL;
    /* Inserting nodes into tree */

    printf("\nEnter root of tree:");
    scanf("%c",&val);

    insert(&root,val);

    /* Finding Labels of Leaf nodes */
    findleafnodelabel(root,1);

    /* Finding Labels of Interior nodes */
    while(root->label== -1)
       findinteriornodelabel(root);

    /* Printing nodes of tree */

    printf("In Order Display\n");
    print_inorder(root);
   
    /* Printing nodes of tree */
    printf("Assembly Code:\n");
    gencode(root);

      
    /* Deleting all nodes of tree */
    deltree(root);
}
