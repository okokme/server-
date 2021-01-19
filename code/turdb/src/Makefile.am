AUTOMAKE_OPTIONS=foreign
bin_PROGRAMS=turdb
turdb_SOURCES=\
	pmd/pmdMain.cpp pmd/pmdTest.cpp \
	bson/src/bsonobj.cpp bson/src/util/json.cpp bson/src/oid.cpp \
	bson/src/lib/base64.cpp bson/src/lib/md5.cpp bson/src/lib/nonce.cpp

turdb_CXXFLAGS=-I../boost -Ibson/src -Iinclude -D_FILE_OFFSET_BITS=64 -ggdb -Wall -O0
turdb_LDADD=-lpthread -lm -lboost_system -lboost_thread -lboost_program_options -lrt
turdb_LDFLAGS=-fPIC -rdynamic -L../boost/stage/lib -pthread
