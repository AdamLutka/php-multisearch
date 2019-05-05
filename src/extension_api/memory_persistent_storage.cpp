#include "memory_persistent_storage.h"
#include "common.h"
#include "needles_bundle.h"
#include "needles_bundle_storage_interface.h"
#include "multisearch_exception.h"
#include "../storage/trie_file_loader.h"
#include "../storage/trie_repository.h"

#include "zend_exceptions.h"

#include <sstream>


using namespace multisearch::storage;

zend_object_handlers memory_persistent_storage_object_handlers;
zend_class_entry *multisearch_ce_memory_persistent_storage;


void preload(const std::vector<std::string>& filepaths)
{
	for (auto& filepath : filepaths)
	{
		if (php_check_open_basedir_ex(filepath.c_str(), 0) == 0)
		{
			auto file_info = trie_repository::get_file_info(filepath);
			if (file_info)
			{
				auto trie = load_trie(filepath);
				if (trie)
				{
					trie->search_in("");
					trie_repository::set_trie(filepath, trie, file_info.modified);
					continue;
				}
			}
			else
			{
				php_log_err(const_cast<char*>(("multisearch: needles preload failed '" + filepath + '\'').c_str()));
			}
		}
		else
		{
			php_log_err(const_cast<char*>(("multisearch: needles preload forbidden (open_basedir restriction) '" + filepath + '\'').c_str()));
		}
	}
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(arginfo_getInstance, 0, 0, MULTISEARCH_CLASSNAME(MemoryPersistentStorage), 0)
MULTISEARCH_END_ARG_INFO()

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


PHP_METHOD(MemoryPersistentStorage, __construct)
{
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();

	zend_throw_exception_ex(multisearch_ce_exception, 0, "MemoryPersistentStorage cannot be constructed. Use getInstance() static method.");
}

PHP_METHOD(MemoryPersistentStorage, getInstance)
{
	zval *zvalue;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();


	zvalue = zend_read_static_property(multisearch_ce_memory_persistent_storage, "instance", sizeof("instance") - 1, 0);
	if (Z_TYPE_P(zvalue) == IS_REFERENCE)
	{
		zvalue = Z_REFVAL_P(zvalue);
	}

	if (Z_TYPE_P(zvalue) == IS_NULL)
	{
		object_init_ex(zvalue, multisearch_ce_memory_persistent_storage);
		zend_update_static_property(multisearch_ce_memory_persistent_storage, "instance", sizeof("instance") - 1, zvalue TSRMLS_DC);
	}

	RETURN_ZVAL(zvalue, 1, 0);
}

PHP_METHOD(MemoryPersistentStorage, setNeedlesBundle)
{
	char *c_name;
	size_t c_name_len;
	zval* needlesBundle;
	zend_long validity_stamp = 0;
	
	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_STRING(c_name, c_name_len)
		Z_PARAM_OBJECT_OF_CLASS(needlesBundle, multisearch_ce_needles_bundle)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(validity_stamp)
	ZEND_PARSE_PARAMETERS_END();


	std::string name(c_name, c_name_len);

	trie_repository::set_trie(name, multisearch_needles_bundle_get_trie(needlesBundle), validity_stamp);
	RETURN_NULL();
}

PHP_METHOD(MemoryPersistentStorage, getNeedlesBundle)
{
	char *c_name;
	size_t c_name_len;
	zend_long validity_stamp = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(c_name, c_name_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(validity_stamp)
	ZEND_PARSE_PARAMETERS_END();


	std::string name(c_name, c_name_len);

	auto trie = trie_repository::get_trie(name, validity_stamp);
	if (!trie)
	{
		std::stringstream ss;
		ss << "No needles bundle with name '" << name << '\'' << " and validity stamp at least " << validity_stamp << '.';
		zend_throw_exception_ex(multisearch_ce_exception, 0, "%s", ss.str().c_str());
		return;
	}

	multisearch_needles_bundle_init(return_value, trie);
}

PHP_METHOD(MemoryPersistentStorage, hasNeedlesBundle)
{
	char *c_name;
	size_t c_name_len;
	zend_long validity_stamp = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(c_name, c_name_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_LONG(validity_stamp)
	ZEND_PARSE_PARAMETERS_END();


	std::string name(c_name, c_name_len);

	auto trie = trie_repository::get_trie(name, validity_stamp);

	RETURN_BOOL(trie != nullptr);
}

PHP_METHOD(MemoryPersistentStorage, removeNeedlesBundle)
{
	char *c_name;
	size_t c_name_len;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(c_name, c_name_len)
	ZEND_PARSE_PARAMETERS_END();


	std::string name(c_name, c_name_len);

	trie_repository::remove_trie(name);
	RETURN_NULL();
}


static zend_function_entry memory_persistent_storage_functions[] = {
	PHP_ME(MemoryPersistentStorage, __construct, arginfo_construct, ZEND_ACC_PRIVATE)
	PHP_ME(MemoryPersistentStorage, getInstance, arginfo_getInstance, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(MemoryPersistentStorage, setNeedlesBundle, arginfo_setNeedlesBundle, ZEND_ACC_PUBLIC)
	PHP_ME(MemoryPersistentStorage, getNeedlesBundle, arginfo_getNeedlesBundle, ZEND_ACC_PUBLIC)
	PHP_ME(MemoryPersistentStorage, hasNeedlesBundle, arginfo_hasNeedlesBundle, ZEND_ACC_PUBLIC)
	PHP_ME(MemoryPersistentStorage, removeNeedlesBundle, arginfo_removeNeedlesBundle, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_memory_persistent_storage(const std::vector<std::string>& needles_bundle_filepaths)
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, MULTISEARCH_CLASSNAME_STR(MemoryPersistentStorage), memory_persistent_storage_functions);

	multisearch_ce_memory_persistent_storage = zend_register_internal_class(&tmp_ce TSRMLS_CC);
	multisearch_ce_memory_persistent_storage->ce_flags |= ZEND_ACC_FINAL;
	multisearch_ce_memory_persistent_storage->create_object = [](zend_class_entry *ce) {
		zend_object *obj = zend_objects_new(ce);

		obj->handlers = &memory_persistent_storage_object_handlers;

		return obj;
	};
	
	zend_declare_property_null(multisearch_ce_memory_persistent_storage, "instance", sizeof("instance") - 1, ZEND_ACC_PRIVATE | ZEND_ACC_STATIC TSRMLS_CC);

	memcpy(&memory_persistent_storage_object_handlers, zend_get_std_object_handlers(), sizeof(memory_persistent_storage_object_handlers));

	memory_persistent_storage_object_handlers.clone_obj = [](zval* object) {
		zend_throw_exception_ex(multisearch_ce_exception, 0, "MemoryPersistentStorage cannot be cloned.");
		return Z_OBJ_P(object);
	};

	zend_class_implements(multisearch_ce_memory_persistent_storage TSRMLS_CC, 1, multisearch_ce_needles_bundle_storage_interface);

	preload(needles_bundle_filepaths);
}
