########################################################
#    Sage code samples (Nov. 2009)
#    from chapter 1 of the CrypTool script
########################################################

print "CHAP 01: ============================================"
print "CHAP 01: ============================================"
print "CHAP 01: ============================================"

# =========================================================================
# SAMPLE 01: Encryption and decryption with Mini-AES
# ==========

# (1) We can encrypt a plaintext using Mini-AES as follows:
from sage.crypto.block_cipher.miniaes import MiniAES
maes = MiniAES()
K = FiniteField(16, "x")
MS = MatrixSpace(K, 2, 2)
P = MS([K("x^3 + x"), K("x^2 + 1"), K("x^2 + x"), K("x^3 + x^2")]); P

key = MS([K("x^3 + x^2"), K("x^3 + x"), K("x^3 + x^2 + x"), K("x^2 + x + 1")]); key

C = maes.encrypt(P, key); C

# Here is the decryption process:
plaintxt = maes.decrypt(C, key)
plaintxt == P


# (2) We can also work directly with binary strings:
from sage.crypto.block_cipher.miniaes import MiniAES
maes = MiniAES()
bin = BinaryStrings()
key = bin.encoding("KE"); key

P = bin.encoding("Encrypt this secret message!")
C = maes(P, key, algorithm="encrypt")
plaintxt = maes(C, key, algorithm="decrypt")
plaintxt == P


# 3) Or work with integers n such that 0 <= n <= 15:
from sage.crypto.block_cipher.miniaes import MiniAES
maes = MiniAES()
P = [n for n in xrange(16)]; P
key = [2, 3, 11, 0]; key

P = maes.integer_to_binary(P)
key = maes.integer_to_binary(key)
C = maes(P, key, algorithm="encrypt"); C
plaintxt = maes(C, key, algorithm="decrypt")
plaintxt == P

