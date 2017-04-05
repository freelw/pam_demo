TARGET:=pam_demo
all:
	gcc -fPIC -c $(TARGET).c
	gcc -shared -o $(TARGET).so $(TARGET).o -lpam
cleanall:
	rm $(TARGET).so $(TARGET).o
install: all
	cp $(TARGET).so /lib/x86_64-linux-gnu/security/$(TARGET).so
