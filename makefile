TARGET:=pam_demo
all:
	g++ -fPIC -c $(TARGET).c  
	g++ -shared -o $(TARGET).so $(TARGET).o -lpam -Wl,--whole-archive /usr/local/lib/libqrencode.a -Wl,--no-whole-archive
cleanall:
	rm $(TARGET).so $(TARGET).o 
install: all
	cp $(TARGET).so /lib/x86_64-linux-gnu/security/$(TARGET).so
