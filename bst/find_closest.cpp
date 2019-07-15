#include <stdlib.h>

class BST {
  public:
    int value;
    BST* left;
    BST* right;

    BST(int val);
    BST& insert(int val);
};

int traverse(BST* node, int target, int best, int bestDistance)
{
	if (node == nullptr) {
		return best;
	}
	
	auto value = node->value;
	
	if (value == target) {
		return value;
	}
	
	auto distance = abs(value - target);
	
	if (distance < bestDistance) {
		best = value;
		bestDistance = distance;
	}
	
	return (target > value)
		? traverse(node->right, target, best, bestDistance)
		: traverse(node->left, target, best, bestDistance);
}


int findClosestValueInBst(BST* tree, int target) {
	auto value = tree->value;
	auto distance = abs(value - target);
	
  return traverse(tree, target, value, distance);
}

int main()
{
	return 0;
}