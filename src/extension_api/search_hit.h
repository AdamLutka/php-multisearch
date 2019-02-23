#ifndef MULTISEARCH_SEARCH_HIT_H
#define MULTISEARCH_SEARCH_HIT_H

#include <string>
#include <cstddef>

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_search_hit;

void multisearch_register_class_search_hit();
void multisearch_init_search_hit(zval* hit, const std::string& key, const std::string& value, std::size_t position);

#endif
