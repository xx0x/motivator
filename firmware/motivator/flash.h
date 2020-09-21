// Callback invoked when received READ10 command.
// Copy disk's data to buffer (up to bufsize) and
// return number of copied bytes (must be multiple of block size)
int32_t msc_read_cb(uint32_t lba, void *buffer, uint32_t bufsize)
{
    // Note: SPIFLash Bock API: readBlocks/writeBlocks/syncBlocks
    // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
    return flash.readBlocks(lba, (uint8_t *)buffer, bufsize / 512) ? bufsize : -1;
}

// Callback invoked when received WRITE10 command.
// Process data in buffer to disk's storage and
// return number of written bytes (must be multiple of block size)
int32_t msc_write_cb(uint32_t lba, uint8_t *buffer, uint32_t bufsize)
{
    digitalWrite(LED_BUILTIN, HIGH);

    // Note: SPIFLash Bock API: readBlocks/writeBlocks/syncBlocks
    // already include 4K sector caching internally. We don't need to cache it, yahhhh!!
    return flash.writeBlocks(lba, buffer, bufsize / 512) ? bufsize : -1;
}

// Callback invoked when WRITE10 command is completed (status received and accepted by host).
// used to flush any pending cache.
void msc_flush_cb(void)
{
    // sync with flash
    flash.syncBlocks();

    // clear file system's cache to force refresh
    fatfs.cacheClear();



    digitalWrite(LED_BUILTIN, LOW);
}

void flashSetup()
{
    flash.begin();
    // Set disk vendor id, product id and revision with string up to 8, 16, 4 characters respectively
    usb_msc.setID("Adafruit", "External Flash", "1.0");
    // Set callback
    usb_msc.setReadWriteCallback(msc_read_cb, msc_write_cb, msc_flush_cb);
    // Set disk size, block size should be 512 regardless of spi flash page size
    usb_msc.setCapacity(flash.pageSize() * flash.numPages() / 512, 512);
    // MSC is ready for read/write
    usb_msc.setUnitReady(true);
    usb_msc.begin();
    // Init file system on the flash
    fatfs.begin(&flash);

    Serial.println("Adafruit TinyUSB Mass Storage External Flash example");
    Serial.print("JEDEC ID: ");
    Serial.println(flash.getJEDECID(), HEX);
    Serial.print("Flash size: ");
    Serial.println(flash.size());


}
