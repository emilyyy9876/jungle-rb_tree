#include "rbtree.h"
#include <stdlib.h>

// 새로 만든 함수들
int rbtree_insert_fixup(rbtree *t, node_t *cur_node);
void node_left_rotate(rbtree *t, node_t *cur_node);
void node_right_rotate(rbtree *t, node_t *cur_node);

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  // TODO: initialize struct if neededa

  // sentinel node 만들기
  node_t *sentinel_node = (node_t *)calloc(1, sizeof(node_t));

  // root를 sentinel node로 설정
  p->nil = sentinel_node;
  p->root = p->nil;

  sentinel_node->color = RBTREE_BLACK;
  // p->nil->key = NULL;
  sentinel_node->parent = NULL;
  sentinel_node->left = NULL;
  sentinel_node->right = NULL;
  return p;
}

void node_left_rotate(rbtree *t, node_t *cur_node)
{
  node_t *new_parent = cur_node->right;
  cur_node->right = new_parent->left;
  if (new_parent->left != t->nil)
  {
    new_parent->left->parent = cur_node;
  }
  new_parent->parent = cur_node->parent;
  if (cur_node->parent == t->nil)
  {
    t->root = new_parent;
  }
  else if (cur_node = cur_node->parent->left)
  {
    cur_node->parent->left = new_parent;
  }
  else
  {
    cur_node->parent->right = new_parent;
  }
}

void node_right_rotate(rbtree *t, node_t *cur_node)
{
  node_t *new_parent = cur_node->left;
  cur_node->left = new_parent->right;
  if (new_parent->right != t->nil)
  {
    new_parent->right->parent = cur_node;
  }
  new_parent->parent = cur_node->parent;
  if (cur_node->parent == t->nil)
  {
    t->root = new_parent;
  }
  else if (cur_node = cur_node->parent->left)
  {
    cur_node->parent->left = new_parent;
  }
  else
  {
    cur_node->parent->right = new_parent;
  }
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}
int rbtree_insert_fixup(rbtree *t, node_t *cur_node)
{
  node_t *grandpa_node = cur_node->parent->parent;
  while (cur_node->parent->color == RBTREE_RED)
  {
    if (cur_node->parent == grandpa_node->left)
    {
      node_t *uncle_node = grandpa_node->right;
      if (uncle_node->color == RBTREE_RED)
      {
        cur_node->parent->color = RBTREE_BLACK;
        uncle_node->color = RBTREE_BLACK;
        grandpa_node = RBTREE_RED;
        cur_node = grandpa_node;
      }
      // cur_node가 부모보드와 꺾인 변에 있을 때:
      else if (cur_node == cur_node->parent->right)
      {
        cur_node = cur_node->parent;
        node_left_rotate(t, cur_node);
      }
      // cur_node가 부모노드와 같은변에 있을 때:
      cur_node->parent->color = RBTREE_BLACK;
      cur_node->parent->parent->color = RBTREE_RED;
      node_right_rotate(t, grandpa_node);
    }
    else
    {
      node_t *uncle_node = grandpa_node->left;
      if (uncle_node->color == RBTREE_RED)
      {
        cur_node->parent->color = RBTREE_BLACK;
        uncle_node->color = RBTREE_BLACK;
        grandpa_node = RBTREE_RED;
        cur_node = grandpa_node;
      }
      else if (cur_node == cur_node->parent->left)
      {
        cur_node = cur_node->parent;
        node_right_rotate(t, cur_node);
      }
      // cur_node가 부모노드와 같은변에 있을 때:
      cur_node->parent->color = RBTREE_BLACK;
      cur_node->parent->parent->color = RBTREE_RED;
      node_left_rotate(t, grandpa_node);
    }
  }
  return 0;
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert

  // 새로운 노드 만들기
  node_t *new_node = (node_t *)calloc(1, sizeof(node_t));
  new_node->key = key;
  new_node->color = RBTREE_RED;

  node_t *parent_node = t->nil;
  node_t *cur_node = t->root;

  while (cur_node != t->nil)
  {
    parent_node = cur_node;
    if (new_node->key < cur_node->key)
    {
      cur_node = cur_node->left;
    }
    else
    {
      cur_node = cur_node->right;
    }
  }
  new_node->parent = parent_node;

  if (parent_node == t->nil)
  {
    t->root = new_node;
  }
  else if (new_node->key < parent_node->key)
  {
    parent_node->left = new_node;
  }
  else
  {
    parent_node->right = new_node;
  }
  new_node->left = t->nil;
  new_node->right = t->nil;
  new_node->color = RBTREE_RED;

  rbtree_insert_fixup(t, new_node);
  t->root->color = RBTREE_BLACK;
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find

  return t->root;
}

node_t *rbtree_min(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  return t->root;
}

int rbtree_erase(rbtree *t, node_t *p)
{
  // TODO: implement erase
  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
