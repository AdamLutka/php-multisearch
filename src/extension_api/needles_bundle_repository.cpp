#include "needles_bundle_repository.h"
#include "common.h"
#include "needles_bundle.h"
#include "multisearch_exception.h"
#include "../storage/trie_file_loader.h"
#include "../storage/trie_repository.h"

#include "zend_exceptions.h"


using namespace multisearch::storage;


zend_class_entry *multisearch_ce_needles_bundle_repository;


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
					trie->searchIn("");
						trie_repository::set_trie(file_info.identifier, trie, file_info.modified);
						continue;
				}
			}
		}

		php_log_err(const_cast<char*>(("multisearch: needles preload failed " + filepath).c_str()));
	}
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_fromFile, 0, 0, 1)
	ZEND_ARG_TYPE_INFO(0, filepath, IS_STRING, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_dispose, 0, 0, 1)
	MULTISEARCH_ARG_OBJ_INFO(0, needlesBundle, NeedlesBundle, 0)
ZEND_END_ARG_INFO()


PHP_METHOD(NeedlesBundleRepository, __construct)
{
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();

	zend_throw_exception_ex(multisearch_ce_exception, 0, "NeedlesBundleRepository cannot be constructed. Use getInstance() static method.");
}

PHP_METHOD(NeedlesBundleRepository, getInstance)
{
	zval *zvalue;
	
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();


	zvalue = zend_read_static_property(multisearch_ce_needles_bundle_repository, "instance", sizeof("instance") - 1, 0);
	if (Z_TYPE_P(zvalue) == IS_NULL)
	{
		object_init_ex(zvalue, multisearch_ce_needles_bundle_repository);
		zend_update_static_property(multisearch_ce_needles_bundle_repository, "instance", sizeof("instance") - 1, zvalue TSRMLS_DC);
	}

	RETURN_ZVAL(zvalue, 1, 0);
}

PHP_METHOD(NeedlesBundleRepository, fromFile)
{
	char *fp;
	size_t fp_len;
	
	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(fp, fp_len)
	ZEND_PARSE_PARAMETERS_END();
	

	std::string filepath(fp, fp_len);

	if (!multisearch_check_open_basedir(filepath))
	{
		return;
	}

	auto file_info = trie_repository::get_file_info(filepath);
	if (!file_info)
	{
		zend_throw_exception_ex(multisearch_ce_exception, 0, "Invalid filepath: %s", filepath.c_str());
		return;
	}

	auto trie = trie_repository::get_trie(file_info.identifier, file_info.modified);
	if (!trie)
	{
		trie = load_trie(filepath);
		if (!trie)
		{
			zend_throw_exception_ex(multisearch_ce_exception, 0, "File cannot be open: %s", filepath.c_str());
			return;
		}

		trie_repository::set_trie(file_info.identifier, trie, file_info.modified);
	}

	multisearch_needles_bundle_init(return_value, trie);
}

PHP_METHOD(NeedlesBundleRepository, dispose)
{
	zval* bundle;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_OBJECT_OF_CLASS(bundle, multisearch_ce_needles_bundle)
	ZEND_PARSE_PARAMETERS_END();


	trie_repository::remove_trie(multisearch_needles_bundle_dispose(bundle));


	RETURN_NULL();
}

static zend_function_entry needles_bundle_repository_functions[] = {
	PHP_ME(NeedlesBundleRepository, __construct, arginfo_void, ZEND_ACC_PRIVATE)
	PHP_ME(NeedlesBundleRepository, getInstance, arginfo_void, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)
	PHP_ME(NeedlesBundleRepository, fromFile, arginfo_fromFile, ZEND_ACC_PUBLIC)
	PHP_ME(NeedlesBundleRepository, dispose, arginfo_dispose, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_needles_bundle_repository(const std::vector<std::string>& preload_filepaths)
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, ZEND_NS_NAME(MULTISEARCH_NS, "NeedlesBundleRepository"), needles_bundle_repository_functions);

	multisearch_ce_needles_bundle_repository = zend_register_internal_class(&tmp_ce TSRMLS_CC);
	zend_declare_property_null(multisearch_ce_needles_bundle_repository, "instance", sizeof("instance") - 1, ZEND_ACC_PRIVATE | ZEND_ACC_STATIC TSRMLS_CC);

	preload(preload_filepaths);
}
