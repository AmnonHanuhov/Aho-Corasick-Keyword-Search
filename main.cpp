#include "aho_corasick/aho_corasick.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace ac = aho_corasick;
using trie = ac::trie;

std::list<ac::emit_collection> get_matches(std::list<string> text_strings, trie& t) {
	std::list<ac::emit_collection> matches;
	for (auto& text : text_strings) {
		auto block_matches = t.parse_text(text);
		matches.push_back(block_matches);
	}
	return matches;
}

std::list<ac::emit_collection> keywords_search(std::list<std::string> keywords, std::list<std::string> blocks, bool stop_at_full, bool check_input) {
	cout << "*** Aho-Corasick keywords search ***" << endl;

	cout << "Generating trie from keywords...";
	trie tn;
	for (auto& keyword : keywords) {
		tn.insert(keyword);
	}
	cout << " done" << endl;

	cout << "Running ";
	return get_matches(blocks, tn);
}