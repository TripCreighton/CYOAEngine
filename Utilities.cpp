#include "Utilities.h"
#include "User.h"

vector<string> Utilities::split(string input, char delimiter) {
	vector<string> result;
	string tempWord;

	for (int i = 0; i < input.length(); i++) {
		if (input[i] == ',') {
			result.push_back(tempWord);
			tempWord = "";

			continue;
		}

		tempWord += input[i];
	}
	result.push_back(tempWord);


	return result;
}

string Utilities::arrayToString(vector<int> input) {
	string result;

	for (int i = 0; i < input.size(); i++) {
		if (i == input.size() - 1) {
			result += to_string(input[i]);
			break;
		}

		result += to_string(input[i]) + ",";
	}

	return result;
}

string Utilities::toLower(string input) {
	string result;

	for (auto c : input)
		result += tolower(c);

	return result;
}
