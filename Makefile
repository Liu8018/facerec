INCS = -I./include
SIMDLIBS = -L./libs -lSimd -lpthread
DLIBLIBS = -L./libs -ldlib -lpthread
OPENCVLIBS = -L./libs -lopencv_core -lopencv_highgui -lopencv_videoio -lopencv_imgproc -lopencv_imgcodecs

facerec:main.o FaceAlignment.o FaceRecognition.o functions.o
	g++ -o $@ $^ $(INCS) $(SIMDLIBS) $(DLIBLIBS) $(OPENCVLIBS)

main.o:main.cpp
	g++ -c -O3 $^ $(INCS) $(SIMDLIBS) $(OPENCVLIBS)

FaceAlignment.o:FaceAlignment.cpp
	g++ -c -O3 $^ $(INCS) $(DLIBLIBS) $(OPENCVLIBS)

FaceRecognition.o:FaceRecognition.cpp
	g++ -c -O3 $^ $(INCS) $(DLIBLIBS) $(OPENCVLIBS)

functions.o:functions.cpp
	g++ -c -O3 $^ $(INCS) $(SIMDLIBS) $(DLIBLIBS) $(OPENCVLIBS)

clean:
	rm *.o
cleanAll:
	rm *.o facerec