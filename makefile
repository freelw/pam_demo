TARGET:=pam_demo
all:
	gcc -fPIC -c pam_module.c
	gcc -shared -o $(TARGET).so $(TARGET).o -lpam
cleanall:
	rm $(TARGET).so $(TARGET).o