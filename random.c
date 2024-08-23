long MULTIPLIER = 214013;
long INCREMENT  = 2531011;
long MODULUS 	= 2147483648;
long next 		= 0;


void setSeed(int s) {
	next = s;
}

long randomInt() {
	next = (next * MULTIPLIER + INCREMENT) % MODULUS;
	return next;
}