#ifndef MULTISEARCH_NEEDLES_BUNDLE_LOADER_INTERFACE_H
#define MULTISEARCH_NEEDLES_BUNDLE_LOADER_INTERFACE_H

extern "C" {
	#include "php.h"
}

extern zend_class_entry *multisearch_ce_needles_bundle_loader_interface;

void multisearch_register_needles_bundle_loader_interface();

#endif
