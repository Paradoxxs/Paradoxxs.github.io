Security is increasingly becoming a selling point for people, which means we are faced with more and more encrypted network connections, chats, and so on. As a result, we need to understand encryption implementations and identify possible ways to decrypt them. This book will not teach you to become a codebreaker, but it will introduce the basics of cryptography.

Cryptology is the study of cryptography and cryptanalysis and involves using mathematical algorithms and techniques to protect and secure information. All cryptography is based on mathematical problems, with the goal of having a problem that is easy to calculate but hard to reverse. For example, factoring two prime numbers is a relatively simple task, but reversing the math to identify the two prime numbers used to calculate the result is difficult. Cryptography has a wide range of applications in areas such as computer security and communications. There are three types of cryptographic algorithms: hashing, symmetric, and asymmetric.

| Feature/Algorithm         | Hash              | Symmetric           | Asymmetric          |
| ------------------------  | ----------------- | ------------------- | ------------------- |
| Number of keys            | 0                 | 1                   | 2                   |
| Speed                     | Fast              | Fast                | Relatively slow     |
| Complexity                | Medium            | Medium              | High                |
| Key management & sharing  | N/A               | Challenging         | Easy & Secure       |
| Examples                  | MD5, SHA1, SHA256 | AES, Blowfish, 3DES | RSA, DSA, Diffie-Hellman |

* Hashing is a one-way cryptographic method that does not allow the hash value to be reversed. Common algorithms include MD5, SHA1, and SHA256. Hashing is often used for integrity checks to ensure that data has not been altered and for storing passwords. To enhance security when hashing passwords, a salt is added, which is a random piece of data that creates uniqueness.
* Symmetric encryption uses a single key for both the encryption and decryption of content. The problem with symmetric encryption is the challenge of exchanging the key with the other party securely, as there is no secure channel available before the key is shared.
* Asymmetric encryption is a cryptographic system that uses a key pair: a public key, which may be distributed, and a private key, which should be kept private. The generation of these keys depends on cryptographic algorithms. Any content encrypted with the private key can be decrypted with the public key and vice versa.

### Ciphers

A stream cipher combines the plaintext with a digital stream (keystream), where each bit is encrypted one at a time with the corresponding digit of the keystream. In contrast, a block cipher key is used to encrypt a block of data as a group instead of one bit at a time.

| Type                        | Initialization vector | Error propagation |
| --------------------------- | --------------------- | ----------------- |
| Electronic codebook (ECB)   | Block                 | No                |
| Cipher block chaining (CBC) | Block                 | Yes               |
| Cipher feedback (CFB)       | Stream                | Yes               |
| Output feedback (OFB)       | Stream                | Yes               |
| Counter mode (CTR)          | Stream                | Yes               |

### Cryptanalysis

The most common scenarios where you will face cryptographic challenges are in encrypted communication applications, where data stored within the application databases is also encrypted, and in ransomware cases. In the latter, the goal is to look for a possible hardcoded key or identify a weakness in the encryption to decrypt everything without paying the ransom. Decrypting is always simpler if you have the key used for encryption. This is why you should look for a hardcoded encryption key or one that can be retrieved from a place you have access to, such as a local database.
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
