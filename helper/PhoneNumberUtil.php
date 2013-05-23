<?php

/**
 * Helper auto-complete for libphonenumberphp extension
 *
 * 
 */
class PhoneNumberUtil {

    /**
     * E164 format is as per INTERNATIONAL format but with no formatting applied e.g. "+41446681800".
     */
    const FORMAT_E164 = 0;
    /**
     * INTERNATIONAL format is consistent with the definition in ITU-T Recommendation E. 123.
     */
    const FORMAT_INTERNATIONAL = 1;
    /**
     * NATIONAL format is consistent with the definition in ITU-T Recommendation E. 123.
     */
    const FORMAT_NATIONAL = 2;
    /**
     * RFC3966 is as per INTERNATIONAL format, but with all spaces and other
     * separating symbols replaced with a hyphen, and with any phone number
     * extension appended with ";ext=". It also will have a prefix of "tel:"
     * added, e.g. "tel:+41-44-668-1800".
     */
    const FORMAT_RFC3966 = 3;

    /** enum PhoneNumberType Phone number types */
	const PHONE_FIXED_LINE = 0;
	const PHONE_MOBILE = 1;
    /**
     * In some regions (e.g. the USA), it is impossible to distinguish between
     * fixed-line and mobile numbers by looking at the phone number itself.
     */
	const PHONE_FIXED_LINE_OR_MOBILE = 2;
	const PHONE_TOLL_FREE = 3;
	const PHONE_PREMIUM_RATE = 4;
	const PHONE_SHARED_COST = 5;
	const PHONE_VOIP = 6;
	const PHONE_PERSONAL_NUMBER = 7;
	const PHONE_PAGER = 8;
	const PHONE_UAN = 9;
	const PHONE_VOICEMAIL = 10;
	const PHONE_UNKNOWN = 11;

    /** enum MatchType Types of phone number matches */
	const MATCH_INVALID_NUMBER = 0;
	const MATCH_NO_MATCH = 1;
	const MATCH_SHORT_NSN_MATCH = 2;
	const MATCH_NSN_MATCH = 3;

    /** Indicates both numbers are an exact match */
	const MATCH_EXACT_MATCH = 4;

    /** enum ErrorType Parsing errors */
	const ERROR_NONE = 0;
	const ERROR_INVALID_COUNTRY_CODE_ERROR = 0;
	const ERROR_NOT_A_NUMBER = 0;
	const ERROR_TOO_SHORT_AFTER_IDD = 0;
	const ERROR_TOO_SHORT_NSN = 0;
	const ERROR_TOO_LONG_NSN = 0;

    /**
     * Convenience method to get a list of what regions libphonenumber has metadata for.
     * @param array $regions
     */
    public static function GetSupportedRegions(&$regions) {}

    /**
     * Returns true if the number is a valid vanity (alpha) number such as 800
     * MICROSOFT. A valid vanity number will start with at least 3 digits and will
     * have three or more alpha characters. This does not do region-specific
     * checks - to work out if this number is actually valid for a region, it
     * should be parsed and methods such as {@link IsPossibleNumberWithReason()} or
     * {@link IsValidNumber() IsValidNumber} should be used.
     * 
     * @param string $number
     * 
     * @return bool True if the supplied number is a vanity (alpha) number
     */
    public static function IsAlphaNumber($number) {}

    /**
     * Converts all alpha characters in a number to their respective digits on
     * a keypad, but retains existing formatting.
     *
     * @param string $number
     */
    public static function ConvertAlphaCharactersInNumber(&$number) {}

    /**
     * Normalizes a string of characters representing a phone number. This
     * converts wide-ascii and arabic-indic numerals to European numerals, and
     * strips punctuation and alpha characters.
     *
     * @param string $number
     */
    public static function NormalizeDigitsOnly(&$number) {}

    /**
     * Gets the national significant number of a phone number. Note a national
     * significant number doesn't contain a national prefix or any formatting.
     *
     * @param resource $number
     * @param string $nationalSignificantNumber
     */
    public static function GetNationalSignificantNumber($number, &$nationalSignificantNumber) {}

    /**
     * Gets the length of the geographical area code from the PhoneNumber object
     * passed in, so that clients could use it to split a national significant
     * number into geographical area code and subscriber number. It works in such
     * a way that the resultant subscriber number would be dialed, at least on
     * some devices. An example of how this could be used:
     *
     * <code>
     * PhoneNumberUtil.Parse("16502530000", "US", $number);
     * PhoneNumberUtil.GetNationalSignificantNumber($number, $nationalSignificantNumber);
     *
     * $areaCodeLength = PhoneNumberUtil.GetLengthOfGeographicalAreaCode($number);
     * if ($areaCodeLength > 0) {
     *   $areaCode = substr($nationalSignificantNumber, 0, $areaCodeLength);
     *   $subscriberNumber = substr($nationalSignificantNumber, $areaCodeLength);
     * } else {
     *   $areaCode = "";
     *   $subscriberNumber = $nationalSignificantNumber;
     * }
     * </code>
     *
     * N.B.: area code is a very ambiguous concept, so the authors generally
     * recommend against using it for most purposes, but recommend using the
     * more general national_number instead. Read the following carefully before
     * deciding to use this method:
     * - geographical area codes change over time, and this method honors those
     *   changes; therefore, it doesn't guarantee the stability of the result it
     *   produces.
     * - subscriber numbers may not be diallable from all devices (notably mobile
     *   devices, which typically requires the full national_number to be dialled
     *   in most regions).
     * - most non-geographical numbers have no area codes, including numbers
     *   from non-geographical entities.
     * - some geographical numbers have no area codes.
     * 
     * @param resource $number
     *
     * @return int
     */
    public static function GetLengthOfGeographicalAreaCode($number) {}

    /**
     * Formats a phone number in the specified format using default rules. Note
     * that this does not promise to produce a phone number that the user can
     * dial from where they are - although we do format in either NATIONAL or
     * INTERNATIONAL format depending on what the client asks for, we do not
     * currently support a more abbreviated format, such as for users in the
     * same area who could potentially dial the number without area code.
     * 
     * @param resource $number The phone number resource to be formatted
     * @param string $number_format One of the FORMAT_ constants
     * @param string $formatted_number The formatted number
     */
    public static function Format($number, $number_format, &$formatted_number) {}


    /**
     * Formats a phone number in national format for dialing using the carrier as
     * specified in the $carrier_code. The $carrier_code will always be used
     * regardless of whether the phone number already has a preferred domestic
     * carrier code stored. If $carrier_code contains an empty string, return the
     * number in national format without any carrier code.
     *
     * @param resource $number
     * @param string $carrier_code
     * @param string $formatted_number
     */
    public static function FormatNationalNumberWithCarrierCode($number, $carrier_code, &$formatted_number) {}


    /**
     * Formats a phone number in national format for dialing using the carrier as
     * specified in the preferred_domestic_carrier_code field of the PhoneNumber
     * object passed in. If that is missing, use the fallback_carrier_code passed
     * in instead. If there is no preferred_domestic_carrier_code, and the
     * fallback_carrier_code contains an empty string, return the number in
     * national format without any carrier code.
     *
     * Use {@link FormatNationalNumberWithCarrierCode} instead if the carrier code passed
     * in should take precedence over the number's preferred_domestic_carrier_code
     * when formatting.
     * 
     * @param resource $number
     * @param string $fallback_carrier_code
     * @param string $formatted_number
     */
    public static function FormatNationalNumberWithPreferredCarrierCode($number,
                                                                        $fallback_carrier_code, &$formatted_number) {}

    /**
     * Gets the type of a phone number.
     *
     * @param resource $number
     *
     * @return int One of the PHONE_ constants
     */
    public static function GetNumberType($number) {}

    /**
     * Tests whether a phone number matches a valid pattern. Note this doesn't
     * verify the number is actually in use, which is impossible to tell by just
     * looking at a number itself.
     * 
     * @param resource $number
     *
     * @return bool If the provided number is valid
     */
    public static function IsValidNumber($number) {}

    /**
     * Tests whether a phone number is valid for a certain region. Note this
     * doesn't verify the number is actually in use, which is impossible to tell
     * by just looking at a number itself. If the country calling code is not the
     * same as the country calling code for the region, this immediately exits
     * with false.  After this, the specific number pattern rules for the region
     * are examined.
     * This is useful for determining for example whether a particular number is
     * valid for Canada, rather than just a valid NANPA number.
     * Warning: In most cases, you want to use IsValidNumber instead. For
     * example, this method will mark numbers from British Crown dependencies
     * such as the Isle of Man as invalid for the region "GB" (United Kingdom),
     * since it has its own region code, "IM", which may be undesirable.
     * 
     * @param resource $number
     * @param string $region
     *
     * @return bool
     */
    public static function IsValidNumberForRegion($number, $region) {}

    /**
     * Returns the region where a phone number is from. This could be used for
     * geo-coding at the region level.
     * 
     * @param resource $number
     * @param string $region
     */
    public static function GetRegionCodeForNumber($number, &$region) {}

    /**
     * Returns the country calling code for a specific region. For example,
     * this would be 1 for the United States, and 64 for New Zealand.
     * 
     * @param string $region
     * @return int The country code for the provided $region
     */
    public static function GetCountryCodeForRegion($region) {}

    /**
     * Returns the region code that matches the specific country code. Note that
     * it is possible that several regions share the same country calling code
     * (e.g. US and Canada), and in that case, only one of the regions (normally
     * the one with the largest population) is returned.
     * 
     * @param int $countryCode
     * @param string $region
     */
    public static function GetRegionCodeForCountryCode($countryCode, &$region) {}

    /**
     * Gets a valid fixed-line number for the specified region. Returns false if
     * the region was unknown, or the region 001 is passed in. For 001
     * (representing non-geographical numbers), call
     * GetExampleNumberForNonGeoEntity instead.
     * 
     * @param string $region
     * @param resource $number
     *
     * @return bool True if the call succeeds
     */
    public static function GetExampleNumber($region, &$number) {}

    /**
     * Gets a valid number of the specified type for the specified region.
     * Returns false if the region was unknown or 001, or if no example number of
     * that type could be found. For 001 (representing non-geographical numbers),
     * call {@link GetExampleNumberForNonGeoEntity} instead.
     * 
     * @param string $region
     * @param string $type
     * @param resource $number
     */
    public static function GetExampleNumberForType($region, $type, &$number) {}

    /**
     * Parses a string and returns a parsed phone number. This method will
     * return an error like {@link ERROR_INVALID_COUNTRY_CODE} if the number is not considered
     * to be a possible number, and {@link ERROR_NO_PARSING_ERROR} if it parsed correctly. Note
     * that validation of whether the number is actually a valid number for a
     * particular region is not performed. This can be done separately with
     * {@link IsValidNumber}.
     *
     * $number can also be provided in RFC3966 format.
     *
     * default_region represents the country that we are expecting the number to
     * be from. This is only used if the number being parsed is not written in
     * international format. The country_code for the number in this case would be
     * stored as that of the default country supplied. If the number is guaranteed
     * to start with a '+' followed by the country calling code, then
     * "ZZ" can be supplied.
     *
     * @param string $number
     * @param string $default_region
     * @param resource $phoneNumber
     *
     * @return int One of the ERROR_ constants
     */
    public static function Parse($number, $default_region, &$phoneNumber) {}

    /**
     * Takes two phone numbers and compares them for equality.
     *
     * Returns {@link PhoneNumberUtil::MATCH_EXACT_MATCH} if the country calling code, NSN, presence of a leading
     * zero for Italian numbers and any extension present are the same.
     * Returns {@link MATCH_NSN_MATCH} if either or both has no country calling code specified,
     * and the NSNs and extensions are the same.
     * Returns {@link MATCH_SHORT_NSN_MATCH} if either or both has no country calling code
     * specified, or the country calling code specified is the same, and one NSN
     * could be a shorter version of the other number. This includes the case
     * where one has an extension specified, and the other does not.
     * Returns {@link MATCH_NO_MATCH} otherwise.
     * For example, the numbers +1 345 657 1234 and 657 1234 are a
     * {@link SHORT_NSN_MATCH}. The numbers +1 345 657 1234 and 345 657 are a NO_MATCH.
     * 
     * @param resource $firstNumber
     * @param resource $secondNumber
     *
     * @return int One of the MATCH_ constants
     */
    public static function IsNumberMatch($firstNumber, $secondNumber) {}

    /**
     * Takes two phone numbers as strings and compares them for equality. This
     * is a convenience wrapper for {@link IsNumberMatch}. No default region is known.
     * Returns MATCH_INVALID_NUMBER if either number cannot be parsed into a phone
     * number.
     * 
     * @param string $firstNumber
     * @param string $secondNumber
     *
     * @return int One of the MATCH_ constants
     */
    public static function IsNumberMatchWithTwoStrings($firstNumber, $secondNumber) {}

    /**
     * Takes two phone numbers and compares them for equality. This is a
     * convenience wrapper for {@link IsNumberMatch}. No default region is known.
     * Returns MATCH_INVALID_NUMBER if second_number cannot be parsed into a phone
     * number.
     * 
     * @param resource $firstNumber
     * @param string $secondNumber
     *
     * @return int One of the MATCH_ constants
     */
    public static function IsNumberMatchWithOneString($firstNumber, $secondNumber) {}


}