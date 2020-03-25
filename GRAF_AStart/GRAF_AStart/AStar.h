#pragma once
#include <vector>

using namespace std;
class Node {
public:
	Node() {}
	~Node() {}
	Node(int LENG, int X, int Y) {
		leng = LENG;
		x = X;
		y = Y;
	}
	int leng;
	int x, y;
};

class AStar
{
	

	vector<vector<int>> map;
	vector<int> noStep;
	vector<Node> oldSteps;
	vector<Node> waitSteps;
	Node startPoint;
	Node searchItem;

	int dx[4] = { -1, 1,  0, 0 };
	int dy[4] = { 0 , 0, -1, 1 };


	bool isHaveOldStep( int x, int y) {
		for (int i = 0; i < oldSteps.size(); ++i)
			if (oldSteps[i].x == x && oldSteps[i].y == y)
				return true;
		return false;
	}

	bool isHaveNoStep(int x,int y) {
		for (int i = 0; i < noStep.size(); ++i)
			if(noStep[i]==map[y][x])
				return true;
		return false;
	}

	void Search() {
		for (int i = 0; i < 4; ++i) {
			if(waitSteps[0].x + dx[i] >=0 && waitSteps[0].y + dy[i]>=0)
				if (!isHaveOldStep(waitSteps[0].x + dx[i], waitSteps[0].y + dy[i]) && !isHaveNoStep(waitSteps[0].x + dx[i], waitSteps[0].y + dy[i])){
					waitSteps.push_back( Node(waitSteps[0].leng - 1, waitSteps[0].x + dx[i], waitSteps[0].y + dy[i]) );
					//cout << waitSteps[0].leng - 1 << " # x = " << waitSteps[0].x + dx[i] << " # y = " << waitSteps[0].y + dy[i]<< endl;
					//if (waitSteps[0].x + dx[i] == searchItem.x && waitSteps[0].y + dy[i] == searchItem.y)
						//cout << "Yess" << endl;
				}
		}
		oldSteps.push_back(waitSteps[0]);
		waitSteps.erase(waitSteps.begin());
	}

	vector<Node> GetStep() {
		vector<Node> answerStep;
		
		for (int j = 0; j < oldSteps.size(); ++j) {
			if (oldSteps[j].x == searchItem.x && oldSteps[j].y == searchItem.y) {
				int leng = oldSteps[j].leng;

				answerStep.push_back(Node(leng, searchItem.x, searchItem.y));

				while (oldSteps.size() > 0 && oldSteps.at(oldSteps.size() - 1).leng <= leng) {
					oldSteps.pop_back();
				}

			}
		}

		if (answerStep.size() > 0)
			while (oldSteps.size() > 0) {
				Node node;
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < oldSteps.size(); ++j) {
						if (oldSteps[j].x + dx[i] == answerStep[answerStep.size() - 1].x && oldSteps[j].y + dy[i] == answerStep[answerStep.size() - 1].y) {
							int leng = oldSteps[j].leng;

							answerStep.push_back(Node(leng, oldSteps[j].x, oldSteps[j].y));

							while (oldSteps.size() > 0 && oldSteps.at(oldSteps.size() - 1).leng <= leng) {
								oldSteps.pop_back();
							}
						}
					}
				}
			}
		else
			answerStep.push_back(Node(0, searchItem.x, searchItem.y));
		/*cout << "Steps:" << endl;
		for (int i = 0; i < answerStep.size(); ++i) {
			cout << "x = " << answerStep[i].x << " # y= " << answerStep[i].y << endl;
		}*/

		return answerStep;
	}

public:
	AStar() {}
	~AStar() {}

	vector<Node> Search(vector<vector<int>> map, vector<int> noStep, vector<int> startPoint, int searchItem) {
		this->map = map;
		this->noStep = noStep;
		bool isYes = false;
		for(int i = 0;i < map.size();++i)
			for (int j = 0; j < map[i].size(); ++j)
				if (map[i][j] == searchItem) {
					this->searchItem.x = j;
					this->searchItem.y = i;
					this->searchItem.leng = 0;
					isYes = true;
				}
		if (!isYes)
		{
			vector<Node> answer;
			answer.push_back(Node(0,startPoint[0], startPoint[1]));
			return answer;
		}

		waitSteps.push_back(Node(-1, startPoint.at(0), startPoint.at(1)));

		while (waitSteps.size()>0) {
			Search();
		}

		return GetStep();
	}

};