namespace trie{
	const int MAXN = 100010;
	const int MAXVER = 100010;
	const int MAXLOG = 20;
	const int MAXNODE = MAXN * MAXLOG + MAXVER;

	int children[MAXNODE][2], size[MAXNODE], root[MAXVER], id = 1;
	int newNode(int x) { 
        children[id][0] = children[x][0];
        children[id][1] = children[x][1];
        size[id] = size[x]; 
        return id++; 
    }
	inline void insert(int currentVersion, int fromVersion, int x, int num = 1) {//insert "num" number of "x", "num" could be a negative number to make "insert" delete "x"
		int i, u = root[currentVersion] = newNode(root[fromVersion]); //from "fromVersion" version to "currentVersion" to record this modification 
		for(i = MAXLOG - 1; i >= 0; i--){
			bool v = (x >> i) & 1;
			children[u][v] = newNode(children[u][v]);
			u = children[u][v];
			size[u] += num;
		}
	}
	inline int getRank(int startVersion, int endVersion, int x) {//find the rank of "x" in the versions between the start version to the end version
		int i, returnValue = 0;
		int l = root[startVersion], r = root[endVersion];
		for(i = MAXLOG - 1; i >= 0; i--) {
			bool v = (x >> i) & 1;
			if(v) returnValue += size[ children[r][0] ] - size[ children[l][0] ];
			l = children[l][v], r = children[r][v];
		}
		return returnValue;
	}
	inline int findKth(int startVersion, int endVersion, int k) {//find the "k" th biggest value in the versions between the start version to the end version
		int i, returnValue = 0;
		int l = root[l], r = root[r];
		for(i = MAXLOG - 1; i >= 0; i--) {
			int leftChildrenSize = size[ children[r][0] ] - size[ children[l][0] ];
			if( k <= leftChildrenSize ) l = children[l][0], r = children[r][0];
			else k -= leftChildrenSize, returnValue |= (1 << i), l = children[l][1], r = children[r][1];
		}
		return returnValue;
	}
}