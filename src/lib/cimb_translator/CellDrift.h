#pragma once

#include <vector>
#include <utility>

class CellDrift
{
public:
	CellDrift(int limit=2);

	static const std::vector<std::pair<int, int>> driftPairs;

	int x() const;
	int y() const;

	void updateDrift(int dx, int dy);

protected:
	int _limit;
	int _x = 0;
	int _y = 0;
};