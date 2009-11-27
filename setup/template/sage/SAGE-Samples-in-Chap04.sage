########################################################
#    Sage code samples (Nov. 2009)
#    from chapter 4 of the CrypTool script
########################################################

print "CHAP 04: ============================================"
print "CHAP 04: ============================================"
print "CHAP 04: ============================================"

# =========================================================================
# SAMPLE 07: Function "enum PrimitiveRoots of an Integer" to calculate
#            all primitive roots for a given number
# -----------------------------------------------------------------
def enum_PrimitiveRoots_of_an_Integer(M):
    r"""
    Return all the primitive roots of the integer M (if possible).
    """
    try:
        g = primitive_root(M)
        # print "Ok"
    except:
        # raise ArithmeticError, "primitive_root() failed for %s." % M
        #print "Not ok"
        return None
    targetOrder = euler_phi(M)
    L=[]
    # Stepping through all odd integers from 1 up to M, not including
    # M. So this loop only considers values of i where 1 <= i < M.
    for i in xrange(1,M,2):
            testGen = Mod(g^i,M)
            if testGen.multiplicative_order() == targetOrder:
                L.append(testGen.lift())
    # removing duplicates
    return Set(L)


# AA_Start -- Testcases for enum_PrimitiveRoots_of_an_Integer(M)
print "\n\nAA_Start -- Testcases for enum_PrimitiveRoots_of_an_Integer(M)"

M=10; print "\n1-----------Testcase: M = %s" % M
LL = enum_PrimitiveRoots_of_an_Integer(M)
if LL==None:
    print M
else:
    print LL

M=8; print "\n2-----------Testcase: M = %s" % M
# M=8 hat keine primitive root mod m. Checke, ob per try - except abgefangen.
LL = enum_PrimitiveRoots_of_an_Integer(M)
if LL==None:
    print M
else:
    print LL

M=17; print "\n3-----------Testcase: M = %s" % M
LL = enum_PrimitiveRoots_of_an_Integer(M)
if LL==None:
    print M
else:
    print LL
# AA_End -- Testcases





# =========================================================================
# SAMPLE 09: Function "count PrimitiveRoots of an IntegerRange" to calculate
#            all primitive roots for a given range of integers
# -----------------------------------------------------------------
def count_PrimitiveRoots_of_an_IntegerRange(start, end, bPrimesOnly=True):
	r"""
	Compute all primitive roots of all numbers between start and end,
	inclusive, and count them.
	If the flag bPrimesOnly is True, it performs primality tests, so it
	allows us to count the number of primes from start to end, inclusive.
        If the flag bPrimesOnly is false, it additionally counts these even
	numbers which have no primitive root.
	"""
	nCheckedNumb = 0
	nCheckedNumb_WithoutPrimitivRoots = 0
	nPrimitiveRoots = 0
	for n in xrange(start, end+1):
		if bPrimesOnly:
			if is_prime(n):
				nCheckedNumb += 1
				L = enum_PrimitiveRoots_of_an_Integer(n)
				nPrimitiveRoots += len(L)
		else:
			nCheckedNumb += 1
			L = enum_PrimitiveRoots_of_an_Integer(n)
			if L==None:
				nCheckedNumb_WithoutPrimitivRoots += 1
			else:
				nPrimitiveRoots += len(L)

	if bPrimesOnly:
		print "Found all %s" % nPrimitiveRoots + \
		      " primitive roots of %s primes." % nCheckedNumb
	else:
		if nCheckedNumb_WithoutPrimitivRoots == 0:
			print "Found all %s " % nPrimitiveRoots + \
			      "primitive roots of %s numbers." % nCheckedNumb
		else:
			print "Found all %s " % nPrimitiveRoots + \
			      "primitive roots of %s numbers." % \
			          (nCheckedNumb - nCheckedNumb_WithoutPrimitivRoots)
			print "(Total of numbers checked: %s, " % nCheckedNumb + \
			      "Amount of numbers without primitive roots: %s)" % \
			          nCheckedNumb_WithoutPrimitivRoots


# BB_Start -- Testcases for count_PrimitiveRoots_of_an_IntegerRange(start, end, bPrimesOnly=True)
print "\n\nBB_Start -- Testcases for count_PrimitiveRoots_of_an_IntegerRange(start, end, bPrimesOnly=True)"

print "\n1-----------Testcase: (1, 500)"
time count_PrimitiveRoots_of_an_IntegerRange(1, 500)

print "\n2-----------Testcase: (5, 6, False)"
time count_PrimitiveRoots_of_an_IntegerRange(5, 6, False)

print "\n3-----------Testcase: (1, 500, False)"
time count_PrimitiveRoots_of_an_IntegerRange(1, 500, False)
# BB_End -- Testcases






# =========================================================================
# SAMPLE 11: Function "count PrimitiveRoots of a PrimesRange" to calculate
#            the number of primitive roots for a given range of primes
# -----------------------------------------------------------------
def count_PrimitiveRoots_of_a_PrimesRange(start, end):
      r"""
      Compute all primitive roots of all primes between start and end,
      inclusive. This uses a primes iterator.
      """
      nPrimes = 0
      nPrimitiveRoots = 0
      for p in primes(start, end+1):
          L = enum_PrimitiveRoots_of_an_Integer(p)
	  print p, len(L)
          nPrimes += 1
          nPrimitiveRoots += len(L)
      print "Found all %s" % nPrimitiveRoots + " primitive roots of %s primes." % nPrimes


# CC_Start -- Testcases for count_PrimitiveRoots_of_a_PrimesRange(start, end)
print "\n\nCC_Start -- Testcases for count_PrimitiveRoots_of_a_PrimesRange(start, end)"
print "-----------Testcase: (1, 1500)"
time count_PrimitiveRoots_of_a_PrimesRange(1, 1500)
# CC_End -- Testcases






# =========================================================================
# SAMPLE 12: Code to generate the database with all primitive roots
#            for all primes between 1 and 100,000
# -----------------------------------------------------------------
def generate_PrimitiveRoots_database():
	start = 1
	end = 10^5
	fileName = "/scratch/mvngu/primroots.dat"
	file = open(fileName, "w")
	for p in primes(start, end+1):
		L = enum_PrimitiveRoots_of_an_Integer(p)
		print p, len(L)
		# Output to a file. The format is:
		# (1) the prime number p under consideration
		# (2) the number of primitive roots of Z/pZ
		# (3) all the primitive roots of Z/pZ
		file.write(str(p) + " " + str(len(L)) + " " + str(L) + "\n")
		file.flush()
	file.close()





# =========================================================================
# SAMPLE 13: Code to generate the graphics about the primitive roots
# -----------------------------------------------------------------
def generate_PrimitiveRoots_graphics_from_database():
	# open a database file on primitive roots from 1 to 100,000
	file = open("/scratch/mvngu/primroots.dat", "r")
	plist = []   # list of all primes from 1 to 100,000
	nlist = []   # number of primitive roots modulo prime p
	minlist = [] # smallest primitive root modulo prime p
	maxlist = [] # largest primitive root modulo prime p
	for line in file:
		# get a line from the database file and tokenize it for processing
		line = line.strip().split(" ", 2)
		# extract the prime number p in question
		plist.append(Integer(line[0]))
		# extract the number of primitive roots modulo p
		nlist.append(Integer(line[1]))
		# extract the list of all primitive roots modulo p
		line = line[-1]
		line = line.replace("{", "")
		line = line.replace("}", "")
		line = line.split(", ")
		# sort the list in non-decreasing order
		line = [Integer(s) for s in line]
		line.sort()
		# get the smallest primitive root modulo p
		minlist.append(line[0])
		# get the largest primitive root modulo p
		maxlist.append(line[-1])
	file.close() # close the database file

	# plot of number of primitive roots modulo p
	nplot = point2d(zip(plist, nlist), pointsize=1)
	nplot.axes_labels(["x", "y"])
	nplot
	# plot of smallest primitive root modulo prime p
	minplot = point2d(zip(plist, minlist), pointsize=1)
	minplot.axes_labels(["x", "y"])
	minplot
	# plot of largest primitive root modulo prime p
	maxplot = point2d(zip(plist, maxlist), pointsize=1)
	maxplot.axes_labels(["x", "y"])
	maxplot





# =========================================================================
# SAMPLE 16: How many RSA keys are there if you know a range for the public keys n?
# -----------------------------------------------------------------
def count_Number_of_RSA_Keys(start, end, Verbose=False):
      r"""
      How many private RSA keys (n,d) exist, if only modulus N is given, and start <= N <= end?
        (prime_range(u,o) delivers all primes >=u und < o).
      Wie viele RSA-Schlüssel gibt es, wenn der Modulus (N) zwischen start und end liegt?
        (prime_range(u,o) liefert alle Primes >=u und < o).
      """
      a = start
      b = end
      s = 0
      comb = 0
      for p in prime_range(1, b/2+1):  # b or b/2+1
          for q in prime_range(p + 1, b/2+1):  # b or b/2+1
              if a <= p * q and p * q <= b:
                  comb = comb +1
                  s = s + (euler_phi(euler_phi(p * q))-1)
                  if Verbose:
                      print "p=%s, " % p + "q=%s, " % q + "s=%s" % s
      print "Number of private keys for modulus in a given range: %s" % s + " (comb=%s), " % comb

      # Just for comparison: How many primes are in this range?
      s = 0
      for p in prime_range(a, b+1):
          if Verbose:
              print "a=%s, " % a + "b=%s, " % b + "p=%s" % p
          s = s + 1
      print "Number of primes in a given range: %s" % s


# DD_Start -- Testcases for count_Number_of_RSA_Keys(start, end)
print "\n\nDD_Start -- Testcases for count_Number_of_RSA_Keys(start, end)"

print "\n-----------Testcase: (100, 1000) [Should deliver 34.816]"
time count_Number_of_RSA_Keys(100, 1000)

print "\n-----------Testcase: (100, 107, True) [Should deliver 23]"
time count_Number_of_RSA_Keys(100, 107, True)

u = 10^3; o = 10^4;
print "\n-----------Testcase: (%s, " % u + "%s) [Should deliver 3.260.044]" % o
time count_Number_of_RSA_Keys(u, o)
# DD_End -- Testcases


