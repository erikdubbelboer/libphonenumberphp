libphonenumberphp
==================

[libphonenumber](http://code.google.com/p/libphonenumber/) binding for php.


Installing/Configuring
----------------------

Make sure to install the cpp version of libphonenumber using their [README](http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/README).

To install the module, run:

<pre>
phpize
./configure
make
sudo make install
</pre>

You will need to edit the `libphonenumberphp.ini` file to point to your extension and database file. You can find your extension directory using:

<pre>
php-config --extension-dir
</pre>

Now copy `libphonenumberphp.ini` to your php install's configuration directory. On Gentoo this will usually be `/etc/php/cgi-php5/ext-active/`. On Ubuntu this will be `/etc/php5/conf.d`

<pre>
cp libphonenumberphp.ini /etc/php5/conf.d/
</pre>

After restarting php the extension should be working.


Usage
-----

Not nearly all functions of the c++ version of libphonenumber are implemented.

libphonenumberphp exports the following class:

```php
<?

class PhoneNumberUtil {
  // Phone number types:
  const FIXED_LINE;
  const MOBILE;
  // In some regions (e.g. the USA), it is impossible to distinguish between fixed-line and mobile numbers
   // by looking at the phone number itself.
  const FIXED_LINE_OR_MOBILE;
  // Freephone lines
  const TOLL_FREE;
  const PREMIUM_RATE;
  // The cost of this call is shared between the caller and the recipient, and is hence typically less
  // than PREMIUM_RATE calls. See http://en.wikipedia.org/wiki/Shared_Cost_Service for more information.
  const SHARED_COST;
  // Voice over IP numbers. This includes TSoIP (Telephony Service over IP).
  const VOIP;
  // A personal number is associated with a particular person, and may be routed to either a MOBILE or
  // FIXED_LINE number. Some more information can be found here: http://en.wikipedia.org/wiki/Personal_Numbers
  const PERSONAL_NUMBER;
  const PAGER;
  // Used for "Universal Access Numbers" or "Company Numbers". They may be further routed to specific
  // offices, but allow one number to be used for a company.
  const UAN;
  // Used for "Voice Mail Access Numbers".
  const VOICEMAIL;
  // A phone number is of type UNKNOWN when it does not fit any of the know patterns for a specific region.
  const UNKNOWN;


  // Parsing errors:
  const NO_PARSING_ERROR;
  const INVALID_COUNTRY_CODE_ERROR;
  const NOT_A_NUMBER;
  const TOO_SHORT_AFTER_IDD;
  const TOO_SHORT_NSN;
  const TOO_LONG_NSN;


  // Parse a string into a PhoneNumber resource object.
  // Returns one of the Parsing errors constants defined above. NO_PARSING_ERROR is returned if it parsed correctly.
  // Note that validation of whether the number is actually a valid number for a particular region is not performed.
  // This can be done separately with IsValidNumber()
  public static function Parse(string number, string default_region, PhoneNumber &phonenumber);

  // Gets the type of a phone number.
  // Returns one of the Phone number type constants defined above.
  public static function GetNumberType(PhoneNumber phonenumber);

  // Returns either true of false.
  // Tests whether a phone number matches a valid pattern. Note this doesn't verify the number is actually in use,
  // which is impossible to tell by just looking at a number itself.
  public static function IsValidNumber(PhoneNumber phonenumber);

  // Returns either true of false.
  // If the country calling code is not the same as the country calling code for the region, this immediately exits
  // with false. After this, the specific number pattern rules for the region are examined.
  public static function IsValidNumberForRegion(PhoneNumber phonenumber, string region);

  // Returns nothing.
  // Fills region with the region code for where a phone number is from.
  public static function GetRegionCodeForNumber(PhoneNumber phonenumber, string &region);

  // Returns the country calling code for a specific region. For example, this would be 1 for the United States,
  // and 64 for New Zealand.
  public static function GetCountryCodeForRegion(string region);

  // Returns nothing.
  // Fills region with the the region code that matches the specific country code. Note that it is possible that several
  // regions share the same country calling code (e.g. US and Canada), and in that case, only one of the
  //  regions (normally the one with the largest population) is returned.
  public static function GetRegionCodeForCountryCode(int countrycode, string &region);
}
```

For example see [test.php](https://github.com/ErikDubbelboer/libphonenumberphp/blob/master/test.php).

For more documentation see [phonenumberutil.h](http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h) from libphonenumber.

