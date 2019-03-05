#include "trie_repository.h"

#include <map>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

using trie_ptr = multisearch::trie_ptr;

std::map<std::string, std::pair<trie_ptr, std::time_t>> tries;


std::time_t multisearch::storage::trie_repository::get_modified_time(const std::string& filepath)
{
	struct stat result;
	if (stat(filepath.c_str(), &result) == 0)
	{
		return result.st_mtime;
	}

	return 0;
}

std::string multisearch::storage::trie_repository::canonicalize_filepath(const std::string& filepath)
{
	char *canonical_filepath = realpath(filepath.c_str(), nullptr);
	return canonical_filepath ? canonical_filepath : "";
}


trie_ptr multisearch::storage::trie_repository::get_trie(const std::string& key, std::time_t validityStamp)
{
	auto it = tries.find(key);
	return it == tries.end() || it->second.second < validityStamp ? nullptr : it->second.first;
}

void multisearch::storage::trie_repository::set_trie(const std::string& key, trie_ptr trie, std::time_t validityStamp)
{
	tries[key] = std::make_pair(trie, validityStamp);
}


void multisearch::storage::trie_repository::remove_trie(trie_ptr trie)
{
	for (auto it = tries.begin(); it != tries.end(); ++it)
	{
		if (it->second.first == trie)
		{
			tries.erase(it);
			break;
		}
	}
}