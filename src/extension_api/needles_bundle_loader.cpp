#include "needles_bundle_loader.h"
#include "common.h"
#include "needles_bundle.h"
#include "multisearch_exception.h"
#include "../storage/trie_file_loader.h"

#include "zend_exceptions.h"


zend_class_entry *multisearch_ce_needles_bundle_loader;


ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_loadFromFile, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, filepath, IS_STRING, 0)
ZEND_END_ARG_INFO()


PHP_METHOD(NeedlesBundleLoader, __construct)
{
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();
}

PHP_METHOD(NeedlesBundleLoader, loadFromFile)
{
	char *fp;
	size_t fp_len;
	
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(fp, fp_len)
	ZEND_PARSE_PARAMETERS_END();
	

	std::string filepath(fp, fp_len);

	auto trie = multisearch::storage::load_trie(filepath);
	if (!trie)
	{
		zend_throw_exception_ex(multisearch_ce_exception, 0, "File cannot be open: %s", filepath.c_str());
		return;
	}

	multisearch_needles_bundle_init(return_value, trie);
}

static zend_function_entry needles_bundle_loader_functions[] = {
	PHP_ME(NeedlesBundleLoader, __construct, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_ME(NeedlesBundleLoader, loadFromFile, arginfo_loadFromFile, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_needles_bundle_loader()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, ZEND_NS_NAME(MULTISEARCH_NS, "NeedlesBundleLoader"), needles_bundle_loader_functions);

	multisearch_ce_needles_bundle_loader = zend_register_internal_class(&tmp_ce TSRMLS_CC);
}
