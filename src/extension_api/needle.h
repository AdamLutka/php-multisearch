#ifndef MULTISEARCH_NEEDLE_H
#define MULTISEARCH_NEEDLE_H

#include <string>

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_needle;

void multisearch_register_class_needle();
void multisearch_init_needle(zval* needle, const std::string& key, const std::string& value);

#endif
