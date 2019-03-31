#ifndef MULTISEARCH_NEEDLES_BUNDLE_STORAGE_INTERFACE_H
#define MULTISEARCH_NEEDLES_BUNDLE_STORAGE_INTERFACE_H

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_needles_bundle_storage_interface;

void multisearch_register_needles_bundle_storage_interface();

#endif
