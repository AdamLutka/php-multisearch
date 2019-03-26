#include "search_hit.h"
#include "common.h"


zend_class_entry *multisearch_ce_search_hit;


static void search_hit_init_props(zval* hit, const std::string& key, const std::string& value, std::size_t position)
{
	zend_update_property_long(multisearch_ce_search_hit, hit, "position", sizeof("position") - 1, position TSRMLS_DC);
	zend_update_property_string(multisearch_ce_search_hit, hit, "key", sizeof("key") - 1, key.c_str() TSRMLS_DC);
	zend_update_property_string(multisearch_ce_search_hit, hit, "value", sizeof("value") - 1, value.c_str() TSRMLS_DC);
}

void multisearch_init_search_hit(zval* hit, const std::string& key, const std::string& value, std::size_t position)
{
	object_init_ex(hit, multisearch_ce_search_hit);
	search_hit_init_props(hit, key, value, position);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_construct, 0, 0, 2)
	ZEND_ARG_TYPE_INFO(0, position, IS_LONG, 0)
	ZEND_ARG_TYPE_INFO(0, key, IS_STRING, 0)
	ZEND_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()


PHP_METHOD(SearchHit, __construct)
{
	zend_long position;
	char *key, *value = 0;
	size_t key_len, value_len = 0;

	ZEND_PARSE_PARAMETERS_START(2, 3)
		Z_PARAM_LONG(position)
		Z_PARAM_STRING(key, key_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(value, value_len)
	ZEND_PARSE_PARAMETERS_END();

	search_hit_init_props(getThis(), std::string(key, key_len), std::string(value, value_len), position);
}

PHP_METHOD(SearchHit, getPosition)
{
	zval *zposition;
	zval rv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();


	zposition = zend_read_property(multisearch_ce_search_hit, getThis(), "position", sizeof("position") - 1, 0, &rv);

	RETURN_ZVAL(zposition, 1, 0);
}

PHP_METHOD(SearchHit, getKey)
{
	zval *zkey;
	zval rv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();
	

	zkey = zend_read_property(multisearch_ce_search_hit, getThis(), "key", sizeof("key") - 1, 0, &rv);

	RETURN_ZVAL(zkey, 1, 0);
}

PHP_METHOD(SearchHit, getValue)
{
	zval *zvalue;
	zval rv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();


	zvalue = zend_read_property(multisearch_ce_search_hit, getThis(), "value", sizeof("value") - 1, 0, &rv);

	RETURN_ZVAL(zvalue, 1, 0);
}


static zend_function_entry search_hit_functions[] = {
	PHP_ME(SearchHit, __construct, arginfo_construct, ZEND_ACC_PUBLIC)
	PHP_ME(SearchHit, getPosition, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_ME(SearchHit, getKey, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_ME(SearchHit, getValue, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_search_hit()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, ZEND_NS_NAME(MULTISEARCH_NS, "SearchHit"), search_hit_functions);

	multisearch_ce_search_hit = zend_register_internal_class(&tmp_ce TSRMLS_CC);
	zend_declare_property_null(multisearch_ce_search_hit, "position", sizeof("position") - 1, ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(multisearch_ce_search_hit, "key",      sizeof("key") - 1,      ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(multisearch_ce_search_hit, "value",    sizeof("value") - 1,    ZEND_ACC_PRIVATE TSRMLS_CC);
}
