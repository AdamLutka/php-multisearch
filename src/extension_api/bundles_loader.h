#ifndef MULTISEARCH_BUNDLES_LOADER_H
#define MULTISEARCH_BUNDLES_LOADER_H

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_bundles_loader;

void multisearch_register_class_bundles_loader();

#endif
