/*****************************************
 *
 * SECUDE Sicherheitstechnologie
 * Informationssystem GmbH, Darmstadt
 *
 * (C) Copyright SECUDE GmbH,  1997 - 2000
 *
 ******************************************/


/*    
    Transport Service Interface (tsi)
    Functions for communication with chipcards and GAO-chipcard-terminals
           Terminal        available protocols
           CCR1          :      T=1, T=14
           CCR2          : T=0, T=1, T=14 and memory cards
           ICT700, ICT710: T=0, T=1, T=14 and memory cards
           CRM700        : T=0, T=1, T=14 and memory cards
    Projekt : PC/CTI
    File    : TSI_FUNC.H
    Version : 2.03
    Date    : 08.11.94
    Author  : GD 3SE3/PUM
*/

#ifdef _WINDOWS                 /* definitions for WINDOWS-DLL's */
	#ifdef _WIN32			   	/* WINDOWS NT ? */
    	#define _F				/* far and pascal not allowed for WINDOWS NT */
		#define _P
	#else						/* WINDOWS 3.1 */
    	#define _F far			/* use far and pascal */
		#define _P pascal
	#endif
#elif _OS2                      /* definitions for OS/2-DLL's */
#    define _F far
#    define _P pascal _loadds
#else
#    define _F
#    define _P
#endif

#ifdef _WINDLL
#    define __E __export        /* Build WINDOWS-DLL -> use the __export keyword for all functions of the DLL */
#elif _OS2DLL
#    define __E _export         /* Build OS/2-DLL -> use the __export keyword for all functions of the DLL */    
#else
#    define __E
#endif

#ifdef __cplusplus              /* extern "C" declaration of C-functions for C++ */
#    define _C "C"
#else
#    define _C
#endif

#ifdef __TURBOC__
#    define TSI_COMMAND_LEN 20
#else
#    define TSI_COMMAND_LEN
#endif

#ifndef uchar
#    define uchar unsigned char
#    define uint  unsigned int
#    define ulong unsigned long
#endif
#ifndef NULL
#    define NULL    ((void *)0)
#endif

/* Definition of the RETURN-Codes (error messages) from the TSI-functions */
#define TSI_OK            0     /* function executed correctly -> OK */
#define TSI_NO_ICC        1     /* no ICC contacted */
#define TSI_STATE_ERR     2     /* command not allowed at this state */
                                /* (e.g.: VCC is off, error executing ICC-OFF of ICC-EJECT, ...) */
#define TSI_BREAK         3     /* communication interrupted (CTRL-BREAK, to many response data,...)*/
#define TSI_COMM_ERR_CT   4     /* communication error PC <-> chipcard terminal */
                                /* no chipcard terminal connected or chipcard terminal not ready */
#define TSI_COMM_ERR_ICC  5     /* communication error with the ICC */
#define TSI_COMX_ERR      6     /* error opening/closing serial interface COMx */
#define TSI_CTH_ERR       7     /* invalid card terminal handle */
#define TSI_WORKING       8     /* TSI-functions already working */
#define TSI_NAD_ERR       9     /* wrong NAD-byte of response data */
                                /* e.g.: NAD-Command=02 and NAD-Response=21 */
#define TSI_PARA_ERR     10     /* wrong parameter (e.g.: invalid protocol, ...) */
#define TSI_CMD_LEN_ERR  11     /* command data to long */
#define TSI_SW_ERR       12     /* tsi_api_chk() -> return code SW1/SW2 not equal reference code */
#define TSI_LENR_ERR     13     /* tsi_api_chk() -> layer-7 response data length to short (shorter than expected with min_lenr) */
#define TSI_JOU_ERR      14     /* error of the internal journal functions */

#define TSI_T0  0               /* tsi_init()  : protocol T=0  (ISO) */
#define TSI_T1  1               /* tsi_init()  : protocol T=1  (ISO) */
#define TSI_T14 2               /* tsi_init()  : protocol T=14 (Germany) */
#define TSI_CTH_MAX   6         /* maximum number of CardTerminalHandles */
#define TSI_CTN_MAX   2         /* maximum number of communication ports with CardTerminals */
                                
#define TSI_COM1 1              /* serial interfaces COM1-COM4 for tsi_init() and tsi_init_std() */    
#define TSI_COM2 2
#define TSI_COM3 3
#define TSI_COM4 4
#define TSI_COM5 5
#define TSI_COM6 6
#define TSI_COM7 7
#define TSI_COM8 8
                                /* Definitions of the Destination-Parameter (P1) of the CT-Commands */
#define TSI_CT   0              /* Destination address for the CT */
#define TSI_ICC1 1              /* Card interfaces number 1 */
#define TSI_ICC2 2              /* Card interfaces number 2 */
#define TSI_ICC3 3              /* Card interfaces number 3 */
#define TSI_ICC4 4              /* Card interfaces number 4 */
#define TSI_ICC5 5              /* Card interfaces number 5 */
                                /* Definitions for the CartTerminalType for tsi_init() and tsi_init_std() */
#define TSI_CT_AUTO   0         /* automatic detection of the connected CardTerminal */
#define TSI_CT_CCR1   1         /* CardTerminalType = CCR1 */
#define TSI_CT_CCR2   2         /* CardTerminalType = CCR2 or other intelligent CT */
#define TSI_CT_CRM7XX 3         /* CardTerminalType = CRM700 and CRM710 */

#define TSI_CMD_CHAINING_SIZE  254  /* maximum block size of chained command blocks */
#define TSI_RESP_CHAINING_SIZE 255  /* maximum block size of chained response blocks
                                       (parameter for IFS_REQUEST - tsi_ifs()) */
#define TSI_CHAIN_BUF_LEN 512   /* number of bytes, by which the chaining buffer is expanded, if
                                   it is to small to hold all chained response data */

#define TSI_BAUD_AUTO 0l        /* Value for auto selection of the baud rate for intelligent CT's for tsi_init_auto() */
#define TSI_BAUD_CT_DEF 9600l   /* Default baudrate of intelligent CT's */

#define TSI_CLOSE_ALL 0xffff    /* Parameter for tsi_close() -> Close all open communications */

#define TSI_NAD_CT   0x12       /* Definition of NODE-ADRESS-Bytes for intelligent CT's */
#define TSI_NAD_ICC1 0x02
#define TSI_NAD_ICC2 0x32
#define TSI_NAD_ICC3 0x42
#define TSI_NAD_ICC4 0x62
#define TSI_NAD_ICC5 0x72

#define TSI_NAD_T14  0x31

                                /* Parameters for the function tsi_winmsg() */
#define TSI_MSGDISABLE 0        /* automatc execution DISABLE */
#define TSI_MSGENABLE  1        /* automatc execution ENABLE */
#define TSI_MSGEXECUTE 2        /* execution of WINDOWS-Messages if there is one available */
                                
#define TSI_DEBUG_NO_LF 0       /* parameters for the tsi_jou_*() - functions */
#define TSI_DEBUG_LF    1
#define TSI_DEBUG_OVERWRITE 0
#define TSI_DEBUG_APPEND    1

#define TSI_ENABLE  1           /* enable flag */
#define TSI_DISABLE 0           /* disable flag */

                                /* check CardTerminalNumber */
#define TSI_CHECK_CTH     if(cth > TSI_CTH_MAX-1 || tsi_cth[cth].installed!=1) return TSI_CTH_ERR;
                                /* check working flag to avoid re-entry problems in MS-WINDOWS */
#define TSI_CHECK_WORKING if(tsi_working) return TSI_WORKING; else tsi_working = 1;

                                /* structure with information about the initialised cth's - internal use only */
struct stsi_cth                 /* CardTerminalHandle structure */
{
    uchar installed;            /* 1 -> Communication initialized */
    uint  ctn;                  /* internal CardTerminalNumber for the basic communication functions */
    uint  dest;                 /* dest - Parameter for extended functions 
                                          Values: TSI_CT, TSI_ICC1, TSI_ICC2, ... */
    uint  cth;                  /* handle to be used for CT-commands of the extended functions */
    uchar proto;                /* transmission protocol for communication (TSI_T1, TSI_T14) */
    uchar init_mode;            /* initialisation mode: 0 = manual; 1 = tsi_init_auto() */
    long  baud_max;             /* maximum baudrate for CT-PTS */
    uint  port;                 /* port number */
    long  baud;                 /* default-parameters */
    char  db;
    char  sb;
    char  p;
};
extern struct stsi_cth tsi_cth[];

extern char tsi_working;        /* this flag is used to avoid re-entry problems of the
                                   TSI-functions with MS-WINDOWS
                                   if a function is called and the flag tsi_working is set
                                   the function returns TSI_WORKING */

extern _C int __E _F _P tsi_open(/*uint _F *cth, uint port, uint dest, uint ctt, long baud_max*/);
/*
    Open a new handle for the communication with the ICC or a CardTerminal.
    Initialization of the serial interface and automatic detection of the connected CT
    and Hardware-Reset of the CT.
    PARAMETER:
    uint *cth ..... CardTerminalHandle: logical card terminal handle, which
                    during initialisation.
                    All further actions must be called with this number.
    uint port ..... physical protnumber
                    Values: TSI_COM1 - TSI_COM4 (COM1-COM4)
    uint dest ..... Destination of the communication with this CardTerminal
                    TSI_ICCx -> Open a handle for the communucation with ICCx of this CardTerminal
                    TSI_CT   -> Open a handle for the communication with the CardTerminal
    uint ctt ...... CardTerminalType
                    Values: TSI_CT_AUTO   -> automatic detection of the CT-Type
                            TSI_CT_CCR1   -> set CT-Type = CCR1
                            TSI_CT_CCR2   -> set CT-Type = CCR2
                            TSI_CT_CRM7XX -> CRM700 or CRM710
    long baud_max.. maximum value of the baud rate for the communication with intelligent CT's
                    TSI_BAUD_AUTO                        -> select maximum baud rate supported
                                                            from the CT
                    TSI_BAUD_CT_DEF                      -> no protocol type selection is executed
                    other value (e.g.: 19200, 38400,...) -> maximum value for auto selection
                                                            of the baud rate
    RETURN: 0 ..... Initialisation OK
            !=0 ... ERROR (see general return codes)
*/

extern _C int __E _F _P tsi_open_man(/*uint _F *cth, uint port, uint dest, uint ctt, uint proto,
                                 long baud, uint db, uint sb, uint p*/);
/*
    Transport Service Interface (tsi)
    Initialize serial interface, assigning of the physical
    port number with the logical CardTerminal-Number and initialize
    the transmission protocol.
    PARAMETER:
    uint *cth ..... CardTerminal-Number: logical number which is assigned
                    with the card terminal.
                    All further communcation functions must be called with this number.
    uint port ..... physical port number
                    Werte: TSI_COM1 - TSI_COM8 (COM1-COM8)
    uint dest ..... Destination of the communication with this CardTerminal
                    TSI_ICCx -> Open a handle for the communucation with ICCx of this CardTerminal
                    TSI_CT   -> Open a handle for the communication with the CardTerminal
    uint ctt ...... CardTerminalType                    
                        TSI_CT_CCR1   -> CardTerminal = CCR1
                        TSI_CT_CCR2   -> CardTerminal = CCR2 or other intelligent CT
                        TSI_CT_CRM7XX -> CRM700 or CRM710
    uint proto .... transmission protocol
                    Value: TSI_T1, TSI_T14
    long baud ..... baudrate  [9600 / 19200]
    uint db ....... data bits [8]
    uint sb ....... stop bits [2]
    uint p ........ parity    ['E']

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_open_cth(/*uint _F *cth, uint port, uint dest*/);
/*
    Open a new handle for the given port and dest parameter.
    This function must be used if two or more handles for one CT are
    required. In this case the first cth is assigned with tsi_open()
    or tsi_open_man() and all other cth's must be assigned with
    tsi_open_cth().
    e.g.: cth1 = COM1, TSI_CT .... assigned with tsi_open    (&cth1, TSI_COM1, TSI_CT, ...)
          cth2 = COM1, TSI_ICC1... assigned with tsi_open_cth(&cth2, TSI_COM1, TSI_ICC1)
          cth3 = COM1, TSI_ICC2... assigned with tsi_open_cth(&cth3, TSI_COM1, TSI_ICC2)
    
    PARAMETER:
    uint *cth ..... CardTerminalHandle: logical card terminal handle, which
                    is assigned during initialization.
                    All further actions must be called with this handle.
    uchar port .... physical portnumber of an already initialized CT
                    Values: TSI_COM1 - TSI_COM4 (COM1-COM4)
    uint dest ..... Destination of the communication with this CTH
                    TSI_ICCx -> Open a handle for the communucation with ICCx
                                of this CardTerminal
                    TSI_CT   -> Open a handle for the communication with the
                                CardTerminal
    RETURN:
            TSI_OK ........OK -> handle installed or handle already exists
            TSI_COMX_ERR...serial interface not initialized
            TSI_CTH_ERR....cannot create a new CardTerminalHandle
*/

extern _C int __E _F _P tsi_ct_type(/*uint cth*/);
/*
    This function is used to give back the CardTerminalType which was
    detected during initialization.
    
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()

    RETURN: TSI_CT_AUTO   -> no CardTerminal detected
            TSI_CT_CCR1   -> CCR1 detected
            TSI_CT_CCR2   -> CCR2 detected
            TSI_CT_CRM7XX -> CRM7XX detected
*/

extern _C int __E _F _P tsi_off(/*uint cth*/);
/*
    Turn off VCC and execute power down procedure.
    This function is only supported with the ChipcardTerminal CCR1.
    PARAMETER:
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_resynch(/*uint cth, uint nadc*/);
/*
    Execute communication layer-2 resynchronisation
    This function should be called if the communication port is reopened
    and the application program wants to communicate with an already
    contacted ICC without reseting the card.
    PARAMETER:
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
    uchar nadc .... NAD-Byte for the RESYNCH-Command:
                        xx
                        ||_ Destination Address
                        |__ Source Address

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_ifs(/*uint cth, uint nadc, uint bl_size*/);
/*
    Execute communication layer-2 IFS-request-command.
    This command is only allowed when the transmission protocol T=1 is used.    
    This command must be executed in order to tell the ICC/CardTerminal the maximum
    size of one transmission block accepted by the PC/Host.
    default block size: ISO7816 - 32 Byte
                        STARCOS V1.1: 64Byte
    
    PARAMETER:
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
    uint bl_size... new transmission block size(e.g. 90 Bytes)
                    The block size is the number of layer-7 data bytes transmitted
                    in one block.

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_api_man(/*uint cth, uint nadc, uint _F *nadr,
                                uint lenc, uchar _F *cmd, uint _F *lenr, uchar _F * _F *resp*/);
extern _C int __E _F _P tsi_api_man_np(/*uint cth, uint nadc, uint _F *nadr,
                                   uint lenc, uchar _F *cmd, uint _F *lenr, uchar _F *resp*/);
/*
    Transport Service Interface (tsi) - Application Protocol Interface
    Basic communication function for layer-7 communication.
    
    PARAMETER:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during initialization.
    uint nadc ..... NAD-Byte for the command:
                        xx
                        ||_ Destination Address
                        |__ Source Address
    uint *nadr .... NAD-Byte of the response - coding like nadc
                    NULL -> NAD of the response will not be returned
    uint lenc ..... length of command data
    uchar *cmd .... pointer to command data
    uint *lenr .... length of response data
                    NULL -> response length is not returned
    uchar **respd.. pointer to response data
                    NULL -> response data are not returned

    RETURN: 0 ..... communication OK
            !=0 ... Error (see general return-codes)
*/
/*
    The function with the "_np" (no pointer) extension has the same functionality
    as the standard function, except it's declaration doesn't have a pointer to
    pointer definition. By calling this function the data to be returned are
    copied into the buffer which must be supplied by the calling functions.
    This function can be used with programming languages which don't support
    pointer to pointer definitions (e.g.: VISUAL BASIC).
*/

extern _C int __E _F _P tsi_close(/*uint cth*/);
/*
    Transport Service Interface (tsi)
    Close serial interface
    PARAMETER:
    uint cth...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
                    0...(TSI_CTN_MAX-1) -> close serial port for desired
                                           CardTerminalNumber
                    TSI_CLOSE_ALL       -> close all serial ports

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_ccr1_timing(/*uint cth, uint freq*/);
/*
    This function is only needed if the ChipcardTerminal CCR1
    is used with another clock frequency than 4.9MHz.
    In this case the function must be called in order to adjust the
    timing for the CCR1-control functions.(RESET, EJECT)

    PARAMETER:
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
    uint freq...... Clock frequency [kHz] which is used with the
                    ChipcardTerminal CCR1
    e.g.:        3500kHz   4900kHz   9800kHz
         RESET   2800連    2000連    1000連
         ENABLE  7000連    5000連    2500連
         EJECT   22400連   16000連   8000連

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_set_timing(/*uint cth, long cwt, long bwt*/);
/*
    This function is used for setting new values for the
    Character Waiting Time(CWT) and the Block Waiting Time(BWT).
    The function must only be called when the default values for
    CWT and BWT don't match with the ICC-/CardTerminal-Parameters.

    PARAMETER:
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
    long cwt ...... new value for Character Waiting Time [ms]
    long bwt ...... new value for Block Waiting Time     [ms]
    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_get_timing(/*uint cth, long _F *cwt, long _F *bwt*/);
/*
    This function returns the current values of the Character Waiting Time(CWT) 
    and the Block Waiting Time(BWT).

    PARAMETER:
    uint cth ...... CardTerminal-Nummer: logical card terminal number, which
                    was assigned during tsi_init()
    long *cwt ..... return value for Character Waiting Time [ms]
    long *bwt ..... return value for Block Waiting Time     [ms]
    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_winmsg(/*int mode*/);
/*
    Execution of WINDOWS-Messages
    This function is used for the execution of WINDOWS-Messages as well
    as enabling and disabling the automatic execution of WINDOWS-
    messages while the TSI-functions are executed.
    Normaly the autoamtic execution is disabled. This means, while the
    TSI-functions are working(e.g.: Waiting for the response after
    sending a command) no WINDOWS-messages are executed.

    PARAMETER: mode: 0(TSI_MSGDISABLE) ... automatc execution DISABLE
                     1(TSI_MSGENABLE) .... automatc execution ENABLE
                     2(TSI_MSGEXECUTE).... execution of WINDOWS-Messages if there
                                           is one available
    RETURN: 0 -> no WINDOWS-Message available
            1 -> one WINDOWS-Message was executet
*/

extern _C int __E _F _P tsi_cancel(/*void*/);
/*
    This function cancels the communication with the CardTerminal.
    The function can be called from the control-function of e.g.
    a CANCEL-Button in MS-Windows to cancel the current communication
    immediatly without waiting for the response of the Chipcard or
    ChipcardTerminal.

    RETURN: TSI_OK
*/

extern _C char _F * __E _F _P tsi_get_msg(/*int msg_code*/);
/*
    Convert return code of tsi_xxx()-functions into text message
    Parameter:
               int msg_code ... return-code of the tsi_xxx() - functions
    RETURN:    char *msg ...... pointer to error message
*/

#ifndef _WINDOWS
    extern _C int tsi_install_break(/*void*/);
    /*
        Install a function for redirection of the CTRL-BREAK-interrupt.
        This function cancels the communictation with the chipcard or
        chipcard terminal.
        RETURN: TSI_OK
                TSI_STATE_ERR  -> redirection not installed
    */

    extern _C int tsi_remove_break(/*void*/);
    /*
        Remove function for redirection of the CTRL-BREAK-Interrupt
        RETURN: TSI_OK
                TSI_STATE_ERR  -> redirection not installed
    */
#endif

extern _C int __E _F _P tsi_req_icc(/*uint cth, uint req_time, char _F *text, uint _F *lenatr, uchar _F * _F *atr*/);
extern _C int __E _F _P tsi_req_icc_np(/*uint cth, uint req_time, char _F *text, uint _F *lenatr, uchar _F *atr*/);
/*
    Wait for ICC and reset ICC.

    CARDTERMINAL: CCR1 and all intelligent CardTerminals
    PARAMETER:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during tsi_init_auto()
    uint req_time.. maximum waiting time for request ICC [0-255 s]
                    when the chipcardterminal CCR1 is used, only 0 s is
                    allowed for req_time.
    char *text .... text to be displayed on the CT-display
                    NULL or emty string -> display default text
    uint *lenatr... length of the received ATR
                    NULL -> don't give back the ATR
    uchar **atr ... pointer to the received ATR
                    NULL -> don't give back the ATR

    RETURN: as defined in the general definition of the RETURN-codes
*/
/*
    The function with the "_np" (no pointer) extension has the same functionality
    as the standard function, except it's declaration doesn't have a pointer to
    pointer definition. By calling this function the data to be returned are
    copied into the buffer which must be supplied by the calling functions.
    This function can be used with programming languages which don't support
    pointer to pointer definitions (e.g.: VISUAL BASIC).
*/

extern _C int __E _F _P tsi_icc_reset(/*uint cth, uint _F *lenatr, uchar _F * _F *atr*/);
extern _C int __E _F _P tsi_icc_reset_np(/*uint cth, uint _F *lenatr, uchar _F *atr*/);
/*
    Execute hardware reset of the ICC or software reset of the CardTerminal
    (only if an intelligent CardTerminal is used).

    CARDTERMINAL: CCR1 and all intelligent CardTerminals
    PARAMETER:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during tsi_init_auto()
                    If the handle was assigned to an ICC a hardware reset
                    of the ICC is executed.
                    If the handle was assigned to a CT a software-reset
                    of the CT is executed(only intelligent CT's).
    uint *lenatr... length of the received ATR
                    NULL -> don't give back the ATR
    uchar **atr ... pointer to the received ATR
                    NULL -> don't give back the ATR

    RETURN: as defined in the general definition of the RETURN-codes
*/
/*
    The function with the "_np" (no pointer) extension has the same functionality
    as the standard function, except it's declaration doesn't have a pointer to
    pointer definition. By calling this function the data to be returned are
    copied into the buffer which must be supplied by the calling functions.
    This function can be used with programming languages which don't support
    pointer to pointer definitions (e.g.: VISUAL BASIC).
*/

extern _C int __E _F _P tsi_icc_eject(/*uint cth, uint eject_time, uint alarm, char _F *text*/);
/*
    Eject contacted ICC.
    CARDTERMINAL: CCR1 and all intelligent CardTerminals
    PARAMETER:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during tsi_init_auto()
    uint eject_time maximum waiting time for removing the ICC [0-255 s]
                    when the chipcardterminal CCR1 is used, only 0 s is
                    allowed for req_time.
    uint alarm .... 0 -> no acustic signal
                    1 -> acustic signal
    char *text .... text to be displayed on the CT-display
                    NULL or emty string -> display default text

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_rdr_status(/*uint cth*/);
/*
    Get the current readerstatus.
    CardTerminal ready ?
    Card contacted ?
    
    CARDTERMINAL: CCR1 and all intelligent CardTerminals
    PARAMETER:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during tsi_init_auto()
                    If the handle was assigned to an ICC the status of
                    the ICC port is returned.
                    If the handle was assigned to a CT the status of the
                    CT is returned.

    RETURN: as defined in the general definition of the RETURN-codes
*/

extern _C int __E _F _P tsi_api(/*uint cth, uint lenc, uchar _F *cmd,
                            uint _F *lenr, uchar _F * _F *resp,
                            uint min_lenr, uint sw, uint sw_c*/);
extern _C int __E _F _P tsi_api_np(/*uint cth, uint lenc, uchar _F *cmd,
                               uint _F *lenr, uchar _F *resp,
                               uint min_lenr, uint sw, uint sw_c*/);
/*
    Communication with the ICC (with CCR1) and with intelligent CT's.
    In addition this function performs some checks of the response data
    if specified with the parameters (min_lenr, sw, sw_c).

    CARDTERMINAL: CCR1 and all intelligent CardTerminals
    PARAMETER:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during tsi_init_auto()
                    If the handle was assigned to an ICC the communication
                    with the according ICC is executed.
                    If the handle was assigned to the CT the communication
                    with the according CT is executed.
    uint lenc ..... length of command data (layer 7 data)
    uchar *cmd .... pointer to command data
    uint *lenr .... length of the received response data
                    NULL -> response data are not given back
    uchar **respd.. pointer to the received response data
                    NULL -> response data are not given back
    uint min_lenr.. minimum length of expected response data
                    if the length of the response data is shorter than
                    expected then TSI_LENR_ERR is returned from tsi_api_chk()
    uint sw ....... compare value for SW1/SW2 (T=0 and T=1) or CCRC/APRC (T=14)
                    if the status SW1/SW2 (CCRC/APRC) is not equal this status, than
                    the function returns TSI_SW_ERR.
    uint sw_c ..... control byte for the compare operation of the status SW1/SW2 (CCRC/APRC)
                    only those bit's which are set to 1 in sw_c are compared !

    RETURN: as defined in the general definition of the RETURN-codes
*/
/*
    The function with the "_np" (no pointer) extension has the same functionality
    as the standard function, except it's declaration doesn't have a pointer to
    pointer definition. By calling this function the data to be returned are
    copied into the buffer which must be supplied by the calling functions.
    This function can be used with programming languages which don't support
    pointer to pointer definitions (e.g.: VISUAL BASIC).
*/

extern _C int __E _F _P tsi_display(/*unsigned int cth, unsigned int time, char _F *text*/);
/*
    tsi_display( .. )
    
    Displays a ASCIIZ-string on the SCT display

    Parameter:
       uint   cth            Card Terminal Handle, device to be used
       uint   time           Displaying time in seconds 0 - 255
       char  *text           Text to be displayed (max 32 char)
    RETURN: int
             0               Function correctly executed
             !=0             ERROR (see general tsi_.. return codes)
*/

extern _C int __E _F _P tsi_version(/*unsigned int cth, unsigned int _F *ver_len, unsigned char _F * _F *version*/);
extern _C int __E _F _P tsi_version_np(/*unsigned int cth, unsigned int _F *ver_len, unsigned char _F *version*/);
/*
    tsi_version( .. )
    
    Get information about the smartcard terminal

    Parameter:
       uchar   cth           Card Terminal Handle, device to be used
       uchar  *ver_len       returns the length of the version
       uchar **version       Pointer for receiving the version
                             (NULL return no data)
    RETURN: int
             0               Function correctly executed
             !=0             ERROR (see general tsi_.. return codes)
*/
/*
    The function with the "_np" (no pointer) extension has the same functionality
    as the standard function, except it's declaration doesn't have a pointer to
    pointer definition. By calling this function the data to be returned are
    copied into the buffer which must be supplied by the calling functions.
    This function can be used with programming languages which don't support
    pointer to pointer definitions (e.g.: VISUAL BASIC).
*/

extern _C int __E _F _P tsi_ctrl_lines(/*unsigned int ctrl_status*/);
/*
    This function enables or disables the check of the control lines of the CT
    when the CCR2 or the CRM7xx is used.
    Normaly PC/CTI checks, whether the control lines DTR/DSR and RTS/CTS
    are connected together. This function can be used to disable this
    feature. In this case the automatic detection of the CT-type is
    not possible.
    PARAMETER:
        uint ctrl_status ... TSI_DISABLE -> disables the check of the control lines
                             TSI_ENABLE  -> reenables the check of the control lines
    RETURN: TSI_OK
*/

extern _C int __E _F _P tsi_ctrl_rs232(/*unsigned int cth, unsigned int bit_dtr, unsigned int bit_rts*/);
/*
    Function for the control of the RTS- and DTR-line of the serial interface

    Parameter:
    uint cth ...... CardTerminalHandle: logical card terminal handle, which
                    was assigned during tsi_open()
    uint bit_dtr... 0 -> DTR-line deactivated
                    1 -> DTR-line activated
    uint bit_rts... 0 -> RTS-line deactivated
                    1 -> RTS-line activated
    RETURN: TSI_OK
*/

extern _C int __E _F _P tsi_debug(/*uint _F *lenc, uchar _F * _F *cmd, uint _F *lenr, uchar _F * _F *respd*/);
extern _C int __E _F _P tsi_debug_np(/*uint _F *lenc, uchar _F *cmd, uint _F *lenr, uchar _F *respd*/);
/*
    This functions returns the last command and response data
    sent with tsi_api() or tsi_api_chk().
    
    PARAMETER:
    uint *lenc .... length of command data
    uchar **cmd ... pointer to pointer to command data: this pointer returns only
                    a valid pointer, if the data of the last call of tsi_api() or
                    tsi_api_chk() are still valid because the command data are
                    not stored in a internal buffer !
    uint *lenr .... length of response data
    uchar **respd.. pointer to pointer to response data

    RETURN: TSI_OK
*/
/*
    The function with the "_np" (no pointer) extension has the same functionality
    as the standard function, except it's declaration doesn't have a pointer to
    pointer definition. By calling this function the data to be returned are
    copied into the buffer which must be supplied by the calling functions.
    This function can be used with programming languages which don't support
    pointer to pointer definitions (e.g.: VISUAL BASIC).
*/

extern _C int __E _F _P tsi_jou_on(/*uint len*/);
/*
    This function turns the journal on.
    Every byte between the PC and the CT/ICC is saved in the internal
    journal buffer.
    PARAMETER:
    uint len ... size of the internal journal buffer
    RETURN: 0  -> OK
            -1 -> error
*/

extern _C int __E _F _P tsi_jou_save(/*char _F *file, uint append, uint linefeed*/);
/*
    This function saves all data stored in the internal journal buffer
    in the given file and clears the journal buffer.
    PARAMETER:
    char *file ...... path\filename of the journal file
    uint append ..... TSI_DEBUG_OVERWRITE->if the journal file allready exists, the
                                           old content is destroyed
                      TSI_DEBUG_APPEND   ->if the journal file allready exists, the
                                           new data are appended at the end of the file
    uint linefeed ... TSI_DEBUG_NO_LF    ->every command/response is stored in one line
                      TSI_DEBUG_LF       ->a linefeed is inserted after 16 bytes in
                                           one line
    RETURN:  0 -> OK
            -1 -> error
*/

extern _C int __E _F _P tsi_jou_get(/*uint number, uint offset, uint len, char *s*/);
/*
    return required journal block in ASCII format
    PARAMETER:
    uint number ... required block number of the journal buffer
                    every command and response is counted as one block
                    e.g.:1 = last response
                         2 = last command
                         ...
    uint offset ... offset within the block
                    0 -> block begin
    uint len ...... number of bytes to be converted
                    0 -> convert total block
    char *s ....... string for the journal block, the journal data
                    is returned in ASCII format
                    e.g.: "PC->CT0 20 00 05 00 B0 00 00 00"
    RETURN: 0 -> OK
*/

extern _C int __E _F _P tsi_jou_free(/*void*/);
/*
    This function calculates the number of bytes free in the
    internal journal buffer
    RETURN: number of bytes free in the journal buffer
*/

extern _C int __E _F _P tsi_jou_clear(/*void*/);
/*
    This function clears the contents of the internal journal buffer
    RETURN: 0 -> OK
*/

extern _C int __E _F _P tsi_jou_off(/*void*/);
/*
    This function turns of the journal.
    The data in the journal buffer are destroyed and
    the journal buffer is deleted.
    RETURN: 0 -> OK
*/

/****************************************
    Functions for internal use only !
*****************************************/
extern int ccr1_status(/*uint cth*/);
extern int ccr1_eject(/*uint cth*/);
extern int ccr1_reset(/*uint cth, uint *lenatr, uchar **atr*/);
extern int convert_status(/*uint ctn, uchar st*/);
extern int tsi_convert_sw(/*uchar *sw*/);
extern uchar tsi_convert_nad(/*uint ctn, uint dest*/);
extern int ccr2_version(/*unsigned int ctn, unsigned int *ver_len, unsigned char **version*/);

