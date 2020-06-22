#include "User.h"

User::User(string username, int currentScore, int highScore, vector<int> currentOutcomes) {
	this->username = username;

	LeaderboardData leaderboardData;
	leaderboardData.username = username;
	leaderboardData.highScore = highScore;

	this->leaderboardData = leaderboardData;
	this->currentOutcomes = currentOutcomes;
	this->currentScore = currentScore;

}

string User::getUsername() {
	return this->username;
}

LeaderboardData User::getLeaderboardData() {
	return this->leaderboardData;
}

vector<int> User::getCurrentOutcomes() {
	return this->currentOutcomes;
}

void User::setOutcome(int pos, int outcome) {
	if (pos >= this->currentOutcomes.size()) return;

	this->currentOutcomes[pos] = outcome;
}

int User::getPoints() {
	return this->currentScore;
}

void User::resetGame() {
	this->currentScore = 0;

	for (int i = 0; i < this->currentOutcomes.size(); i++)
		this->currentOutcomes[i] = -1;
}

void User::addPoints(int points) {
	this->currentScore += points;
}


