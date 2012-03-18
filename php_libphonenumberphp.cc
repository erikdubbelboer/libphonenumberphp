
#include "php_libphonenumberphp.h"

#include <string>

// These are defined (somewhere) and will cause errors when including logger.h
#undef LOG_WARNING
#undef LOG_INFO
#undef LOG_DEBUG
#include "phonenumbers/logger.h"
#include "phonenumbers/phonenumber.pb.h"
#include "phonenumbers/phonenumberutil.h"


using std::string;
using std::set;
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




ZEND_BEGIN_ARG_INFO(arginfo_GetSupportedRegions, 0)
  ZEND_ARG_INFO(1, regions)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#154
PHP_METHOD(PhoneNumberUtil, GetSupportedRegions) {
  zval*       regionsz;
  set<string> regions;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &regionsz) == FAILURE) {
    RETURN_NULL();
  }

  // Make sure the regions argument is passed as referrence.
  if (!PZVAL_IS_REF(regionsz)) {
    php_error(E_ERROR, "%s() regions should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  array_init(regionsz);

  util->GetSupportedRegions(&regions);

  for (set<string>::iterator i = regions.begin(); i != regions.end(); ++i) {
    add_next_index_string(regionsz, (*i).c_str(), 1);
  }

  RETURN_NULL();
}






ZEND_BEGIN_ARG_INFO(arginfo_IsAlphaNumber, 0)
  ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#169
PHP_METHOD(PhoneNumberUtil, IsAlphaNumber) {
  char* numberstr;
  int   numberstrlen;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "s", &numberstr, &numberstrlen) == FAILURE) {
    RETURN_NULL();
  }

  RETURN_BOOL(util->IsAlphaNumber(string(numberstr, numberstrlen)));
}







ZEND_BEGIN_ARG_INFO(arginfo_ConvertAlphaCharactersInNumber, 0)
  ZEND_ARG_INFO(1, number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#177
PHP_METHOD(PhoneNumberUtil, ConvertAlphaCharactersInNumber) {
  zval*  numberz;
  string number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Make sure the number argument is passed as referrence.
  if (!PZVAL_IS_REF(numberz)) {
    php_error(E_ERROR, "%s() number should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  number = Z_STRVAL_P(numberz);

  util->ConvertAlphaCharactersInNumber(&number);

  ZVAL_STRING(numberz, number.c_str(), 1);
}







ZEND_BEGIN_ARG_INFO(arginfo_NormalizeDigitsOnly, 0)
  ZEND_ARG_INFO(1, number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#181
PHP_METHOD(PhoneNumberUtil, NormalizeDigitsOnly) {
  zval*  numberz;
  string number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "z", &numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Make sure the number argument is passed as referrence.
  if (!PZVAL_IS_REF(numberz)) {
    php_error(E_ERROR, "%s() number should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  number = Z_STRVAL_P(numberz);

  util->NormalizeDigitsOnly(&number);

  ZVAL_STRING(numberz, number.c_str(), 1);
}


  
  
  


ZEND_BEGIN_ARG_INFO(arginfo_GetNationalSignificantNumber, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(1, national_significant_num)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#186
PHP_METHOD(PhoneNumberUtil, GetNationalSignificantNumber) {
  zval*        numberz;
  PhoneNumber* number;

  zval*  national_significant_numz;
  string national_significant_num;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rz", &numberz, &national_significant_numz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the number argument is passed as referrence.
  if (!PZVAL_IS_REF(national_significant_numz)) {
    php_error(E_ERROR, "%s() national_significant_num should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  util->GetNationalSignificantNumber(*number, &national_significant_num);

  ZVAL_STRING(national_significant_numz, national_significant_num.c_str(), 1);
}







ZEND_BEGIN_ARG_INFO(arginfo_GetLengthOfGeographicalAreaCode, 0)
  ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#191
PHP_METHOD(PhoneNumberUtil, GetLengthOfGeographicalAreaCode) {
  zval*        numberz;
  PhoneNumber* number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "r", &numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  RETURN_LONG(util->GetLengthOfGeographicalAreaCode(*number));
}






ZEND_BEGIN_ARG_INFO(arginfo_Format, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(0, number_format)
  ZEND_ARG_INFO(1, formatted_number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#265
PHP_METHOD(PhoneNumberUtil, Format) {
  zval*        numberz;
  PhoneNumber* number;

  long number_format;

  zval*  formatted_numberz;
  string formatted_number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rlz", &numberz, &number_format, &formatted_numberz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the formatted argument is passed as referrence.
  if (!PZVAL_IS_REF(formatted_numberz)) {
    php_error(E_ERROR, "%s() formatted should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  util->Format(*number, (PhoneNumberUtil::PhoneNumberFormat)number_format, &formatted_number);

  ZVAL_STRING(formatted_numberz, formatted_number.c_str(), 1);
}






ZEND_BEGIN_ARG_INFO(arginfo_FormatNationalNumberWithCarrierCode, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(0, carrier_code)
  ZEND_ARG_INFO(1, formatted_number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#283
PHP_METHOD(PhoneNumberUtil, FormatNationalNumberWithCarrierCode) {
  zval*        numberz;
  PhoneNumber* number;

  char* carrier_code;
  int   carrier_codelen;

  zval*  formatted_numberz;
  string formatted_number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsz", &numberz, &carrier_code, &carrier_codelen, &formatted_numberz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the formatted argument is passed as referrence.
  if (!PZVAL_IS_REF(formatted_numberz)) {
    php_error(E_ERROR, "%s() formatted should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  util->FormatNationalNumberWithCarrierCode(*number, string(carrier_code, carrier_codelen), &formatted_number);

  ZVAL_STRING(formatted_numberz, formatted_number.c_str(), 1);
}







ZEND_BEGIN_ARG_INFO(arginfo_FormatNationalNumberWithPreferredCarrierCode, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(0, fallback_carrier_code)
  ZEND_ARG_INFO(1, formatted_number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#292
PHP_METHOD(PhoneNumberUtil, FormatNationalNumberWithPreferredCarrierCode) {
  zval*        numberz;
  PhoneNumber* number;

  char* fallback_carrier_code;
  int   fallback_carrier_codelen;

  zval*  formatted_numberz;
  string formatted_number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "rsz", &numberz, &fallback_carrier_code, &fallback_carrier_codelen, &formatted_numberz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the formatted argument is passed as referrence.
  if (!PZVAL_IS_REF(formatted_numberz)) {
    php_error(E_ERROR, "%s() formatted should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(number, PhoneNumber*, &numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  util->FormatNationalNumberWithPreferredCarrierCode(*number, string(fallback_carrier_code, fallback_carrier_codelen), &formatted_number);

  ZVAL_STRING(formatted_numberz, formatted_number.c_str(), 1);
}







// TODO: FormatNumberForMobileDialing
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#307







// TODO: FormatOutOfCountryCallingNumber
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#317







//TODO: FormatInOriginalFormat
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#329







// TODO: FormatOutOfCountryKeepingAlphaChars
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#339







// TODO: TruncateTooLongNumber
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#361







ZEND_BEGIN_ARG_INFO(arginfo_GetNumberType, 0)
  ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO();

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






ZEND_BEGIN_ARG_INFO(arginfo_IsValidNumber, 0)
  ZEND_ARG_INFO(0, number)
ZEND_END_ARG_INFO();

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






ZEND_BEGIN_ARG_INFO(arginfo_IsValidNumberForRegion, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(0, region)
ZEND_END_ARG_INFO();

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






ZEND_BEGIN_ARG_INFO(arginfo_GetRegionCodeForNumber, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(1, region)
ZEND_END_ARG_INFO();

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






ZEND_BEGIN_ARG_INFO(arginfo_GetCountryCodeForRegion, 0)
  ZEND_ARG_INFO(0, region)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#393
PHP_METHOD(PhoneNumberUtil, GetCountryCodeForRegion) {
  char* regionstr;
  int   regionstrlen;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "s", &regionstr, &regionstrlen) == FAILURE) {
    RETURN_NULL();
  }

  RETURN_LONG(util->GetCountryCodeForRegion(string(regionstr, regionstrlen)));
}






ZEND_BEGIN_ARG_INFO(arginfo_GetRegionCodeForCountryCode, 0)
  ZEND_ARG_INFO(0, countrycode)
  ZEND_ARG_INFO(1, region)
ZEND_END_ARG_INFO();

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







// TODO: IsNANPACountry
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#403







// TODO: GetNddPrefixForRegion
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#407







// TODO: IsPossibleNumberWithReason
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#416







// TODO: IsPossibleNumber
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#435







// TODO: IsPossibleNumberForString
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#439







ZEND_BEGIN_ARG_INFO(arginfo_GetExampleNumber, 0)
  ZEND_ARG_INFO(0, region_code)
  ZEND_ARG_INFO(1, number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#461
PHP_METHOD(PhoneNumberUtil, GetExampleNumber) {
  char* region_code;
  int   region_codelen;

  zval*        numberz;
  PhoneNumber* number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "sz", &region_code, &region_codelen, &numberz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the number argument is passed as referrence.
  if (!PZVAL_IS_REF(numberz)) {
    php_error(E_ERROR, "%s() number should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  number = new PhoneNumber();

  bool success = util->GetExampleNumber(string(region_code, region_codelen), number);

  if (success) {
    // Set the value and add it to our resource list.
    ZEND_REGISTER_RESOURCE(numberz, number, PhoneNumber_resource_list);

    RETURN_TRUE;
  } else {
    convert_to_null(numberz);

    RETURN_FALSE;
  }
}







ZEND_BEGIN_ARG_INFO(arginfo_GetExampleNumberForType, 0)
  ZEND_ARG_INFO(0, region_code)
  ZEND_ARG_INFO(0, type)
  ZEND_ARG_INFO(1, number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#468
PHP_METHOD(PhoneNumberUtil, GetExampleNumberForType) {
  char* region_code;
  int   region_codelen;

  long type;

  zval*        numberz;
  PhoneNumber* number;

  if (zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "slz", &region_code, &region_codelen, &type, &numberz) == FAILURE) {
    RETURN_NULL();
  }
  
  // Make sure the number argument is passed as referrence.
  if (!PZVAL_IS_REF(numberz)) {
    php_error(E_ERROR, "%s() number should be passed by reference", get_active_function_name(TSRMLS_C));
    RETURN_NULL();
  }

  number = new PhoneNumber();

  bool success = util->GetExampleNumberForType(string(region_code, region_codelen), (PhoneNumberUtil::PhoneNumberType)type, number);

  if (success) {
    // Set the value and add it to our resource list.
    ZEND_REGISTER_RESOURCE(numberz, number, PhoneNumber_resource_list);

    RETURN_TRUE;
  } else {
    convert_to_null(numberz);

    RETURN_FALSE;
  }
}







// TODO: GetExampleNumberForNonGeoEntity
// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#476







ZEND_BEGIN_ARG_INFO(arginfo_Parse, 0)
  ZEND_ARG_INFO(0, number)
  ZEND_ARG_INFO(0, default_region)
  ZEND_ARG_INFO(1, phonenumber)
ZEND_END_ARG_INFO();

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

    RETURN_LONG(err);
  }

  // Set the value and add it to our resource list.
  ZEND_REGISTER_RESOURCE(numberz, number, PhoneNumber_resource_list);

  RETURN_LONG(0);
}







ZEND_BEGIN_ARG_INFO(arginfo_IsNumberMatch, 0)
  ZEND_ARG_INFO(0, first_number)
  ZEND_ARG_INFO(0, second_number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#507
PHP_METHOD(PhoneNumberUtil, IsNumberMatch) {
  zval*        first_numberz;
  PhoneNumber* first_number;
  
  zval*        second_numberz;
  PhoneNumber* second_number;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "rr", &first_numberz, &second_numberz) == FAILURE) {
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumbers from our resource list.
  ZEND_FETCH_RESOURCE(first_number , PhoneNumber*, &first_numberz , -1, PhoneNumber_resource_name, PhoneNumber_resource_list);
  ZEND_FETCH_RESOURCE(second_number, PhoneNumber*, &second_numberz, -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  RETURN_LONG(util->IsNumberMatch(*first_number, *second_number));
}







ZEND_BEGIN_ARG_INFO(arginfo_IsNumberMatchWithTwoStrings, 0)
  ZEND_ARG_INFO(0, first_number)
  ZEND_ARG_INFO(0, second_number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#523
PHP_METHOD(PhoneNumberUtil, IsNumberMatchWithTwoStrings) {
  char* first_number;
  int   first_numberlen;

  char* second_number;
  int   second_numberlen;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "ss", &first_number, &first_numberlen, &second_number, &second_numberlen) == FAILURE) {
    RETURN_NULL();
  }

  RETURN_LONG(util->IsNumberMatchWithTwoStrings(string(first_number, first_numberlen), string(second_number, second_numberlen)));
}







ZEND_BEGIN_ARG_INFO(arginfo_IsNumberMatchWithOneString, 0)
  ZEND_ARG_INFO(0, first_number)
  ZEND_ARG_INFO(0, second_number)
ZEND_END_ARG_INFO();

// See http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h#531
PHP_METHOD(PhoneNumberUtil, IsNumberMatchWithOneString) {
  zval*        first_numberz;
  PhoneNumber* first_number;
  
  char* second_number;
  int   second_numberlen;

  if (zend_parse_parameters_ex(0, ZEND_NUM_ARGS() TSRMLS_CC, "rs", &first_numberz, &second_number, &second_numberlen) == FAILURE) {
    RETURN_NULL();
  }

  // Fetch the pointer to the PhoneNumber from our resource list.
  ZEND_FETCH_RESOURCE(first_number , PhoneNumber*, &first_numberz , -1, PhoneNumber_resource_name, PhoneNumber_resource_list);

  RETURN_LONG(util->IsNumberMatchWithOneString(*first_number, string(second_number, second_numberlen)));
}






// Exported class functions.
zend_function_entry PhoneNumberUtil_methods[] = {
  #define ENTRY(name) PHP_ME(PhoneNumberUtil, name, arginfo_##name, ZEND_ACC_PUBLIC | ZEND_ACC_STATIC)

  ENTRY(GetSupportedRegions)
  ENTRY(IsAlphaNumber)
  ENTRY(ConvertAlphaCharactersInNumber)
  ENTRY(NormalizeDigitsOnly)
  ENTRY(GetNationalSignificantNumber)
  ENTRY(GetLengthOfGeographicalAreaCode)
  ENTRY(Format)
  ENTRY(FormatNationalNumberWithCarrierCode)
  ENTRY(FormatNationalNumberWithPreferredCarrierCode)
  //ENTRY(FormatNumberForMobileDialing)
  //ENTRY(FormatOutOfCountryCallingNumber)
  //ENTRY(FormatInOriginalFormat)
  //ENTRY(FormatOutOfCountryKeepingAlphaChars)
  //ENTRY(TruncateTooLongNumber)
  ENTRY(GetNumberType)
  ENTRY(IsValidNumber)
  ENTRY(IsValidNumberForRegion)
  ENTRY(GetRegionCodeForNumber)
  ENTRY(GetCountryCodeForRegion)
  ENTRY(GetRegionCodeForCountryCode)
  //ENTRY(IsNANPACountry)
  //ENTRY(GetNddPrefixForRegion)
  //ENTRY(IsPossibleNumberWithReason)
  //ENTRY(IsPossibleNumber)
  //ENTRY(IsPossibleNumberForString)
  ENTRY(GetExampleNumber)
  ENTRY(GetExampleNumberForType)
  //ENTRY(GetExampleNumberForNonGeoEntity)
  ENTRY(Parse)
  ENTRY(IsNumberMatch)
  ENTRY(IsNumberMatchWithTwoStrings)
  ENTRY(IsNumberMatchWithOneString)

  #undef ENTRY

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

  // Format types
  REG(E164);
  REG(INTERNATIONAL);
  REG(NATIONAL);
  REG(RFC3966);

  // Phone number types
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

  // Types of phone number matches
  REG(INVALID_NUMBER);
  REG(NO_MATCH);
  REG(SHORT_NSN_MATCH);
  REG(NSN_MATCH);
  REG(EXACT_MATCH);

  // Parsing errors
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

