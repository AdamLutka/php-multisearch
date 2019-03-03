#include "trie_file_loader.h"

#include <fstream>
#include <memory>


void replaceInString(std::string& subject, const std::string& search, const std::string& replace)
{
	std::size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

multisearch::trie_ptr multisearch::storage::load_trie(std::string filepath)
{
	auto trie = std::make_shared<multisearch::trie>();

	std::ifstream file(filepath);
	if (!file.is_open())
	{
		return nullptr;
	}

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}

		auto offset = line.find('\t');
		std::string key, value;
		if (std::string::npos == offset)
		{
			key = line;
		}
		else
		{
			key = line.substr(0, offset);
			value = offset >= line.size() - 1 ? "" : line.substr(offset + 1, line.size());
		}
		
		replaceInString(key, "\\n", "\n");
		replaceInString(key, "\\t", "\t");
		replaceInString(value, "\\n", "\n");
		replaceInString(value, "\\t", "\t");

		trie->insert(key, value);
	}

	return trie;
}
