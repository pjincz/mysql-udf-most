all:
	g++ main.cpp -shared -o mysql-udf-most.so -I /usr/include/mysql

clean:
	rm -rf *.so

install:
	cp -f mysql-udf-most.so /usr/lib/mysql/plugin
	echo "DROP FUNCTION most; CREATE AGGREGATE FUNCTION most RETURNS STRING SONAME 'mysql-udf-most.so';" | mysql -u root -p 

uninstall:
	rm -rf /usr/lib/mysql/plugin/mysql-udf-most.so
	echo "DROP FUNCTION most" | mysql -u root -p
