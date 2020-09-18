#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <time.h>

namespace CalculationSection
{
	class Custom_unsorted_set
	{
	private:
		std::vector<glm::vec3> unsorted_container;
	public:
		bool duplicateCheck(glm::vec3 value)
		{
			bool result = false;
			for (size_t i = 0; i < unsorted_container.size(); ++i) {
				if (glm::all(glm::equal(unsorted_container[i], value))) {
					result = true;
					break;
				}
			}
			return result;
		}
		void insert(glm::vec3 value) {
			if (!duplicateCheck(value))
				unsorted_container.push_back(value);
		}
		int size(void) { return unsorted_container.size(); }
	};

	class RandomWalk
	{
	public:
		std::vector<glm::vec3> walkers;
		std::vector<std::vector<glm::vec3>> histories; // histories.size() == walkers.size()
		std::vector<std::vector<bool>> availability; // availability.size() == walkers.size()
		std::vector<bool> trapped; // trapped.size() == walkers.size()
		std::vector<float> distance; // distance.size() == walkers.size()
		std::vector<std::vector<glm::vec3>> histories_interval_one; // histories_interval_one.size() == walkers.size()
		std::vector<int> countOfSAW; // countOfSAW.size() == walkers.size()
		bool intersectInNextStep;
		bool intersected;
		std::vector<bool> returnedToOrigin; // returnedToOrigin.size() == walkers.size()

	public:
		void Init(std::vector<glm::vec3> walkers);
		std::vector<int> Update(int simulation_id, int dimension, std::vector<int>& countOfPosNegMove, int stepSize, int stepCount, bool walkerStepInfinite);

	private:
		std::vector<int> SimpleMultipleRandomWalk(int simulation_id, int dimension, std::vector<int>& countOfPosNegMove, int stepSize, int stepCount, bool walkerStepInfinite);
		std::vector<int> SelfAvoidingRandomWalk(int simulation_id, int dimension, std::vector<int>& countOfPosNegMove, int stepSize, int stepCount, bool walkerStepInfinite);
		void MoveNextWalk(int i, int dir, int stepSize);
		bool CheckIntersection(void);
		int CountNumOfOwnSAW(int i);
	};

	struct vec3compare {
		bool operator() (const glm::vec3& lhs, const glm::vec3& rhs) const;
	};
}