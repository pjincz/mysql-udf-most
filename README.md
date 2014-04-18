mysql-udf-most
==============

add an aggregate function to mysql, to find the most frequently occurring value

Install
-------

    make
    sudo make install
	> CREATE AGGREGATE FUNCTION most RETURNS STRING SONAME 'mysql-udf-most.so';
	> CREATE AGGREGATE FUNCTION most_times RETURNS INT SONAME 'mysql-udf-most.so';

Uninstall
---------

    sudo make uninstall
	> DROP FUNCTION most;
	> DROP FUNCTION most_times;

Usage
-----

	select most(xxx), most_times(xxx) from xxx;
