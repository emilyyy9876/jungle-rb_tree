#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

// 새로 만든 함수들---전방선언
void rbtree_insert_fixup(rbtree *t, node_t *cur_node);
void node_left_rotate(rbtree *t, node_t *cur_node);
void node_right_rotate(rbtree *t, node_t *cur_node);
void rbtree_transplant(rbtree *t, node_t *killed, node_t *refill);

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
  if (cur_node == NULL || cur_node->right == NULL)
  {
    printf("잡았다 node_left_rotate 요놈!!!\n");
    return;
  }

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
  else if (cur_node == cur_node->parent->left)
  {
    cur_node->parent->left = new_parent;
  }
  else
  {
    cur_node->parent->right = new_parent;
  }
  new_parent->left = cur_node;
  cur_node->parent = new_parent;
}

void node_right_rotate(rbtree *t, node_t *cur_node)
{
  if (cur_node == NULL || cur_node->left == NULL)
  {
    printf("잡았다 node_right_rotate 요놈!!!");
    return;
  }

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
  else if (cur_node == cur_node->parent->right)
  {
    cur_node->parent->right = new_parent;
  }
  else
  {
    cur_node->parent->left = new_parent;
  }
  new_parent->right = cur_node;
  cur_node->parent = new_parent;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  t->root = NULL;
  t->nil = NULL;
  free(t);
}
void rbtree_insert_fixup(rbtree *t, node_t *new_node)
{
  // cur_node: 회전할 node
  // node_t *cur_node = (node_t *)calloc(1, sizeof(node_t));
  while (new_node->parent->color == RBTREE_RED)
  {
    // 부모가 할아버지의 왼쪽에 있을 때
    if (new_node->parent == new_node->parent->parent->left)
    {
      node_t *uncle_node = new_node->parent->parent->right; // 1. 삼촌색이 빨간색일때
      if (uncle_node->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        uncle_node->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        new_node = new_node->parent->parent;
      }
      // 2. 삼촌색이 검은색일때
      else
      {
        if (new_node == new_node->parent->right)
        {
          new_node = new_node->parent;
          node_left_rotate(t, new_node);
        }

        // 3. 삼촌색이 검은색이고, 삽입된 노드가 부모의 왼쪽일때
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        node_right_rotate(t, new_node->parent->parent);
      }
    }
    // 부모가 할아버지의 오른쪽에 있을 때
    else
    {
      node_t *uncle_node = new_node->parent->parent->left;
      // 1. 삼촌이 빨간색일 때
      if (uncle_node->color == RBTREE_RED)
      {
        new_node->parent->color = RBTREE_BLACK;
        uncle_node->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        // new_node = new_node->parent->parent;
      }
      // 2. 삼촌이 검은색이고, 삽입된 노드가 부모의 왼쪽일 때
      else
      {
        if (new_node == new_node->parent->left)
        {
          new_node = new_node->parent;
          node_right_rotate(t, new_node);
        }
        new_node->parent->color = RBTREE_BLACK;
        new_node->parent->parent->color = RBTREE_RED;
        node_left_rotate(t, new_node->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
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
  // free(cur_node); -------------double free detected 에러..현재 cur은 로컬변수이므로 해제 필요없음
  return t->root;
}

node_t *rbtree_find(const rbtree *t, const key_t key)
{
  // TODO: implement find
  // 노드 current 초기화
  node_t *cur_node = t->root;
  // 노드 current가 null이 아닌동안
  while (cur_node != t->nil)
  {
    // 만약 key값이 current보다 크면
    if (key > cur_node->key)
    {
      cur_node = cur_node->right;
    }
    // 만약 key값이 current보다 작으면
    else if (key < cur_node->key)
    {
      cur_node = cur_node->left;
    }
    else
    {
      return (cur_node);
    }
  }
  // 이 후에도 못 찾으면
  return NULL;
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
  node_t *killed = p;
  color_t killed_oigin_color = killed->color;
  if (p->left == t->nil)
  {
  }
  else if (p->right == t->nil)
  {
  }
  else
  {
  }

  return 0;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
