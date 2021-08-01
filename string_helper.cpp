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

	// Returns the starting index of the pattern in the string,
	// else returns string::npos
	size_t kmp(const std::string& text, const std::string& pattern) {
		if (text.empty() or text.length() < pattern.length())
			return std::string::npos;
		if (pattern.empty()) return 0;
		// Compute vector to maintain size of suffix which is same as prefix
		std::vector<int> lps(pattern.length(), 0);
		size_t index = 0;
		for (size_t j = 1; j < pattern.length();) {
			if (pattern.at(index) == pattern.at(j)) {
				lps[j] = index + 1;
				++index;
				++j;
			} else {
				if (index != 0) {
					index = lps[index - 1];
				} else {
					lps[j] = 0;
					++j;
				}
			}
		}

		// Do the actual mattern matching using the computed array
		size_t index_text = 0, index_pattern = 0;
		while (index_text < text.length() and
			   index_pattern < pattern.length()) {
			if (text.at(index_text) == pattern.at(index_pattern)) {
				++index_pattern;
				++index_text;
			} else {
				if (index_pattern != 0) {
					index_pattern = lps.at(index_pattern - 1);
				} else {
					index_text++;
				}
			}
			if (index_pattern == pattern.length())
				return index_text - pattern.size();
		}
		return std::string::npos;
	}
}  // namespace string_helper