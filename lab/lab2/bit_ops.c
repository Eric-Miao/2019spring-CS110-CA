
/* Return the nth bit of x.
   Assume 0 <= n <= 31 */

unsigned get_bit (unsigned x, unsigned n){
  return ((x >> n) & 1);
}

/* Set the nth bit of the value of x to v.
   Assume 0 <= n <= 31, and v is 0 or 1 */
void set_bit (unsigned *x, unsigned n, unsigned v){
  // *x^=((*x&(1<<n) )^ (v<<n));
  unsigned int temp =*x&(1<<n);
  temp^= v<<n;
  *x^=temp;
}

/* Flip the nth bit of the value of x.
   Assume 0 <= n <= 31 */
void flip_bit (unsigned *x, unsigned n){
  int nth_bit = get_bit(*x,n);
  nth_bit ^= 1;
  set_bit(x,n,nth_bit);
}
