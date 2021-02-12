Instruction Processor
=====================

This project requires the implemenation of a very simple processor to execute instructions. The instruction format used is intended to be very simple (while not being space efficient):

Instructions are all 4 bytes. Each byte represents the following:

- Byte 0: Operation to execute
- Byte 1: Source register
- Byte 2: Destination register
- Byte 3: Immediate Value (signed)
