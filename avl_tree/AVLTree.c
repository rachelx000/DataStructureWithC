#include <stdlib.h>
#include <stdio.h>
#include "AVLTree.h"

/*
 * This structure represents a single node in AVL tree.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`) and two fields
 * representing the data stored at this node, it contain the `height` field
 * that is used to track the height of the subtree rooted at each node, and
 * the `parents` field stores the pointer to the parent node of each node
 *
 * You should not modify this structure.
 */
struct avl_node
{
    int key;
    void* value;
    int height;
    struct avl_node* left;
    struct avl_node* right;
    struct avl_node* parent;
};

/*
 * This structure represents an entire AVL.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct avl
{
    struct avl_node* root;
};

/*
* This function should allocate and initialize a new, empty, AVL and return
* a pointer to it.
*/
struct avl* avl_create(){
    struct avl* new_avl = malloc(sizeof(struct avl));
    if (!new_avl) {
        printf("Error: Memory allocation to new binary search tree failed!\n");
        exit(1);
    }
    return new_avl;
}

/*
 * Helper function for avl_free that uses post-order traversal to free the memory
 * allocated for each node
 * */
void __free_node(struct avl_node* node) {
    if (node) {
        __free_node(node->left);
        __free_node(node->right);
        free(node);
    }
}

/*
 * This function should free the memory associated with a AVL tree.  While this
 * function should up all memory used in the AVL itself, it should not free
 * any memory allocated to the pointer values stored in the AVL.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   avl - the AVL tree to be destroyed.  May not be NULL.
 */
void avl_free(struct avl* avl) {
    if (avl) {
        __free_node(avl->root);
        free(avl);
    }
    else {
        printf("Error: Invalid AVL to be removed!\n");
        exit(1);
    }
}

/*
 * Helper function for avl_size that uses post-order traversal to count all
 * node of a AVL tree from the root
 * */
int __count_node(struct avl_node* node) {
    if (!node) { return 0; }
    else { return 1+__count_node(node->left)+__count_node(node->right); }
}

/*
 * This function should return the total number of elements stored in a given
 * AVL tree.
 *
 * Params:
 *   avl - the AVL tree whose elements are to be counted.  May not be NULL.
 */
int avl_size(struct avl* avl) {
    return __count_node(avl->root);
}

/*
 * Helper function to return the height of a given node in the AVL tree. Return
 * -1 if the node is NULL
 */
int __height(struct avl_node* node) {
    if (node) { return node->height; }
    else { return -1; }
}

/*
 * Helper function to calculate the balance factor of the subtree rooted at the given
 * node in the AVL tree. Return a integer >0 if the subtree is left-heavy, 0 if the
 * subtree is balanced, <0 if the subtree is right-heavy
 */
int __balance_factor(struct avl_node* node) {
    if (node) {
        return __height(node->right)-__height(node->left);
    } else {
        printf("Error: Attempt to calculate the balance factor of an non-existed node\n");
        exit(1);
    }
}

/*
 * Helper function to update the height of a node
 */
void __update_height(struct avl_node* node) {
    if (node) {
        node->height = __height(node->left) < __height(node->right) ?
                       __height(node->right)+1 : __height(node->left)+1;
    } else {
        printf("Error: Attempt to update the height of an non-existed node\n");
        exit(1);
    }
}

/*
 * Helper function to perform a left rotation on the subtree of the AVL centered
 * around the given node
 */
struct avl_node* __rotate_left(struct avl_node* node) {
    if (node) {
        struct avl_node* center = node->right;
        node->right = center->left;
        if (node->right) { node->right->parent = node; }
        center->left = node;
        node->parent = center;
        __update_height(node);
        __update_height(center);
        return center;
    } else {
        printf("Error: Attempt to perform left-rotation on an non-existed node\n");
        exit(1);
    }
}

/*
 * Helper function to perform a right rotation on the subtree of the AVL centered
 * around the given node
 */
struct avl_node* __rotate_right(struct avl_node* node) {
    if (node) {
        struct avl_node* center = node->left;
        node->left = center->right;
        if (node->left) { node->left->parent = node; }
        center->right = node;
        node->parent = center;
        __update_height(node);
        __update_height(center);
        return center;
    } else {
        printf("Error: Attempt to perform right-rotation on an non-existed node\n");
        exit(1);
    }
}

/*
 * Helper function to perform a rebalancing on the subtree of the AVL centered
 * around the given node
 *
 * Coding Tip: Remember original parent of the node!!!!!!!!!!
 *
 */
void __rebalance(struct avl* avl, struct avl_node* node) {
    if (node) {
        if (__balance_factor(node) < -1) {            // if subtree is left heavy
            if (__balance_factor(node->left) > 0) {
                // if subtree is left-right heavy
                node->left = __rotate_left(node->left);
                node->left->parent = node;
            }
            struct avl_node* original_parent = node->parent;
            struct avl_node* new_node = __rotate_right(node);
            new_node->parent = original_parent;
            if (original_parent) {
                int LR = original_parent->left == node ? 1 : 0;    // 1 -> left child, 0 -> right child
                if (LR) { original_parent->left = new_node; }
                else { original_parent->right = new_node; }
            } else {
                avl->root=new_node;
            }
        }
        else if (__balance_factor(node) > 1) {        // if subtree is right heavy
            if (__balance_factor(node->right) < 0) {
                // if subtree is right-left heavy
                node->right = __rotate_right(node->right);
                node->right->parent = node;
            }
            struct avl_node* original_parent = node->parent;
            struct avl_node* new_node = __rotate_left(node);
            new_node->parent = original_parent;
            if (original_parent) {
                int LR = original_parent->left == node ? 1 : 0;    // 1 -> left child, 0 -> right child
                if (LR) { original_parent->left = new_node; }
                else { original_parent->right = new_node; }
            } else {
                avl->root=new_node;
            }
        }
        else {
            __update_height(node);
        }
    } else {
        printf("Error: Attempt to rebalance an non-existed node\n");
        exit(1);
    }
}

/*
 * This function should insert a new key/value pair into the AVL tree. The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the AVL.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   avl - the AVL tree into which a new key/value pair is to be inserted. May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the AVL.
 *   value - the value being inserted into the AVL.  This should be stored in
 *     the AVL alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void avl_insert(struct avl* avl, int key, void* value) {
    if ( avl ) {
        // Step 1: Insert the new node at the next opening spot in the tree as normal
        struct avl_node* parent_node = NULL;
        struct avl_node* curr_node = avl->root;
        int LR;    // LR = 0 for left child; = 1 for right child;

        // find the parent of the correct empty space for the node in the avl tree
        while (curr_node) {
            parent_node = curr_node;
            if (key < curr_node->key) { LR = 0; curr_node = curr_node->left; }
            else { LR = 1; curr_node = curr_node->right; }
        }
        // create the node and insert it as root if the avl tree is empty, or insert
        // as a child of the searched parent node
        curr_node = malloc(sizeof(struct avl_node));
        *curr_node = (struct avl_node){.key = key, .value=value, .height = 0, .left=NULL, .right=NULL, .parent=parent_node};
        if (!parent_node) {
            avl->root = curr_node;
        } else {
            if ( LR == 0 ) { parent_node->left = curr_node; }
            else { parent_node->right = curr_node; }
            // avl_DFS(avl);
            // Step 2: Trace backward to perform rebalancing at each node until reaching the root
            while (parent_node) {
                __rebalance(avl, parent_node);
                parent_node = parent_node->parent;
            }
        }
    } else {
        printf("Error: Invalid AST tree for inserting the element!\n");
        exit(1);
    }
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given AVL tree. If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   avl - the AVL tree from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the AVL tree.
 */
void avl_remove(struct avl* avl, int key) {
    if ( avl ) {
        // Step 1: Remove the target node from the tree as normal
        struct avl_node* parent_node = NULL;
        struct avl_node* curr_node = avl->root;
        int LR;    // LR = 0 for left child; = 1 for right child;
        // find the node to be removed and its parent based on key
        while (curr_node) {
            if ( key == curr_node->key ) { break; }
            else {
                parent_node = curr_node;
                if ( key < curr_node->key ) { LR = 0; curr_node = curr_node->left; }
                else { LR = 1; curr_node = curr_node->right; }
            }
        }
        if (!curr_node) {
            printf("Warning: Attempt to remove non-existed node from the AVL tree\n");
        }
        else {
            struct avl_node* last_modified_node = parent_node;
            struct avl_node* replaced_node;
            if ( !curr_node->left && !curr_node->right ) {
                // if the target node has no children, just update the parent node to
                // point to NULL instead of target node
                replaced_node = NULL;
            } else if ( !curr_node->left || !curr_node->right ) {
                // if the target node has only one child, update the parent node to point
                // to the child instead of target node
                replaced_node = curr_node->left ? curr_node->left : curr_node->right;
            } else {
                // if the target node has two children, find its in-order successor with the sucessor's parent
                struct avl_node* s_parent = curr_node;
                struct avl_node* s = curr_node->right;
                // branch right in the tree from N, and continue to branch left until reaching a node with no
                // left child
                while ( s->left ) {
                    s_parent = s;
                    s = s->left;
                }
                // update the successor and its parent nodes
                s->left = curr_node->left;
                if (s->left) {s->left->parent = s;}
                s->parent = parent_node;
                if (s_parent != curr_node) {
                    s_parent->left = s->right;
                    if (s_parent->left) { s_parent->left->parent = s_parent; }
                    s->right = curr_node->right;
                    if (s->right) { s->right->parent = s; }
                    last_modified_node = s_parent;
                } else {
                  	last_modified_node = s;
                }
                replaced_node = s;
            }
            // update the parent node to point to the replaced node or NULL
            if ( !parent_node ) {
              	// printf("Remove at root\n");
                avl->root = replaced_node;
                if (replaced_node) { replaced_node->parent = NULL; };
            } else {
              	// printf("Remove at parent node: %d\n", parent_node->key);
                if ( LR == 0 ) {
                  parent_node->left = replaced_node;
                  if (replaced_node) { replaced_node->parent = parent_node; }
                } else {
                  parent_node->right = replaced_node;
                  if (replaced_node) { replaced_node->parent = parent_node; }
                }
            }
            // free the memory allocated for the removed node
            free(curr_node);
            // if (last_modified_node) { printf("last_modified_node: %d\n", last_modified_node->key); }
            // Step 2: Trace backward from the last modified node to perform rebalancing at each node until reaching the root
        	while (last_modified_node) {
            	__rebalance(avl, last_modified_node);
            	last_modified_node = last_modified_node->parent;
        	}
        }
    }
    else {
        printf("Error: Invalid AST tree for removing the element!\n");
        exit(1);
    }
}

/*
 * This function should return the value associated with a specified key in a
 * given AVL tree. If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the AVL does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   avl - the AVL tree from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `avl` or NULL,
 *   if the key `key` was not found in `avl`.
 */
void* avl_get(struct avl* avl, int key) {
    struct avl_node* curr_node = avl->root;
    while (curr_node) {
        if ( key == curr_node->key ) { return curr_node->value; }
        else if ( key < curr_node->key ){ curr_node = curr_node->left; }
        else { curr_node = curr_node->right; }
    }
    return NULL;
}

/*
 * Helper function for avl_DFS to process every node of a AVL tree from the root
 * */
void __pre_traversal(struct avl_node* node) {
    if (node) {
       	printf("%d ", node->key);
        __pre_traversal(node->left);
        __pre_traversal(node->right);
    }
}

/*
 * This function should perform pre-order DFS traversal on the given AVL tree.
 *
 * Params:
 *   avl - the AVL tree whose elements are to be traversed. May not be NULL.
 */
void avl_DFS(struct avl* avl) {
    if ( avl ) {
        printf("Pre-order DFS Traversal:\t");
        __pre_traversal(avl->root);
        printf("\n");
    } else {
        printf("Error: Invalid AVL tree for in-order DFS traversal!\n");
        exit(1);
    }
}

/*
 * Helper function for avl_DFS_detailed to process every node of a AVL tree from the root
 * */
void __pre_traversal_detailed(struct avl_node* node) {
    if (node) {
      	if (node->parent) {
        	printf("%d (with parent %d and height %d) | ", node->key, node->parent->key, node->height);
        } else {
          	if (node->left && node->right)
          		printf("%d (with height %d and left %d and right %d) | ", node->key, node->height, node->left->key, node->right->key);
            else if (node->left)
              	printf("%d (with height %d and left %d) | ", node->key, node->height, node->left->key);
            else if (node->right)
              	printf("%d (with height %d and left %d) | ", node->key, node->height, node->right->key);
            else
              	printf("%d (with height %d) | ", node->key, node->height);
        }
        __pre_traversal_detailed(node->left);
        __pre_traversal_detailed(node->right);
    }
}

/*
 * This function should perform pre-order DFS traversal with details on the given AVL tree.
 * (For Debugging and Testing Only)
 * Params:
 *   avl - the AVL tree whose elements are to be traversed. May not be NULL.
 */
void avl_DFS_detailed(struct avl* avl) {
    if ( avl ) {
        printf("Pre-order DFS Traversal with Details: ");
        __pre_traversal_detailed(avl->root);
        printf("\n");
    } else {
        printf("Error: Invalid AVL tree for in-order DFS traversal!\n");
        exit(1);
    }
}




