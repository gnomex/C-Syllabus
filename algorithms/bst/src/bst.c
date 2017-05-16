#include <stdlib.h>
#include <stdio.h>

typedef struct _no t_no;

struct _no {
  t_no *parent;
  t_no *left;
  t_no *right;
  int value;
};

typedef struct _tree {
  t_no *root;
  t_no *min;
  t_no *max;
  int length;
} t_tree;

t_tree* initialize_tree() {
  t_tree *self = NULL;

  if (!(self = (t_tree*) malloc( sizeof(t_tree) )))
    return NULL;

  self->root = NULL;
  self->min = NULL;
  self->max = NULL;
  self->length = 0;

  return self;
}

t_no* alloc_new_node(int value) {
  t_no *self = NULL;

  if (!(self = (t_no*) malloc( sizeof(t_no) )))
    return NULL;

  self->value = value;
  self->parent = NULL;
  self->left  = NULL;
  self->right = NULL;

  return self;
}

void traverse(t_no *no) {
  if (!no)
    return;

  traverse(no->left);
  printf("%d\n", no->value );
  traverse(no->right);
}

// int SEARCH() {}
// int MINIMUM() {}
// int MAXIMUM() {}
// int PREDECESSOR() {}
// int SUCCESSOR() {}
// int DELETE() {}

t_no* insert_recursive(t_no* node, t_no* x) {
  if (!node)
    return x;

  if (x->value < node->value)
    node->left = insert_recursive(node->left, x);
  else
    node->right = insert_recursive(node->right, x);

  return node;
}

void insert(t_tree *tree, t_no *no) {
  // if (!tree->root) {
  //   tree->root = no;
  //   return;
  // }

  tree->root = insert_recursive(tree->root, no);
}

void insert_iterative(t_tree *tree, t_no *no) {
  t_no *parent, *tmp;

  if (!tree->root) {
    tree->root = no;
    return;
  }

  parent = NULL;
  tmp = tree->root;

  while (tmp) {
    parent = tmp;

    if (no->value < tmp->value)
      tmp = tmp->left;
    else
      tmp = tmp->right;
  }

  if (no->value < parent->value)
    parent->left = no;
  else
    parent->right = no;
}


// int shallow() {}
// int maxPathHeight(){}
// int minPathHeight(){}

// void print(){}

// void inorderTreeWalk(){}
// void preorderTreeWalk(){}
// void postorderTreeWalk(){}

// void* find(BNode* x, int k) {
//   if (x || x.key == k ) return x;

//   return k < x.key ? find(x->left, k) : find(x->right, k);
// }

// void buildCompleteBSTFromArray(){}
// void buildCompleteBSTFromAnotherMessyBST(){}


int main(int argc, char const *argv[]) {
  t_tree *tree = initialize_tree();

  insert_iterative(tree, alloc_new_node(10));
  insert_iterative(tree, alloc_new_node(2));
  insert_iterative(tree, alloc_new_node(23));
  insert_iterative(tree, alloc_new_node(5));
  insert_iterative(tree, alloc_new_node(9));
  insert_iterative(tree, alloc_new_node(100));

  traverse(tree->root);

  return 0;
}
