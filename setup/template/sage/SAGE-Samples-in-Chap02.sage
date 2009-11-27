########################################################
#    Sage code samples (Nov. 2009)
#    from chapter 2 of the CrypTool script
########################################################

print "CHAP 02: ============================================"
print "CHAP 02: ============================================"
print "CHAP 02: ============================================"

# =========================================================================
# SAMPLE 01: Simple Transposition by shifting (key and inverse key explicitely given)
# ==========

# transposition cipher using a block length of 14
T = TranspositionCryptosystem(AlphabeticStrings(), 14)
# given plaintext
P   = "a b c d e f g h i j k l m n"
# encryption key
key = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 2]

# encode plaintext (get rid of non-alphabet chars, convert lower-case into upper-case)
msg = T.encoding(P)
# encrypt plaintext by shifting to the left by 2 letters (do it in two steps)
E   = T(key)
C   = E(msg); C

# decrypt ciphertext by shifting to the left by 12 letters
keyInv = [13, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
D   = T(keyInv)
D(C)

# Representation of key and inverse key as permutations
E
D



# =========================================================================
# SAMPLE 02: Simple Transposition by shifting (key and inverse key constructed with "range")
# ======

# transposition cipher using a block length of 14, code more variable
keylen = 14
shift = 2
A = AlphabeticStrings()
T = TranspositionCryptosystem(A, keylen)

# construct the plaintext string from the first 14 letters of the alphabet plus blanks
# plaintext   = "A B C D E F G H I J K L M N"
A.gens()
P='' 
for i in range(keylen): P=P + " " + str(A.gen(i))

P

# encryption key
# key = [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 1, 2]
key = [(i+shift).mod(keylen) + 1 for i in range(keylen)]; key

# encode plaintext (get rid of non-alphabet chars)
msg = T.encoding(P)

# encrypt plaintext by shifting to the left by 2 letters (do it in one step)
C   = T.enciphering(key, msg); C

# decrypt ciphertext by shifting to the left by 12 letters
# keyInv = [13, 14, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12]
shiftInv=keylen-shift;
keyInv = [(i+shiftInv).mod(keylen) + 1 for i in range(keylen)]; keyInv
DC   = T.enciphering(keyInv, C); DC

# using the deciphering method requires to change the type of the variable key
DC  = T.deciphering(T(key).key(), C); DC

# representation of key and inverse key as permutations
T(key)
T(key).key()
T(keyInv)




# =========================================================================
# SAMPLE 03: Simple Column Transposition with randomly generated (permutation) key
# ==========

# Remark: Enciphering here requires, that the length of msg is a multiple of keylen
keylen = 14   # length of key
A = AlphabeticStrings()
T = TranspositionCryptosystem(A, keylen); T

P = "a b c d e f g h i j k l m n o p q r s t u v w x y z a b"
key = T.random_key(); key
msg = T.encoding(P); msg
C   = T.enciphering(key, msg); C
DC  = T.deciphering(key, C); DC

# Just another way of decryption: Using "enciphering" with the inverse key
keyInv = T.inverse_key(key); keyInv
DC     = T.enciphering(keyInv, C); DC

# Test correctness of decryption
msg == DC





# =========================================================================
# SAMPLE 04: Simple Column Transposition (showing the key_space)
# ==========

keylen = 14   # length of key
A = AlphabeticStrings()
T = TranspositionCryptosystem(A, keylen); T
T.key_space()
# Remark: The key space is not quite correct as also permutations shorter than keylen are counted.

P = "a b c d e f g h i j k l m n o p q r s t u v w x y z a b"
key = T.random_key(); key
msg = T.encoding(P); msg

# enciphering in one and in two steps
C   = T.enciphering(key, msg); C

enc = T(key); enc.key()
C = enc(msg); C

# deciphering
DC  = T.deciphering(key, C); DC





# =========================================================================
# SAMPLE 05: Monoalphabetic Substitution with randomly generated key
# ==========

# plaintext/ciphertext alphabet
A   = AlphabeticStrings()
S   = SubstitutionCryptosystem(A)

P   = "Substitute this with something else better."
key = S.random_key(); key

# method encoding can be called from A or from T
msg = A.encoding(P); msg
C   = S.enciphering(key, msg); C

DC  = S.deciphering(key, C); DC
msg == DC




# =========================================================================
# SAMPLE 06: Caesar (substitution by shifting the alphabet; key explicitely given, step-by-step approach)
# ==========

# plaintext/ciphertext alphabet
A = AlphabeticStrings()
P = "Shift the alphabet three positions to the right."

# construct Caesar cipher
S = SubstitutionCryptosystem(A)
key = A([3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
         20, 21, 22, 23, 24, 25, 0, 1, 2])

# encrypt message
msg     = A.encoding(P); msg
encrypt = S(key); encrypt
C       = encrypt(msg); C

# decrypt message
keyInv = A([23, 24, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
            14, 15, 16, 17, 18, 19, 20, 21, 22])
decrypt = S(keyInv); decrypt
DC      = decrypt(C); DC
msg == DC




# =========================================================================
# SAMPLE 07: Caesar (substitution by shifting the alphabet; substitution key generated, len shown)
# ==========

# plaintext/ciphertext alphabet
A = AlphabeticStrings()
keylen = len(A.gens()); keylen
shift  = 3
P = "Shift the alphabet three positions to the right."

# construct Caesar cipher
S = SubstitutionCryptosystem(A)
# key = A([3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, \
#          20, 21, 22, 23, 24, 25, 0, 1, 2])
key = [(i+shift).mod(keylen) for i in range(keylen)];
key = A(key); key
len(key)

# encrypt message
msg     = A.encoding(P); msg
C       = S.enciphering(key, msg); C

# decrypt message
# keyInv = A([23, 24, 25, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
#             14, 15, 16, 17, 18, 19, 20, 21, 22])
shiftInv=keylen-shift;
keyInv = [(i+shiftInv).mod(keylen) for i in range(keylen)];
keyInv = A(keyInv); keyInv
DC     = S.enciphering(keyInv, C); DC

# Just another way of decryption: Using "deciphering" with the key
DC     = S.deciphering(key, C); DC

msg == DC






# =========================================================================
# SAMPLE 08: A shift cipher over the upper-case letters of the English alphabet
# ==========

# construct Shift cipher directly
shiftcipher = ShiftCryptosystem(AlphabeticStrings()); shiftcipher
P = shiftcipher.encoding("Shift me any number of positions."); P
key = 12 # shift can be any integer number

# shift the plaintext by 12 positions to get the ciphertext
C = shiftcipher.enciphering(key, P); C

# decrypt the ciphertext and ensure that it is the original plaintext
DC = shiftcipher.deciphering(key, C); DC

DC == P





# =========================================================================
# SAMPLE 09: Constructing the Caesar cipher using the shift cipher
# ==========

# create a Caesar cipher
caesarcipher = ShiftCryptosystem(AlphabeticStrings())
P = caesarcipher.encoding("Shift the alphabet by three positions to the right."); P

key = 3 # shift the plaintext by exactly 3 positions
C = caesarcipher.enciphering(key, P); C

# decrypt the ciphertext and ensure that it is the original plaintext
DC = caesarcipher.deciphering(key, C); DC

DC == P





# =========================================================================
# SAMPLE 10: An affine cipher with key (3; 13)
# ==========

# create an affine cipher
affineCipher = AffineCryptosystem(AlphabeticStrings()); affineCipher
P = affineCipher.encoding("The affine cryptosystem.")
P

# encrypt the plaintext using the key (3, 13)
a, b = (3, 13)
C = affineCipher.enciphering(a, b, P)
C

# decrypt the ciphertext and make sure that it is equivalent to the original plaintext
DC = affineCipher.deciphering(a, b, C)
DC

DC == P





# =========================================================================
# SAMPLE 11: Constructing a shift cipher using the affine cipher
# ==========

# construct a shift cipher
shiftcipher = AffineCryptosystem(AlphabeticStrings()); shiftcipher
P = shiftcipher.encoding("Shift me any number of positions.")
P

# shift the plaintext by 12 positions to get the ciphertext
a, b = (1, 12)
C = shiftcipher.enciphering(a, b, P)
C

# decrypt the ciphertext and ensure that it is the original plaintext
DC = shiftcipher.deciphering(a, b, C); P

DC == P





# =========================================================================
# SAMPLE 12: Constructing the Caesar cipher using the affine cipher
# ==========

# create a Caesar cipher
caesarcipher = AffineCryptosystem(AlphabeticStrings())
P = caesarcipher.encoding("Shift the alphabet by three positions to the right.")
P

# shift the plaintext by 3 positions
a, b = (1, 3)
C = caesarcipher.enciphering(a, b, P)
C

# decrypt the ciphertext and ensure that it is the original plaintext
DC = caesarcipher.deciphering(a, b, C)
DC

DC == P





# =========================================================================
# SAMPLE 13: Monoalphabetic substitution with a binary alphabet
# ==========

# the plaintext/ciphertext alphabet
B = BinaryStrings()
# substitution cipher over the alphabet B; no keylen argument possible
S = SubstitutionCryptosystem(B); S
# To get a substitute for each symbol, key has always the length of the alphabet
key = S.random_key(); key
len(key)
P = "Working with binary numbers."
# encryption
msg = B.encoding(P); msg
C   = S.enciphering(key, msg); C
# decryption
DC  = S.deciphering(key, C); DC
msg == DC
### This does not work yet: AlphabeticStrings().encoding only accepty strings
### A = AlphabeticStrings()
### DDC = A.encoding(DC); DDC
### P == DCC



# =========================================================================
# SAMPLE 14: Monoalphabetic substitution with a hexadecimal alphabet (and decoding in Python)
# ==========

A = HexadecimalStrings()
S = SubstitutionCryptosystem(A)
key = S.random_key(); key
len(key)
# Number of possible keys
factorial(len(key))

P   = "Working with a larger alphabet."

msg = A.encoding(P); msg
C   = S.enciphering(key, msg); C

DC  = S.deciphering(key, C); DC
msg == DC

# Conversion hex back to ASCII:
# - AlphabeticStrings() and HexadecimalStrings() don't have according methods.
# - So we used Python directly.
import binascii
DDC = binascii.a2b_hex(repr(DC)); DDC

P == DDC


# =========================================================================
# SAMPLE 15: Vigenère cipher
# ==========

# construct Vigenere cipher
keylen = 14
A = AlphabeticStrings()
V = VigenereCryptosystem(A, keylen); V

# alternative could be a given key: key = A('ABCDEFGHIJKLMN'); key
key = V.random_key(); key
len(key)

# encoding
P = "The Vigenere cipher is polyalphabetic."
len(P)
msg = V.encoding(P); msg     # alternative: msg = A.encoding(P); msg

# encryption [2 alternative ways (in two steps or in one): both work]
# encrypt = V(key); encrypt
# C = encrypt(msg); C
C   = V.enciphering(key, msg); C

# decryption
DC  = V.deciphering(key, C); DC
msg == DC




# =========================================================================
# SAMPLE 16: Hill cipher
# ==========

# construct a Hill cipher
keylen = 19    # keylen = 3  # Alternative key length with non-random small key
A = AlphabeticStrings()
H = HillCryptosystem(A, keylen); H

# To create key non-randomly, HKS is necessary [even H.key_space() is not enough].
# HKS = H.key_space()
# key = HKS([[1,0,1],[0,1,1],[2,2,3]]); key

# Random key creation
key = H.random_key(); key
key.det()
H.block_length()

# encoding and encryption
P = "Hill or matrix cipher uses matrix operations."
len(P)
# implementation requires: Length of msg is a multiple of matrix dimension (block_length)
msg = H.encoding(P); msg
len(msg)

# encryption (two possible ways)
# encrypt = H(key); encrypt
# C = encrypt(msg); C
C  = H.enciphering(key, msg); C

# decryption
DC  = H.deciphering(key, C); DC
msg == DC

# alternative decryption using inverse matrix (both ways to invert work)
# keyInv = key.inverse(); keyInv
keyInv = H.inverse_key(key); keyInv
DC     = H.enciphering(keyInv, C); DC
msg == DC


