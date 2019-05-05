#ifndef MULTISEARCH_TRIE_H
#define MULTISEARCH_TRIE_H

#include "aho_corasick/trie.hpp"

#include <string>
#include <memory>

namespace multisearch
{

	using trie = ahocorasick::Trie<std::string, std::string>;
	using trie_ptr = std::shared_ptr<trie>;

}

#endif
