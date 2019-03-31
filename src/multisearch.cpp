#include "php_multisearch.h"
#include "extension_api/needle.h"
#include "extension_api/search_hit.h"
#include "extension_api/needles_bundle.h"
#include "extension_api/needles_bundle_loader.h"
#include "extension_api/memory_persistent_storage.h"
#include "extension_api/multisearch_exception.h"

#include <sstream>


std::vector<std::string> ini_parse_array(const std::string& value)
{
	std::vector<std::string> result;
	std::istringstream stream(value);
	std::string part;

	while (std::getline(stream, part, ' '))
	{
		if (!part.empty())
		{
			result.push_back(part);
		}
	}

	return std::move(result);
}


PHP_INI_BEGIN()
	PHP_INI_ENTRY("multisearch.needles.preload", "", PHP_INI_PERDIR, NULL)
PHP_INI_END()


PHP_MINIT_FUNCTION(multisearch)
{
	REGISTER_INI_ENTRIES();

	char preload_key[] = "multisearch.needles.preload";

	multisearch_register_class_needle();
	multisearch_register_class_search_hit();
	multisearch_register_class_needles_bundle();
	multisearch_register_class_needles_bundle_loader();
	multisearch_register_class_memory_persistent_storage(ini_parse_array(INI_STR(preload_key)));
	multisearch_register_class_exception();

	return SUCCESS;
}

PHP_MINFO_FUNCTION(multisearch)
{
	DISPLAY_INI_ENTRIES();
}

PHP_MSHUTDOWN_FUNCTION(multisearch)
{
	UNREGISTER_INI_ENTRIES();

	return SUCCESS;
}


zend_module_entry multisearch_module_entry = {
	STANDARD_MODULE_HEADER,
	PHP_MULTISEARCH_EXTNAME,
	NULL,
	PHP_MINIT(multisearch),
	PHP_MSHUTDOWN(multisearch),
	NULL,
	NULL,
	PHP_MINFO(multisearch),
	PHP_MULTISEARCH_VERSION,
	STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_MULTISEARCH
extern "C" {
	ZEND_GET_MODULE(multisearch)
}
#endif

