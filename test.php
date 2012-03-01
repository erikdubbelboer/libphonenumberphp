#!/usr/bin/php -d extension=./modules/libphonenumberphp.so
<?


error_reporting(E_ALL | E_STRICT);


function test($name, $number, $cc, $parse, $valid = false, $type = 0) {
  echo '.';

  $err = PhoneNumberUtil::Parse($number, $cc, &$p);

  if ($err != $parse) {
    echo $name . " failed on parse!\n";
    return;
  }

  if (PhoneNumberUtil::isValidNumber($p) != $valid) {
    echo $name . " failed on valid!\n";
    return;
  }
  
  if (PhoneNumberUtil::GetNumberType($p) != $type) {
    echo $name . " failed on type!\n";
    return;
  }
}


test('valid full mobile number'    , '+31651245374'   , 'ZZ', PhoneNumberUtil::NO_PARSING_ERROR          , true, PhoneNumberUtil::MOBILE);
test('valid region specific number', '6 512 45 374'   , 'NL', PhoneNumberUtil::NO_PARSING_ERROR          , true, PhoneNumberUtil::MOBILE);
test('valid full land number'      , '+31 848-393-464', 'ZZ', PhoneNumberUtil::NO_PARSING_ERROR          , true, PhoneNumberUtil::FIXED_LINE);

error_reporting(0);
test('invalid number'              , '651245374'      , 'ZZ', PhoneNumberUtil::INVALID_COUNTRY_CODE_ERROR);
error_reporting(E_ALL | E_STRICT);


PhoneNumberUtil::Parse('+31651245374', 'ZZ', &$p);

echo '.';
if (!PhoneNumberUtil::IsValidNumberForRegion($p, 'NL')) {
  echo "IsValidNumberForRegion 1 failed!\n";
}
echo '.';
if (PhoneNumberUtil::IsValidNumberForRegion($p, 'BE')) {
  echo "IsValidNumberForRegion 2 failed!\n";
}


echo '.';
PhoneNumberUtil::Format($p, PhoneNumberUtil::RFC3966, &$s);

if ($s != '+31-6-51245374') {
  echo "Format failed!\n";
}


PhoneNumberUtil::GetRegionCodeForNumber($p, &$cc);

echo '.';
if ($cc != 'NL') {
  echo "GetRegionCodeForNumber failed!\n";
}


echo '.';
if (PhoneNumberUtil::GetCountryCodeForRegion('NL') != 31) {
  echo "GetCountryCodeForRegion failed!\n";
}


PhoneNumberUtil::GetRegionCodeForCountryCode(31, &$cc);

echo '.';
if ($cc != 'NL') {
  echo "GetRegionCodeForCountryCode failed!\n";
}


echo "all tests done.\n";

