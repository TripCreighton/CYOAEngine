#include "Game.h"

Game::Game() {
	this->addStage("You wake up in the middle of the kitchen", {
			"Go to the stove", "Leave the house"
		}, {
			Outcome(3, 1), Outcome(3, 7)
		});

	this->addStage("You are at the stove.", { "Cook pasta", "Cook rice" }, { Outcome(3, 2), Outcome(2, 2) });
	
	this->addStage("You notice the water is boiling over.", { "Turn down stove", "Pour the boiling water on the floor" }, {Outcome(3, 3), Outcome(-1, 4)});

	this->addStage("You succesfully prepared your meal!", { "Enjoy the meal", "Dump into trash can" }, {Outcome(4, 5), Outcome(-1, 4)});

	this->addStage("You starved and have lost!\n\nTotal score: %i\n", {}, {});

	this->addStage("You feel nourished and have a lot of energy!", { "Take a nap", "Leave the house" }, {Outcome(5, 6), Outcome(2, 7)}); 

	this->addStage("You settle in for a long nap!\n\nTotal score: %i\n ", {}, {});

	this->addStage("You are outside the house.", { "Go to the cellar", "Take a walk in the woods" }, {Outcome(3, 9), Outcome(1, 8)}); 

	this->addStage("While on your walk in the woods, you get eaten by a bear.\n\nTotal score: %i\n", {}, {});

	this->addStage("You enter the cellar of the house.", { "Check the wine rack", "Check mysterious closet" }, {Outcome(3, 10), Outcome(-1, 11)});

	this->addStage("You find two extremely potent bottles of chardonnay and sauvignon.", { "Drink the chardonnay", "Drink the sauvignon" }, {Outcome(1, 13), Outcome(1, 12)});

	this->addStage("You open up the mysterious closet and are immediately attacked by a skeleton.\n\nTotal score: %i\n", {}, {});

	this->addStage("You drink the sauvignon, realize its poisoned, and instantly black out.", {}, { Outcome(0, 0) });

	this->addStage("You drink the chardonnay, next thing you know you're sitting on the ground outside.\n\nTotal score: %i\n", {}, {});

	// Parse user data:
	ifstream iFileStream;
	iFileStream.open("user_data.txt");

	string tempLine;
	while (getline(iFileStream, tempLine)) {
		if (tempLine == "") continue;

		vector<string> splitData = Utilities::split(tempLine, ',');

		if (splitData.size() >= 2) {
			vector<int> tempValues;
			int currentScore = 0;

			// Parse outcome data:
			for (int count = 2; count < splitData.size(); count++) {
				int parsedOutcome = stoi(splitData[count]);

				// Parse the users current score based on their chosen outcomes:
				if (parsedOutcome != -1 && parsedOutcome - 1 >= 0)
					currentScore += this->stages[count - 2].getOutcome(parsedOutcome - 1).getPointValue();

				tempValues.push_back(parsedOutcome);
			}

			this->users.push_back(User(splitData[0], currentScore, stoi(splitData[1]), tempValues));
		}
	}
	iFileStream.close();
	
}

void Game::advanceStage(string username) {
	if (!this->doesUserExist(username)) return;

	auto user = this->getUser(username);

	// Determine the most recent stage:
	Stage currentStage;
	int stageIndex = 0;
	
	if (user->getCurrentOutcomes()[0] == -1) {
		currentStage = this->stages[0];
	} else {
		int index = 0;
		while (true) {
			int currentOutcome = user->getCurrentOutcomes()[index];
		
			if (currentOutcome != -1) {
				index = this->stages[index].getOutcome(currentOutcome - 1).getOutcomeStage();

			} else {
				currentStage = this->stages[index];
				stageIndex = index;

				break;
			}
		}
	}

	// Verify the stage is not an endgame stage:
	if (currentStage.getOptions().size() == 0) {
		// Check if the endgame stage adds points:
		if (currentStage.getOutcomes().size() > 0) {
			int pointValue = currentStage.getOutcome(0).getPointValue();

			if (pointValue < 0) {
				cout << "You have lost " << pointValue << " points!" << endl;
			} else {
				cout << "You have gained " << pointValue << " points!" << endl;
			}

			this->setUserOutcome(username, stageIndex, 0);
			user->addPoints(pointValue);
		}
		
		printf(currentStage.getPrompt().data(), user->getPoints());

		this->saveUserData();

		cout << "Would you like to restart your game? (Y/N): ";
		string response;
		 
		cin >> response;

		if (Utilities::toLower(response) == "y") {
			user->resetGame();

			this->advanceStage(username);
		}

		return;
	}

	cout << currentStage.getPrompt() << endl;

	// List all available options:
	for (int i = 0; i < currentStage.getOptions().size(); i++)
		cout << i + 1 << ") " << currentStage.getOptions()[i] << endl;
	cout << currentStage.getOptions().size() + 1 << ") Save & quit to main menu." << endl << endl;

	cout << "Choice: ";
	int choice = 0;

	cin >> choice;

	// Verify the choice is valid:
	if (cin.fail() || choice < 1 || choice > currentStage.getOptions().size() + 1) {
		cin.clear();
		cin.ignore(1024 * 10, '\n');

		cout << "\nInvalid choice!\n" << endl;
		this->advanceStage(username);
		
		return;
	}

	// If the user chooses quit, save and go to main menu:
	if (choice == currentStage.getOptions().size() + 1) {
		this->saveUserData();
		cout << "Your game has been saved! Thank you for playing!" << endl << endl;

		return;
	}

	// Calculate the points they earned:
	Outcome outcome = currentStage.getOutcome(choice - 1);
	int pointValue = outcome.getPointValue();

	if (pointValue == 0) {
		pointValue = -1 * user->getPoints();
	} else if (pointValue < 0) {
		cout << "You have lost " << pointValue << " points!" << endl;
	} else {	
		cout << "You have gained " << pointValue << " points!" << endl;
	}

	// Set the outcome:
	this->setUserOutcome(username, stageIndex, choice);
	user->addPoints(pointValue);
	
	cout << "You now have " << user->getPoints() << " points!" << endl;
	cout << endl;

	// Recursively advance the stage:
	this->advanceStage(username);
}

void Game::addStage(string prompt, vector<string> options, vector<Outcome> outcomes) {
	this->stages.push_back(Stage(prompt, options, outcomes));
}

LeaderboardData Game::getUserLeaderboardData(string username) {
	for (User user : this->users) {
		if (user.getUsername() == Utilities::toLower(username)) {
			return user.getLeaderboardData();
		}
	}

	// Return empty if nothing exists:
	return LeaderboardData();
}

void Game::saveUserData() {
	ofstream fileStream("user_data.txt");

	// Save all users (all though this isnt efficient in anyway, for the amount of users its fine):
	for (auto user : this->users) 
		fileStream << user.getUsername() + "," + to_string(user.getLeaderboardData().highScore < user.getPoints() ? user.getPoints() : user.getLeaderboardData().highScore) + "," + Utilities::arrayToString(user.getCurrentOutcomes()) + "\n";
}

void Game::deleteAllUsers() {
	ofstream fileStream("user_data.txt", std::ios_base::out);

	fileStream << "";
}

bool Game::addUser(string username) {
	// Check if the user exists:
	if (this->doesUserExist(username)) return false;

	vector<int> tempVector;
	for (int count = 0; count < this->stages.size(); count++)
		tempVector.push_back(-1);

	User user(Utilities::toLower(username), 0, 0, tempVector);
	this->users.push_back(user);

	ofstream fileStream("user_data.txt", ios_base::app | ios_base::out);
	
	fileStream << user.getUsername() + "," + to_string(user.getLeaderboardData().highScore) + "," + Utilities::arrayToString(tempVector) + "\n";

	fileStream.close();

	return true;
}

bool Game::doesUserExist(string username) {
	for (int i = 0; i < this->users.size(); i++)
		if (this->users[i].getUsername() == Utilities::toLower(username)) 
			return true;

	return false;
}

User* Game::getUser(string username) {
	// Find the user and pass it by reference:
	for (int i = 0; i < this->users.size(); i++)
		if (this->users[i].getUsername() == Utilities::toLower(username)) 
			return &this->users[i];

	return nullptr;
}

bool Game::setUserOutcome(string username, int pos, int outcome) {
	auto user = this->getUser(username);

	// Verify the user exists:
	if (!this->doesUserExist(username)) return false;

	// Verify the stage exists:
	if (pos < 0 || pos >= this->stages.size())
		return false;

	// Verify the selected outcome is not greater than the available outcomes:
	if (outcome < 0 || outcome > this->stages[pos].getOutcomes().size())
		return false;

	user->setOutcome(pos, outcome);

	return true;
}

vector<User> Game::getSortedUsers() {
	vector<User> fixedUsers = this->users;

	for (int i = 0; i < fixedUsers.size(); i++) {
		for (int l = 0; l < fixedUsers.size(); l++) {
			if (i != l && fixedUsers[i].getLeaderboardData().highScore > fixedUsers[l].getLeaderboardData().highScore) {
				User temp = fixedUsers[i];;

				fixedUsers[i] = fixedUsers[l];
				fixedUsers[l] = temp;
			}
		}
	}

	return fixedUsers;
}

Stage::Stage() { }

Stage::Stage(string promptText, vector<string> options, vector<Outcome> outcomes) {
	this->promptText = promptText;
	this->options = options;
	this->outcomes = outcomes;
}

void Stage::setPrompt(string prompt) {
	this->promptText = prompt;
}

void Stage::addOption(string option) {
	this->options.push_back(option);
}

void Stage::addOutcome(int value, int outcomeStage) {
	this->outcomes.push_back(Outcome(value, outcomeStage));
}

Outcome Stage::getOutcome(int i) {
	return this->outcomes[i];
}

vector<Outcome> Stage::getOutcomes() {
	return this->outcomes;
}

string Stage::getPrompt() {
	return this->promptText;
}

vector<string> Stage::getOptions() {
	return this->options;
}

Outcome::Outcome(int pointValue, int outcomeStage) {
	this->pointValue = pointValue;
	this->outcomeStage = outcomeStage;
}

int Outcome::getPointValue() {
	return pointValue;
}

int Outcome::getOutcomeStage() {
	return outcomeStage;
}

void Outcome::setPointValue(int pointValue) {
	this->pointValue = pointValue;
}