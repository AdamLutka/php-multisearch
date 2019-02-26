#include "needles_bundle_loader.h"
#include "common.h"
#include "needles_bundle.h"
#include "multisearch_exception.h"

#include "zend_exceptions.h"

#include <cstddef>
#include <string>
#include <cstring>
#include <map>
#include <memory>
#include <fstream>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

using TriePtrT = std::shared_ptr<multisearch_needles_bundle_trie>;


zend_class_entry *multisearch_ce_needles_bundle_loader;

std::map<std::string, std::pair<TriePtrT, time_t>> bundles;


time_t getModifiedTime(const std::string& filepath)
{
	struct stat result;
	if (stat(filepath.c_str(), &result) == 0)
	{
		return result.st_mtime;
	}

	return 0;
}

bool canonicalizeFilepath(const std::string& originFilepath, std::string& canonicalizedFilepath)
{
	char *filepath = realpath(originFilepath.c_str(), nullptr);
	if (filepath)
	{
		canonicalizedFilepath = filepath;
		return true;
	}
	else
	{
		return false;
	}
}

void replaceInString(std::string& subject, const std::string& search, const std::string& replace)
{
	std::size_t pos = 0;
	while ((pos = subject.find(search, pos)) != std::string::npos)
	{
		subject.replace(pos, search.length(), replace);
		pos += replace.length();
	}
}

TriePtrT load_trie(std::string filepath)
{
	auto trie = std::make_shared<multisearch_needles_bundle_trie>();

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


ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_loadNeedlesBundle, 0, 0, 1)
	ZEND_ARG_INFO(0, filepath)
ZEND_END_ARG_INFO()


PHP_METHOD(NeedlesBundleLoader, __construct)
{
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();
}

PHP_METHOD(NeedlesBundleLoader, loadNeedlesBundle)
{
	char *fp;
	size_t fp_len;
	
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(fp, fp_len)
	ZEND_PARSE_PARAMETERS_END();
	
	std::string originFilepath(fp, fp_len);
	std::string filepath;
	if (!canonicalizeFilepath(originFilepath, filepath))
	{
		zend_throw_exception_ex(multisearch_ce_exception, 0, "Filepath (%s) cannot be resolved: %s", originFilepath.c_str(), std::strerror(errno));
		return;
	}

	auto fIt = bundles.find(filepath);
	auto modifiedTime = getModifiedTime(filepath);
	TriePtrT trie;

	if (fIt == bundles.end() || modifiedTime > fIt->second.second)
	{
		trie = load_trie(filepath);
		if (!trie)
		{
			zend_throw_exception_ex(multisearch_ce_exception, 0, "File cannot be open: %s", filepath.c_str());
			return;
		}

		bundles[filepath] = std::make_pair(trie, modifiedTime);
	}
	else
	{
		trie = fIt->second.first;
	}

	multisearch_init_needles_bundle(return_value, trie);
}

static zend_function_entry needles_bundle_loader_functions[] = {
	PHP_ME(NeedlesBundleLoader, __construct, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_ME(NeedlesBundleLoader, loadNeedlesBundle, arginfo_loadNeedlesBundle, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_needles_bundle_loader()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, ZEND_NS_NAME(MULTISEARCH_NS, "NeedlesBundleLoader"), needles_bundle_loader_functions);

	multisearch_ce_needles_bundle_loader = zend_register_internal_class(&tmp_ce TSRMLS_CC);
}
