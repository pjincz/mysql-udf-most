all:
	g++ main.cpp -shared -o mysql-udf-most.so -I /usr/include/mysql -fPIC

clean:
	rm -rf *.so

install:
	cp -f mysql-udf-most.so /usr/lib/mysql/plugin

uninstall:
	rm -rf /usr/lib/mysql/plugin/mysql-udf-most.so
