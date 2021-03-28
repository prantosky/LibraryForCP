#include <algorithm>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

namespace string_helper {
	std::vector<std::string> split(const std::string& str,
								   const char separator) {
		std::vector<std::string> results;
		std::stringstream iss(str);
		std::string token;
		while (std::getline(iss, token, separator)) {
			if (not token.empty()) results.push_back(token);
			token = "";
		}
		return results;
	}

	std::vector<std::string> regexSplit(const std::string& str,
										const std::regex& pattern) {
		std::vector<std::string> results;
		std::copy(
			std::sregex_token_iterator(str.begin(), str.end(), pattern, -1),
			std::sregex_token_iterator(), std::back_inserter(results));
		return results;
	}
	// check whether string s is subsequqence of string t or not
	bool isSubsequence(const std::string& s, const std::string& t) {
		int i = 0;
		int j = 0;
		int found = 0;
		while (i < s.size() && j < t.size()) {
			if (s[i] == t[j]) {
				found++;
				i++;
				j++;
			} else {
				j++;
			}
		}
		if (found == s.size()) {
			return true;
		} else {
			return false;
		}
	}
}  // namespace string_helper