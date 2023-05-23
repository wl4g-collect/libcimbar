/* This code is subject to the terms of the Mozilla Public License, v.2.0. http://mozilla.org/MPL/2.0/. */
#include "AdjacentCellFinder.h"

AdjacentCellFinder::AdjacentCellFinder(const CellPositions::positions_list& positions, int dimensions_x, int dimensions_y, int marker_size_x, int marker_size_y)
	: _positions(positions)
	, _dimensionsX(dimensions_x)
	, _markerSizeX(marker_size_x)
{
	int midHeight = dimensions_y - marker_size_y - marker_size_y;
	int midCells = dimensions_x * midHeight;
	int edgeCells = calc_mid_width() * marker_size_y;
	_firstMid = edgeCells;
	_firstBottom = edgeCells + midCells;
}

std::array<int, 4> AdjacentCellFinder::find(int index) const
{
	std::array<int,4> adj = {
		right(index), left(index), bottom(index), top(index)
	};
	return adj;
}

int AdjacentCellFinder::dimensions_x() const
{
	return _dimensionsX;
}

int AdjacentCellFinder::marker_size_x() const
{
	return _markerSizeX;
}

int AdjacentCellFinder::calc_mid_width() const
{
	return _dimensionsX - _markerSizeX - _markerSizeX;
}

int AdjacentCellFinder::first_mid() const
{
	return _firstMid;
}

int AdjacentCellFinder::in_row_with_margin(int index) const
{
	if (index < _firstMid)  // top
		return 1;
	if (index < _firstBottom)  // middle
		return 0;
	else
		return 1; // bottom
}

int AdjacentCellFinder::right(int index) const
{
	int next = index+1;
	if (next >= (int)_positions.size())
		return -1;
	if (_positions[next].first < _positions[index].first)  // loop
		return -1;
	return next;
}

int AdjacentCellFinder::left(int index) const
{
	int next = index-1;
	if (next < 0)
		return -1;
	if (_positions[next].first > _positions[index].first)  // loop
		return -1;
	return next;
}

int AdjacentCellFinder::bottom(int index) const
{
	int increment = _dimensionsX;
	if (in_row_with_margin(index))
		increment -= _markerSizeX;
	int next = index + increment;
	if (in_row_with_margin(next))
		next -= _markerSizeX;

	if (next >= (int)_positions.size())
		return -1;
	if (_positions[next].first != _positions[index].first)  // near anchor
		return -1;
	return next;
}

int AdjacentCellFinder::top(int index) const
{
	int increment = _dimensionsX;
	if (in_row_with_margin(index))
		increment -= _markerSizeX;
	int next = index - increment;
	if (in_row_with_margin(next))
		next += _markerSizeX;

	if (next < 0)
		return -1;
	if (_positions[next].first != _positions[index].first)  // near anchor
		return -1;
	return next;
}
