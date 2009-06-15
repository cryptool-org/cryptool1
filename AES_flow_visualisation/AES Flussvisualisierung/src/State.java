public class State 
{
    public State() {
        round = 0;
        startValues = new int[16];
        int i,j;
        for( i=0; i<16; i++ )
            startValues[i] = (int) (Math.random( )*256);
        afterFirstKeyValues = new int[16];
        afterSBoxValues = new int[16];
        afterShiftValues = new int[16];
        inMixColumn = new int[24*4];
        afterMixValues = new int[16];
        roundKeyValues = new int[16];
        secondKeyValues = new int[16];
        resultValues = new int[16];

        sbox = new int[256];
        preCalc();

        for( i=0; i<4; i++ )
            for( j=0; j<4; j++ )
                roundKeyValues[4*i+j] =  (int) (Math.random( )*256);
        for( i=0; i<16; i++ ) 
            secondKeyValues[i] = roundKeyValues[i];
        newKey( secondKeyValues );
        rcon = Gf28.mult( rcon, 2 );

        calc();
    }

    public void setStartValues( int[] v, int[] k )
    {
        int i;
        for( i=0; i<16; i++ ) {
            startValues[i] = v[i];
        }
        if( k!=null ) {
            for( i=0; i<16; i++ ) {
                roundKeyValues[i] = k[i];
                secondKeyValues[i] = k[i];
            }

            round = 0;
            rcon = 1;
            newKey( secondKeyValues );
            rcon = Gf28.mult( rcon, 2 );
        }
        
        calc();
    }

    public void clearKey( )
    {
        int i;
        round = 0;
        for( i=0; i<16; i++ ) {
            roundKeyValues[i] = 0;
            secondKeyValues[i] = 0;
        }
        rcon = 1;
        newKey( secondKeyValues );
        rcon = Gf28.mult( rcon, 2 );
        
        calc();
    }
    

    private int byteSub( int x ) {
        if( x>0 ) { // calc inverse in GF(2^8)
            x = Gf28.inverse( x );
        }
        return Gf28.div(Gf28.polymult( x, 0x1f ), 0x101).r ^ 0x63;
    }

    private void preCalc() {
        int i;
        for( i=0; i<256; i++ )
            sbox[i] = byteSub(i);
    }

    public void calc() {
        int i,j,m;
        if( round != 0 ) 
            for( i=0; i<16; i++ )
                afterFirstKeyValues[i] = startValues[i];
        else
            for( i=0; i<4; i++ )
                for( j=0; j<4; j++ )
                    afterFirstKeyValues[i*4+j] = startValues[i*4+j] ^ roundKeyValues[i*4+j];

        for( i=0; i<16; i++ )
           afterSBoxValues[i] = sbox[afterFirstKeyValues[i]];
        for( i=0; i<4; i++ )
            for( j=0; j<4; j++ )
                afterShiftValues[4*i+j] = afterSBoxValues[4*((i+j)%4)+j];
        for( i=0; i<4; i++ ) {
            for( j=0; j<4; j++ )
                for( m=0; m<4; m++ )
                    inMixColumn[24*i+j*4+m] = Gf28.mult(afterShiftValues[4*i+3-j],mixColumnMatrix[j*4+m]);



            for( m=0; m<4; m++ ) 
                inMixColumn[24*i+16+m] = inMixColumn[24*i+m]^inMixColumn[24*i+4+m]; 
            for( m=0; m<4; m++ ) 
                inMixColumn[24*i+20+m] = inMixColumn[24*i+8+m]^inMixColumn[24*i+16+m]; 
            
        }

        for( i=0; i<4; i++ )
            for( j=0; j<4; j++ )
                afterMixValues[4*i+j] = inMixColumn[24*i+12+j] ^ inMixColumn[24*i+20+j]; 
        for( i=0; i<16; i++ )
            resultValues[i] = afterMixValues[i] ^ secondKeyValues[i];
    }
    
    public void print() 
    {
        int i;
        StringBuffer s = new StringBuffer().append("input [");
        
        for(i=0; i<16; i++ )
            s.append(" ").append(DrawScheme.intToHex( startValues[i] ));
        System.out.println( s + " ]" );

        s = new StringBuffer().append("after ByteSub [");
        for(i=0; i<16; i++ )
            s.append(" ").append(DrawScheme.intToHex( afterSBoxValues[i] ));
        System.out.println( s + " ]" );

        s = new StringBuffer().append("after Shift [");
        for(i=0; i<16; i++ )
            s.append(" ").append(DrawScheme.intToHex( afterShiftValues[i] ));
        System.out.println( s + " ]" );

        s = new StringBuffer().append("in MixColumn [");
        for(i=0; i<24*4; i++ )
            s.append(" ").append(DrawScheme.intToHex( inMixColumn[i] ));
        System.out.println( s + " ]" );

        s = new StringBuffer().append("after MixColumn [");
        for(i=0; i<16; i++ )
            s.append(" ").append(DrawScheme.intToHex( afterMixValues[i] ));
        System.out.println( s + " ]" );

        s = new StringBuffer().append("result [");
        for(i=0; i<16; i++ )
            s.append(" ").append(DrawScheme.intToHex( resultValues[i] ));
        System.out.println( s + " ]" );
        
    }
  
    
    public int getStartValue( int index ) 
    {
        return startValues[index];
    }

    public int getResultValue( int index ) 
    {
        return resultValues[index];
    }

    private void newKey( int key[] ) 
    {
        int i, j, tmp;

        for( i=0; i<4; i++ )
            for( j=0; j<4; j++ ) {
                tmp = key[((i+3)%4)*4 + j];
                if( i==0 ) {
                    tmp = byteSub( key[((i+3)%4)*4 + (j+1)%4]);
                    if( j==0 )
                        tmp ^= rcon;
                }

                key[4*i+j] ^= tmp;
            }
    }
    
    public State nextRound() 
    {
        State n = new State();
        int i;
        for( i=0; i<256; i++ )
            n.sbox[i] = sbox[i];
        for( i=0; i<16; i++ )
            n.startValues[i] = resultValues[i];
        for( i=0; i<16; i++ )
            n.roundKeyValues[i] = secondKeyValues[i];
        n.rcon = rcon;
        n.newKey( n.roundKeyValues );
        n.rcon = Gf28.mult( rcon, 2 );
        n.round = round+1;
        for( i=0; i<16; i++ ) 
            n.secondKeyValues[i] = n.roundKeyValues[i];

        n.calc();
        return n;
    }
    
    
    public int startValues[], afterFirstKeyValues[];
    public int afterSBoxValues[];
    public int afterShiftValues[];
    public int inMixColumn[];
    public int afterMixValues[];
    public int roundKeyValues[];
    public int secondKeyValues[];
    public int resultValues[];
    public int sbox[];
    public int rcon = 1;
    public int round;
    

    // a_3, a_2, ...
    final static int mixColumnMatrix[] = { 1,1,3,2,1,3,2,1,3,2,1,1,2,1,1,3 };
}
