#include "aho_corasick/aho_corasick.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <list>

namespace ac = aho_corasick;
using trie = ac::trie;

std::list<trie::emit_collection> get_matches(std::vector<string> blocks, bool stop_at_full, trie& t, trie& tr) {
	std::list<trie::emit_collection> matches;
	for (auto& block : blocks) {
		trie::emit_collection block_matches;
		t.parse_text(block, stop_at_full, block_matches);
		tr.parse_reverse_text(block, stop_at_full, block_matches);
		matches.push_back(block_matches);
	}
	return matches;
}

/* TODO
Inputs:
- std::list<string> blocks - Permutation of the blocks

- std::vector<std::vector<std::set<unsigned>>> keywords - each index correlates to one keyword and contains a vector where each index correlates to prefix
  length and contains a set of matching suffixes

- std::list<trie::emit_collection> matches - a 

void collect_matches(std::list<string> blocks, std::vector<std::vector<std::set<unsigned>>> keywords, std::list<trie::emit_collection> matches) {
    // TODO: build trie
    auto matches = get_matches(blocks, false, t, tr);
    // list of blocks, order matters cause it's a permutation
	for (const auto& block_matches : matches) {
	    // TODO: check if last element in list
	    const auto& next_block_matches = block_matches->next;
	    for (const auto& keyword : keywords) {
	        if (!(prefix_match = block_matches.find(keyword.first).second.find(PREFIX)) || 
				!(suffix_match = next_block_matches.find(keyword.first).second.find(SUFFIX)))
	            continue;
	        // Block 1 has a prefix match of this keyword and Block 2 has a suffix match of this keyword
	        if(!(full_match = keywords[keyword.first][prefix_match].find(suffix_match)))
	            continue;
	        // The pair contains a full match
	        // TODO: add this pair, and the starting position of the keyword inside the block. Currently not supported
	    }
	    
	}
}**/

int main(int argc, char** argv) {
	std::cout << "*** Aho-Corasick Keyword Search ***" << std::endl;

	cout << "Please insert your keywords - to finish enter 'finish'" << std::endl;
	std::string keyword;
	std::vector<std::string> keywords;
	std::cin >> keyword;
	while (keyword  != "finish") {
		keywords.push_back(keyword);
		std::cin >> keyword;
	}
	std::cout << "Generating trie...";
	trie t, tr;
	unsigned i = 0;
	for (auto keyword : keywords) {
		t.insert(keyword, i, false);
		reverse(keyword.begin(), keyword.end());
		tr.insert(keyword, i, true);
		i++;
	}
	std::cout << " Done" << std::endl;

	std::cout << "Please insert your blocks - to finish enter 'finish'" << std::endl;
	std::string block;
	std::vector<std::string> blocks;
	std::cin >> block;
	while (block != "finish") {
		blocks.push_back(block);
		std::cin >> block;
	}

	std::cout << "Running" << std::endl;
	auto matches = get_matches(blocks, false, t, tr);
	int j = 0;
	for (auto& block_matches : matches) {
		std::cout << "Block: " << blocks[j] << std::endl;
	    for (auto& match : block_matches) {
	        for (auto& pair : match.second) {
	            std::cout << "Keyword: " << keywords[match.first] << " match type: " << pair.first << " length: " << pair.second << std::endl;
	        }
	    }
		std::cout << "***" << std::endl;
		j++;
	}
	return 0;
}