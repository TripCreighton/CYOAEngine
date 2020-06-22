#include "Utilities.h"

struct LeaderboardData {
	string username;
	int highScore;
};

class User {
private: 
	string username;
	int currentScore;
	LeaderboardData leaderboardData;
	vector<int> currentOutcomes;
public:
	User(string username, int currentScore, int highScore, vector<int> currentOutcomes);

	string getUsername();
	LeaderboardData getLeaderboardData();
	vector<int> getCurrentOutcomes();
	void setOutcome(int pos, int outcome);
	int getPoints();
	void resetGame();
	void addPoints(int points);
};
