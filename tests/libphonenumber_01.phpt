--TEST--
Basic tests for PhoneNumberUtil
--FILE--
<?

error_reporting(E_ALL | E_STRICT);


function test($name, $number, $cc, $parse, $valid = false, $type = 0) {
  $err = PhoneNumberUtil::Parse($number, $cc, $p);

  if ($err != $parse) {
    echo $name . " failed on parse!\n";
    return;
  }

  if (is_null($p)) {
    return;
  }

  if (PhoneNumberUtil::IsValidNumber($p) != $valid) {
    echo $name . " failed on valid!\n";
    return;
  }
  
  if (PhoneNumberUtil::GetNumberType($p) != $type) {
    echo $name . " failed on type!\n";
    return;
  }
}


test('valid full mobile number'    , '+31651245374'   , 'ZZ', PhoneNumberUtil::ERROR_NO_PARSING_ERROR, true, PhoneNumberUtil::PHONE_MOBILE);
test('valid region specific number', '6 512 45 374'   , 'NL', PhoneNumberUtil::ERROR_NO_PARSING_ERROR, true, PhoneNumberUtil::PHONE_MOBILE);
test('valid full land number'      , '+31 848-393-464', 'ZZ', PhoneNumberUtil::ERROR_NO_PARSING_ERROR, true, PhoneNumberUtil::PHONE_FIXED_LINE);

test('invalid number' , '651245374', 'ZZ', PhoneNumberUtil::ERROR_INVALID_COUNTRY_CODE_ERROR);


PhoneNumberUtil::GetSupportedRegions($regions);

if (!is_array($regions) || empty($regions)) {
  echo "GetSupportedRegions failed!\n";
}


if (!PhoneNumberUtil::IsAlphaNumber('800MICROSOFT')) {
  echo "IsAlphaNumber failed!\n";
}



$number = '800 MICROSOFT';

PhoneNumberUtil::ConvertAlphaCharactersInNumber($number);

if ($number !== '800 642767638') {
  echo "ConvertAlphaCharactersInNumber failed\n";
}



PhoneNumberUtil::Parse('+31651245374', 'NL', $p);

PhoneNumberUtil::GetNationalSignificantNumber($p, $s);

if ($s !== '651245374') {
  echo "GetNationalSignificantNumber failed!\n";
}




if (!PhoneNumberUtil::GetExampleNumber('NL', $p)) {
  echo "GetExampleNumber 1 failed!\n";
}

if (!is_resource($p)) {
  echo "GetExampleNumber 2 failed!\n";
}



if (!PhoneNumberUtil::GetExampleNumberForType('NL', PhoneNumberUtil::PHONE_MOBILE, $p)) {
  echo "GetExampleNumberForType 1 failed!\n";
}

if (!is_resource($p)) {
  echo "GetExampleNumberForType 2 failed!\n";
}



PhoneNumberUtil::Parse('16502530000', 'US', $p);

if (PhoneNumberUtil::GetLengthOfGeographicalAreaCode($p) !== 3) {
  echo "GetLengthOfGeographicalAreaCode failed!\n";
}




PhoneNumberUtil::Parse('+31651245374', 'ZZ', $p);

if (!PhoneNumberUtil::IsValidNumberForRegion($p, 'NL')) {
  echo "IsValidNumberForRegion 1 failed!\n";
}
if (PhoneNumberUtil::IsValidNumberForRegion($p, 'BE')) {
  echo "IsValidNumberForRegion 2 failed!\n";
}


if (PhoneNumberUtil::IsNumberMatch($p, $p) != PhoneNumberUtil::MATCH_EXACT_MATCH) {
    echo "IsNumberMatch 1 failed!\n";
}


PhoneNumberUtil::Format($p, PhoneNumberUtil::FORMAT_RFC3966, $s);

if ($s != 'tel:+31-6-51245374') {
  echo "Format failed!\n";
}


PhoneNumberUtil::GetRegionCodeForNumber($p, $cc);

if ($cc != 'NL') {
  echo "GetRegionCodeForNumber failed!\n";
}


if (PhoneNumberUtil::GetCountryCodeForRegion('NL') != 31) {
  echo "GetCountryCodeForRegion failed!\n";
}


PhoneNumberUtil::GetRegionCodeForCountryCode(31, $cc);

if ($cc != 'NL') {
  echo "GetRegionCodeForCountryCode failed!\n";
}


echo "all tests done.\n";
