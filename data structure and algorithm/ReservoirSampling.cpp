#include <vector>
#include <random>
#include <iostream>

using namespace std;

random_device rd;
mt19937 mt(rd());

uint32_t isSelected(uint32_t rand_right_range)
{
	uniform_int_distribution<uint32_t> random_dist(1, rand_right_range);
	return random_dist(mt);
}

bool isExisted(const vector<uint32_t> vec_be_checked, uint32_t element)
{
	for (const auto &var : vec_be_checked)
	{
		if (var == element)
		{
			return true;
		}
	}
	return false;
}

// 每个数留在池中的概率 = 出现时的概率(reservoir_capacity / candidate_num) * 不会被池丢弃的概率 [1 - (reservoir_capacity / candidate_num * 1 / reservoir_capacity)]
void ReservoirSampling(vector<uint32_t>& res_vec, uint32_t reservoir_capacity, uint32_t candidate_num)
{
	if (reservoir_capacity < 1 || candidate_num < 1)
	{
		return;
	}
	for (uint32_t idx = 0; idx < reservoir_capacity; ++idx)
	{
		res_vec[idx] = idx + 1;
	}
	for (uint32_t idx = reservoir_capacity + 1; idx < candidate_num + 1; ++idx)
	{
		if (isSelected(idx) <= reservoir_capacity /*!isExisted(res_vec,idx*/)
		{
			size_t idx_element_to_droped = isSelected(reservoir_capacity - 1);
			res_vec[idx_element_to_droped] = idx;
		}
	}
}

void PrintResultVector(const vector<uint32_t>& res_vec)
{
	for (const auto &res : res_vec)
	{
		cout << res << " ";
	}
	cout << endl;
}

int main()
{
	uint32_t reservoir_capacity;
	uint32_t candidate_num;

	cout << "input reservoir capacity : " << endl;
	cin >> reservoir_capacity;
	cout << "input candidate num : " << endl;
	cin >> candidate_num;

	vector<uint32_t> res_vec(reservoir_capacity, 0);

	ReservoirSampling(res_vec, reservoir_capacity, candidate_num);
	PrintResultVector(res_vec);

	getchar();
	getchar();
}