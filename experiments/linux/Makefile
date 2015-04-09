obj-m := snet_driver.o snet_fha.o

all:
    make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
    rm -rf *.o *~ core .depend .*.cmd *.ko *.mod.c .tmp_versions Module.symvers modules.order
