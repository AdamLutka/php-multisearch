#include "trie_repository.h"

#include <map>

using trie_ptr = multisearch::trie_ptr;
using file_info = multisearch::storage::trie_repository::file_info;
using file_identifier = multisearch::storage::trie_repository::file_identifier;

std::map<file_identifier, std::pair<trie_ptr, std::time_t>> tries;


file_info multisearch::storage::trie_repository::get_file_info(const std::string& filepath)
{
	file_info info;
	struct stat result;

	if (stat(filepath.c_str(), &result) == 0)
	{
		info.identifier = file_identifier(result.st_dev, result.st_ino);
		info.modified = result.st_mtime;
	}
	else
	{
		info.identifier = file_identifier(0, 0);
		info.modified = 0;
	}

	return info;
}

trie_ptr multisearch::storage::trie_repository::get_trie(const file_identifier& identifier, std::time_t validityStamp)
{
	auto it = tries.find(identifier);
	return it == tries.end() || it->second.second < validityStamp ? nullptr : it->second.first;
}

void multisearch::storage::trie_repository::set_trie(const file_identifier& identifier, trie_ptr trie, std::time_t validityStamp)
{
	tries[identifier] = std::make_pair(trie, validityStamp);
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