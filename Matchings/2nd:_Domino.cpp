#include <iostream>
#include <vector>
#include <fstream>

bool kuhn_alg(int vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& matchings, std::vector<bool>& used);

int main()
{

	std::ifstream input("dominoes.in");
	std::ofstream output("dominoes.out");

	int lines_num = 0;
	int columns_num = 0;

	int domino_cost = 0;
	int chip_cost = 0;

	input >> lines_num >> columns_num >> domino_cost >> chip_cost;

	int squares_num = lines_num * columns_num;

	std::vector<std::vector<char>> board(lines_num, std::vector<char>(columns_num));
	std::vector<std::vector<int>> graph(squares_num);

	for (int line = 0; line < lines_num; ++line) {
		for (int column = 0; column < columns_num; ++column)
			input >> board[line][column];
	}

	int stars_num = 0;

	for (int line = 0; line < lines_num; ++line) {
		for (int column = 0; column < columns_num; ++column) {
			if (board[line][column] == '*') {
				if (column < columns_num - 1 && board[line][column + 1] == '*') {
					graph[line * columns_num + column].push_back(line * columns_num + column + 1);
					graph[line * columns_num + column + 1].push_back(line * columns_num + column);
				}

				if (line < lines_num - 1 && board[line + 1][column] == '*') {
					graph[line * columns_num + column].push_back((line + 1) * columns_num + column);
					graph[(line + 1) * columns_num + column].push_back(line * columns_num + column);
				}

				++stars_num;
			}
		}
	}

	if (chip_cost * 2 <= domino_cost) {
		output << chip_cost * stars_num;

		return 0;
	}

	std::vector<bool> used(squares_num, false);
	std::vector<int> matchings(squares_num, -1);

	for (int vertex = 0; vertex < squares_num; ++vertex) {
		used.assign(squares_num, false);

		kuhn_alg(vertex, graph, matchings, used);
	}

	int matches_num = 0;

	for (const auto& match : matchings) {
		if (match != -1)
			++matches_num;
	}

	matches_num /= 2;

	output << matches_num * domino_cost + (stars_num - matches_num * 2) * chip_cost;

	input.close();
	output.close();

	return 0;
}

bool kuhn_alg(int vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& matchings, std::vector<bool>& used) {
	if (used[vertex])
		return false;

	used[vertex] = true;

	for (const auto& neighbour : graph[vertex]) {
		if (matchings[neighbour] == -1 || kuhn_alg(matchings[neighbour], graph, matchings, used)) {
			matchings[neighbour] = vertex;
			matchings[vertex] = neighbour;

			return true;
		}
	}

	return false;
}
