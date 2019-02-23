#include "php_multisearch.h"
#include "extension_api/needle.h"
#include "extension_api/search_hit.h"
#include "extension_api/needles_bundle.h"
#include "extension_api/bundles_loader.h"
#include "extension_api/multisearch_exception.h"


PHP_MINIT_FUNCTION(multisearch)
{
	multisearch_register_class_needle();
	multisearch_register_class_search_hit();
	multisearch_register_class_needles_bundle();
	multisearch_register_class_bundles_loader();
	multisearch_register_class_exception();

	return SUCCESS;
}



zend_module_entry multisearch_module_entry = {
    STANDARD_MODULE_HEADER,
    PHP_MULTISEARCH_EXTNAME,
    NULL,
    PHP_MINIT(multisearch),
    NULL,
    NULL,
    NULL,
    NULL,
    PHP_MULTISEARCH_VERSION,
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_MULTISEARCH
extern "C" {
	ZEND_GET_MODULE(multisearch)
}
#endif

