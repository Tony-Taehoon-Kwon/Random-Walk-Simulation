#include "RandomWalk.h"
#include <set>

using namespace CalculationSection;

void RandomWalk::Init(std::vector<glm::vec3> _walkers)
{
	if (walkers.size() != 0 || histories.size() != 0
		|| availability.size() != 0 || trapped.size() != 0
		|| distance.size() != 0 || histories_interval_one.size() != 0
		|| countOfSAW.size() != 0 || returnedToOrigin.size() != 0)
	{
		walkers.clear();
		histories.clear();
		availability.clear();
		trapped.clear();
		distance.clear();
		histories_interval_one.clear();
		countOfSAW.clear();
		returnedToOrigin.clear();
	}
	walkers = _walkers;
	histories.resize(walkers.size());
	availability.resize(walkers.size());
	trapped.resize(walkers.size());
	distance.resize(walkers.size());
	histories_interval_one.resize(walkers.size());
	countOfSAW.resize(walkers.size());
	returnedToOrigin.resize(walkers.size());

	/* record the initial position of all walkers,
	   and initialize the availabilty of direction to next move for self-avoiding RW */
	for (size_t i = 0; i < walkers.size(); ++i)
	{
		histories[i].push_back(walkers[i]);
		trapped[i] = false;
		distance[i] = 0;
		histories_interval_one[i].push_back(walkers[i]);
		countOfSAW[i] = 0;
		returnedToOrigin[i] = false;

		for (int j = 0; j < 6; ++j)
			availability[i].push_back(true);
	}
	intersectInNextStep = false;
	intersected = false;
	srand((unsigned int)time(NULL));
}

std::vector<int> RandomWalk::Update(int simulation_id, int dimension, std::vector<int>& countOfPosNegMove, 
	int stepSize, int stepCount, bool walkerStepInfinite)
{
	if (simulation_id == 1 || simulation_id == 5)
		return SelfAvoidingRandomWalk(simulation_id, dimension, countOfPosNegMove, stepSize, stepCount, walkerStepInfinite);
	else
		return SimpleMultipleRandomWalk(simulation_id, dimension, countOfPosNegMove, stepSize, stepCount, walkerStepInfinite);
}

std::vector<int> RandomWalk::SimpleMultipleRandomWalk(int simulation_id, int dimension, std::vector<int>& countOfPosNegMove,
	int stepSize, int stepCount, bool walkerStepInfinite)
{
	std::vector<int> walkersDir(walkers.size(), -1);

	/* for all walkers */
	for (size_t i = 0; i < walkers.size(); ++i)
	{
		/* if the walker was stop already,
		   and the simulation of move is finished, then skip */
		if (trapped[i])
			continue;

		/* if walker moved N fixed step already,
		   stop the walker */
		if (!walkerStepInfinite && histories[i].size() > (unsigned)stepCount) {
			trapped[i] = true; // reuse trapped variable to signal stop

			if (simulation_id == 2) {
				/* calculate the distance from the origin */
				distance[i] = std::sqrtf(walkers[i].x * walkers[i].x
					+ walkers[i].y * walkers[i].y
					+ walkers[i].z * walkers[i].z);
			}
			else if (simulation_id == 3) {
				/* if walker returns to origin, stop the walker */
				if (walkers[i].x == 0 && walkers[i].y == 0 && walkers[i].z == 0)
					returnedToOrigin[i] = true;
			}
			else if (simulation_id == 5) {
				/* if a walker intersects with the other walker
					then stop all walkers in next step */
				if (CheckIntersection()) {
					trapped[0] = true;
					trapped[1] = true;
					intersected = true;
				}
			}
			else if (simulation_id == 6) {
				/* count the number of own SAW */
				countOfSAW[i] = CountNumOfOwnSAW(i);
			}
			continue;
		}

		if (simulation_id == 3 &&
			histories[i].size() != 1) { // number of steps can be found in histories[i].size()
			
			/* if walker returns to origin, stop the walker */
			if (walkers[i].x == 0 && walkers[i].y == 0 && walkers[i].z == 0) {
				trapped[i] = true; // reuse trapped variable to signal stop
				returnedToOrigin[i] = true;
				continue;
			}
		}
		else if (intersectInNextStep) { // related to simulation_id == 4
			trapped[0] = true; // stop first walker
			trapped[1] = true; // stop second walker
			intersected = true;
			continue;
		}
		
		int dir = -1;
		if (dimension == 3)
		{
			/* 0: +stepSize(x)
			   1: -stepSize(x)
			   2: +stepSize(y)
			   3: -stepSize(y)
			   4: +stepSize(z)
			   5: -stepSize(z) */
			dir = rand() % 6;
		}
		else if (dimension == 2)
		{
			/* 0: +stepSize(x)
			   1: -stepSize(x)
			   2: +stepSize(y)
			   3: -stepSize(y) */
			dir = rand() % 4;
		}
		else
		{
			/* 0: +stepSize(x)
			   1: -stepSize(x) */
			dir = rand() % 2;
		}
		MoveNextWalk(i, dir, stepSize);
		walkersDir[i] = dir;

		/* change the coordinates */
		if (dimension == 3)
		{
			if (dir == 2)		dir = 4;
			else if (dir == 3)	dir = 5;
			else if (dir == 4)	dir = 2;
			else if (dir == 5)	dir = 3;
		}
		else if (dimension == 2)
		{
			if (dir == 2)		dir = 3;
			else if (dir == 3)	dir = 2;
		}
		countOfPosNegMove[dir] += 1;

		if (simulation_id == 4 && i == 1 &&
			histories[i].size() > 1) {

			/* if a walker intersects with the other walker
				then stop all walkers in next step */
			if (CheckIntersection())
				intersectInNextStep = true;
		}
	}
	return walkersDir;
}

void RandomWalk::MoveNextWalk(int i, int dir, int stepSize)
{
	/*	0: +stepSize(x)
		1: -stepSize(x)
		2: +stepSize(y)
		3: -stepSize(y)
		4: +stepSize(z)
		5: -stepSize(z) */

	switch (dir)
	{
	case 0: 
		for (int j = 1; j <= stepSize; ++j) {
			histories_interval_one[i].push_back(
				glm::vec3(walkers[i].x + j, walkers[i].y, walkers[i].z));
		}
		walkers[i].x += stepSize; histories[i].push_back(walkers[i]);
		break;
	case 1:
		for (int j = 1; j <= stepSize; ++j) {
			histories_interval_one[i].push_back(
				glm::vec3(walkers[i].x - j, walkers[i].y, walkers[i].z));
		}
		walkers[i].x -= stepSize; histories[i].push_back(walkers[i]);
		break;
	case 2:
		for (int j = 1; j <= stepSize; ++j) {
			histories_interval_one[i].push_back(
				glm::vec3(walkers[i].x, walkers[i].y + j, walkers[i].z));
		}
		walkers[i].y += stepSize; histories[i].push_back(walkers[i]);
		break;
	case 3:
		for (int j = 1; j <= stepSize; ++j) {
			histories_interval_one[i].push_back(
				glm::vec3(walkers[i].x, walkers[i].y - j, walkers[i].z));
		}
		walkers[i].y -= stepSize; histories[i].push_back(walkers[i]);
		break;
	case 4:
		for (int j = 1; j <= stepSize; ++j) {
			histories_interval_one[i].push_back(
				glm::vec3(walkers[i].x, walkers[i].y, walkers[i].z + j));
		}
		walkers[i].z += stepSize; histories[i].push_back(walkers[i]);
		break;
	case 5:
		for (int j = 1; j <= stepSize; ++j) {
			histories_interval_one[i].push_back(
				glm::vec3(walkers[i].x, walkers[i].y, walkers[i].z - j));
		}
		walkers[i].z -= stepSize; histories[i].push_back(walkers[i]);
		break;
	}
}

std::vector<int> RandomWalk::SelfAvoidingRandomWalk(int simulation_id, int dimension, std::vector<int>& countOfPosNegMove,
	int stepSize, int stepCount, bool walkerStepInfinite)
{
	std::vector<int> walkersDir(walkers.size(), -1);

	/* for all walkers */
	for (size_t i = 0; i < walkers.size(); ++i)
	{
		/* if the walker is trapped in its track,
		   and the simulation of move is finished, then skip */
		if (trapped[i])
			continue;

		/* if walker moved N fixed step already,
		   stop the walker */
		if (!walkerStepInfinite && histories[i].size() > (unsigned)stepCount) {
			trapped[i] = true; // reuse trapped variable to signal stop
			
			if (simulation_id == 5) {
				/* if a walker intersects with the other walker
					then stop all walkers in next step */
				if (CheckIntersection()) {
					trapped[0] = true;
					trapped[1] = true;
					intersected = true;
				}
			}
			continue;
		}

		if (intersectInNextStep) { // related to simulation_id == 5
			trapped[0] = true; // stop first walker
			trapped[1] = true; // stop second walker
			intersected = true;
			continue;
		}

		/* reinitialize the availability for the next move */
		for (int j = 0; j < dimension * 2; ++j)
			availability[i][j] = true;

		/* for all history of the walker, check the availability for next move */
		for (size_t j = 0; j < histories[i].size(); ++j)
		{
			if (walkers[i].x + stepSize == histories[i][j].x
				&& walkers[i].y == histories[i][j].y
				&& walkers[i].z == histories[i][j].z)
				availability[i][0] = false;

			if (walkers[i].x - stepSize == histories[i][j].x
				&& walkers[i].y == histories[i][j].y
				&& walkers[i].z == histories[i][j].z)
				availability[i][1] = false;

			if (dimension >= 2)
			{
				if (walkers[i].x == histories[i][j].x
					&& walkers[i].y + stepSize == histories[i][j].y
					&& walkers[i].z == histories[i][j].z)
					availability[i][2] = false;

				if (walkers[i].x == histories[i][j].x
					&& walkers[i].y - stepSize == histories[i][j].y
					&& walkers[i].z == histories[i][j].z)
					availability[i][3] = false;
			}

			if (dimension == 3)
			{
				if (walkers[i].x == histories[i][j].x
					&& walkers[i].y == histories[i][j].y
					&& walkers[i].z + stepSize == histories[i][j].z)
					availability[i][4] = false;

				if (walkers[i].x == histories[i][j].x
					&& walkers[i].y == histories[i][j].y
					&& walkers[i].z - stepSize == histories[i][j].z)
					availability[i][5] = false;
			}
		}

		/* count available path */
		int countAvailablePath = 0;

		for (int j = 0; j < dimension * 2; ++j)
		{
			if (availability[i][j] == true)
				++countAvailablePath;
		}

		/* if there is no where to go, don't move.
		   set the trapped signal as true */
		if (countAvailablePath == 0)
		{
			trapped[i] = true;
			continue;
		}

		/* calculate the next direction */
		int dirTrueIndex = rand() % countAvailablePath;
		int dir = -1;

		for (int j = 0; j < dimension * 2; ++j)
		{
			if (availability[i][j] == true)
			{
				if (dirTrueIndex == 0)
					dir = j;
				--dirTrueIndex;
			}
		}

		MoveNextWalk(i, dir, stepSize);
		walkersDir[i] = dir;

		/* change the coordinates */
		if (dimension == 3)
		{
			if (dir == 2)		dir = 4;
			else if (dir == 3)	dir = 5;
			else if (dir == 4)	dir = 2;
			else if (dir == 5)	dir = 3;
		}
		else if (dimension == 2)
		{
			if (dir == 2)		dir = 3;
			else if (dir == 3)	dir = 2;
		}
		countOfPosNegMove[dir] += 1;

		if (simulation_id == 5 && (i == 1 || trapped[1]) &&
			histories[i].size() > 1) {

			/* if a walker intersects with the other walker
				then stop all walkers in next step */
			if (CheckIntersection())
				intersectInNextStep = true;
		}
	}
	return walkersDir;
}

bool RandomWalk::CheckIntersection(void)
{
	bool result = false;

	for (unsigned i = 0; i < histories_interval_one[0].size(); ++i) {
		for (unsigned j = 0; j < histories_interval_one[1].size(); ++j) {
			
			/* skip the initial position intersection */
			if (i == 0 && j == 0)
				continue;

			/* if a walker intersects with the other walker's trace, then signal true */
			if (histories_interval_one[0][i].x == histories_interval_one[1][j].x
			 && histories_interval_one[0][i].y == histories_interval_one[1][j].y
			 && histories_interval_one[0][i].z == histories_interval_one[1][j].z) {
				result = true;
				break;
			}
		}
	}
	return result;
}

int RandomWalk::CountNumOfOwnSAW(int i)
{
	Custom_unsorted_set unique_history;

	for (size_t j = 0; j < histories[i].size(); ++j)
		unique_history.insert(histories[i][j]);

	/* exclude the initial position from the history */
	return unique_history.size() - 1;
}