
#include "libphonenumberphp.h"

#include <string>

// These are defined (somewhere) and will cause errors when including logger.h
#undef LOG_WARNING
#undef LOG_INFO
#undef LOG_DEBUG
#include "phonenumbers/logger.h"
#include "phonenumbers/phonenumber.pb.h"
#include "phonenumbers/phonenumberutil.h"


using std::string;
using i18n::phonenumbers::Logger;
using i18n::phonenumbers::PhoneNumber;
using i18n::phonenumbers::PhoneNumberUtil;



// Simple logger that logs nothing for now.
class PHPLogger : public Logger {
public:
  ~PHPLogger() {
  }

  void WriteMessage(const string& msg) {
    // This outputs a lot more than we want so I disabled it for now.
    //php_error(E_WARNING, msg.c_str());
  }
};




#define PhoneNumber_resource_name "PhoneNumber Resource"


PhoneNumberUtil* util; // We only need one instance since we only call thread safe methods.
PHPLogger        logger;
static int       PhoneNumber_resource_list; // List of PhoneNumber pointers.



// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#496
PHP_METHOD(PhoneNumberUtil, Parse) {
  char* numberstr;
  int   numberstrlen;

  char* regionstr;
  int   regionstrlen;

  zval*        numberz;
  PhoneNumber* number;


  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "ssz", &numberstr, &numberstrlen, &regionstr, &regionstrlen, &numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Make sure the PhoneNumber is passed as referrence.
  if (!PZVAL_IS_REF(numberz)) {
    php_error(E_ERROR, "%s() PhoneNumber should be passed as reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  number = new PhoneNumber();

  int err = util->Parse(string(numberstr, numberstrlen), string(regionstr, regionstrlen), number);

  if (err != PhoneNumberUtil::NO_PARSING_ERROR) {
    convert_to_null(numberz);

    php_error(E_WARNING, "%s() phone number parse error", get_active_function_name(TSRMLS_C), err);
    RETURN_LONG(err);
  }

  // Set the value and add it to our resource list.
  ZEND_REGISTER_RESOURCE(numberz, number, PhoneNumber_resource_list);

  RETURN_LONG(0);
}


// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#368
PHP_METHOD(PhoneNumberUtil, GetNumberType) {
  zval*        numberz;
  PhoneNumber* number;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "r", &numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  RETURN_LONG(util->GetNumberType(*number));
}


// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#371
PHP_METHOD(PhoneNumberUtil, IsValidNumber) {
  zval*        numberz;
  PhoneNumber* number;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "r", &numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  RETURN_BOOL(util->IsValidNumber(*number));
}


// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#376
PHP_METHOD(PhoneNumberUtil, IsValidNumberForRegion) {
  zval*        numberz;
  PhoneNumber* number;

  char* regionstr;
  int   regionstrlen;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "rs", &numberz, &regionstr, &regionstrlen) == FAILURE) {
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  RETURN_BOOL(util->IsValidNumberForRegion(*number, string(regionstr, regionstrlen)));
}


// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#388
PHP_METHOD(PhoneNumberUtil, GetRegionCodeForNumber) {
  zval*        numberz;
  PhoneNumber* number;

  zval*  regionz;
  string region;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &numberz, &regionz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the region code is passed as referrence.
  if (!PZVAL_IS_REF(regionz)) {
    php_error(E_ERROR, "%s() region code should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  util->GetRegionCodeForNumber(*number, &region);

  ZVAL_STRING(regionz, region.c_str(), 1);
}


// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#393
PHP_METHOD(PhoneNumberUtil, GetCountryCodeForRegion) {
  char* regionstr;
  int   regionstrlen;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "s", &regionstr, &regionstrlen) == FAILURE) {
    RETURN_NULL();
  }

  RETURN_LONG(util->GetCountryCodeForRegion(string(regionstr, regionstrlen)));
}


// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#397
PHP_METHOD(PhoneNumberUtil, GetRegionCodeForCountryCode) {
  long   cc;
  zval*  regionz;
  string region;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "lz", &cc, &regionz) == FAILURE) {
    RETURN_NULL();
  }

  // Make sure the region code is passed as referrence.
  if (!PZVAL_IS_REF(regionz)) {
    php_error(E_ERROR, "%s() region code should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  util->GetRegionCodeForCountryCode(cc, &region);

  ZVAL_STRING(regionz, region.c_str(), 1);
}



// Exported class functions.
function_entry PhoneNumberUtil_methods[] = {
  PHP_ME(PhoneNumberUtil, Parse                      , NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
  PHP_ME(PhoneNumberUtil, GetNumberType              , NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
  PHP_ME(PhoneNumberUtil, IsValidNumber              , NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
  PHP_ME(PhoneNumberUtil, IsValidNumberForRegion     , NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
  PHP_ME(PhoneNumberUtil, GetRegionCodeForNumber     , NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
  PHP_ME(PhoneNumberUtil, GetCountryCodeForRegion    , NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)
  PHP_ME(PhoneNumberUtil, GetRegionCodeForCountryCode, NULL, ZEND_ACC_PUBLIC | ZEND_ACC_ALLOW_STATIC)

  {NULL, NULL, NULL}
};


// This function is called when a PhoneNumber resource is destroyed.
void PhoneNumber_resource_destruction_handler(zend_rsrc_list_entry *rsrc TSRMLS_DC) {
  PhoneNumber *number = (PhoneNumber*) rsrc->ptr;

  delete number;
}


PHP_MINIT_FUNCTION(libphonenumberphp) {
  util = PhoneNumberUtil::GetInstance();

  PhoneNumberUtil::SetLogger(&logger);


  // Register the PhoneNumber resource.
  PhoneNumber_resource_list = zend_register_list_destructors_ex(PhoneNumber_resource_destruction_handler, NULL, PhoneNumber_resource_name, module_number);

  zend_class_entry ce;
  INIT_CLASS_ENTRY(ce, "PhoneNumberUtil", PhoneNumberUtil_methods);
  zend_class_entry* PhoneNumberUtil_class = zend_register_internal_class(&ce TSRMLS_CC);


  // Register all class constants.
  #define REG(name) zend_declare_class_constant_long(PhoneNumberUtil_class, #name, sizeof(#name) - 1, PhoneNumberUtil::name TSRMLS_CC);

  REG(FIXED_LINE);
  REG(MOBILE);
  REG(FIXED_LINE_OR_MOBILE);
  REG(TOLL_FREE);
  REG(PREMIUM_RATE);
  REG(SHARED_COST);
  REG(VOIP);
  REG(PERSONAL_NUMBER);
  REG(PAGER);
  REG(UAN);
  REG(VOICEMAIL);
  REG(UNKNOWN);

  REG(NO_PARSING_ERROR);
  REG(INVALID_COUNTRY_CODE_ERROR);
  REG(NOT_A_NUMBER);
  REG(TOO_SHORT_AFTER_IDD);
  REG(TOO_SHORT_NSN);
  REG(TOO_LONG_NSN);

  #undef REG

  return SUCCESS;
}


PHP_MINFO_FUNCTION(libphonenumberphp) {
  php_info_print_table_start();
  php_info_print_table_header(2, "libphonenumberphp support", "enabled");
  php_info_print_table_end();
}


zend_module_entry libphonenumberphp_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_LIBPHONENUMBERPHP_EXTNAME,
    NULL,                  /* Functions */
    PHP_MINIT(libphonenumberphp),
    NULL,
    NULL,                  /* RINIT */
    NULL,                  /* RSHUTDOWN */
    PHP_MINFO(libphonenumberphp), /* MINFO */
#if ZEND_MODULE_API_NO >= 20010901
    PHP_LIBPHONENUMBERPHP_EXTVER,
#endif
    STANDARD_MODULE_PROPERTIES
};


#ifdef COMPILE_DL_LIBPHONENUMBERPHP
extern "C" {
ZEND_GET_MODULE(libphonenumberphp)
}
#endif

