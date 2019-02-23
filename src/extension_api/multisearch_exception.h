#ifndef MULTISEARCH_EXCEPTION_H
#define MULTISEARCH_EXCEPTION_H

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_exception;

void multisearch_register_class_exception();

#endif
