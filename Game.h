#include "Utilities.h"
#include "User.h"

class Outcome;
class Stage;
class Game;

class Outcome {
private:
	int pointValue;
	int outcomeStage;
public:
	/*
	 - Sets point and outcome stage values
	*/
	Outcome(int pointValue, int outcomeStage);
	
	/*
	 - Returns the current point value for this outcome.

	 - Type: Integer
	 - Params: N/A
	 */
	int getPointValue();

	/*
	 - Returns the outcome stage for this outcome.

	 - Type: Integer
	 - Params: N/A
	 */
	int getOutcomeStage();

	/*
	 - A set function for the point value.

	 - Type: Void
	 - Params:
	  - pointValue - The new point value to set the current point value to.
	 */
	void setPointValue(int pointValue);
};

class Stage {
private:
	string promptText;
	vector<string> options;
	vector<Outcome> outcomes;
public:
	/*
	 - Default constructor
	*/
	Stage();
	
	/*
	 - Sets all parameters to associated variables
	*/
	Stage(string promptText, vector<string> options, vector<Outcome> outcomes);

	/*
	 - A setter for the prompt

	 - Type: Void
	 - Params: N/A
	 */
	void setPrompt(string prompt);

	/*
	 - Adds an option to the stage

	 - Type: Void
	 - Params:
	  - option - The option to add.
	 */
	void addOption(string option);

	/*
	 - Adds an outcome to the stage

	 - Type: Void
	 - Params:
	  - value - The point value
	  - outcomeStage - The outcome stage
	 */
	void addOutcome(int value, int outcomeStage);

	/*
	 - A getter for the specified outcome

	 - Type: Outcome
	 - Params:
	  - i - The outcome id
	 */
	Outcome getOutcome(int i);

	/*
	 - A getter for all of the outcomes

	 - Type: Vector of type Outcome
	 - Params: N/A
	 */
	vector<Outcome> getOutcomes();

	/*
	 - A getter for the prompt

	 - Type: String
	 - Params: N/A
	 */
	string getPrompt();

	/*
	 - A getter for all of the options.

	 - Type: Vector of type String
	 - Params: N/A
	 */
	vector<string> getOptions();
};

class Game
{
private:
	vector<User> users;
	vector<Stage> stages;

public:
	/*
	 - Adds all stages programatically
	 - Reads and parses all users in the user_data.txt file
	 */
	Game();

	/*
	 - Advances the stage by one based on the users decision

	 - Type: Void
	 - Params:
	  - username - The username of the user to advance.
	 */
	void advanceStage(string username);

	/*
	 - Wrapper for adding stages in a clean way (only used within the constructor)

	 - Type: Void
	 - Params:
	  - prompt - The prompt for the user to follow and decide on
	  - options - The options to user is presented with
	  - outcomes - The outcomes which are index-associated with the options parameterf
	 */
	void addStage(string prompt, vector<string> options, vector<Outcome> outcomes);

	/*
	 - Returns the leaderboard data for a specific user

	 - Type: LeaderboardData
	 - Params:
	  - username - The username of the user to get leaderboard data for
	 */
	LeaderboardData getUserLeaderboardData(string username);

	/*
	 - Saves all users data synchronously 

	 - Type: Void
	 - Params: N/A
	 */
	void saveUserData();

	/*
	 - Deletes all users synchronously

	 - Type: Void
	 - Params: N/A
	 */
	void deleteAllUsers();

	/*
	 - Adds a user to the user table and returns the success state

	 - Type: Bool 
	 - Params:
	  - username - The username of the user to add.
	 */
	bool addUser(string username);

	/*
	 - Returns whether the user exists

	 - Type: Bool
	 - Params:
	  - username - The username of the user to search for.
	 */
	bool doesUserExist(string username);

	/*
	 - Returns a reference to the user object (in memory), if the user does not exist a nullptr is returned.

	 - Type: User* (Pointer)
	 - Params:
	  - username - The username of the user to search for.
	 */
	User* getUser(string username);

	/*
	 - A wrapper to set the users outcome without having to directly modify the user table via a reference. Returns true or false based on success.

	 - Type: Bool
	 - Params:
	  - username - The username of the user to advance.
	  - pos - The index of the stage.
	  - outcome - The chosen outcome
	 */
	bool setUserOutcome(string username, int pos, int outcome);

	/*
	 - Returns a sorted (ascending) list of users based on their highscores.

	 - Type: Vector of type User
	 - Params: N/A
	 */
	vector<User> getSortedUsers();
};
