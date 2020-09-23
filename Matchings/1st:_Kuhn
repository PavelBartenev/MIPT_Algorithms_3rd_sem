#include <iostream>
#include <vector>


bool kuhn_alg(int vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& matchings, std::vector<bool>& used);


int main()
{
	int left_part_size = 0;
	int right_part_size = 0;

	std::cin >> left_part_size >> right_part_size;

	std::vector<std::vector<int>> graph(left_part_size);

	for (int left_vertex = 0; left_vertex < left_part_size; ++left_vertex) {
		int cur_right_vertex = 1;

		std::cin >> cur_right_vertex;

		while (cur_right_vertex != 0) {
			graph[left_vertex].push_back(cur_right_vertex - 1);
			std::cin >> cur_right_vertex;
		}
	}

	std::vector<int> matchings(right_part_size, -1);
	std::vector<bool> used(left_part_size, false);

	for (int vert = 0; vert < left_part_size; ++vert) {
		used.assign(left_part_size, false);

		kuhn_alg(vert, graph, matchings, used);
	}

	int matchings_number = 0;

	for (int right_vert = 0; right_vert < right_part_size; ++right_vert) {
		if (matchings[right_vert] != -1)
			++matchings_number;
	}

	std::cout << matchings_number << "\n";

	for (int right_vert = 0; right_vert < right_part_size; ++right_vert) {
		if (matchings[right_vert] != -1)
			std::cout << matchings[right_vert] + 1 << " " << right_vert + 1 << "\n";
	}

	return 0;
}

bool kuhn_alg(int vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& matchings, std::vector<bool>& used) {
	if (used[vertex])
		return false;

	used[vertex] = true;

	for (const auto& right_vert : graph[vertex]) {
		if (matchings[right_vert] == -1 || kuhn_alg(matchings[right_vert], graph, matchings, used)) {
			matchings[right_vert] = vertex;

			return true;
		}
	}

	return false;
}
