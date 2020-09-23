#include <iostream>
#include <vector>
#include <queue>

bool kuhn_alg(int vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& matchings, std::vector<char>& used);

int main()
{
	int parties_number = 0;

	int men_number = 0;
	int girls_number = 0;

	std::cin >> parties_number;

	std::vector<std::vector<int>> friendship_graph;
	std::vector<std::vector<int>> non_friendship_graph;

	std::vector<int> matchings;
	std::vector<char> used;

	for (int party = 0; party < parties_number; ++party) {
		friendship_graph.clear();
		non_friendship_graph.clear();

		std::cin >> men_number >> girls_number;

		friendship_graph.resize(men_number);
		non_friendship_graph.resize(men_number);
		matchings.assign(girls_number, -1);

		for (int guy = 0; guy < men_number; ++guy) {
			int girl = 1;
			
			while (girl != -1) {
				std::cin >> girl;
				--girl;
				if (girl != -1)
					friendship_graph[guy].push_back(girl);
			}
		}

		std::vector<char> is_friend(girls_number, 0);

		for (int guy = 0; guy < men_number; ++guy) {
			for (int girl : friendship_graph[guy])
				is_friend[girl] = 1;

			for (int girl = 0; girl < girls_number; ++girl)
				if (!is_friend[girl])
					non_friendship_graph[guy].push_back(girl);

			is_friend.assign(girls_number, 0);
		}

		used.assign(men_number, 0);

		for (int guy = 0; guy < men_number; ++guy) {
			if (kuhn_alg(guy, non_friendship_graph, matchings, used))
				used.assign(men_number, 0);
		}

		std::vector<char> with_nonfriend(men_number, 0);

		for (int girl = 0; girl < girls_number; ++girl)
			if (matchings[girl] != -1)
				with_nonfriend[matchings[girl]] = true;

		std::vector<char> guys_to_invite(men_number, 0);
		std::vector<char> girls_not_to_invite(girls_number, 0);

		std::queue<int> guys_to_check;
		std::queue<int> girls_to_check;

		for (int guy = 0; guy < men_number; ++guy) {
			if (!with_nonfriend[guy]) {
				guys_to_invite[guy] = true;
				for (int girl : non_friendship_graph[guy])
					girls_to_check.push(girl);
			}
		}

		while (!guys_to_check.empty() || !girls_to_check.empty()) {
			while (!guys_to_check.empty()) {
				int guy = guys_to_check.front();
				guys_to_invite[guy] = true;
				guys_to_check.pop();

				for (int girl : non_friendship_graph[guy])
					if (!girls_not_to_invite[girl])
						girls_to_check.push(girl);
			}

			while (!girls_to_check.empty()) {
				int girl = girls_to_check.front();
				girls_not_to_invite[girl] = true;
				girls_to_check.pop();
				
				if (matchings[girl] != -1 && !guys_to_invite[matchings[girl]])
					guys_to_check.push(matchings[girl]);
			}
		}

		int guys_invited = 0;

		for (int guy = 0; guy < men_number; ++guy)
			if (guys_to_invite[guy])
				++guys_invited;

		int girls_invited = 0;

		for (int girl = 0; girl < girls_number; ++girl)
			if (!girls_not_to_invite[girl])
				++girls_invited;

		std::cout << guys_invited << ' '  << girls_invited << '\n';

		for (int guy = 0; guy < men_number; ++guy)
			if (guys_to_invite[guy])
				std::cout << guy + 1 << ' ';

		std::cout << '\n';

		for (int girl = 0; girl < girls_number; ++girl)
			if (!girls_not_to_invite[girl])
				std::cout << girl + 1 << ' ';

		std::cout << '\n' << '\n';
	}

	return 0;
}


bool kuhn_alg(int vertex, const std::vector<std::vector<int>>& graph, std::vector<int>& matchings, std::vector<char>& used) {
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



