TARGET:=pam_demo
all:
	g++ -fPIC -c $(TARGET).c  
	#g++ -c -fPIC $(TARGET).c -o $(TARGET).o 
#	g++ -c -fPIC /usr/local/lib/libqrencode.a  -o qren.o
	#ld -shared -fPIC  $(TARGET).o /usr/local/lib/libqrencode.a -o merge.o
	#g++ -c -fPIC merge0.o -o merge.o
	#g++ -shared -o $(TARGET).so $(TARGET).o -lpam -lqrencode -Wl,--whole-archive /usr/local/lib/libqrencode.a 
	g++ -shared -o $(TARGET).so -lpam -Wl,--whole-archive /usr/local/lib/libqrencode.a -Wl,--no-whole-archive
cleanall:
	rm $(TARGET).so $(TARGET).o 
install: all
	cp $(TARGET).so /lib/x86_64-linux-gnu/security/$(TARGET).so
