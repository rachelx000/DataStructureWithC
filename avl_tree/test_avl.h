#ifndef __TEST_AVL_H
#define __TEST_AVL_H

const char *REMOVE_CASE1_EXPECTED_OUTPUT[4] = {
    "Expected Pre-order DFS Traversal:\t2 1 3",
    "Expected Pre-order DFS Traversal:\t2 3",
    "Expected Pre-order DFS Traversal:\t3",
    "Expected Pre-order DFS Traversal:\t(Empty)"
};

const char *REMOVE_CASE2_EXPECTED_OUTPUT[4] = {
    "Expected Pre-order DFS Traversal:\t2 1 3",
    "Expected Pre-order DFS Traversal:\t2 1",
    "Expected Pre-order DFS Traversal:\t1",
    "Expected Pre-order DFS Traversal:\t(Empty)"
};

const char *REMOVE_CASE3_EXPECTED_OUTPUT[4] = {
    "Expected Pre-order DFS Traversal:\t2 1 3",
    "Expected Pre-order DFS Traversal:\t3 1",
    "Expected Pre-order DFS Traversal:\t1",
    "Expected Pre-order DFS Traversal:\t(Empty)"
};

const char *REMOVE_CASE4_EXPECTED_OUTPUT[9] = {
    "Expected Pre-order DFS Traversal:\t45 30 20 40 60 50 70 80",
    "Expected Pre-order DFS Traversal:\t45 30 20 40 70 60 80",
    "Expected Pre-order DFS Traversal:\t45 40 20 70 60 80",
    "Expected Pre-order DFS Traversal:\t45 40 70 60 80",
    "Expected Pre-order DFS Traversal:\t70 45 60 80",
    "Expected Pre-order DFS Traversal:\t70 60 80",
    "Expected Pre-order DFS Traversal:\t80 60",
    "Expected Pre-order DFS Traversal:\t80",
    "Expected Pre-order DFS Traversal:\t(Empty)",
};

const char *REMOVE_CASE5_EXPECTED_OUTPUT[14] = {
    "Expected Pre-order DFS Traversal:\t5 -3 -7 -9 -5 1 -1 3 9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t5 -3 -7 -5 1 -1 3 9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t5 -3 -5 1 -1 3 9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t5 1 -3 -1 3 9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t5 1 -1 3 9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t5 1 3 9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t9 5 3 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t9 5 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t9 7 13 11 15",
    "Expected Pre-order DFS Traversal:\t13 9 11 15",
    "Expected Pre-order DFS Traversal:\t13 11 15",
    "Expected Pre-order DFS Traversal:\t13 15",
    "Expected Pre-order DFS Traversal:\t15",
    "Expected Pre-order DFS Traversal:\t(Empty)",
};

const char *REMOVE_CASE6_EXPECTED_OUTPUT[12] = {
    "Expected Pre-order DFS Traversal:\t21 9 3 0 6 15 12 18 27 24 30 33",
    "Expected Pre-order DFS Traversal:\t24 9 3 0 6 15 12 18 27 30 33",
    "Expected Pre-order DFS Traversal:\t27 9 3 0 6 15 12 18 30 33",
    "Expected Pre-order DFS Traversal:\t27 9 3 0 6 15 12 18 30 33",
    "Expected Pre-order DFS Traversal:\t9 3 0 6 30 15 12 18 33",
    "Expected Pre-order DFS Traversal:\t12 3 0 6 30 15 18 33",
    "Expected Pre-order DFS Traversal:\t15 3 0 6 30 18 33",
    "Expected Pre-order DFS Traversal:\t18 3 0 6 30 33",
    "Expected Pre-order DFS Traversal:\t30 3 0 6 33",
    "Expected Pre-order DFS Traversal:\t3 0 33 6",
    "Expected Pre-order DFS Traversal:\t6 0 33",
    "Expected Pre-order DFS Traversal:\t33 0"
};

const char *REMOVE_CASE7_EXPECTED_OUTPUT[15] = {
    "Expected Pre-order DFS Traversal:\t0 -24 -61 -88 -38 -23 -7 59 7 5 1 33 72 76",
    "Expected Pre-order DFS Traversal:\t0 -24 -61 -88 -38 -23 59 7 5 1 33 72 76",
    "Expected Pre-order DFS Traversal:\t0 -24 -38 -88 -23 59 7 5 1 33 72 76",
    "Expected Pre-order DFS Traversal:\t7 0 -24 -88 -23 5 1 59 33 72 76",
    "Expected Pre-order DFS Traversal:\t7 0 -23 -88 5 1 59 33 72 76",
    "Expected Pre-order DFS Traversal:\t7 1 -23 -88 5 59 33 72 76",
    "Expected Pre-order DFS Traversal:\t7 -23 -88 5 59 33 72 76",
    "Expected Pre-order DFS Traversal:\t7 -23 -88 59 33 72 76",
    "Expected Pre-order DFS Traversal:\t33 -23 -88 72 59 76",
    "Expected Pre-order DFS Traversal:\t59 -23 -88 72 76",
    "Expected Pre-order DFS Traversal:\t72 -23 -88 76",
    "Expected Pre-order DFS Traversal:\t-23 -88 76",
    "Expected Pre-order DFS Traversal:\t76 -88",
    "Expected Pre-order DFS Traversal:\t-88",
    "Expected Pre-order DFS Traversal:\t(Empty)"
};

#endif