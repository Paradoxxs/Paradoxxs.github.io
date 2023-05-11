Key indicators for recognizing encryption algorithms:

## Symmetric algorithms

### RC4

- Usage of 0x100 in two loops: first in the initialization stage and then in the scrambling stage.
- Key length: 1 to 256 bytes; 16 bytes is very common.

#### Consists of three stages

- Key-scheduling algorithm (initialization stage)
  - Creates a substitution box with values from 0x00 to 0xFF.
- Pseudo-random generation stage (scrambling stage)
  - Uses the key to scramble the substitution box, thereby creating a stream of semi-random bytes.
- XOR stage
  - XORs the input against the generated stream.

### Salsa20

The algorithm can be recognized based on the constant interaction with two strings.

#### Pseudocode

The main component of the algorithm is the Quarter-Round, which takes 4-word input and produces a 4-word output.

```c++
Define QR(a, b, c, d)
( b ^= ROTL(a + d, 7)
c ^= ROTL(b + a, 9)
d ^= ROTL(c + b,13)
a ^= ROTL(d + c,18))
```

### AES

The easiest way to recognize the AES algorithm is by the lookup table for either S-Boxes or T-Tables, depending on the implementation.

### Blowfish

Can be recognized by the required S-boxes and P-arrays.

## Asymmetric algorithms

### RSA

It is common for authors to use the WinCrypt API, as it is simple, reliable, and secure.

#### Math

````text
c = ciphertext
p and q = prime numbers
n = p * q
phi = (p-1)*(q-1)  
d = inverse(e, phi)  
m = pow(c,d,n)
````

#### Weakness

Small 'e' values can be problematic, as can small 'n' values. If the 'n' value is small, we can determine the two prime numbers that were multiplied together to produce the result. Sites like factordb.com can help with this problem.

### Elliptic Curve (ECC)

Due to the difficulty of writing the algorithm correctly, it is usually possible to find an open-source repository that was used to implement the algorithm, e.g. [curve25519-donna](https://github.com/agl/curve25519-donna).