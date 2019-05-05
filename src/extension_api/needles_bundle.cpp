#include "needles_bundle.h"
#include "common.h"
#include "needle.h"
#include "search_hit.h"

#include "zend_exceptions.h"

#include <cstring>


zend_object_handlers needles_bundle_object_handlers;

typedef struct {
	zend_object std;
	multisearch_needles_bundle_trie_ptr trie;
} needles_bundle_object;

static inline needles_bundle_object *php_needles_bundle_from_obj(zend_object *obj) {
	return (needles_bundle_object*)((char*)(obj)-XtOffsetOf(needles_bundle_object, std));
}

#define Z_NB_OBJ_P(zv)  php_needles_bundle_from_obj(Z_OBJ_P((zv)))


zend_class_entry *multisearch_ce_needles_bundle;


static zend_object *needles_bundle_create_object(const multisearch_needles_bundle_trie_ptr& trie, zend_class_entry *ce)
{
	needles_bundle_object *intern = (needles_bundle_object*)ecalloc(1, sizeof(needles_bundle_object));

	zend_object_std_init(&intern->std, ce TSRMLS_CC);
	object_properties_init(&intern->std, ce);

	intern->std.handlers = &needles_bundle_object_handlers;

	new (&intern->trie) multisearch_needles_bundle_trie_ptr();
	intern->trie = trie;

	return &intern->std;
}

void multisearch_needles_bundle_init(zval* bundle, const multisearch_needles_bundle_trie_ptr& trie)
{
	ZVAL_OBJ(bundle, needles_bundle_create_object(trie, multisearch_ce_needles_bundle));
}

multisearch_needles_bundle_trie_ptr multisearch_needles_bundle_get_trie(zval* bundle)
{
	needles_bundle_object *intern = Z_NB_OBJ_P(bundle);
	return intern && intern->trie ? intern->trie : nullptr;
}

static void needles_bundle_object_destroy(zend_object *object)
{
	zend_objects_destroy_object(object); /* call __destruct() from userland */
}

static void needles_bundle_object_free(zend_object *object)
{
	needles_bundle_object *intern;
	intern = (needles_bundle_object *)((char *)object - XtOffsetOf(needles_bundle_object, std));
	if (intern) {
		intern->trie.reset();
	}
	zend_object_std_dtor(object); /* call Zend's free handler, which will free object properties */
}

static HashTable* needles_bundle_object_get_debug_info(zval *object, int *is_temp)
{
	HashTable *ht;
	zval pairs;

	*is_temp = 1;
	array_init(&pairs);

	needles_bundle_object *intern = Z_NB_OBJ_P(object);
	if (intern && intern->trie)
	{
		for (auto& needle : *intern->trie)
		{
			auto& key = needle.getKey();
			auto& value = needle.getValue();

			add_assoc_string(&pairs, key.c_str(), (char*)value.c_str());
		}
	}

	ALLOC_HASHTABLE(ht);
	zend_hash_init(ht, 1, NULL, ZVAL_PTR_DTOR, 0);
	zend_hash_str_update(ht, "pairs", sizeof("pairs") - 1, &pairs);

	return ht;
}


ZEND_BEGIN_ARG_INFO_EX(arginfo_construct, 0, 0, 0)
ZEND_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_insert, 0, 1, IS_VOID, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, key, IS_STRING, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, value, IS_STRING, 0)
MULTISEARCH_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_getNeedles, 0, 0, IS_ARRAY, 0)
MULTISEARCH_END_ARG_INFO()

MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(arginfo_searchIn, 0, 1, IS_ARRAY, 0)
	MULTISEARCH_ARG_TYPE_INFO(0, haystack, IS_STRING, 0)
MULTISEARCH_END_ARG_INFO()


PHP_METHOD(NeedlesBundle, __construct)
{
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();
}

PHP_METHOD(NeedlesBundle, insert)
{
	char *key, *value = 0;
	size_t key_len, value_len;

	zval *zthis;

	ZEND_PARSE_PARAMETERS_START(1, 2)
		Z_PARAM_STRING(key, key_len)
		Z_PARAM_OPTIONAL
		Z_PARAM_STRING(value, value_len)
	ZEND_PARSE_PARAMETERS_END();

	needles_bundle_object *intern = Z_NB_OBJ_P(getThis());
	if (intern && intern->trie)
	{
		if (!intern->trie.unique())
		{	// need to make copy of trie
			intern->trie.reset(new multisearch_needles_bundle_trie(*intern->trie));
		}

		std::string valueStr = value ? value : "";
		intern->trie->insert(key, valueStr);
	}

	RETURN_NULL();
}

PHP_METHOD(NeedlesBundle, getNeedles)
{
	ZEND_PARSE_PARAMETERS_START(0, 0)
	ZEND_PARSE_PARAMETERS_END();

	array_init(return_value);

	needles_bundle_object *intern = Z_NB_OBJ_P(getThis());
	if (intern && intern->trie)
	{
		for (auto& needle : *intern->trie)
		{
			auto& key = needle.getKey();
			auto& value = needle.getValue();

			zval zNeedle;
			multisearch_init_needle(&zNeedle, key, value);

			add_next_index_zval(return_value, &zNeedle);
		}
	}
}

PHP_METHOD(NeedlesBundle, searchIn)
{
	char* haystack;
	size_t haystack_len;

	ZEND_PARSE_PARAMETERS_START(1, 1)
		Z_PARAM_STRING(haystack, haystack_len)
	ZEND_PARSE_PARAMETERS_END();

	array_init(return_value);

	needles_bundle_object *intern = Z_NB_OBJ_P(getThis());
	if (intern && intern->trie)
	{
		auto sIt = intern->trie->search_in(haystack);
		while (++sIt)
		{
			auto& key = sIt->getKey();
			auto& value = sIt->getValue();
			auto position = sIt->getPosition();

			zval zSearchHit;
			multisearch_init_search_hit(&zSearchHit, key, value, position);

			add_next_index_zval(return_value, &zSearchHit);
		}
	}
}

static zend_function_entry needles_bundle_functions[] = {
	PHP_ME(NeedlesBundle, __construct, arginfo_construct, ZEND_ACC_PUBLIC)
	PHP_ME(NeedlesBundle, insert, arginfo_insert, ZEND_ACC_PUBLIC)
	PHP_ME(NeedlesBundle, getNeedles, arginfo_getNeedles, ZEND_ACC_PUBLIC)
	PHP_ME(NeedlesBundle, searchIn, arginfo_searchIn, ZEND_ACC_PUBLIC)
	PHP_FE_END
};


void multisearch_register_class_needles_bundle()
{
	zend_class_entry tmp_ce;
	INIT_CLASS_ENTRY(tmp_ce, MULTISEARCH_CLASSNAME_STR(NeedlesBundle), needles_bundle_functions);

	multisearch_ce_needles_bundle = zend_register_internal_class(&tmp_ce TSRMLS_CC);
	multisearch_ce_needles_bundle->create_object = [](zend_class_entry *ce) {
		return needles_bundle_create_object(std::make_shared<multisearch_needles_bundle_trie>(), ce);
	};

	memcpy(&needles_bundle_object_handlers, zend_get_std_object_handlers(), sizeof(needles_bundle_object_handlers));

	needles_bundle_object_handlers.free_obj = needles_bundle_object_free; /* This is the free handler */
	needles_bundle_object_handlers.dtor_obj = needles_bundle_object_destroy; /* This is the dtor handler */
	needles_bundle_object_handlers.get_debug_info = needles_bundle_object_get_debug_info;
	needles_bundle_object_handlers.offset = XtOffsetOf(needles_bundle_object, std); /* Here, we declare the offset to the engine */
	needles_bundle_object_handlers.clone_obj = [](zval* object) {
		needles_bundle_object *intern = Z_NB_OBJ_P(object);
		auto trie = intern ? intern->trie : std::make_shared<multisearch_needles_bundle_trie>();
		auto new_bundle = needles_bundle_create_object(trie, intern->std.ce);

		zend_objects_clone_members(new_bundle, Z_OBJ_P(object));

		return new_bundle;
	};
}
