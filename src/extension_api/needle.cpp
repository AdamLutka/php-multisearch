#include "needle.h"
#include "common.h"


zend_class_entry *multisearch_ce_needle;


static void needle_init_props(zval* needle, const std::string& key, const std::string& value)
{
	zend_update_property_string(multisearch_ce_needle, needle, "key", sizeof("key") - 1, key.c_str() TSRMLS_DC);
	zend_update_property_string(multisearch_ce_needle, needle, "value", sizeof("value") - 1, value.c_str() TSRMLS_DC);
}

void multisearch_init_needle(zval* needle, const std::string& key, const std::string& value)
{
	object_init_ex(needle, multisearch_ce_needle);
	needle_init_props(needle, key, value);
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_void, 0, 0, 0)
ZEND_END_ARG_INFO()

ZEND_BEGIN_ARG_INFO_EX(arginfo_construct, 0, 0, 1)
	MULTISEARCH_ARG_TYPE_INFO(0, key, IS_STRING, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, value, IS_STRING, 0)
ZEND_END_ARG_INFO()


PHP_METHOD(Needle, __construct)
{
	char *key, *value = 0;
	size_t key_len, value_len = 0;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(key, key_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(value, value_len)
	ZEND_PARSE_PARAMETERS_END();

	needle_init_props(getThis(), std::string(key, key_len), std::string(value, value_len));
}

PHP_METHOD(Needle, getKey)
{
	zval *zkey;
	zval rv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();
	

	zkey = zend_read_property(multisearch_ce_needle, getThis(), "key", sizeof("key") - 1, 0, &rv);

	RETURN_ZVAL(zkey, 1, 0);
}

PHP_METHOD(Needle, getValue)
{
	zval *zvalue;
	zval rv;

	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();


	zvalue = zend_read_property(multisearch_ce_needle, getThis(), "value", sizeof("value") - 1, 0, &rv);

	RETURN_ZVAL(zvalue, 1, 0);
}


static zend_function_entry needle_functions[] = {
	PHP_ME(Needle, __construct, arginfo_construct, ZEND_ACC_PUBLIC)
	PHP_ME(Needle, getKey, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_ME(Needle, getValue, arginfo_void, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_needle()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, MULTISEARCH_CLASSNAME_STR(Needle), needle_functions);

	multisearch_ce_needle = zend_register_internal_class(&tmp_ce TSRMLS_CC);
	zend_declare_property_null(multisearch_ce_needle, "key",   sizeof("key") - 1,   ZEND_ACC_PRIVATE TSRMLS_CC);
	zend_declare_property_null(multisearch_ce_needle, "value", sizeof("value") - 1, ZEND_ACC_PRIVATE TSRMLS_CC);
}
