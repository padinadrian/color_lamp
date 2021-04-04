Programming the nrf52840:

1. Build the sketch using Arduino IDE
2. Find the folder where the Arduino outputs the hex file
3. Copy the hex file to this folder
4. Run uf2conv.py:

./uf2conv.py color_lamp.ino.hex -c -f 0xADA52840 -o color_lamp.uf2

5. Double click the button on the feather. Folder should appear
6. Copy the uf2 file to the folder