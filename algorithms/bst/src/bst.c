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

t_no* find_minimum(t_no* no) {
  if (!no->left)
    return no;

  return find_minimum(no->left);
}

t_no* find_maximum(t_no* no) {
  if (!no->right)
    return no;

  return find_maximum(no->right);
}


// int SEARCH() {}
t_no* minimum(t_tree* tree) {

  if (!tree->root)
    return NULL;

  return find_minimum(tree->root);
}

t_no* maximum(t_tree* tree) {
  if (!tree->root)
    return NULL;

  return find_maximum(tree->root);
}

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
// void buildCompleteBSTFromArray(){}
// void buildCompleteBSTFromAnotherMessyBST(){}

t_no* search_r(t_no* no, int v) {
  if (!no)
    return NULL;

  if ( no->value == v )
    return no;

  return v > no->value ? search_r(no->right, v) : search_r(no->left, v);
}

t_no* search_itarative(t_no* no, int v) {

  while (no && no->value != v) {
    no = v > no->value ? no->right : no->left;
  }

  return no;
}

t_no* search(t_tree* tree, int v) {
  if (!tree->root)
    return NULL;

  return search_r(tree->root, v);
}

void find_and_search_r(t_tree* tree, int v) {
  t_no *lol = search(tree, v);

  printf("[R] Looking for: %d\n", v);

  if (lol)
    printf("%d\n", lol->value);
  else
    printf("NULL\n");
}

void find_and_search_iterative(t_tree* tree, int v) {
  t_no *lol = search_itarative(tree->root, v);

  printf("[I] Looking for: %d\n", v);

  if (lol)
    printf("%d\n", lol->value);
  else
    printf("NULL\n");
}

int main(int argc, char const *argv[]) {
  t_tree *tree = initialize_tree();

  insert_iterative(tree, alloc_new_node(10));
  insert_iterative(tree, alloc_new_node(2));
  insert_iterative(tree, alloc_new_node(23));
  insert_iterative(tree, alloc_new_node(5));
  insert_iterative(tree, alloc_new_node(9));
  insert_iterative(tree, alloc_new_node(100));

  traverse(tree->root);

  find_and_search_r(tree, 1);
  find_and_search_r(tree, 10);
  find_and_search_r(tree, 23);
  find_and_search_r(tree, 2);
  find_and_search_r(tree, 9);
  find_and_search_r(tree, 99);

  find_and_search_iterative(tree, 1);
  find_and_search_iterative(tree, 10);
  find_and_search_iterative(tree, 23);
  find_and_search_iterative(tree, 2);
  find_and_search_iterative(tree, 9);
  find_and_search_iterative(tree, 99);

  t_no *min = NULL, *max = NULL;
  min = minimum(tree);
  max = maximum(tree);

  printf("Min: %d\n", min->value);
  printf("Max: %d\n", max->value);

  return 0;
}
