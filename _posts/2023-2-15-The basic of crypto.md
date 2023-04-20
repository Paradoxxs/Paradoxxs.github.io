# The basic of cryptography

## Cryptography

Security is becoming and selling point for people, and this means we are faced with more and more encrypted network connections, chat, etc. This means for us that we need to be able to look at the implementation of encryption and being able to identify possible ways to decrypt it again. This book will not teach you to become a code breaker. This section will introduce the basics of cryptography.

Cryptology is the study of cryptography and cryptanalysis, and it involves the use of mathematical algorithms and techniques to protect and secure information. All cryptography is based on mathematical problems, to goal is to have a problem that is easy to calculate but hard to reverse the math. E.g. factoring two prime numbers, is a relatively easy task to perform, but reversing the math to identify what two prime numbers were used to calculate the result is hard. Crypto has a wide range of applications in areas such as computer security, communications and etc. There exist three types of crypto algorithms, Hashing, symmetric and asymmetric

| Feature/Algorithmn       | Hash              | Symmetric           | Aymmetric              |
| ------------------------ | ----------------- | ------------------- | ---------------------- |
| number of keys           | 0                 | 1                   | 2                      |
| Speed                    | Fast              | Fast                | Relative slow          |
| Complexity               | Medium            | Medium              | High                   |
| Key management & sharing | N/A               | Challenging         | Easy & Secure          |
| Examples                 | MD5, SHA1, SHA256 | AES, Blowfish, 3DES | RSA, DSA, Diffiehelman |

* Hashing is one-way cryptography as it does not allow the hash value to be reversed back again. Common algorithms are MD5, SHA1, and SHA256. Hashing is often used for integrity checks to ensure the data have not been altered. and for storing passwords. For additional security when hashing passwords, an salt is added, which is a random piece of data added to the hashing input to create uniqueness.
* Symmetric encryption uses a single key for both the encryption and decryption of content.\
  The problem with symmetric encryption is how to exchange the key with the other party since there does not exist a secure channel to use before the key is shared.
* Asymmetric encryption is a cryptographic system that uses key pair: a public key, which may be distributed, and a private key, which should be kept private. The generation of these keys depends on cryptographic algorithms. Any content that is encrypted with the private key can be decrypted with the public key and vice versa.


### Ciphers

Stream cipher is when the plain text is combined with a digital stream (keystream), where each bit is encrypted one at the time, with the corresponding digit of the keystream.\
Block cipher key is used to encrypt a block of data as a group instead one bit at the time.

| Type                        | Initialization vector | Error propagation |
| --------------------------- | --------------------- | ----------------- |
| Electornic code book (ECB)  | Block                 | No                |
| Cipher block chaining (CBC) | Block                 | Yes               |
| Cipher feedback (CFB)       | Stream                | Yes               |
| Output feedback (OFB)       | Stream                | Yes               |
| Counter mode (CTR)          | Stream                | Yes               |

### Crypto analysis

The most common place where you will be faced with cryptographic challenges is either with encrypted communication applications, where the data stored within the application databases are also encrypted. And with ransomware where if the goal is to look for a possible hard-coded key or identify a weakness in the encryption to identify a method of decrypting everything without paying the ransomware. When it comes to decrypting it is always simpler if you have the key that was used to encrypt the content. This is why look if the developer has either hardcoded the encryption key or is retrieved from a place you also have access to, such as a local database.

Here example of AES implementation within android notices the hardcoded key that is used to encrypt the content:

```
class AES256 {
    private val ALGORITHM = "AES"
    private val KEY = "1Hbfh667adfDEJ78"

    fun encrypt(value: String): String {
        val key: Key = generateKey()
        val cipher = Cipher.getInstance(ALGORITHM)
        cipher.init(Cipher.ENCRYPT_MODE, key)
        val encryptedByteValue = cipher.doFinal(value.toByteArray(charset("utf-8")))
        val encryptedValue64 = Base64.encodeBase64String(encryptedByteValue)
        return encryptedValue64
    }
```
The next stage is to look for what data is encrypted and then implement a function that reverses the whole process giving you access to the plaintext.

## Crypto code analysis

lets see how you analysis cryptographic code, but before we do that we should cover the basic operation used in crypto algorithms.

### Bitwise operation

I will just start with some basic bitwise operation, that is the corner stone logic for crypto operations.

### AND

The out is true only if both of the input are true.

**True table**

| and |   |   |   |
| --- | - | - | - |
|     | 0 | 1 |   |
| 0   | 0 | 0 |   |
| 1   | 0 | 1 |   |

### NOT

Not operand is and simple inverter give it a 0 it will turn it into 1 and give 1 and it will become an 0

**True table**

| not |   |   |   |
| --- | - | - | - |
| 0   | 1 |   |   |
| 1   | 0 |   |   |

### OR

The rule is that the outcome is true if either or both of the inputs are true.

**True table**

| OR |   |   |   |
| -- | - | - | - |
|    | 0 | 1 |   |
| 0  | 0 | 1 |   |
| 1  | 1 | 1 |   |

### XOR

Work very similar to _or_, it comes out as true if either one of the inputs is one. If they are both 1, it comes out as 0 which is why it called exclusive.\
Another way of putting is, the outcome is _one_ if the two input differ, otherwise it _zero_

Logic table

| XOR |   |   |   |
| --- | - | - | - |
| A   | 0 | 0 | 1 |
| B   | 0 | 1 | 0 |
| XOR | 0 | 1 | 1 |

**True table**

| XOR |   |   |
| --- | - | - |
|     | 0 | 1 |
| 0   | 0 | 1 |
| 1   | 1 | 0 |






When it comes to malware it is more difficult as you are not able to decompile it back into code. forcing you to either look at the assembly code or pseudo _c_ code. One of the most commonly used algorithms is RC4. This might be because of the efficiency as a stream cipher and relatively easy implementation. RC4 uses a symmetric key stream cipher to encrypt and decrypt the plaintext. The whole process consists of three stages, and is relatively easy to identify, by its usage of _0x100_ (_256_) in two loops. The first is in the initialization stage and then the next is the scrambling stage. It is common for the key to have a length of 16 bytes.

What you can do is look for encrypted data in the _.data_ section. One way to identify encrypted data is by looking for a random chuck of data with references in the code. Next is to look at the usage of the data in the code. when it comes to RC4 it uses loops with a range of _256_. Let's go through the three stages of RC4 to get an idea of how it works.

1. Keyscheduling algorithm (initialization stage), create substitution box with values from 0x00 to 0xFF(256), Where each value is swapped with another based on a calculation.

```python
def KSA(key):

  s = range(0,256)
  j = 0
  for i in range(0,256):
    j = (j + s[i] + key[i % len(key)]) % 256 # Table is then scrambled, swapping each value with another 
    s[i], s[j] = s[j], s[i] # Swap s[i] with s[j]
  return s
```

```c
void rc4_init(unsigned char *S, unsigned char *key, int key_length) {
    for (int i = 0; i < 256; i++) {
        S[i] = i;
    }
    int j = 0;
    for (int i = 0; i < 256; i++) {
        j = (j + S[i] + key[i % key_length]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
    }
}
```

1. Pseudorandom generation stage, which generates and outputs the keystream. Using the key to scramble the substitution box, creating a stream of semi-random bytes

```python
def PRGA(s):
  i = 0
  j = 0
  while True: # responsible for outputting the keystream used for the XOR
    i = (i+1) % 256 
    j = (j+ s[i]) % 256
    s[i],s[j] = s[j], s[i]
    k = s[(s[i] 6 s[j]) % 256]
    yield k # k is the generator containing the keysteam
```

```c
void rc4_keystream(unsigned char *S, unsigned char *keystream, int keystream_length) {
    int i = 0;
    int j = 0;
    for (int k = 0; k < keystream_length; k++) {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        unsigned char temp = S[i];
        S[i] = S[j];
        S[j] = temp;
        int t = (S[i] + S[j]) % 256;
        keystream[k] = S[t];
    }
}
```

1. XOR stage, where each byte of the plaintext is _XOR_ with the keystream.

```python
def rc4():

  plaintext = "Encryption_test"
  key = [ord(c) for c in "encryption_key"]
  output = ""

  S = KSA(key)
  keystream = PGRA(S)

  for c in plaintext: 
    output += "%02x" % (ord(c) ^ keystream.next()) #Output the chipertext as hex
  print(output) #display the chipertext
```

```c
void rc4_encrypt(unsigned char *S, unsigned char *data, int data_length) {
    unsigned char keystream[data_length];
    rc4_keystream(S, keystream, data_length);
    for (int i = 0; i < data_length; i++) {
        data[i] ^= keystream[i]; //XOR each byte of the plaintext with a byte of the keystream
    }
```

I will not be going through any more algorithms or implementations. This is just the basics of cryptographic analysis. Identifying weakness within cryptographic implementation is out of the scope of this book. I will recommend when faced with encrypted data, looking for the algorithms and the key used to encrypt the data. Then implementing a function for decrypting the data. If it is not possible to identify both it is time to hand it over to an expert codebreaker.

#### Terminology

Let's start by covering some of the basic terminologies within cryptography.

| Term                          | Description                                                                                                                                                        |
| ----------------------------- | ------------------------------------------------------------------------------------------------------------------------------------------------------------------ |
| Plaintext                     | The data that is readable by everyone                                                                                                                              |
| Ciphertext                    | The data after it have been encrypted.                                                                                                                             |
| Encrypt                       | Process of turning plaintext into ciphertext                                                                                                                       |
| Decrypt                       | Turning ciphertext to plaintext                                                                                                                                    |
| Key & crypto variable         | The key is used by the encryption algorithm for turning the plaintext into ciphertext, and reversing the process.                                                  |
| Algorithm                     | The mathematical formula used to perform the encryption, decryption, message digest and digital signature                                                          |
| Key length                    | The length of the key measured in bits, the longer the key the more effort is need to attack it.                                                                   |
| Work factor                   | The amount of time it take for an attacker to break an encryption                                                                                                  |
| Chaining                      | Using the previous cipher block as the key for the next encryption block, The purpose is to destroy patterns.                                                      |
| Key clustering                | Is when two key generate the same ciphertext output from the same plaintext input, This must be avoided                                                            |
| Initialization vector & nonce | Random bit data that is the same length as the block size that is XOR with the message. Initial vector are used to create a unique cipher text, to avoid patterns. |
| Confusion                     | Hiding the relationship between the plaintext and the resulted ciphertext by making it random                                                                      |
| Diffusion                     | When changing a bit in the plaintext half the bit in ciphertext should be changed                                                                                  |
| Avalanche                     | Small change in plaintext will result in large change in ciphertext, one bit change in plaintext should result in 50% change in ciphertext.                        |
| Hash                          | Cryptography operation on a piece of information which return a fix length string, that can not be reversed. Used to verify the integrity of files                 |
| Message digest                | Output of hashing function                                                                                                                                         |
| Digital signature             | Encrypting the message digest with the once private key, which prove authenticity and integrity of a message                                                       |
| Key encrypting key            | Key used to encrypt another key.                                                                                                                                   |
| Key exchange                  | Technique for two parties to establish an symmetric encryption key when there is no secure channel.                                                                |
| Transposition                 | Rearrange the letters of a paintext message                                                                                                                        |
| Entropy                       | The amount of randomness in the data set.                                                                                                                          |





#### Salsa20

Salsa20 uses a fixed-length key and a fixed-length nonce (a number that is used only once) to encrypt and decrypt data. The key and nonce are used to initialize a state array, which is then used to generate a keystream that is combined with the plaintext (in the case of encryption) or the ciphertext (in the case of decryption) to produce the encrypted/decrypted output.

The algorithms can be recognized based on the constant iteration with two strings.

**pseudocode**

Main component of the algoritm is the QuaterRound with takes 4 word input and produces 4 word output

```
Define QR(a, b, c, d)
( b ^= ROTL(a + d, 7)
c ^= ROTL(b + a, 9)
d ^= ROTL(c + b,13)
a ^= ROTL(d + c,18))
```

### Asymmetric algorithm

#### RSA

It every common for authors to use the WinCrypt API as it simple, reliable and secure

**Math**

```
c = ciphertext
p and q = prime numbers
n = p * q
phi = (p1)*(q1)  
d = inverse(e, phi)  
m = pow(c,d,n)
```

**Weakness**

Small e value can be a problem, the same goes for the n value if the n value is small we can figure out what the two prime number that was multiplied together to the result, sites like factordb.com can help with this problem.

#### Elliptic Curve (ECC)

Because of the difficult of writing the algorithm correctly, you are usually be able to find the open source repository that was used to implement the algorithm, e.g. [curve25519donna](https://github.com/agl/curve25519donna)