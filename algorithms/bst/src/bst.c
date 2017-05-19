#include <stdlib.h>
#include <stdio.h>

#define LOG(f_, ...) printf((f_), __VA_ARGS__)

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

  if (no->parent)
    printf("P [%d] ", no->parent->value );

  if (!no->left && !no->right)
    printf(", leaf, ");

  printf(" value: %d\n", no->value );

  traverse(no->right);
}

void traverse_order(t_no *no) {
  if (!no)
    return;

  if (no->parent)
    printf("P [%d]", no->parent->value );

  printf("Root value: %d\n", no->value );

  traverse(no->left);
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


t_no* successor(t_no *x) {
  t_no *y;

  if (x->right)
    return find_minimum(x->right);

  y = x->parent;
  // go up and find the first left branch
  while(y && x == y->right) {
    x = y;
    y = y->parent;
  }

  return y;
}

t_no* predecessor(t_no *x) {
  t_no *y;

  if (x->left)
    return find_maximum(x->left);

  y = x->parent;
  // go up and find the first right branch
  while(y && x == y->left) {
    x = y;
    y = y->parent;
  }

  return y;
}

void remove_link(t_no *parent, t_no *child) {
  if (child == parent->left)
    parent->left = NULL;
  else
    parent->right = NULL;

  free(child);
}

void transplant(t_tree *tree, t_no *u, t_no *v) {

  if (!u->parent)
    tree->root = v;
  else if (u == u->parent->left)
    u->parent->left = v;
  else
    u->parent->right = v;

  if (v)
    v->parent = u->parent;
}

void delete(t_tree *T, t_no *z) {
  t_no *y = NULL;

  if (!z->left)
    transplant(T, z, z->right);
  else if (!z->right)
    transplant(T, z, z->left);
  else {
    y = find_minimum(z->right);

    LOG("sucessor is %d\n", y->value);

    if (y->parent != z) {
      transplant(T, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    transplant(T, z, y);
    y->left = z->left;
    y->left->parent = y;
  }

}

void delete_bugado(t_no* x) {
  t_no *tricky = NULL;
  int tmp;

  // I - no child: just remove
  if (!x->right && !x->left) {
    remove_link(x->parent, x);
    return;
  }

  // II - one child: replace with child
  // left
  if (!x->right && x->left) {
    x->value = x->left->value;
    x->left = NULL;
    return;
  }
  // right
  if (x->right && !x->left) {
    x->value = x->right->value;
    x->right = NULL;
    return;
  }

  // III - two children
  if (x->right && x->left) {
    LOG("\n\ntwo childs for %d, left %d and right %d!\n", x->value, x->left->value, x->right->value);

    tricky = successor(x);
    LOG("sucessor is %d\n", tricky->value);
    x->value = tricky->value;

    delete_bugado(tricky);
  }
}

t_no* insert_recursive(t_no* vader, t_no* node, t_no* x) {
  if (!node){
    LOG("leaf\n", NULL);
    x->parent = vader;
    return x;
  }

  if (x->value < node->value){
    LOG("left of %d\n", node->value);
    node->left = insert_recursive(node, node->left, x);
  }
  else{
    LOG("right of %d\n", node->value);
    node->right = insert_recursive(node, node->right, x);
  }

  return node;
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

  no->parent = parent;

  if (no->value < parent->value)
    parent->left = no;
  else
    parent->right = no;
}


void insert(t_tree *tree, t_no *no) {
  LOG("adding %d\n", no->value);
  tree->root = insert_recursive(tree->root, tree->root, no);
}


// int shallow() {}
// int maxPathHeight(){}
// int minPathHeight(){}
// void inorderTreeWalk(){}
// void preorderTreeWalk(){}
// void postorderTreeWalk(){}
// void buildCompleteBSTFromArray(){}
// void buildCompleteBSTFromAnotherMessyBST(){}

int height(t_no *x) {
  int d, e;

  if (!x)
    return -1;

  e = height(x->left);
  d = height(x->right);

  return d > e ? d + 1 : e + 1;
}

int size(t_no *x) {
  int d, e;

  if (!x)
    return 0;

  e = size(x->left);
  d = size(x->right);

  return d + e + 1;
}

int leaf_number(t_no *x) {

  if (!x)
    return 0;

  if (!x->left && !x->right)
    return 1;

  return leaf_number(x->left) + leaf_number(x->right);
}

int min(int x, int y) {
  return x >= y ? x : y;
}

int minimum_path_size(t_no *x) {
  int d, e;

  if (!x)
    return 0;

  e = minimum_path_size(x->left);
  d = minimum_path_size(x->right);

  if (e && d)
    return min(e, d) + 1;

  return d + e + 1;
}

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

  // insert_iterative(tree, alloc_new_node(10));
  // insert_iterative(tree, alloc_new_node(2));
  // insert_iterative(tree, alloc_new_node(23));
  // insert_iterative(tree, alloc_new_node(5));
  // insert_iterative(tree, alloc_new_node(9));
  // insert_iterative(tree, alloc_new_node(100));

  insert(tree, alloc_new_node(10));
  // insert(tree, alloc_new_node(12));
  insert(tree, alloc_new_node(11));
  insert(tree, alloc_new_node(4));
  insert(tree, alloc_new_node(2));
  insert(tree, alloc_new_node(25));
  insert(tree, alloc_new_node(23));
  insert(tree, alloc_new_node(5));
  insert(tree, alloc_new_node(6));
  insert(tree, alloc_new_node(90));
  insert(tree, alloc_new_node(9));
  insert(tree, alloc_new_node(1));
  insert(tree, alloc_new_node(100));

  LOG("root is %d\n", tree->root->value );
  traverse_order(tree->root);

  LOG("\nTree initialized! size is %d\n", size(tree->root));
  LOG("Min path is %d\n", minimum_path_size(tree->root));
  LOG("leaf count is %d\n\n------", leaf_number(tree->root));


  LOG("-> delete 90\n", NULL );
  delete(tree, search(tree, 90));
  traverse_order(tree->root);
  LOG("size is %d\n", size(tree->root));
  LOG("leaf count is %d\n", leaf_number(tree->root));


  LOG("-> delete the root 10\n", NULL );
  delete(tree, search(tree, 10));
  LOG("new root is %d\n", tree->root->value );
  traverse_order(tree->root);
  LOG("size is %d\n", size(tree->root));
  LOG("leaf count is %d\n", leaf_number(tree->root));


  LOG("-> delete 4\n", NULL );
  delete(tree, search(tree, 4));
  traverse_order(tree->root);
  LOG("size is %d\n", size(tree->root));
  LOG("leaf count is %d\n", leaf_number(tree->root));



  // find_and_search_r(tree, 1);
  // find_and_search_r(tree, 10);
  // find_and_search_r(tree, 23);
  // find_and_search_r(tree, 2);
  // find_and_search_r(tree, 9);
  // find_and_search_r(tree, 99);

  // find_and_search_iterative(tree, 1);
  // find_and_search_iterative(tree, 10);
  // find_and_search_iterative(tree, 23);
  // find_and_search_iterative(tree, 2);
  // find_and_search_iterative(tree, 9);
  // find_and_search_iterative(tree, 99);

  // t_no *min = NULL, *max = NULL;
  // min = minimum(tree);
  // max = maximum(tree);

  // printf("Min: %d\n", min->value);
  // printf("Max: %d\n", max->value);

  return 0;
}
