#include "needles_bundle_loader_interface.h"
#include "common.h"

zend_class_entry *multisearch_ce_needles_bundle_loader_interface;


ZEND_BEGIN_ARG_INFO_EX(arginfo_loadFromFile, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, filepath, IS_STRING, 0)
ZEND_END_ARG_INFO()


static zend_function_entry needles_bundle_loader_interface_functions[] = {
	PHP_ABSTRACT_ME(NeedlesBundleLoaderInterface, loadFromFile, arginfo_loadFromFile)
	PHP_FE_END
};


void multisearch_register_needles_bundle_loader_interface()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, ZEND_NS_NAME(MULTISEARCH_NS, "NeedlesBundleLoaderInterface"), needles_bundle_loader_interface_functions);

	multisearch_ce_needles_bundle_loader_interface = zend_register_internal_interface(&tmp_ce TSRMLS_CC);
}
