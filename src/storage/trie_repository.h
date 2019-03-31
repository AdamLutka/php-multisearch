#ifndef MULTISEARCH_NEEDLES_BUNDLE_LOADER_H
#define MULTISEARCH_NEEDLES_BUNDLE_LOADER_H

extern "C" {
	#include "php.h"
}

#include "../trie.h"

#include <string>
#include <ctime>
#include <sys/stat.h>


namespace multisearch
{
	namespace storage
	{
		namespace trie_repository
		{
			using file_identifier = std::pair<dev_t, ino_t>;

			struct file_info
			{
				file_identifier identifier;
				time_t modified;

				operator bool()
				{
					return identifier.first > 0 && identifier.second > 0 && modified > 0;
				}
			};


			file_info get_file_info(const std::string& filepath);

			trie_ptr get_trie(const std::string& identifier, std::time_t validityStamp = 0);
			void set_trie(const std::string& identifier, trie_ptr trie, std::time_t validityStamp = 0);
			void set_trie(const file_identifier& identifier, trie_ptr trie, std::time_t validityStamp = 0);

			bool remove_trie(const std::string& identifier);

		}
	}
}

#endif
