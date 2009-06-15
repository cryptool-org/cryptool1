class Gf28 
{
    public static class DivResult {
        public DivResult( int qu, int re ) {
            q=qu; r = re;
        }
        public int q, r;
    };

    public static int modm( int f ) {  // calc f mod x^8 + x^4 + x^3 + x + 1
        DivResult d = div( f, 0x11b);
        return d.r;
    }

    public static int degree( int f ) {
        int d = 0;
        while( f>1 ) {
            f >>= 1;
            d++;
        }
        return d;
    }
    
            
    public static DivResult div( int f, int m ) {
        int d = m;
        int q = 0;
        int i=1;
        int d_f = degree( f );
        int d_d = degree( d );
        int d_m = degree( m );
        
        while( d_f>=d_m ) {
            if( d_f<d_d ) {
                d >>= d_d - d_f;
                i >>= d_d - d_f;
            } else {
                d <<= d_f - d_d;
                i <<= d_f - d_d;
            }
            d_d = d_f;
            f ^= d;
            q ^= i;
            d_f = degree( f );
        }
        
        return new DivResult( q, f);
    }

    public static int polymult( int a, int b ) {
        int r = 0;
        while( b>0 ) {
            if( (b & 1)>0 )
                r ^= a;
            a <<= 1;
            b >>= 1;
        }
        return r;
    }
    
    public static int mult( int a, int b ) {
        return modm( polymult(a,b) );
    }

    public static int inverse( int r ) {
        int s = 1, s_old = 0;
        int r_old = 0x11b;
        int save_s;
        while( r>1 ) {
            DivResult d = div( r_old, r );
            r_old = r;
            r = d.r;
            save_s = s;
            s = s_old ^ mult(d.q,s);
            s_old = save_s;
        }
        return modm(s);
    }
}
