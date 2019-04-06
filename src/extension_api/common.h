#ifndef MULTISEARCH_COMMON_H
#define MULTISEARCH_COMMON_H

#include <string>

#define _MULTISEARCH_STR(str) #str
#define MULTISEARCH_STR(str) _MULTISEARCH_STR(str)

#define MULTISEARCH_NS MultiSearch
#define MULTISEARCH_NS_STR MULTISEARCH_STR(MULTISEARCH_NS)

#define MULTISEARCH_CLASSNAME(classname) MULTISEARCH_NS\\classname
#define MULTISEARCH_CLASSNAME_STR(classname) MULTISEARCH_NS_STR "\\" #classname

#define MULTISEARCH_ARG_OBJ_INFO(pass_by_ref, name, classname, allow_null) ZEND_ARG_OBJ_INFO(pass_by_ref, name, classname, allow_null)
#define MULTISEARCH_ARG_TYPE_INFO(pass_by_ref, name, type_hint, allow_null) ZEND_ARG_TYPE_INFO(pass_by_ref, name, type_hint, allow_null)

#if PHP_VERSION_ID >= 70200

#define MULTISEARCH_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null)
#define MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null)

#else

#define MULTISEARCH_BEGIN_ARG_WITH_RETURN_OBJ_INFO_EX(name, return_reference, required_num_args, class_name, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, IS_OBJECT, MULTISEARCH_STR(class_name), allow_null)
#define MULTISEARCH_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, allow_null) \
	ZEND_BEGIN_ARG_WITH_RETURN_TYPE_INFO_EX(name, return_reference, required_num_args, type, NULL, allow_null)

#endif

#define MULTISEARCH_END_ARG_INFO() ZEND_END_ARG_INFO()


bool multisearch_check_open_basedir(const std::string& filepath);


#endif
