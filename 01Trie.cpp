const int MAXN = 100010;
const int MAXLOG = 20;
const int MAXNODE = MAXN * MAXLOG;

namespace trie{
	int children[MAXNODE][2], size[MAXNODE], id = 2;
	inline void insert(int x, int num = 1) {//insert "num" number of "x", "num" could be a negative number to make "insert" delete "x"
		int u = 1;
		for(int i = MAXLOG - 1; i >= 0; i--){
			bool v = (x >> i) & 1;
			if(!children[u][v]) children[u][v] = newNode();
			u = children[u][v];
			size[u] += num;
		}
	}
	inline int getRank(int x) {//find the rank of "x"
		int u = 1, returnValue = 0;
		for(int i = MAXLOG - 1; i >= 0; i--) {
			bool v = (x >> i) & 1;
			if(v) returnValue += size[ children[u][0] ];
			u = children[u][v];
			if(!u) break;
		}
		return returnValue;
	}
	inline int findKth(int k) {//find the "k" th biggest value
		int u = 1, returnValue = 0;
		for(int i = MAXLOG - 1; i >= 0; i--) {
			int leftChildrenSize = size[ children[u][0] ];
			if( k <= leftChildrenSize ) u = children[u][0];
			else k -= leftChildrenSize, returnValue |= (1 << i), u = children[u][1];
		}
		return returnValue;
	}
	int newNode() {// clear the children and size and create a new node, this is important as clear only delete the starting node
		children[id][0] = children[id][1] = size[id] = 0;
		return id++;
	}
	void clear(){// delete the whole trie only by one operation. Delete the starting node
		children[1][0] = children[1][1] = 0;
		id = 2;
	} 
} 

