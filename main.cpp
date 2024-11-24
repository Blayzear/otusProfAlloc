#include<map>
#include<cmath>
#include<iostream>
#include"container.cpp"

int main() {
	auto map_std = std::map<int, int, std::less<int>>{};
	for (int i = 0; i < 10; ++i) {
		map_std[i] = static_cast<int>(std::tgamma(i+1));
	}

	auto map_custom = std::map<int, int, std::less<int>,
		MyAllocator<std::pair<const int, int>>>{};
	for (int i = 0; i < 10; ++i) {
		map_custom[i] = static_cast<int>(std::tgamma(i + 1));
	}

	for (const auto& [key, value] : map_std) {
		std::cout << key << " " << value << " ";
	};
	std::cout << "\n";
	for (const auto& [key, value] : map_custom) {
		std::cout << key << " " << value << " ";
	};
	std::cout << "\n";

	MyContainer<int> c_std;
	for (int i = 0; i < 10; ++i) {
		c_std.push_back(i);
	}
	std::cout << "\n";
	MyContainer<int, MyAllocator<int>> c_custom;
	for (int i = 0; i < 10; ++i) {
		c_custom.push_back(i);
	}

	for (auto n = c_std.begin(); n != c_std.end(); n++)
	{
		std::cout << *n << ' ';
	}
	std::cout << "\n";
	for (auto n = c_custom.begin(); n != c_custom.end(); n++)
	{
		std::cout << *n << ' ';
	}
	return 0;
}