/*---------------------------------------------------------------------------*/
/*									     */
/*	COPYRIGHT	1994, 1995, 1996     Applied Research Corporation    */
/*									     */
/*			1997, 1998	     Space Applications Corporation  */
/*									     */
/*			ALL RIGHTS RESERVED				     */
/*									     */
/*---------------------------------------------------------------------------*/
#ifndef _H_PROTO
#define _H_PROTO
/*
   ** from herr.c
 */
    extern const char *tk_HEstring
                (hdf_err_code_t error_code);

    extern VOID tk_HEpush
                (hdf_err_code_t error_code, const char * function_name,
                 const char * file_name, intn line);

    extern VOID tk_HEreport
                (const char *,...);

    extern VOID tk_HEprint
                (FILE * stream, int32 print_level);

    extern int16 tk_HEvalue
                (int32 level);

    extern VOID tk_HEPclear
                (void);
extern PGSt_SMF_status 
PGS_SMF_GetMsgByCode(     /* Get message by code */
    PGSt_SMF_code code,   /* Input  code */
    char          msg[]);  /* Output user pre-defined message string */

extern PGSt_SMF_status 
PGS_SMF_SetDynamicMsg(          /* Set dynamic message */
    PGSt_SMF_code  code,        /* Input code */
    char          *msg,         /* Input message string to be saved into the
				   static buffer */
    char          *funcname); 

extern PGSt_SMF_status 
PGS_SMF_SetStaticMsg(            /* Set static message */
    PGSt_SMF_code  code,         /* Input code */
    char          *funcname);

extern PGSt_SMF_status 
PGS_PC_GetReference(PGSt_MET_Logical prodID, PGSt_integer *version,char *referenceID);
#endif

#ifdef __cplusplus
extern "C" {
#endif
PGSt_SMF_status
tk_Env(                                /* get default file location */
    char             *environment,     /* file type to request location */
    char             *defaultLoc);      /* actual reference ID string */
#ifdef __cplusplus
}
#endif
