#include "trie_file_loader.h"

#include <fstream>
#include <memory>


multisearch::trie_ptr multisearch::storage::load_trie(std::string filepath)
{
	std::ifstream file(filepath);
	if (!file.is_open())
	{
		return nullptr;
	}

	auto trie = std::make_shared<multisearch::trie>();

	std::string line;
	while (std::getline(file, line))
	{
		if (line.empty())
		{
			continue;
		}

		std::size_t s, d, separator_index = std::string::npos;
		for (s = 0, d = 0; s < line.size() && d < line.size(); ++s, ++d)
		{
			if (line[s] == '\t' && separator_index == std::string::npos)
			{
				separator_index = d;
			}

			if (line[s] == '\\' && line[s + 1] == 't')
			{
				line[d] = '\t';
				++s;
			}
			else if (line[s] == '\\' && line[s + 1] == 'n')
			{
				line[d] = '\n';
				++s;
			}
			else if (d != s)
			{
				line[d] = line[s];
			}
		}

		line.resize(d);

		std::string value;
		if (separator_index != std::string::npos)
		{
			value = line.substr(separator_index + 1);
			line.resize(separator_index);
		}

		trie->insert(line, value);
	}

	return trie;
}
