blackbox: blackboxFunc.cpp blackboxMain.cpp
	g++ -pthread -o $@ $^ `pkg-config --cflags --libs opencv`

clean: blackbox
	rm -rf blackbox
	
