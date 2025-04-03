#ifndef __AVL_H
#define __AVL_H

struct avl;

struct avl* avl_create();
void avl_free(struct avl* avl);
int avl_size(struct avl* avl);
void avl_insert(struct avl* avl, int key, void* value);
void avl_remove(struct avl* avl, int key);
void* avl_get(struct avl* avl, int key);
void avl_DFS(struct avl* avl);
void avl_DFS_detailed(struct avl* avl);

#endif