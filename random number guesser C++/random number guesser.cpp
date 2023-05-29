#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

const int array_size = 4;
const int tries = 7;
int leftTries = tries;
int digits_array[array_size] = { -1 };
std::string arrayToStr;

void ResetArray() {
	for (int i = 0; i < array_size; i++) {
		digits_array[i] = -1;
	}
}

void PrintArray() {
	std::cout << "Digits array: ";
	for (int i = 0; i < array_size; i++) {
		std::cout << digits_array[i] << " ";
	}
	std::cout << "\n";
}

bool DoesContain(const int& digit) {
	for (int i = 0; i < array_size; i++) {
		if (digits_array[i] == digit)
			return true;
	}
	return false;
}

void GenerateRandomNumber() {
	int digitsIndex = 0;
	do {
		int randomDigit = (rand() % 9) + 1;
		if (DoesContain(randomDigit) == false) {
			digits_array[digitsIndex] = randomDigit;
			digitsIndex++;
		}
	} while (digitsIndex != array_size);
}

bool ContainsOnlyDigits(std::string str) {
	for (int i = 0; i < str.size(); i++) {
		if (str[i] < 48 && str[i] > 57) {
			return false;
		}
	}
	return true;
}

bool CheckIfGood(const std::string& guessNumberStr) {
	if (guessNumberStr.size() != array_size) {
		std::cout << "Marimea gresita.\n";
		return false;
	}
	if (ContainsOnlyDigits(guessNumberStr) == false) {
		std::cout << "Poti introduce doar cifre.\n";
		return false;
	}
	return true;
}

std::string ArrayToStr() {
	// Aceasta functie construeste un string din cifrele din array. ( {1,2,3,4} -> "1234" )
	std::string str;
	for (int i = 0; i < array_size; i++) {
		str += std::to_string(digits_array[i]);
	}
	return str;
}

int CalcCorrectDigits(const std::string& str) {
	int rs = 0;
	for (int i = 0; i < str.size(); i++) {
		// Ia fiecare cifra pe rand si foloseste find() ca sa o caute in arrayToStr.
		if (arrayToStr.find(str[i]) != std::string::npos) {
			rs++;
		}
	}
	return rs;
}

int CalcCorrectPosition(const std::string& str) {
	int rs = 0;
	for (int i = 0; i < str.size(); i++) {
		// Ca pozitia sa fie corect aceasta trebuie sa coincida cu i.
		if (arrayToStr.find(str[i]) == i) {
			rs++;
		}
	}
	return rs;
}

int main()
{
	srand(static_cast<unsigned int>(time(nullptr)));
	// Genereaza array-ul cu cifre random (care nu se repeta, de marimea arraySize)
	GenerateRandomNumber();
	arrayToStr = ArrayToStr();
	// Se da print la acel array general
	//PrintArray(); DEBUG
	std::string guessNumberStr("");
	bool Guessed = false;
	do {
		std::cin >> guessNumberStr;
		// Verifica ca string-ul citit de la tastatura sa ideplineasca urmatoarele conditii:
		// - sa aiba aceeasi marime ca si array-ul cu cifre.
		// - sa contina doar cifre (intre '0' si '9').
		if (CheckIfGood(guessNumberStr)) {
			leftTries--;
			std::cout << "Tries left: " << leftTries << "\n";
			int calcCorrectDigits = CalcCorrectDigits(guessNumberStr);
			int calcCorrectPositions = CalcCorrectPosition(guessNumberStr);
			std::cout << "Correct digits: " << CalcCorrectDigits(guessNumberStr) << "\n";
			std::cout << "Correct positions: " << CalcCorrectPosition(guessNumberStr) << "\n";
			if (calcCorrectPositions == 4) {
				Guessed = true;
			}
		}
		else {
			std::cout << "Bad.\n";
		}
	} while ( leftTries > 0 && !Guessed);
	if (Guessed) {
		std::cout << "You guessed it!\n";
	}
	else {
		std::cout << "L bozo.\n";
	}
}