#ifndef MULTISEARCH_PHP_MULTISEARCH_H
#define MULTISEARCH_PHP_MULTISEARCH_H

#define PHP_MULTISEARCH_VERSION "1.0"
#define PHP_MULTISEARCH_EXTNAME "multisearch"

#ifdef HAVE_CONFIG_H
	#include "config.h"
#endif

extern "C" {
	#include "php.h"
}

extern zend_module_entry multisearch_module_entry;

#endif
