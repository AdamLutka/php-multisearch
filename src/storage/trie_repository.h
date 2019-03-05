#ifndef MULTISEARCH_NEEDLES_BUNDLE_LOADER_H
#define MULTISEARCH_NEEDLES_BUNDLE_LOADER_H

extern "C" {
	#include "php.h"
}

#include "../trie.h"

#include <string>
#include <ctime>


namespace multisearch
{
	namespace storage
	{
		namespace trie_repository
		{
			
			std::time_t get_modified_time(const std::string& filepath);
			std::string canonicalize_filepath(const std::string& filepath);

			trie_ptr get_trie(const std::string& key, std::time_t validityStamp = 0);
			void set_trie(const std::string& key, trie_ptr trie, std::time_t validityStamp = 0);

		}
	}
}

#endif
