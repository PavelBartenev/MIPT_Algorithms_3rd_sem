#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <vector>

struct order {
	int departure_time;
	int arrival_time;
	int x_start;
	int y_start;
	int x_end;
	int y_end;
	int ride_time;

	order(int x_start, int y_start, int x_end, int y_end, int departure_time)
		: x_start{ x_start }, x_end{ x_end }, y_start{ y_start }, y_end{ y_end }, departure_time{ departure_time },
		arrival_time{ departure_time + std::abs(x_start - x_end) + std::abs(y_start - y_end) }, ride_time{ arrival_time - departure_time }{}

	int distance(const order& other) {
		return std::abs(other.x_start - x_end) + std::abs(other.y_start - y_end);
	}
};

class Taxi_manager {
public:
	std::vector<order> schedule;

	Taxi_manager() = default;

	~Taxi_manager() = default;

	void append_order(int departure_time, int x_start, int y_start, int x_end, int y_end) {
		schedule.emplace_back(x_start, y_start, x_end, y_end, departure_time);
	}

	int number_of_taxi_required() {
		std::vector<std::vector<int>>route(schedule.size());

		build_route(route);

		std::vector<int> matchings(schedule.size(), -1);
		std::vector<bool> used(schedule.size(), false);

		for (size_t ride = 0; ride < schedule.size(); ++ride) {
			kuhn_alg(ride, route, matchings, used);
			used.assign(schedule.size(), false);
		}

		int one_taxi_rides_max_num = 0;

		for (size_t ride = 0; ride < matchings.size(); ++ride) {
			if (matchings[ride] != -1)
				++one_taxi_rides_max_num;
		}

		return schedule.size() - one_taxi_rides_max_num;
	}

private:
	void build_route(std::vector<std::vector<int>>& route) {
		for (size_t ride = 0; ride < schedule.size(); ++ride) {
			for (size_t next_ride = ride + 1; next_ride < schedule.size(); ++next_ride) {
				if (schedule[next_ride].departure_time >= schedule[ride].arrival_time + schedule[ride].distance(schedule[next_ride]) + 1)
					route[ride].push_back(next_ride);
			}
		}
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
};



int main()
{
	Taxi_manager manager;

	int orders_number = 0;
	std::cin >> orders_number;

	int hours = 0;
	int minutes = 0;
	int x_start = 0;
	int y_start = 0;
	int x_end = 0;
	int y_end = 0;

	for (int order = 0; order < orders_number; ++order) {
		scanf("%d:%d %d %d %d %d", &hours, &minutes, &x_start, &y_start, &x_end, &y_end);
		manager.append_order(hours * 60 + minutes, x_start, y_start, x_end, y_end);
	}

	std::cout << manager.number_of_taxi_required();

	return 0;
}
 
