#include <stdlib.h>
#include <stdio.h>
#include "BinarySearchTree.h"
#include "../queue/Queue.h"

/*
 * This structure represents a single node in a BST.  In addition to containing
 * pointers to its two child nodes (i.e. `left` and `right`), it contains two
 * fields representing the data stored at this node.  The `key` field is an
 * integer value that should be used as an identifier for the data in this
 * node.  Nodes in the BST should be ordered based on this `key` field.  The
 * `value` field stores data associated with the key.
 *
 * You should not modify this structure.
 */
struct bst_node
{
    int key;
    void* value;
    struct bst_node* left;
    struct bst_node* right;
};

/*
 * This structure represents an entire BST.  It specifically contains a
 * reference to the root node of the tree.
 *
 * You should not modify this structure.
 */
struct bst
{
    struct bst_node* root;
};

/*
* This function should allocate and initialize a new, empty, BST and return
* a pointer to it.
*/
struct bst* bst_create(){
    struct bst* new_bst = malloc(sizeof(struct bst));
    if (!new_bst) {
        printf("Error: Memory allocation to new binary search tree failed!\n");
        exit(1);
    }
    return new_bst;
}

/*
 * Helper function for bst_free that uses post-order traversal to free the memory
 * allocated for each node
 * */
void __free_node(struct bst_node* node) {
    // Use post-order traversal to free the memory allocated for each node
    if (node) {
        __free_node(node->left);
        __free_node(node->right);
        free(node);
    }
}

/*
 * This function should free the memory associated with a BST.  While this
 * function should up all memory used in the BST itself, it should not free
 * any memory allocated to the pointer values stored in the BST.  This is the
 * responsibility of the caller.
 *
 * Params:
 *   bst - the BST to be destroyed.  May not be NULL.
 */
void bst_free(struct bst* bst) {
    if (bst) {
        __free_node(bst->root);
        free(bst);
    }
    else {
        printf("Error: Invalid BST to be removed!\n");
        exit(1);
    }
}

/*
 * Helper function for bst_size that uses post-order traversal to count all
 * node of a BST from the root
 * */
int __count_node(struct bst_node* node) {
    if (!node) { return 0; }
    else { return 1+__count_node(node->left)+__count_node(node->right); }
}

/*
 * This function should return the total number of elements stored in a given
 * BST.
 *
 * Params:
 *   bst - the BST whose elements are to be counted.  May not be NULL.
 */
int bst_size(struct bst* bst) {
    return __count_node(bst->root);
}

/*
 * This function should insert a new key/value pair into the BST.  The key
 * should be used to order the key/value pair with respect to the other data
 * stored in the BST.  The value should be stored along with the key, once the
 * right location in the tree is found.
 *
 * Params:
 *   bst - the BST into which a new key/value pair is to be inserted.  May not
 *     be NULL.
 *   key - an integer value that should be used to order the key/value pair
 *     being inserted with respect to the other data in the BST.
 *   value - the value being inserted into the BST.  This should be stored in
 *     the BST alongside the key.  Note that this parameter has type void*,
 *     which means that a pointer of any type can be passed.
 */
void bst_insert(struct bst* bst, int key, void* value) {
    struct bst_node* parent_node = NULL;
    struct bst_node* curr_node = bst->root;
    int LR;    // LR = 0 for left child; = 1 for right child;

    // find the parent of the correct empty space for the node in the bst tree
    while (curr_node) {
        parent_node = curr_node;
        if (key < curr_node->key) { LR = 0; curr_node = curr_node->left; }
        else { LR = 1; curr_node = curr_node->right; }
    }

    // create the node and insert it as root if the bst is empty, or insert
    // as a child of the searched parent node
    curr_node = malloc(sizeof(struct bst_node));
    *curr_node = (struct bst_node){.key = key, .value=value, .left=NULL, .right=NULL};
    if (!parent_node) { bst->root = curr_node; }
    else {
      if ( LR == 0 ) { parent_node->left = curr_node; }
      else { parent_node->right = curr_node; }
    }
}

/*
 * This function should remove a key/value pair with a specified key from a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should remove the first one it encounters (i.e. the one closest to
 * the root of the tree).
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair to be removed from the BST.
 */
void bst_remove(struct bst* bst, int key) {
    if ( bst ) {
        struct bst_node* parent_node = NULL;
        struct bst_node* curr_node = bst->root;
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
            printf("Error: Attempt to remove non-existed node from the BST\n");
            free(bst);
            exit(1);
        }
        else {
            struct bst_node* replaced_node;
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
                struct bst_node* s_parent = curr_node;
                struct bst_node* s = curr_node->right;
                // branch right in the tree from N, and continue to branch left until reaching a node with no
                // left child
                while ( s->left ) {
                    s_parent = s;
                    s = s->left;
                }
                // update the successor and its parent node
                s->left = curr_node->left;
                if (s_parent != curr_node) {
                    s_parent->left = s->right;
                    s->right = curr_node->right;
                }
                replaced_node = s;
            }
            // update the parent node to point to the replaced node or NULL
            if ( !parent_node ) {
                bst->root = replaced_node;
            } else {
                if ( LR == 0 ) { parent_node->left = replaced_node; }
                else { parent_node->right = replaced_node; }
            }
            // free the memory allocated for the removed node
            free(curr_node);
        }
    }
    else {
        printf("Error: Invalid BST for removing the element!\n");
        exit(1);
    }
}

/*
 * This function should return the value associated with a specified key in a
 * given BST.  If multiple values with the same key exist in the tree, this
 * function should return the first one it encounters (i.e. the one closest to
 * the root of the tree).  If the BST does not contain the specified key, this
 * function should return NULL.
 *
 * Params:
 *   bst - the BST from which a key/value pair is to be removed.  May not
 *     be NULL.
 *   key - the key of the key/value pair whose value is to be returned.
 *
 * Return:
 *   Should return the value associated with the key `key` in `bst` or NULL,
 *   if the key `key` was not found in `bst`.
 */
void* bst_get(struct bst* bst, int key){
    struct bst_node* curr_node = bst->root;
    while (curr_node) {
        if ( key == curr_node->key ) { return curr_node->value; }
        else if ( key < curr_node->key ){ curr_node = curr_node->left; }
        else { curr_node = curr_node->right; }
    }
    return NULL;
}

/*
 * Helper function for bst_DFS that uses pre-order traversal to process
 * every node of a BST from the root
 * */
void __pre_traversal(struct bst_node* node) {
    if (node) {
        printf("%d ", node->key);
        __pre_traversal(node->left);
        __pre_traversal(node->right);
    }
}

/*
 * Helper function for bst_DFS that uses in-order traversal to process
 * every node of a BST from the root
 * */
void __in_traversal(struct bst_node* node) {
    if (node) {
        __in_traversal(node->left);
        printf("%d ", node->key);
        __in_traversal(node->right);
    }
}

/*
 * Helper function for bst_DFS that uses post-order traversal to process
 * every node of a BST from the root
 * */
void __post_traversal(struct bst_node* node) {
    if (node) {
        __post_traversal(node->left);
        __post_traversal(node->right);
        printf("%d ", node->key);
    }
}

/*
 * This function should perform DFS traversal on the given BST.
 *
 * Params:
 *   bst - the BST whose elements are to be traversed.  May not be NULL.
 *   order - the speciifc type of depth-first BST traversal
 */
void bst_DFS(struct bst* bst, enum DFS_order order) {
    if ( bst ) {
        switch (order) {
            case PRE:
                printf("Pre-order DFS Traversal:  ");
                __pre_traversal(bst->root);
                break;
            case IN:
                printf("In-order DFS Traversal:   ");
                __in_traversal(bst->root);
                break;
            case POST:
                printf("Post-order DFS Traversal: ");
                __post_traversal(bst->root);
                break;
        }
        printf("\n");
    } else {
        printf("Error: Invalid BST for DFS traversal!\n");
        exit(1);
    }
}

/*
 * Helper function for bst_BFS that uses queue to process every
 * node of a BST from the root
 * */
void __bfs_traversal(struct bst_node* root) {
    struct queue* queue = queue_create();
    queue_enqueue(queue, root);
    struct bst_node* curr_node;
    while (!queue_isempty(queue)) {
        curr_node = queue_dequeue(queue);
        printf("%d ", curr_node->key);
        if (curr_node) {
            if (curr_node->left) { queue_enqueue(queue, curr_node->left); }
            if (curr_node->right) { queue_enqueue(queue, curr_node->right); }
        }
    }
    queue_free(queue);
}

/*
 * This function should perform BFS traversal on the given BST.
 *
 * Params:
 *   bst - the BST whose elements are to be traversed.  May not be NULL.
 */
void bst_BFS(struct bst* bst) {
    if ( bst ) {
        printf("BFS Traversal:\t\t  ");
        __bfs_traversal(bst->root);
        printf("\n");
    } else {
        printf("Error: Invalid BST for DFS traversal!\n");
        exit(1);
    }
}