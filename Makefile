all	:
	swig -c++ -python -I/usr/local/include/ sparse_map.i
	CC="g++ --std=c++0x -I/usr/local/include/ -I/usr/include/python2.7/" LDSHARED="g++ /usr/lib/i386-linux-gnu/libstdc++.so.6 --shared " python setup.py build_ext --inplace

clean:
	git clean -f
