bin/testListArray: testListArray.cpp ListArray.h List.h
	mkdir -p bin
	g++ -o bin/testListArray testListArray.cpp ListArray.h

clean:
	rm -r *.o *.gch bin
bin/testNode: testNode.cpp Node.h
	mkdir -p bin
	g++ -std=gnu++17 -Wall -Wextra -O2 -o bin/testNode testNode.cpp

