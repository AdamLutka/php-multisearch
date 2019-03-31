#include "trie_repository.h"

#include <map>
#include <sstream>

using trie_ptr = multisearch::trie_ptr;
using file_info = multisearch::storage::trie_repository::file_info;

std::map<std::string, std::pair<trie_ptr, std::time_t>> tries;


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

trie_ptr multisearch::storage::trie_repository::get_trie(const std::string& identifier, std::time_t validityStamp)
{
	auto it = tries.find(identifier);
	return it == tries.end() || it->second.second < validityStamp ? nullptr : it->second.first;
}

void multisearch::storage::trie_repository::set_trie(const std::string& identifier, trie_ptr trie, std::time_t validityStamp)
{
	tries[identifier] = std::make_pair(trie, validityStamp);
}

void multisearch::storage::trie_repository::set_trie(const file_identifier& identifier, trie_ptr trie, std::time_t validityStamp)
{
	std::stringstream ss;
	ss << identifier.first << '-' << identifier.second;
	multisearch::storage::trie_repository::set_trie(ss.str(), trie, validityStamp);
}


bool multisearch::storage::trie_repository::remove_trie(const std::string& identifier)
{
	return tries.erase(identifier) > 0;
}