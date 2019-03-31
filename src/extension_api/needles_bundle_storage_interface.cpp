#include "needles_bundle_storage_interface.h"
#include "common.h"


zend_class_entry *multisearch_ce_needles_bundle_storage_interface;


ZEND_BEGIN_ARG_INFO_EX(arginfo_setNeedlesBundle, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	MULTISEARCH_ARG_OBJ_INFO(0, needlesBundle, NeedlesBundle, 0)
	ZEND_ARG_TYPE_INFO(0, validityStamp, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_getNeedlesBundle, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, validityStamp, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_hasNeedlesBundle, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, validityStamp, IS_LONG, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_removeNeedlesBundle, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, name, IS_STRING, 0)
ZEND_END_ARG_INFO()


static zend_function_entry needles_bundle_storage_interface_functions[] = {
	PHP_ABSTRACT_ME(NeedlesBundleStorageInterface, setNeedlesBundle, arginfo_setNeedlesBundle)
	PHP_ABSTRACT_ME(NeedlesBundleStorageInterface, getNeedlesBundle, arginfo_getNeedlesBundle)
	PHP_ABSTRACT_ME(NeedlesBundleStorageInterface, hasNeedlesBundle, arginfo_hasNeedlesBundle)
	PHP_ABSTRACT_ME(NeedlesBundleStorageInterface, removeNeedlesBundle, arginfo_removeNeedlesBundle)
	PHP_FE_END
};


void multisearch_register_needles_bundle_storage_interface()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, ZEND_NS_NAME(MULTISEARCH_NS, "NeedlesBundleStorageInterface"), needles_bundle_storage_interface_functions);

	multisearch_ce_needles_bundle_storage_interface = zend_register_internal_class(&tmp_ce TSRMLS_CC);
}
