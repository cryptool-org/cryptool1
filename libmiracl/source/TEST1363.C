/* test driver amnd function exerciser for P1363 Functions */
/* see comments in p1363.c */

/* define this next to use Windows DLL */
/* #define MR_P1363_DLL  */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "p1363.h"

int main(int argc,char **argv)
{   
    int i,ip,len,mlen,lsbw,lsbw0,lsbw1,lsbv0,lsbv1;
    BOOL compress,precompute;
    octet s,p,f,g,c,d,seed;
    octet s0,s1,w0,w1,u0,u1,v0,v1,z;
    octet wx,wy,wx0,wx1,wy0,wy1,vx0,vx1,vy0,vy1;
    octet z1,z2,f1;
    dl_domain dom;
    ecp_domain epdom;
    ec2_domain e2dom;
    if_public_key pub;
    if_private_key priv;
 
    int res,bytes;
    char raw[100];
    char ch=0x01;

    argc--; argv++;
    compress=precompute=FALSE;

    ip=0;
    while (ip<argc)
    {
        if (strcmp(argv[ip],"-c")==0)
        {
            compress=TRUE;
            ip++; 
            continue;
        }

        if (strcmp(argv[ip],"-p")==0)
        {
            precompute=TRUE;
            ip++; 
            continue;
        }
 
        if (strcmp(argv[ip],"-r")==0)
        {
            ip++;
            if (ip<argc)
            {
                ch=(char)atoi(argv[ip++]); 
                continue;
            }
        }

        printf("Command line error\n");
        exit(0);
    }

    len=100;                     /* fake random seed source */
    for (i=0;i<100;i++) raw[i]=ch+i;

    RANDOM_START(100,raw,&seed);

    bytes=DL_DOMAIN_INIT(&dom,"common.dss",NULL,16,precompute);

    res=DL_DOMAIN_VALIDATE(NULL,&dom);
    if (res!=0)
    {
        printf("Domain parameters are invalid\n");
        return 0;
    }
    OCTET_INIT(&s0,bytes);
    OCTET_INIT(&s1,bytes);
    OCTET_INIT(&w0,bytes);
    OCTET_INIT(&w1,bytes);

    DL_KEY_PAIR_GENERATE(NULL,&dom,&seed,&s0,&w0);
    DL_KEY_PAIR_GENERATE(NULL,&dom,&seed,&s1,&w1);

    OCTET_INIT(&z,bytes);
    OCTET_INIT(&z1,bytes);
    OCTET_INIT(&z2,bytes);
    DLSVDP_DH(NULL,&dom,&s0,&w1,&z);
    DLSVDP_DH(NULL,&dom,&s1,&w0,&z1);

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("DLSVDP-DH - OK\n");
    else
    {
        printf("*** DLSVDP-DH Failed\n");
        return 0;
    }

    res=DLSVDP_DHC(NULL,&dom,&s1,&w0,TRUE,&z2);

    if (OCTET_COMPARE(&z,&z2)==0)
        printf("DLSVDP-DHC Compatibility Mode - OK\n");
    else
    {
        printf("*** DLSVDP-DHC Compatibility Mode Failed\n");
        return 0;
    }

    DLSVDP_DHC(NULL,&dom,&s0,&w1,FALSE,&z);
    DLSVDP_DHC(NULL,&dom,&s1,&w0,FALSE,&z1);

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("DLSVDP-DHC - OK\n");
    else
    {
        printf("*** DLSVDP-DHC Failed\n");
        return 0;
    }

    OCTET_INIT(&u0,bytes);
    OCTET_INIT(&u1,bytes);
    OCTET_INIT(&v0,bytes);
    OCTET_INIT(&v1,bytes);

    DL_KEY_PAIR_GENERATE(NULL,&dom,&seed,&u0,&v0);
    DL_KEY_PAIR_GENERATE(NULL,&dom,&seed,&u1,&v1);

    DLSVDP_MQV(NULL,&dom,&s0,&u0,&v0,&w1,&v1,&z);
    DLSVDP_MQV(NULL,&dom,&s1,&u1,&v1,&w0,&v0,&z1);

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("DLSVDP-MQV - OK\n");
    else
    {
        printf("*** DLSVDP-MQV Failed\n");
        return 0;
    }

    DLSVDP_MQVC(NULL,&dom,&s0,&u0,&v0,&w1,&v1,TRUE,&z2);

    if (OCTET_COMPARE(&z,&z2)==0)
        printf("DLSVDP-MQVC Compatibility Mode - OK\n");
    else
    {
        printf("*** DLSVDP-MQVC Compatibility Mode Failed\n");
        return 0;
    }

    DLSVDP_MQVC(NULL,&dom,&s0,&u0,&v0,&w1,&v1,FALSE,&z);
    DLSVDP_MQVC(NULL,&dom,&s0,&u0,&v0,&w1,&v1,FALSE,&z1);

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("DLSVDP-MQVC - OK\n");
    else
    {
        printf("*** DLSVDP-MQVC Failed\n");
        return 0;
    }

    OCTET_INIT(&s,bytes);
    OCTET_INIT(&p,bytes);

    DL_KEY_PAIR_GENERATE(NULL,&dom,&seed,&s,&p);
    res=DL_PUBLIC_KEY_VALIDATE(NULL,&dom,TRUE,&p);
    if (res!=0)
    {
        printf("DL Public Key is invalid!\n");
        return 0;
    }

    OCTET_INIT(&f,bytes);
    OCTET_INIT(&c,bytes);
    OCTET_INIT(&d,bytes);

    OCTET_COPY(&seed,&f);       /* fake a random message */
    f.val[0]=1;                 /* make sure its less than group order */

    res=DLSP_DSA(NULL,&dom,&seed,&s,&f,&c,&d); /* sign it   */
    res=DLVP_DSA(NULL,&dom,&p,&c,&d,&f);       /* verify it */
    if (res==0)
        printf("DL DSA Signature - OK\n");
    else
    {
        printf("*** DL DSA Signature Failed\n");
        return 0;
    }
    
    OCTET_INIT(&f1,bytes);
    res=DLSP_NR(NULL,&dom,&seed,&s,&f,&c,&d); /* sign it */
    res=DLVP_NR(NULL,&dom,&p,&c,&d,&f1);

    if (OCTET_COMPARE(&f,&f1)==0)
        printf("DL  NR Signature - OK\n");
    else
    {
        printf("*** DL  NR Signature Failed\n");
        return 0;
    }
    
    OCTET_KILL(&s0); OCTET_KILL(&s1);
    OCTET_KILL(&w0); OCTET_KILL(&w1);
    OCTET_KILL(&z); OCTET_KILL(&z1); OCTET_KILL(&z2);
    OCTET_KILL(&u0); OCTET_KILL(&u1);
    OCTET_KILL(&v0); OCTET_KILL(&v1);
    OCTET_KILL(&s); OCTET_KILL(&p);
    OCTET_KILL(&f); OCTET_KILL(&f1);
    OCTET_KILL(&c); OCTET_KILL(&d);

    DL_DOMAIN_KILL(&dom);

/* Now test Elliptic Curves mod p */

    bytes=ECP_DOMAIN_INIT(&epdom,"common.ecs",NULL,16,precompute);
    res=ECP_DOMAIN_VALIDATE(NULL,&epdom);
    if (res!=0)
    {
        printf("Domain parameters are invalid\n");
        return 0;
    }
    OCTET_INIT(&s0,bytes);
    OCTET_INIT(&s1,bytes);
    OCTET_INIT(&wx0,bytes);
    OCTET_INIT(&wx1,bytes);
    OCTET_INIT(&wy0,bytes);
    OCTET_INIT(&wy1,bytes);

    lsbw0=ECP_KEY_PAIR_GENERATE(NULL,&epdom,&seed,&s0,&wx0,&wy0);
    res=ECP_PUBLIC_KEY_VALIDATE(NULL,&epdom,TRUE,&wx0,&wy0,0);
    if (res!=0)
    {
        printf("ECP Public Key is invalid!\n");
        return 0;
    }

    lsbw1=ECP_KEY_PAIR_GENERATE(NULL,&epdom,&seed,&s1,&wx1,&wy1);
    res=ECP_PUBLIC_KEY_VALIDATE(NULL,&epdom,TRUE,&wx1,&wy1,0);
    if (res!=0)
    {
        printf("ECP Public Key is invalid!\n");
        return 0;
    }

    OCTET_INIT(&z,bytes);
    OCTET_INIT(&z1,bytes);
    OCTET_INIT(&z2,bytes);

    if (compress)
    {
        ECPSVDP_DH(NULL,&epdom,&s0,&wx1,NULL,lsbw1,&z);
        ECPSVDP_DH(NULL,&epdom,&s1,&wx0,NULL,lsbw0,&z1);
    }
    {
        ECPSVDP_DH(NULL,&epdom,&s0,&wx1,&wy1,0,&z);
        ECPSVDP_DH(NULL,&epdom,&s1,&wx0,&wy0,0,&z1);
    }
    if (OCTET_COMPARE(&z,&z1)==0)
        printf("ECPSVDP-DH - OK\n");
    else
    {
        printf("*** ECPSVDP-DH Failed\n");
        return 0;
    }

    if (compress)
        ECPSVDP_DHC(NULL,&epdom,&s1,&wx0,NULL,lsbw0,TRUE,&z2);
    else
        ECPSVDP_DHC(NULL,&epdom,&s1,&wx0,&wy0,0,TRUE,&z2);

    if (OCTET_COMPARE(&z,&z2)==0)
        printf("ECPSVDP-DHC Compatibility Mode - OK\n");
    else
    {
        printf("*** ECPSVDP-DHC Compatibility Mode Failed\n");
        return 0;
    }

    if (compress)
    {
        ECPSVDP_DHC(NULL,&epdom,&s0,&wx1,NULL,lsbw1,FALSE,&z);
        ECPSVDP_DHC(NULL,&epdom,&s1,&wx0,NULL,lsbw0,FALSE,&z1);
    }
    else
    {
        ECPSVDP_DHC(NULL,&epdom,&s0,&wx1,&wy1,0,FALSE,&z);
        ECPSVDP_DHC(NULL,&epdom,&s1,&wx0,&wy0,0,FALSE,&z1);
    }
    if (OCTET_COMPARE(&z,&z1)==0)
        printf("ECPSVDP-DHC - OK\n");
    else
    {
        printf("*** ECPSVDP-DHC Failed\n");
        return 0;
    }

    OCTET_INIT(&u0,bytes);
    OCTET_INIT(&u1,bytes);
    OCTET_INIT(&vx0,bytes);
    OCTET_INIT(&vx1,bytes);
    OCTET_INIT(&vy0,bytes);
    OCTET_INIT(&vy1,bytes);

    lsbv0=ECP_KEY_PAIR_GENERATE(NULL,&epdom,&seed,&u0,&vx0,&vy0);
    lsbv1=ECP_KEY_PAIR_GENERATE(NULL,&epdom,&seed,&u1,&vx1,&vy1);

    if (compress)
    {
        ECPSVDP_MQV(NULL,&epdom,&s0,&u0,&vx0,&wx1,NULL,lsbw1,&vx1,NULL,lsbv1,&z);
        ECPSVDP_MQV(NULL,&epdom,&s1,&u1,&vx1,&wx0,NULL,lsbw0,&vx0,NULL,lsbv0,&z1);
    }
    else
    {
        ECPSVDP_MQV(NULL,&epdom,&s0,&u0,&vx0,&wx1,&wy1,0,&vx1,&vy1,0,&z);
        ECPSVDP_MQV(NULL,&epdom,&s1,&u1,&vx1,&wx0,&wy0,0,&vx0,&vy0,0,&z1);
    }

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("ECPSVDP-MQV - OK\n");
    else
    {
        printf("*** ECPSVDP-MQV Failed\n");
        return 0;
    }

    if (compress)
       ECPSVDP_MQVC(NULL,&epdom,&s0,&u0,&vx0,&wx1,NULL,lsbw1,&vx1,NULL,lsbv1,TRUE,&z2);
    else
       ECPSVDP_MQVC(NULL,&epdom,&s0,&u0,&vx0,&wx1,&wy1,0,&vx1,&vy1,0,TRUE,&z2);
       
    if (OCTET_COMPARE(&z,&z2)==0)
        printf("ECPSVDP_MQVC Compatibility Mode - OK\n");
    else
    {
        printf("*** ECPSVDP_MQVC Compatibility Mode Failed\n");
        return 0;
    }

    if (compress)
    {
        ECPSVDP_MQVC(NULL,&epdom,&s0,&u0,&vx0,&wx1,NULL,lsbw1,&vx1,NULL,lsbv1,FALSE,&z);
        ECPSVDP_MQVC(NULL,&epdom,&s1,&u1,&vx1,&wx0,NULL,lsbw0,&vx0,NULL,lsbv0,FALSE,&z1);
    }
    else
    {
        ECPSVDP_MQVC(NULL,&epdom,&s0,&u0,&vx0,&wx1,&wy1,0,&vx1,&vy1,0,FALSE,&z);
        ECPSVDP_MQVC(NULL,&epdom,&s1,&u1,&vx1,&wx0,&wy0,0,&vx0,&vy0,0,FALSE,&z1);
    }

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("ECPSVDP-MQVC - OK\n");
    else
    {
        printf("*** ECPSVDP-MQVC Failed\n");
        return 0;
    }

    OCTET_INIT(&s,bytes);
    OCTET_INIT(&wx,bytes);
    OCTET_INIT(&wy,bytes);

    lsbw=ECP_KEY_PAIR_GENERATE(NULL,&epdom,&seed,&s,&wx,&wy);
    if (compress)
        res=ECP_PUBLIC_KEY_VALIDATE(NULL,&epdom,TRUE,&wx,NULL,lsbw);
    else
        res=ECP_PUBLIC_KEY_VALIDATE(NULL,&epdom,TRUE,&wx,&wy,0);

    if (res!=0)
    {
        printf("ECP Public Key is invalid!\n");
        return 0;
    }

    OCTET_INIT(&f,bytes);
    OCTET_INIT(&f1,bytes);
    OCTET_INIT(&c,bytes);
    OCTET_INIT(&d,bytes);
 
    OCTET_COPY(&seed,&f);      /* fake a random message */
    f.val[0]=1;                /* make sure its less than group order */

    res=ECPSP_DSA(NULL,&epdom,&seed,&s,&f,&c,&d);
    if (compress)
        res=ECPVP_DSA(NULL,&epdom,&wx,NULL,lsbw,&c,&d,&f);
    else
        res=ECPVP_DSA(NULL,&epdom,&wx,&wy,0,&c,&d,&f);

    if (res==0)
        printf("ECP DSA  Signature - OK\n");
    else
    {
        printf("*** ECP DSA Signature Failed\n");
        return 0;
    } 

    res=ECPSP_NR(NULL,&epdom,&seed,&s,&f,&c,&d);
    if (compress)
        res=ECPVP_NR(NULL,&epdom,&wx,NULL,lsbw,&c,&d,&f1);
    else
        res=ECPVP_NR(NULL,&epdom,&wx,&wy,0,&c,&d,&f1);


    if (OCTET_COMPARE(&f,&f1)==0)
        printf("ECP  NR  Signature - OK\n");
    else
    {
        printf("*** ECP  NR Signature Failed\n");
        return 0;
    } 

    OCTET_KILL(&s0); OCTET_KILL(&s1);
    OCTET_KILL(&wx0); OCTET_KILL(&wx1);
    OCTET_KILL(&wy0); OCTET_KILL(&wy1);
    OCTET_KILL(&z); 
    OCTET_KILL(&z1); OCTET_KILL(&z2);
    OCTET_KILL(&u0); OCTET_KILL(&u1);
    OCTET_KILL(&vx0); OCTET_KILL(&vx1);
    OCTET_KILL(&vy0); OCTET_KILL(&vy1);
    OCTET_KILL(&s); 
    OCTET_KILL(&wx); OCTET_KILL(&wy);
    OCTET_KILL(&f); OCTET_KILL(&f1);
    OCTET_KILL(&c); OCTET_KILL(&d);

    ECP_DOMAIN_KILL(&epdom);

/* Now test Elliptic Curves mod 2^m */

    bytes=EC2_DOMAIN_INIT(&e2dom,"common2.ecs",NULL,16,precompute);
    res=EC2_DOMAIN_VALIDATE(NULL,&e2dom);
    if (res!=0)
    {
        printf("Domain parameters are invalid\n",res);
        return 0;
    }

    OCTET_INIT(&s0,bytes);
    OCTET_INIT(&s1,bytes);
    OCTET_INIT(&wx0,bytes);
    OCTET_INIT(&wx1,bytes);
    OCTET_INIT(&wy0,bytes);
    OCTET_INIT(&wy1,bytes);

    lsbw0=EC2_KEY_PAIR_GENERATE(NULL,&e2dom,&seed,&s0,&wx0,&wy0);
    lsbw1=EC2_KEY_PAIR_GENERATE(NULL,&e2dom,&seed,&s1,&wx1,&wy1);

    OCTET_INIT(&z,bytes);
    OCTET_INIT(&z1,bytes);
    OCTET_INIT(&z2,bytes);

    if (compress)
    {
        EC2SVDP_DH(NULL,&e2dom,&s0,&wx1,NULL,lsbw1,&z);
        EC2SVDP_DH(NULL,&e2dom,&s1,&wx0,NULL,lsbw0,&z1);
    }
    {
        EC2SVDP_DH(NULL,&e2dom,&s0,&wx1,&wy1,0,&z);
        EC2SVDP_DH(NULL,&e2dom,&s1,&wx0,&wy0,0,&z1);
    }
    if (OCTET_COMPARE(&z,&z1)==0)
        printf("EC2SVDP-DH - OK\n");
    else
    {
        printf("*** EC2SVDP-DH Failed\n");
        return 0;
    }

    if (compress)
        EC2SVDP_DHC(NULL,&e2dom,&s1,&wx0,NULL,lsbw0,TRUE,&z2);
    else
        EC2SVDP_DHC(NULL,&e2dom,&s1,&wx0,&wy0,0,TRUE,&z2);

    if (OCTET_COMPARE(&z,&z2)==0)
        printf("EC2SVDP-DHC Compatibility Mode - OK\n");
    else
    {
        printf("*** EC2SVDP-DHC Compatibility Mode Failed\n");
        return 0;
    }

    if (compress)
    {
        EC2SVDP_DHC(NULL,&e2dom,&s0,&wx1,NULL,lsbw1,FALSE,&z);
        EC2SVDP_DHC(NULL,&e2dom,&s1,&wx0,NULL,lsbw0,FALSE,&z1);
    }
    else
    {
        EC2SVDP_DHC(NULL,&e2dom,&s0,&wx1,&wy1,0,FALSE,&z);
        EC2SVDP_DHC(NULL,&e2dom,&s1,&wx0,&wy0,0,FALSE,&z1);
    }
    if (OCTET_COMPARE(&z,&z1)==0)
        printf("EC2SVDP-DHC - OK\n");
    else
    {
        printf("*** EC2SVDP-DHC Failed\n");
        return 0;
    }

    OCTET_INIT(&u0,bytes);
    OCTET_INIT(&u1,bytes);
    OCTET_INIT(&vx0,bytes);
    OCTET_INIT(&vx1,bytes);
    OCTET_INIT(&vy0,bytes);
    OCTET_INIT(&vy1,bytes);

    lsbv0=EC2_KEY_PAIR_GENERATE(NULL,&e2dom,&seed,&u0,&vx0,&vy0);
    lsbv1=EC2_KEY_PAIR_GENERATE(NULL,&e2dom,&seed,&u1,&vx1,&vy1);

    if (compress)
    {
        EC2SVDP_MQV(NULL,&e2dom,&s0,&u0,&vx0,&wx1,NULL,lsbw1,&vx1,NULL,lsbv1,&z);
        EC2SVDP_MQV(NULL,&e2dom,&s1,&u1,&vx1,&wx0,NULL,lsbw0,&vx0,NULL,lsbv0,&z1);
    }
    else
    {
        EC2SVDP_MQV(NULL,&e2dom,&s0,&u0,&vx0,&wx1,&wy1,0,&vx1,&vy1,0,&z);
        EC2SVDP_MQV(NULL,&e2dom,&s1,&u1,&vx1,&wx0,&wy0,0,&vx0,&vy0,0,&z1);
    }

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("EC2SVDP-MQV - OK\n");
    else
    {
        printf("*** EC2SVDP-MQV Failed\n");
        return 0;
    }

    if (compress)
       EC2SVDP_MQVC(NULL,&e2dom,&s0,&u0,&vx0,&wx1,NULL,lsbw1,&vx1,NULL,lsbv1,TRUE,&z2);
    else
       EC2SVDP_MQVC(NULL,&e2dom,&s0,&u0,&vx0,&wx1,&wy1,0,&vx1,&vy1,0,TRUE,&z2);
       
    if (OCTET_COMPARE(&z,&z2)==0)
        printf("EC2SVDP_MQVC Compatibility Mode - OK\n");
    else
    {
        printf("*** EC2SVDP_MQVC Compatibility Mode Failed\n");
        return 0;
    }

    if (compress)
    {
        EC2SVDP_MQVC(NULL,&e2dom,&s0,&u0,&vx0,&wx1,NULL,lsbw1,&vx1,NULL,lsbv1,FALSE,&z);
        EC2SVDP_MQVC(NULL,&e2dom,&s1,&u1,&vx1,&wx0,NULL,lsbw0,&vx0,NULL,lsbv0,FALSE,&z1);
    }
    else
    {
        EC2SVDP_MQVC(NULL,&e2dom,&s0,&u0,&vx0,&wx1,&wy1,0,&vx1,&vy1,0,FALSE,&z);
        EC2SVDP_MQVC(NULL,&e2dom,&s1,&u1,&vx1,&wx0,&wy0,0,&vx0,&vy0,0,FALSE,&z1);
    }

    if (OCTET_COMPARE(&z,&z1)==0)
        printf("EC2SVDP-MQVC - OK\n");
    else
    {
        printf("*** EC2SVDP-MQVC Failed\n");
        return 0;
    }

    OCTET_INIT(&s,bytes);
    OCTET_INIT(&wx,bytes);
    OCTET_INIT(&wy,bytes);

    lsbw=EC2_KEY_PAIR_GENERATE(NULL,&e2dom,&seed,&s,&wx,&wy);
    if (compress)
        res=EC2_PUBLIC_KEY_VALIDATE(NULL,&e2dom,TRUE,&wx,NULL,lsbw);
    else
        res=EC2_PUBLIC_KEY_VALIDATE(NULL,&e2dom,TRUE,&wx,&wy,0);

    if (res!=0)
    {
        printf("EC2 Public Key is invalid!\n");
        return 0;
    }

    OCTET_INIT(&f,bytes);
    OCTET_INIT(&f1,bytes);
    OCTET_INIT(&c,bytes);
    OCTET_INIT(&d,bytes);

    OCTET_COPY(&seed,&f);         /* fake a random message */
    f.val[0]=1;                   /* make sure its less than group order */  

    res=EC2SP_DSA(NULL,&e2dom,&seed,&s,&f,&c,&d);
    if (compress)
        res=EC2VP_DSA(NULL,&e2dom,&wx,NULL,lsbw,&c,&d,&f);
    else
        res=EC2VP_DSA(NULL,&e2dom,&wx,&wy,0,&c,&d,&f);

    if (res==0)
        printf("EC2 DSA  Signature - OK\n");
    else
    {
        printf("*** EC2 DSA Signature Failed\n");
        return 0;
    } 

    res=EC2SP_NR(NULL,&e2dom,&seed,&s,&f,&c,&d);
    if (compress)
        res=EC2VP_NR(NULL,&e2dom,&wx,NULL,lsbw,&c,&d,&f1);
    else
        res=EC2VP_NR(NULL,&e2dom,&wx,&wy,0,&c,&d,&f1);


    if (OCTET_COMPARE(&f,&f1)==0)
        printf("EC2  NR  Signature - OK\n");
    else
    {
        printf("*** EC2  NR Signature Failed\n");
        return 0;
    } 

    OCTET_KILL(&s0); OCTET_KILL(&s1);
    OCTET_KILL(&wx0); OCTET_KILL(&wx1);
    OCTET_KILL(&wy0); OCTET_KILL(&wy1);
    OCTET_KILL(&z); 
    OCTET_KILL(&z1); OCTET_KILL(&z2);
    OCTET_KILL(&u0); OCTET_KILL(&u1);
    OCTET_KILL(&vx0); OCTET_KILL(&vx1);
    OCTET_KILL(&vy0); OCTET_KILL(&vy1);
    OCTET_KILL(&s); 
    OCTET_KILL(&wx); OCTET_KILL(&wy);
    OCTET_KILL(&f); OCTET_KILL(&f1);
    OCTET_KILL(&c); OCTET_KILL(&d);

    EC2_DOMAIN_KILL(&e2dom);

    printf("Generating 1024-bit RSA Key Pair....\n");
    bytes=IF_KEY_PAIR(NULL,&seed,1024,65537,&priv,&pub);

    OCTET_INIT(&f,bytes);
    OCTET_INIT(&f1,bytes);
    OCTET_INIT(&g,bytes);

    f.len=20;
    for (i=0;i<20;i++) f.val[i]=i+1;    /* fake a message */
    IFEP_RSA(NULL,&pub,&f,&g);
    IFDP_RSA(NULL,&priv,&g,&f1);

    if (OCTET_COMPARE(&f,&f1)==0)
        printf("RSA Encryption - OK\n");
    else
    {
        printf("RSA Encryption Failed\n");
        return 0;
    } 

    OCTET_INIT(&s,bytes);
    OCTET_CLEAR(&f1);

    IFSP_RSA1(NULL,&priv,&f,&s);
    IFVP_RSA1(NULL,&pub,&s,&f1);

    if (OCTET_COMPARE(&f,&f1)==0)
        printf("RSA1 Signature - OK\n");
    else
    {
        printf("RSA1 Signature Failed\n");
        return 0;
    } 

    f.len=20;
    for (i=0;i<20;i++) f.val[i]=i+1;    /* fake a message */
    f.val[19]=12;                       /* =12 mod 16     */
    OCTET_CLEAR(&f1);

    IFSP_RSA2(NULL,&priv,&f,&s);
    IFVP_RSA2(NULL,&pub,&s,&f1);

    if (OCTET_COMPARE(&f,&f1)==0)
        printf("RSA2 Signature - OK\n");
    else
    {
        printf("RSA2 Signature Failed\n");
        return 0;
    } 

    IF_PUBLIC_KEY_KILL(&pub);
    IF_PRIVATE_KEY_KILL(&priv);

    printf("Generating 1024-bit RW Key Pair....\n");
    IF_KEY_PAIR(NULL,&seed,1024,2,&priv,&pub);

    OCTET_CLEAR(&f1);
    IFSP_RW(NULL,&priv,&f,&s);
    IFVP_RW(NULL,&pub,&s,&f1);

    if (OCTET_COMPARE(&f,&f1)==0)
        printf("RW Signature - OK\n");
    else
    {
        printf("RW Signature Failed\n");
        return 0;
    } 

    printf("\nP1363 IFSSA Signature\n");
    OCTET_CLEAR(&g);
    OCTET_COPY(&seed,&g);       /* random 20-byte message */
    printf("Message is \n");
    OCTET_OUTPUT(&g);
    mlen=1023; 
    EMSA2(&g,NULL,mlen,&f);
    printf("Message Representative is\n");
    OCTET_OUTPUT(&f);
    IFSP_RW(NULL,&priv,&f,&s);
    printf("Signature is\n");
    OCTET_OUTPUT(&s);
    printf("Verification\n");
    printf("Message Representative is\n");
    IFVP_RW(NULL,&pub,&s,&f1);
    OCTET_OUTPUT(&f1);
    if (OCTET_COMPARE(&f,&f1)==0)
        printf("IFSSA Signature - OK\n");
    else
    {
        printf("IFSSA Signature Failed\n");
        return 0;
    } 
    
    IF_PUBLIC_KEY_KILL(&pub);
    IF_PRIVATE_KEY_KILL(&priv);

    OCTET_KILL(&f); OCTET_KILL(&f1);
    OCTET_KILL(&g); OCTET_KILL(&s);

    return 0;
}

