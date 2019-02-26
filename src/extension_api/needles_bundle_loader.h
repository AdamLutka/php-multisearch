#ifndef MULTISEARCH_NEEDLES_BUNDLE_LOADER_H
#define MULTISEARCH_NEEDLES_BUNDLE_LOADER_H

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_needles_bundle_loader;

void multisearch_register_class_needles_bundle_loader();

#endif
