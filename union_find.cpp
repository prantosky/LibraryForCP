#include <numeric>
#include <vector>

class union_find {
 private:
	std::vector<int> nodes;
	std::vector<int> rank;

 public:
	union_find(int node_count) {
		nodes.assign(node_count, 0);
		rank.assign(node_count, 1);
		std::iota(nodes.begin(), nodes.end(), 0);
	}

	int root(int i) {
		while (i != nodes[i]) {
			nodes[i] = nodes[nodes[i]];
			i = nodes[i];
		}
		return i;
	}

	bool find(int p, int q) { return root(p) == root(q); }

	void union_by_rank(int p, int q) {
		int i = root(p);
		int j = root(q);
		if (i == j) return;
		if (rank[i] < rank[j]) {
			nodes[i] = j;
			rank[j] += rank[i];
		} else {
			nodes[j] = i;
			rank[i] += rank[j];
		}
	}
	int get_rank(int i) { return rank[i]; }
};
