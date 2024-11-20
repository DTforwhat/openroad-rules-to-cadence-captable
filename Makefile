edit:WriteCaptable.o main.o	
	cc -o edit WriteCaptable.o main.o	

main.o:main.cpp WriteCaptable.h	
	cc -c main.cpp	

WriteCaptable.o:WriteCaptable.cpp WriteCaptable.h	
	cc -c WriteCaptable.cpp	

clean:
	rm edit WriteCaptable.o main.o	
