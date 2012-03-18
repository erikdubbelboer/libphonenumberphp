
#ifndef PHP_LIBPHONENUMBERPHP_H
#define PHP_LIBPHONENUMBERPHP_H


#define PHP_LIBPHONENUMBERPHP_EXTNAME "libphonenumberphp"
#define PHP_LIBPHONENUMBERPHP_EXTVER "1.0"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

extern "C" {
#include "php.h"
#include "ext/standard/info.h"
}

extern zend_module_entry libphonenumberphp_module_entry;
#define phpext_libphonenumberphp_ptr &libphonenumberphp_module_entry;


#endif	/* PHP_LIBPHONENUMBERPHP_H */

