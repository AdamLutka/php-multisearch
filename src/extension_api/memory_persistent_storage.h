#ifndef MULTISEARCH_MEMORY_PERSISTENT_STORAGE_H
#define MULTISEARCH_MEMORY_PERSISTENT_STORAGE_H

extern "C" {
	#include "php.h"
}


#include <vector>
#include <string>


extern zend_class_entry *multisearch_ce_memory_persistent_storage;

void multisearch_register_class_memory_persistent_storage(const std::vector<std::string>& needles_bundle_filepaths);

#endif
