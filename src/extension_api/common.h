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

bool multisearch_check_open_basedir(const std::string& filepath);

#endif
