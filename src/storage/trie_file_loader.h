#ifndef MULTISEARCH_TRIE_FILE_LOADER_H
#define MULTISEARCH_TRIE_FILE_LOADER_H

#include "../trie.h"

#include <string>

namespace multisearch
{
	namespace storage
	{
		trie_ptr load_trie(std::string filepath);
	}
}

#endif
