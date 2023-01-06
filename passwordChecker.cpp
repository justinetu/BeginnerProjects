#include <iostream>
#include <string>
#include <regex>

// The dot in front of the characters means that any character can appear before it. It doesn't matter how many times it appears

class shortpass {};
class noNumbers{};
class noUppercase{};
class noLowercase{};
class noSpecialChars{};

bool isLongEnough(std::string s) {
	if (s.length() >= 8)
		return true;
	return false;
}

int main() {
	// Password must meet a few requirements.
	std::string password;
	std::string lowercase = "(?=.*[a-z])";
	std::string upperCase = "(?=.*[A-Z])";
	std::string specialCharacters = "(?=.*[!@#$%^&*()_+])";
	std::string numbers = "(?=.*[0-9])";
	const int PASSWORD_LENGTH = 8;
	std::string lowercaseRegexPattern = lowercase;
	std::string upperCaseRegexPattern = upperCase;
	std::string specialCharsRegexPattern = specialCharacters;
	std::string numbersRegexPattern = numbers;

	// Contains at least a lowercase character
	std::regex first_regexRule(lowercaseRegexPattern);

	// Contains at least an uppercase character
	std::regex second_regexRule(upperCaseRegexPattern);

	// Contains at least 1 special character
	std::regex third_regexRule(specialCharsRegexPattern);

	// Contains at least 1 number
	std::regex fourth_regexRule(numbersRegexPattern);

	std::cout << "Choose password\n" << "\n" << "-At least one letter and one number\n"
		<< "-At least 8 characters and no spaces\n" << "-At least one special character\n"
		<< "-At least one lowercase character\n" << "-At least one uppercase character\n";

	bool isValidLowercase, isValidUppercase, isValidSpecialChars, isValidNumbers;
	bool passwordCreated = false;

	std::cout << "\nEnter your password >> ";

	std::cin >> password;

	while (passwordCreated == false) {
		try {
			isValidLowercase = regex_search(password, first_regexRule);
			if (!isValidLowercase)
				throw noLowercase();
		}
		catch (noLowercase) {
			std::cout << "Error. Password must contain at least one lowercase character\n";
		}
		try {
			bool validLength = isLongEnough(password);
			if(!validLength)
				throw shortpass();
		}
		catch (shortpass) {
			std::cout << "Error. Password must be at least " << PASSWORD_LENGTH << " characters.\n";
		}
		try {
			isValidUppercase = regex_search(password, second_regexRule);
			if (!isValidUppercase)
				throw noUppercase();
		}
		catch (noUppercase) {
			std::cout << "Error. Password must contain at least one upper case character.\n";
		}
		try {
			isValidSpecialChars = regex_search(password, third_regexRule);
			if (!isValidSpecialChars)
				throw noSpecialChars();
		}
		catch (noSpecialChars) {
			std::cout << "Error. Password must contain at least one special character\n";
		}
		try {
			isValidNumbers = regex_search(password, fourth_regexRule);
			if (!isValidNumbers)
				throw noNumbers();
		}
		catch (noNumbers) {
			std::cout << "Error. Password must contain at least 1 number\n";
		}
		if (isValidLowercase && isValidUppercase && isValidNumbers && isValidSpecialChars) {
		std::cout << "\nPassword successfully created.";
		break;
		}
		else {
			std::cout << "\n" << "Try again. Enter your password >> ";
			std::cin >> password;
		}
	}

}