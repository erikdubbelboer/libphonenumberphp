libphonenumberphp
==================

[libphonenumber](http://code.google.com/p/libphonenumber/) binding for php.


Installing/Configuring
----------------------

Make sure to install the cpp version of libphonenumber using their [README](http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/README).

Don't forget to run `sudo make install` after the last `make` to install the library and header files in the correct directories.

Next to install the module, run:

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

Keep in mind that not all functions of the c++ version of libphonenumber are implemented.

For examples [see the tests](https://github.com/ErikDubbelboer/libphonenumberphp/blob/master/tests/libphonenumber_01.phpt).

For more documentation see [phonenumberutil.h](http://code.google.com/p/libphonenumber/source/browse/trunk/cpp/src/phonenumbers/phonenumberutil.h) from libphonenumber.

