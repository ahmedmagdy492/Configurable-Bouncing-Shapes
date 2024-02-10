#pragma once

#include <iostream>
#include <vector>
#include <sstream>

class Utils {
public:
	template<typename Base, typename T>
	static inline bool instanceof(const T* ptr) {
		return dynamic_cast<const Base*>(ptr) != nullptr;
	}

	static bool ContainsDigitsOnly(std::string str) {
		for (char c : str) {
			if (c != '-' && !std::isdigit(c)) {
				return false;
			}
		}

		return true;
	}

	/// <summary>
	/// Checks whether a given num is in the given range inclusive or not
	/// </summary>
	/// <param name="num"></param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	static bool IsNumberInRange(int num, int start, int end) {
		return num >= start && num <= end;
	}

	static std::vector<std::string>* SplitString(const std::string& str) {
		std::string token;
		std::stringstream line(str);
		std::vector<std::string>* words = new std::vector<std::string>();

		while (std::getline(line, token, ' ')) {
			words->push_back(token);
		}

		return words;
	}
};