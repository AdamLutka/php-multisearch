#include "common.h"
#include "multisearch_exception.h"

#include "php.h"
#include "zend_exceptions.h"


bool multisearch_check_open_basedir(const std::string& filepath)
{
	if (php_check_open_basedir_ex(filepath.c_str(), 0) == 0)
	{
		return true;
	}
	else
	{
		zend_throw_exception_ex(multisearch_ce_exception, 0, "Forbidden (open_basedir restriction): %s", filepath.c_str());
		return false;
	}
}