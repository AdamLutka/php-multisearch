#include "needles_bundle_storage_interface.h"
#include "common.h"


zend_class_entry *multisearch_ce_needles_bundle_storage_interface;


MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_setNeedlesBundle, 0, 2, IS_VOID, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	MULTISEARCH_ARG_OBJ_INFO(0, needlesBundle, MULTISEARCH_CLASSNAME(NeedlesBundle), 0)
	MULTISEARCH_ARG_TYPE_INFO(0, validityStamp, IS_LONG, 0)
MULTISEARCH_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_getNeedlesBundle, 0, 1, MULTISEARCH_CLASSNAME(NeedlesBundle), 0)
	MULTISEARCH_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, validityStamp, IS_LONG, 0)
MULTISEARCH_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_hasNeedlesBundle, 0, 1, _IS_BOOL, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, name, IS_STRING, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, validityStamp, IS_LONG, 0)
MULTISEARCH_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_removeNeedlesBundle, 0, 1, IS_VOID, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, name, IS_STRING, 0)
MULTISEARCH_END_ARG_INFO()


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
	INIT_CLASS_ENTRY(tmp_ce, MULTISEARCH_CLASSNAME_STR(NeedlesBundleStorageInterface), needles_bundle_storage_interface_functions);

	multisearch_ce_needles_bundle_storage_interface = zend_register_internal_interface(&tmp_ce TSRMLS_CC);
}
