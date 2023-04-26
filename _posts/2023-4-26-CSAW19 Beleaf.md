# Solving the CSAW19 Beleaf Challenge

## Introduction
In this article, we will discuss how to solve the CSAW19 Beleaf challenge. The challenge involves finding the correct key (flag) from a given program. We will walk through the analysis of the program, the creation of a Ghidra script to help us find the flag, and the final solution. The program for this challenge can be found here: https://github.com/guyinatuxedo/nightmare/tree/master/modules/03-beginner_re/csaw19_beleaf

1. Analyzing the Program
The program is written in C and consists of a main function that performs the following operations:

a. Asks the user for input, which should be the flag.
b. Checks if the input length is less than 33 characters. If it is, the program prints "Incorrect!" and exits.
c. For each character in the input, it calls the `transform_input` function to find the index of the character in a DWORD table (4 bytes). The `transform_input` function returns the index of the character.
d. Compares the returned index with the corresponding value in the `Valid_index_array` table (8 bytes). If they do not match, the program prints "Incorrect!" and exits.
e. If all character indexes match the corresponding values in the `Valid_index_array`, the program prints "Correct!".

2. Creating a Ghidra Script
To find the correct flag, we will create a Ghidra script to help us analyze the program. This script will do the following:

a. Obtain the addresses of the `Valid_index_array` and the lookup table for the character indexes.
b. Loop through the `Valid_index_array` and store each index value.
c. Loop through each index and find the corresponding character in the lookup table.

Here is the Ghidra script:

```python
import sys

def getAddress(offset):
	return currentProgram.getAddressFactory().getDefaultAddressSpace().getAddress(offset)

l = currentProgram.getListing()
indexes = []

# Address of the valid index table
values_offset = getAddress(0x003014e0)

# loop through the table and get every 8 value because of qword
for i in range(33):
	next_address = values_offset.add(i*8)
	indexes.append(l.getDataAt(next_address).getValue().getValue())
	
# Address of the lookup table
values_offset1 = getAddress(0x00301020)

print(indexes)

# Loop through all the valid index and see what character value they match in the index look up table
for index in indexes:
	next_address = values_offset1.add(index * 4)
    # Writes about the results
	sys.stdout.write(chr(l.getDataAt(next_address).getValue().getValue()))

print("\nFinish")
```

## Finding the Flag
Running the Ghidra script, we can obtain the correct flag by analyzing the output. The script prints the character values corresponding to the valid indexes, revealing the correct flag.

## Conclusion
By understanding the program logic, creating a Ghidra script to analyze the program, and interpreting the output, we can successfully solve the CSAW19 Beleaf challenge. This step-by-step guide demonstrates the power of reverse engineering and how tools like Ghidra can help us find solutions to complex challenges.