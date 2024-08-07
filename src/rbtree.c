#include "rbtree.h"
#include <stdlib.h>
#include <stdio.h>

// 새로 만든 함수들---전방선언
void rbtree_insert_fixup(rbtree *t, node_t *cur_node);
void node_left_rotate(rbtree *t, node_t *cur_node);
void node_right_rotate(rbtree *t, node_t *cur_node);
void rbtree_transplant(rbtree *t, node_t *killed, node_t *refill);
void rbtree_delete_fixup(rbtree *t, node_t *cur_node);
node_t *successor_finder(node_t *, rbtree *t);
void delete_node(rbtree *t, node_t *node);

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
void delete_node(rbtree *t, node_t *node)
{
  if (node == t->nil)
    return;
  delete_node(node->right);
  delete_node(node->left);
  node = NULL;
  free(node);
}
void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory

  free(t);
}
void rbtree_insert_fixup(rbtree *t, node_t *new_node)
{
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
  node_t *cur = t->root;
  while (cur->left != t->nil)
  {
    cur = cur->left;
  }
  return cur;
}

node_t *rbtree_max(const rbtree *t)
{
  // TODO: implement find
  node_t *cur = t->root;
  while (cur->right != t->nil)
  {
    cur = cur->right;
  }
  return cur;
}

void rbtree_transplant(rbtree *t, node_t *killed, node_t *replacing)
{
  // 만약 삭제할 노드가 root노드이면->
  if (killed->parent == t->nil)
  {
    t->root = replacing;
  }
  // 만약 삭제할 노드가 왼쪽자식이면
  else if (killed == killed->parent->left)
  {
    killed->parent->left = replacing;
  }
  // 만약 삭제할 노드가 오른쪽자식이면
  else
  {
    killed->parent->right = replacing;
  }
  replacing->parent = killed->parent;
}
node_t *successor_finder(node_t *successor_seeker, rbtree *t)
{
  node_t *cur = successor_seeker;
  while (cur != t->nil)
  {
    cur = cur->left;
  }
  return cur->parent;
}

int rbtree_erase(rbtree *t, node_t *killed_node)
{
  // focus node---->의 색이 삭제할 색이 됨
  // replaer node--->삭제될 노드 자리를 채울 노드

  node_t *replacer_node;
  node_t *focused_node = killed_node;

  color_t focused_oigin_color = focused_node->color;
  if (killed_node->left == t->nil)
  {
    replacer_node = killed_node->right;
    rbtree_transplant(t, killed_node, killed_node->left);
  }
  else if (killed_node->right == t->nil)
  {
    replacer_node = killed_node->left;
    rbtree_transplant(t, killed_node, killed_node->right);
  }
  else
  {
    focused_node = successor_finder(killed_node->right, t);
    focused_oigin_color = focused_node->color;
    replacer_node = focused_node->right;
    if (focused_node->parent == killed_node)
    {
      replacer_node->parent = focused_node;
    }
    else
    {
      rbtree_transplant(t, focused_node, focused_node->right);
      focused_node->right = killed_node->right;
      focused_node->right->parent = focused_node;
    }
    rbtree_transplant(t, killed_node, focused_node);
    focused_node->left = killed_node->left;
    focused_node->left->parent = focused_node;
    focused_node->color = killed_node->color;
  }
  if (focused_oigin_color == RBTREE_BLACK)
  {
    rbtree_delete_fixup(t, replacer_node);
  }

  return 0;
}

void rbtree_delete_fixup(rbtree *t, node_t *cur_node)
{
  // 회전의 기준점
  node_t *bro_node;
  while (cur_node != t->root && cur_node->color == RBTREE_BLACK)
  {
    // 1. 삭제할 노드가 왼쪽자식일 때
    if (cur_node == cur_node->parent->left)
    {
      bro_node = cur_node->parent->right;
      //.........형제의 색이 빨간색일 때----->case 1
      if (bro_node->color == RBTREE_RED)
      {
        bro_node->color = RBTREE_BLACK;
        cur_node->parent->color = RBTREE_RED;
        node_left_rotate(t, cur_node->parent);
        bro_node = cur_node->parent->right;
      }
      //..........형제가 검은색이고
      //.....형제의 자식들이 검은색일 때------>case 2
      if (bro_node->left->color == RBTREE_BLACK && bro_node->right->color == RBTREE_BLACK)
      {
        bro_node->color = RBTREE_RED;
        cur_node = cur_node->parent;
      }
      else
      {
        // 형제의 일직선 상의 자식이 검은색일 때---> case 4
        if (bro_node->right->color == RBTREE_BLACK)
        {
          bro_node->left->color = RBTREE_BLACK;
          bro_node->color = RBTREE_RED;
          node_right_rotate(t, bro_node);
          // 회전 후 형제 노드 재조정
          bro_node = cur_node->parent->right;
        }
        // 형제의 꺾인 자식이 검은색일 때--->case 3
        bro_node->color = cur_node->parent->color;
        cur_node->parent->color = RBTREE_BLACK;
        bro_node->right->color = RBTREE_BLACK;
        node_left_rotate(t, cur_node->parent);
        cur_node = cur_node->parent;
      }
    }
    // 2. 삭제할 노드가 오른쪽자식일 때
    else
    {
      bro_node = cur_node->parent->left;
      //.........형제의 색이 빨간색일 때----->case 1
      if (bro_node->color == RBTREE_RED)
      {
        bro_node->color = RBTREE_BLACK;
        cur_node->parent->color = RBTREE_RED;
        node_right_rotate(t, cur_node->parent);
        bro_node = cur_node->parent->left;
      }
      //..........형제가 검은색이고
      //.....형제의 자식들이 검은색일 때------>case 2
      if (bro_node->left->color == RBTREE_BLACK && bro_node->right->color == RBTREE_BLACK)
      {
        bro_node->color = RBTREE_RED;
        cur_node = cur_node->parent;
      }
      else
      {
        // 형제의 꺾인 자식이 빨간색일 때---> case 3
        if (bro_node->left->color == RBTREE_BLACK)
        {
          bro_node->right->color = RBTREE_BLACK;
          bro_node->color = RBTREE_RED;
          node_left_rotate(t, bro_node);
          // 회전 후 형제 노드 재조정
          bro_node = cur_node->parent->right;
        }
        // 형제의 일직선 상의 자식이 빨간색일 때---> case 4
        bro_node->color = cur_node->parent->color;
        cur_node->parent->color = RBTREE_BLACK;
        bro_node->left->color = RBTREE_BLACK;
        node_right_rotate(t, cur_node->parent);
        cur_node = t->root;
      }
    }
  }
  cur_node->color = RBTREE_BLACK;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n)
{
  // TODO: implement to_array
  return 0;
}
