#include "rbtree.h"

#include <stdlib.h>

rbtree *new_rbtree(void)
{
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));

  // TODO: initialize struct if needed
  // p를 초기화 안해도 됨??--calloc이니까?

  if (p->root != NULL || p->nil != NULL)
  {
    p->root = NULL;
    p->nil = NULL;
  }

  // sentinel node 만들기
  p->nil = (node_t *)calloc(1, sizeof(node_t));
  // root를 sentinel node로 설정
  p->root = p->nil;
  // p->nill을 정의하기--sentinel node의 p,left, right,key등은 수행과정에서 값이 채워질 수 있으나 의미를 갖지 않음
  p->nil->color = RBTREE_BLACK;
  p->nil->key = NULL;
  p->nil->parent = NULL;
  p->nil->left = NULL;

  return p;
}

void delete_rbtree(rbtree *t)
{
  // TODO: reclaim the tree nodes's memory
  free(t);
}

node_t *rbtree_insert(rbtree *t, const key_t key)
{
  // TODO: implement insert

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

// 테스트를 위한 main 함수
int main(void)
{
  rbtree *tree = new_rbtree();

  // 트리 삭제 (메모리 해제)
  delete_rbtree(tree);
  return 0;
}