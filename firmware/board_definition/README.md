
## libraries/Adafruit_SPIFlash/src/Adafruit_SPIFlashBase.cpp
add `S25FL064L` to `possible_devices` list

## packages/adafruit/hardware/samd/1.5.11/boards.txt

add

```
xx0x_motivator.name=xx0x Motivator
xx0x_motivator.vid.0=0x239A
xx0x_motivator.pid.0=0x801B
xx0x_motivator.vid.1=0x239A
xx0x_motivator.pid.1=0x001B
xx0x_motivator.upload.tool=bossac
xx0x_motivator.upload.protocol=sam-ba
xx0x_motivator.upload.maximum_size=262144
xx0x_motivator.upload.offset=0x2000
xx0x_motivator.upload.use_1200bps_touch=true
xx0x_motivator.upload.wait_for_upload_port=true
xx0x_motivator.upload.native_usb=true
xx0x_motivator.build.mcu=cortex-m0plus
xx0x_motivator.build.f_cpu=48000000L
xx0x_motivator.build.usb_product="xx0x Motivator"
xx0x_motivator.build.usb_manufacturer="xx0x"
xx0x_motivator.build.board=XX0X_MOTIVATOR
xx0x_motivator.build.core=arduino
xx0x_motivator.build.extra_flags=-DARDUINO_SAMD_ZERO -DARDUINO_SAMD_FEATHER_M0 -DARM_MATH_CM0PLUS -DADAFRUIT_FEATHER_M0_EXPRESS -D__SAMD21G18A__ {build.usb_flags}
xx0x_motivator.build.ldscript=linker_scripts/gcc/flash_with_bootloader.ld
xx0x_motivator.build.openocdscript=openocd_scripts/feather_m0_express.cfg
xx0x_motivator.build.variant=xx0x_motivator
xx0x_motivator.build.variant_system_lib=
xx0x_motivator.build.vid=0x239A
xx0x_motivator.build.pid=0x801B
xx0x_motivator.bootloader.tool=openocd
xx0x_motivator.bootloader.file=featherM0/bootloader-feather_m0-v2.0.0-adafruit.5.bin
xx0x_motivator.menu.usbstack.arduino=Arduino
xx0x_motivator.menu.usbstack.tinyusb=TinyUSB
xx0x_motivator.menu.usbstack.tinyusb.build.flags.usbstack=-DUSE_TINYUSB
xx0x_motivator.menu.debug.off=Off
xx0x_motivator.menu.debug.on=On
xx0x_motivator.menu.debug.on.build.flags.debug=-g
```

## Extract xx0x_motivator.zip
To directory `packages/adafruit/hardware/samd/1.5.11/variants/xx0x_motivator`