#ifndef MULTISEARCH_COMMON_H
#define MULTISEARCH_COMMON_H

#include <string>

#define MULTISEARCH_NS "MultiSearch"
#define MULTISEARCH_ARG_OBJ_INFO(pass_by_ref, name, classname, allow_null) ZEND_ARG_OBJ_INFO(pass_by_ref, name, MultiSearch\\classname, allow_null)

bool multisearch_check_open_basedir(const std::string& filepath);

#endif
