/*---------------------------------------------------------------------------*/
/*									     */
/*	COPYRIGHT	1994, 1995, 1996     Applied Research Corporation    */
/*									     */
/*			1997, 1998	     Space Applications Corporation  */
/*									     */
/*			ALL RIGHTS RESERVED				     */
/*									     */
/*---------------------------------------------------------------------------*/
/*******************************************************************************
BEGIN_FILE_PROLOG:

FILENAME:   
        PGS_MET_GetPCAttr
 
DESCRIPTION:
        Retrieves parameter values from the PCF table which are either located as 
	HDF attributes in defined product files or in separate ASCII files. ASCII files
	must be in flat ODL format. 
	
AUTHOR: 
        Alward N. Siyyid/ EOSL
        Carol S. W. Tsai / Applied Reseach Corporation
        Peter D. Noerdlinger / SM&A Corp
	Abe Taaheri / Emergent Information Technologies, Inc.

HISTORY:
        18-MAY-95      ANS     Initial version
	01-JUN-95      ANS     Code inspection updates
	13-July-95     ANS     Improved Fortran example
	24-July-95     ANS     Added error handling in case parameters are not 
			       defined in hdf or ascii file
	25-July-95     ANS     Fixed ECSed01030
        09-Aug-95      ANS     Added function name to the C synopsis
	11-MAR-96      ANS     Updated for tk5+
        08-Apr-97      CSWT    Added code so that landsat7 files and the different
                               groups in an ascii file can be read.
                               Changed code to return a different status code for
                               "Bad ODL" and "Praameter Not Set"
        14-Apr-97      CSWT    Added  code for reading Node value that is the type
                               of datetime in Landsat7 metadata
 
        30-May-97      CSWT    Changed code to enable the user to retrieve the 
                               container attribute value from an ASCII Metadata 
                               file
        15-Jun-97      CSWT    Added code enable the datetime data that is not in the type of
                               string but in the type of UTC DATETIME format without double
                               quotes surrounding it can be retreived from the HDF metadat
                               file or non-HDF metadata file. 
        07-Aug-97      CSWT    Dued to the Archive metadata was not written to the ASCII 
                               metadata file .met that was generated when the user write the  
                               metadata attaching to the HDF file.  Added code to enable the 
                               user to retrieve the Inventory metadata from the ASCII metadata 
                               file, .met, whereas retrieve the Archive metadata from the HDF
                               file even the given input file is an ASCII metadata file .met(
                               This changing is for NCR ECSed07758 about PGEs need to get 
                               metadata from HDF files in B.0)
        01-Oct-97      CSWT    Modified the code that set hdfattrnameflag to be PGS_TRUE if 
                               the HDF attribuet name is equal to productmetadata.X or 
                               archivemetadata.X (X=0...n) to set hdfattrnameflag to be 
                               PGS_TRUE if the HDF attribuet name is equal to coremetadata.X
                               (x=0...n) (This changing is for NCR ECSed09301 about change
                               the Flag set up for archive HDF attribute to inventory) 
        02-Oct-97      CSWT    Fixed Bug ECSed09222 about a defect in retrieving the Attribute 
                               of Date and Time values
        18-Oct-97      CSWT    Changed the variable zone_hours, Zone hours from GMT (-12 - +12),  
                               that defined as a data type of long to be the data type of short 
                               in order to prevent a core dump problem on sgi old 32 bit and  
                               sgi new 32 bit from executing the MET TestDriver program to
                               retrieve the attribute value with the data type of DateTime 
        22-Dec-97      CSWT    Added C library function free() to release previously allocated
                               memory for variable date_time_Ptr, a ODLDate struct pointer
                               declared to hold date and time values (This change is for NCR
                               ECSed10255 about a user (ASTER) is getting a core dump in
                               _get_pcattrib)
        02-Feb-98      CSWT    Deteted two printf, the C User Command, statements called for debugging  
                               Added C Standard I/O function "fclose" to close the file associated 
                               with fp which is a file pointer previously obtaioned using C Standard
                               I/O function "fopen" (This change is for NCRed11788 about Toolkit 
                               5.2.1 PGS_MET_GetPCAttr.c fopen without matching fclose)
        27-May-98      CSWT    Modified the if statement
                               from:
                               if(valueNode->item.precision == 99) Zcharth = PGS_TRUE;
                               to:
                               if(valueNode->item.precision == -99) Zcharth = PGS_TRUE;
                               dued to item.precision, a field defined in the function cvtvalue() 
                               to hold date/time value, was modified from the original value
                               of 99 to -99 if zone indicator existing in the data file (This
                               change is for NCR ECSed15136 about The date_time values are too long)
        12-Jun-98      CSWT    Modified code that call the function CopyAggregate() to copy a 
                               source aggregate node with all of its parameters and all of the node's 
                               progeny into a destination temporal node to only assign the address of 
                               start of a source aggregate node into a destination temporal node 
                               and also deleted code that call the function RemoveAggregate() to remove an
                               aggregate node and all its progeny as long as the function CopyAggregate()
                               being called (This change is for NCR ECSed15508 about it spends too much 
                               time to retrieve the data for badpixelinformation)

        18-Aug-1998   STX S.Zeng  Modified for Win95
        12-Jan-1999    PDN    corrected the leap year calculation
	25-Aug-2000    AT      Modified the code to enable users to
	                       retrieve attribute from an ASCII metadata file in
			       the INVENTORYMETADATA section (or from landsat7 
			       ASCII metadata file)(NCR ECSed27912). Introduced
			       metflag(with default value of "FLASE") that will
			       be "TRUE" if hdfAttrName is set to
			       "PGS_MET_GRP_NAME=INVENTORYMETADAT" as mentioned
			       in the example for PGS_MET_GetPCAttr in the
			       TOOLKIT Users Guide.The metflag will be "TRUE" if
			       hdfAttrName containes "PGS_MET_LSAT_GRP=" that is
			       used to get attributes from Landsat7 ASCII
			       metadata file as  mentioned in the example for 
			       PGS_MET_GetPCAttr in the TOOLKIT Users Guide.

END_FILE_PROLOG
*******************************************************************************/

/* include files */

#include "PGS_MET.h"
#include <ctype.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

/* odl include files */

#include <CUC/odldef.h>
#include <CUC/odlinter.h>

/***************************************************************************
BEGIN_PROLOG:

TITLE: 
        Accesses metadata parameters in HDF products or independent ASCII files
  
NAME:  
        PGS_MET_GetPCAttr()

SYNOPSIS:
C:
        #include "PGS_MET.h"

	PGSt_SMF_status
	PGS_MET_GetPCAttr(
	PGSt_PC_Logical  fileId,
	PGSt_integer     version,
	char *           hdfAttrName,
	char *           parmName,
	void *           parmValue)

FORTRAN:
         include "PGS_MET_13.f"
	 include "PGS_MET.f" 
	 include "PGS_SMF.h"
         integer function pgs_met_getpcattr(fileId, version, hdfAttrName, parmName, parmValue) 

         character*      fileId
	 integer	 version
	 character*	 hdfAttrName
	 character*      parmName
	 'user defined'  parmValue
   
DESCRIPTION:
	Metadata parameters held in HDF attributes or in a separate ascii file
	can be read and parsed using this tool

INPUTS:
        Name            Description            Units    	Min          Max
        ----            -----------             -----   	---          ---
        fileId		product file id		none		variable     variable
	version		product version number  none		1	     variable
	hdfAttrName	name of HDF attribute   none		N/A	     N/A
			containing metadata
	parmName	metadata parameter name none            N/A          N/A
	

OUTPUTS:
	attrValue       value of attribute to   none            N/A          N/A
			be passed back to the 
			user

RETURNS:   
   	PGS_S_SUCCESS			
	PGSMET_E_PCREAD_ERR	"Unable to obtain <filename or attribute filename> from the PC table"
				Most likely that <filename or attribute filename> is not defined in the PCF
	PGSMET_E_FILETOODL_ERR  "Unable to convert <filename> into an ODL format"
				error returns from lower level routines should expalin the problem
	PGSMET_E_AGGREGATE_ERR		Unable to create odl aggregate <aggregate name>
					It definately means that ODL routine has failed to allocate 
					enough memory
	PGSMET_E_SYS_OPEN_ERR	Unable to open pc attribute file
				Usually if the file does not exist at the path given, check the name and path of the file
	PGSMET_E_ODLTOVAL_ERR   Unable to convert attribute values from the odl format
				error returns from lower level routines should expalin the problem

EXAMPLES:
C:

	This is just an extract of the call from a full example given in PGS_MET_Init() prolog.

ival =0;
	ret = PGS_MET_GetPCAttr(MODIS_FILE, 1, "metadata", "SizeMBECSDataGranule", &ival);
	strcpy(datetime, "");
	ret = PGS_MET_GetPCAttr(MODIS_FILE, 1, "metadata", "RangeBeginningDateTime", &datetime);       
	dval = 0;
	ret = PGS_MET_GetPCAttr(MODIS_FILE, 1, "metadata", "EastBoundingCoordinate", &dval);
	printf("%d %lf %s\n", ival, dval, datetime);
	for(i = 0; i < 6; i++) dvals[i] = 0.0;
	ret = PGS_MET_GetPCAttr(MODIS_FILE, 1, "metadata", "GRingPointLatitude.1", dvals);
	for(i = 0; i < 6; i++) printf("%lf", dvals[i]);
	printf("\n");

	for(i = 0; i<3; i++) strcpy(svals[i], "");
        ret = PGS_MET_GetPCAttr(MODIS_FILE, 1, "metadata",  "LocalityValue", svals);
        for(i = 0; i<3; i++) printf("%s ", svals[i]);
        printf("\n");
	for(i = 0; i<5; i++) ivals[i] = 0;
        ret = PGS_MET_GetPCAttr(MODIS_FILE, 1, "metadata",  "ZoneIdentifier", ivals);
        for(i = 0; i<5; i++) printf("%d ", ivals[i]);
        printf("\n");

FORTRAN:

This is just an extract of the call from a full example given in PGS_MET_Init() prolog.

C	Note the way _i for integer, _d for double and _s for strings are used 
C	at the end of the function name. This is necessary because fortran 
C	compiler would complain about type conflicts if a generic name
C	is used

C	 retrieve some of the values previously set from the written hdf attrbute 
	ival(1) =0
	result = pgs_met_getpcattr_i(MODIS_FILE, 1, "coremetadata.0", "SizeMBECSDataGranule", ival)

	datetime = ""
	result = pgs_met_getpcattr_s(MODIS_FILE,, 1, "coremetadata.0", "RangeBeginningDateTime", datetime)
	dval(1) = 0
	ret = pgs_met_getpcattr_d(MODIS_FILE,, 1, "coremetadata.0", "EastBoundingCoordinate", dval)
	print *, ival(1), dval(1), datetime
	do 10 i = 1,6
		dvals(i) = 0.0
 10	continue
	ret = pgs_met_getpcattr_d(MODIS_FILE,, 1, "coremetadata.0", "GRingPointLatitude.1", dvals)
	print *, dvals(1), dvals(2), dvals(3), dvals(4), dvals(5), dvals(6)

C	user is required to assign space for the strings as well 

	svals(1) = ""
	svals(2) = ""
	svals(3) = ""
	ret = pgs_met_getpcattr_s(MODIS_FILE,, 1, "coremetadata.0", "LocalityValue", svals)
	print *, svals(1), svals(2), svals(3)
	do 20 i = 1,6
                ivals(i) = 0
 20	continue
	ret = pgs_met_getpcattr_i(MODIS_FILE, 1, "coremetadata.0", "ZoneIdentifier", ivals)
	print *, ivals(1), ivals(2), ivals(3), ivals(4), ivals(5), ivals(6)
	if(ret.NE.PGS_S_SUCCESS) then
                print *, "GetPCAttr failed. See Logstatus for details\n"
	endif

NOTES:
	User is responsible for the returned buffers to be large enough to 
	hold the returned values. 
	It is very important that variable string pointers are used for string manipulations.
        This is because void interface is used. For e.g. the following piece of code would give
        an error or unexpected results:

        .
        .
        char a[100];
        .
        .
        retVal = PGS_MET_GetPCAttr(MODIS_FILE, version, hdfAttrName, "SATELLITE_NAME", a);
        retVal = PGS_MET_GetPCAttr(MODIS_FILE, version, hdfAttrName, "SATELLITE_NAME", &a);

        The first call is wrong because the routine expects char** but cannot force it
        because of void interface. The second call is wrong too because of the declaration
        of 'a' which is a constant pointer, i.e. it would always point to the same
        location in memory of 100 bytes. Only the following construct will work with
        the routine in which the string pointer is declared as a variable

        char *a;
        .
        .
        a = (char *) malloc(100) / remember the user is responsible for the memory space /
        retVal = PGS_MET_GetPCAttr(MODIS_FILE, version, hdfAttrName, "SATELLITE_NAME", &a);

        The above discussion is also true for arrays of strings. For e.g. the following
        is not allowed for the same reasons as above

        .
        .
        char a[10][100];
        .
        .
	retVal = PGS_MET_GetPCAttr(MODIS_FILE, version, hdfAttrName, "SATELLITE_NAME", &a[0]);

	while the following is acceptable

        .
        .
        char *a[10];
        .
        .
        a[0] = (char *) malloc(100) / remember the user is responsible for the memory space /
        retVal = PGS_MET_GetPCAttr(MODIS_FILE, version, hdfAttrName, "SATELLITE_NAME", &a[0]);

        Another important point is that there may be cases where metadata name is shared.
        For e.g. there could be a metadata attribute called LATITUDE defining sub-satellite point
        and there could be another giving grid reference. In such cases the tool distinguishes
        between the two using the CLASS of the metadata which is part of the input name string.
        For eg. The above mentioned latitudes can be represented as follows:

        attrNameStr = "LATITUDE.GRID"
	attrNameStr = "LATITUDE.SATELLITE"

        where GRID and SATELLITE are the two classes respectively.

        The CLASS field is optional and is needed only under the aforementioned circumstances.

	ASCII file should be in a simple Parameter = Value format i.e
		satellite name = "MODIS"
		satellite_sensor = "INFRARED"
		.
		.
		.
			
	Addendum for tk5+
 
	In Tk5, the number of values for a particular metadata parameter was fixed in the datadictionary.
	This has now changed and the user has the freedom to set 1 to n values for a particlar parameter
	where n is defined in the NUM_VAL field in the MCF. In this case where the values are being
	retrieved, the end of array is marked by:

		INT_MAX			for integers
		UINT_MAX			for unsigned integers
		DBL_MAX			for doubles
		NULL			char * (strings)
	FORTRAN USERS:

		Use PGSd_MET_INT_MAX and PGSd_MET_DBL_MAX and PGSd_MET_STR_END.

	The user can check for these values to determine the actual number of values retrieved.
	In case where the number of values retieved is equal to n, there is no end of array marker
	since user is expected to know n for setting the return buffer.

        The return types supported for the void interface are PGSt_integer, PGSt_double and char * and
        their array counterparts. PGSt_real has been omitted because of the changes in tk5+. This routine
        
        user is still required to assign enough space for the returned values.

	The use of name.class stated above still holds true but now class is used to define matadata
        with multiple instances. See PGS_MET_SetAttr for more details on multiplicity.

	***IMPORTANT***

	The void buffer should always be large enough for the returned values otherwise routine behavior
	is uncertain. 

	Addendum for Release A

	The separate ascii file can now be in the same format as the output from the PGS_MET_Write().

        ****IMPORTANT***
        
        When the user wants to retrieve attribute value by calling this function, the second input 
        parameter hdfAttrName, name of hdf attribute to be searched, should be defined as follows:
       
        hdfAttrName for the  Core metadata is defined to contain in the "coremetadata.X" (X=0,...,9) 
        family of global attributes within an  HDF file.

        hdfAttrName for the  Archive metadata is defined to contain in the "archivemetadata.X" 
        (X=0,...,9) family of global attributes within an  HDF file. 
 
        hdfAttrName for the  Archive metadata is defined to contain in the "ProductMetadata.X" 
        (X=0,...,9) family of global attributes within an  HDF file.(This is a special case for
        MODIS Instrument Team) 
 

REQUIREMENTS:
        PGSTK-0290 PGSTK-0235

DETAILS:
	See MET userguide
	
GLOBALS:
	PGSg_MET_MasterNode
FILES:
	PCF.v5, generic product file, separate ascii file

FUNCTIONS_CALLED:
	PGS_PC_GetPCSData
	PGS_PC_GetFileAttr
	PGS_MET_HDFToODL
	PGS_MET_GetSetAttr
	PGS_MET_ErrorMsg
	PGS_MET_NameAndClass
	NewAggregate
	FindParameter
	FindObject
	FirstValue
	NewValue
	PasteAggregate
	RemoveAggregate
	ReadLabel

END_PROLOG:
***************************************************************************/


AGGREGATE        PGSg_MET_AggList[PGSd_MET_NUM_OF_SIG] = {NULL};
char             PGSg_MET_AttrHandle[PGSd_MET_NUM_OF_SIG][PGSd_MET_SIGNATURE_L] = {""};

PGSt_SMF_status
PGS_MET_GetPCAttr(
       PGSt_PC_Logical 	fileId,                /* file id for the file containing
                                               * parameter data
                                               */
       PGSt_integer   	version,               /* product version number */
       char *	      	hdfAttrName,	       /* name of hdf attribute to be searched */
       char *         	parmName,              /* Parameter name to be retrieved
                                                */
       void *       	parmValue)             /* Parameter value buffer to hold
                                                * the retrieved value
                                                */
{
        struct ODLDate
        {
          short             year;                 /* Year number                    */
          short             doy;                  /* Day of year (0-366)            */
          char              month;                /* Month of year (1-12)           */
          char              day;                  /* Day of month (1-31)            */
          short             zone_hours;           /* Zone hours from GMT (-12 - +12)*/
          char              zone_minutes;         /* Zone minutes from GMT (0-59)   */
          char              hours;                /* Hours of day (0-23)            */
          char              minutes;              /* Minutes of hour (0-59)         */
          char              seconds;              /* Seconds of minute (0-59)       */
          long              nanoseconds;          /* Nanoseconds (0-999999999)      */
        };
 

        long                    iyear;         
        long                    imonth;         
        long                    iday;         
        long                    nday;         
        long                    izonehours;       
        long                    izoneminutes;       
        long                    ihours;       
        long                    iminutes;    
        long                    iseconds;  
        double                  inanoseconds;         

        struct ODLDate *        date_time_Ptr;
	extern AGGREGATE	PGSg_MET_MasterNode[];
	FILE *			attrFile = NULL;
	AGGREGATE		aggNode = NULL;
        AGGREGATE               landsatNode = NULL;
	AGGREGATE               objectNode = NULL;
	PARAMETER               parmNode = NULL;
        PARAMETER               classParmNode = NULL;
        VALUE                   classValueNode = NULL;
        VALUE                   valueNode = NULL;
	PGSt_SMF_status 	retVal = PGS_S_SUCCESS;	/* SDPS toolkit ret value */
	PGSt_integer		odlRetVal = 0;  /* ODl function return value */
	char *			errInserts[PGSd_MET_MAX_ERR_INSERTS] = {NULL}; 
							/* Dynamic strings inserted in 
							 * error messages
							 */
	char *			funcName = "PGS_MET_GetPCAttr";
	char * 			HDFfilenameafterDot;
        char *                  hdfattrn;
        char                    hdfattrname[PGSd_PC_FILE_PATH_MAX] = "";
	char  			Fileattr[PGSd_PC_FILE_PATH_MAX] = "";
	char  			fileattr[PGSd_PC_FILE_PATH_MAX] = "";
	char  			fileAttr[PGSd_PC_FILE_PATH_MAX] = "";
	char                    fileName[PGSd_PC_FILE_PATH_MAX] = "";
	char * 			DotcheckPtr = NULL;
	char * 			strPtr = NULL;
	char * 			strPtrFile = NULL;
	PGSt_integer		i;
	PGSt_integer		mdFlag = PGS_FALSE;
        char **                 datetimePtr = NULL;
        char **                 strPtr1 = NULL;
	PGSt_integer*            intPtr = NULL;
        PGSt_double*             dblPtr = NULL;
	char                    metClass[PGSd_MET_CLASS_L] = "";
	char 			cmonth[PGSd_MET_NAME_L] = "";
	char 			cday[PGSd_MET_NAME_L] = "";
        char                    chours[PGSd_MET_NAME_L] = "";
        char                    czonehours[PGSd_MET_NAME_L] = "";
        char                    czoneminutes[PGSd_MET_NAME_L] = "";
        char                    cminutes[PGSd_MET_NAME_L] = "";
        char                    cseconds[PGSd_MET_NAME_L] = "";
        char                    date_time_name[PGSd_MET_NAME_L] = "";
        char *                  ccinanoseconds;
        char                    cinanoseconds[PGSd_MET_NAME_L] = "";
	char 			name[PGSd_MET_NAME_L] = "";
	PGSt_integer		locVersion;
	char                   signature[PGSd_MET_SIGNATURE_L];
	PGSt_integer		fileInBuffer = 1;
	PGSt_integer            bufferIndex = 0;
	PGSt_integer            st_time = 0;
	static PGSt_integer	month1[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	static PGSt_integer	month2[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
	static PGSt_integer	newFilePosition = 0;
	char			locAggrName[100];
	char *                  charPtr = NULL;
        PGSt_boolean            leapyear = PGS_FALSE;
        PGSt_boolean            landsatFlag = PGS_FALSE;
        PGSt_boolean            yearday = PGS_FALSE;
        PGSt_boolean            secondiszero = PGS_FALSE;
        PGSt_boolean            zonehoursiszero = PGS_FALSE;
        PGSt_boolean            Zchar = PGS_FALSE;
        PGSt_boolean            HDFflag = PGS_FALSE;
        PGSt_boolean            hdfattrnameflag = PGS_FALSE;
        int                     iattr;
	
        FILE                    *fp;
        PGSt_boolean            metflag = PGS_FALSE;


	struct stat buf;

        /* clear the errno for the ODL routines */
 
        if (errno == ERANGE)
        {
                errno = 0;
        }

        strcpy(hdfattrname,hdfAttrName);

        for (i=0; hdfattrname[i]; i++)
        {
            hdfattrname[i] = tolower(hdfattrname[i]);
        }


        /* set hdfattrnameflag to be PGS_TRUE if the HDF attribuet name is equal to
         * coremetadata.X where .x is a squeence number beginning at 0 and
         * running as high as 9
         */

        for (iattr=0; iattr < 10; iattr++){
        switch(iattr){
          case  0 : hdfattrn = "coremetadata.0"; break;
          case  1 : hdfattrn = "coremetadata.1"; break;
          case  2 : hdfattrn = "coremetadata.2"; break;
          case  3 : hdfattrn = "coremetadata.3"; break;
          case  4 : hdfattrn = "coremetadata.4"; break;
          case  5 : hdfattrn = "coremetadata.5"; break;
          case  6 : hdfattrn = "coremetadata.6"; break;
          case  7 : hdfattrn = "coremetadata.7"; break;
          case  8 : hdfattrn = "coremetadata.8"; break;
          case  9 : hdfattrn = "coremetadata.9"; break;
          }

          if (strcmp(hdfattrname, hdfattrn) ==0)
          {
              hdfattrnameflag = PGS_TRUE;
          }
        }
         
	/* set metflag to PGS_TRUE if attribute to be retrieved from an ASCII 
	   file from INVENTORYMETADATA section */ 
	if(hdfAttrName != NULL && *hdfAttrName != '\0')
	{
	    if(strlen(hdfAttrName) > (strlen(PGSd_MET_GROUP_STR) + 1))
	    {
		if(strncmp(hdfAttrName, PGSd_MET_GROUP_STR, strlen(PGSd_MET_GROUP_STR)) == 0)
		{
		    metflag = PGS_TRUE;
		}
	    }
	/* set metflag to PGS_TRUE if attribute to be retrieved from an ASCII 
	   metadata file of landsat7 */ 
	    else if(strlen(hdfAttrName) > (strlen(PGSd_MET_LSAT_GRP_STR) + 1))
	    {
		if(strncmp(hdfAttrName, PGSd_MET_LSAT_GRP_STR, strlen(PGSd_MET_LSAT_GRP_STR)) == 0)
		{
		    metflag = PGS_TRUE;
		}
	    }
	}
	
	/* get product input filename and the name of the file containing the attributes */

	locVersion = version; 

	retVal = PGS_PC_GetReference(fileId, &version, fileName);
	errInserts[0] = "input filename";
	if(retVal == PGS_S_SUCCESS)
	{
	   errInserts[0] = "attribute filename";
	   retVal = PGS_PC_GetFileAttr(fileId, locVersion, PGSd_PC_ATTRIBUTE_LOCATION,
				       PGSd_PC_FILE_PATH_MAX, fileAttr);

          /* Set HDFflag to be PGS_TRUE if the attribute of the file associated with the 
           * particular ID and version contains ".met" and the filename associated with the
           * logical identifier and version number is a HDF file existing in the same 
           * directory as the ASCII metadata file .met is.
           */
 
          DotcheckPtr = strrchr(fileAttr,'.');
          if(DotcheckPtr != NULL)
          {
             strcpy(Fileattr,fileAttr);
             strcpy(fileattr,fileAttr);

             HDFfilenameafterDot = strrchr(fileattr, '.');
             if(strcmp(HDFfilenameafterDot,".met") == 0)
             {
                if ((fp = fopen(fileName, "r")) != NULL) 
                {
                    HDFflag = PGS_TRUE; 
                    strcpy(fileAttr,fileattr);
                    fclose(fp);
                }
                else HDFflag = PGS_FALSE;
             }
             else HDFflag = PGS_FALSE;
          }
        }

	if(retVal != PGS_S_SUCCESS)
	{
	   /* error message is 
		"Unable to obtain <filename or attribute filename> from the PC table */
		
	   (void) PGS_MET_ErrorMsg(PGSMET_E_PCREAD_ERR,
                                     funcName, 1, errInserts);
           return(PGSMET_E_PCREAD_ERR);
	}

	/* if the two filenames are same then attributes are in HDF attribute */

#ifdef VISUAL_CPLUSPLUS
    strPtr = strrchr(fileAttr, (int)'\\') + 1;
    strPtrFile = strrchr(fileName, (int)'\\') + 1;
#else
	strPtr = strrchr(fileAttr, (int)'/') + 1;
	strPtrFile = strrchr(fileName, (int)'/') + 1;
#endif

	/* prepare a unique signature */

	if(strcmp(strPtr, strPtrFile) == 0 && HDFflag == PGS_FALSE)
	{
		/* find modification time for the file and put it in the signature */
        	sprintf(signature,"%s/%s", fileName, hdfAttrName);
	}

        /* set signature specially for retrieving the archive metadata from the HDF file when
         * the user sets up the first parameter "fileId", file id for the file containing
         * parameter data is the ASCII metadata file .met file
         */

	else if(HDFflag == PGS_TRUE && hdfattrnameflag == PGS_FALSE && metflag
		== PGS_FALSE)
	{
                /* find modification time for the file and put it in the signature */
                sprintf(signature,"%s/%s", Fileattr, hdfAttrName);
	}
	else
	{
		/* find modification time for the file and put it in the signature */
		stat(fileAttr, &buf);
                st_time = buf.st_mtime;
		sprintf(signature,"%s%d", fileAttr, st_time);
	}

        /* find out if the signature already exists */

	fileInBuffer = 1;
	bufferIndex = 0;
	while(PGSg_MET_AttrHandle[bufferIndex][0] != '\0' && bufferIndex < PGSd_MET_NUM_OF_GROUPS)
	{
                	fileInBuffer = strcmp(signature, PGSg_MET_AttrHandle[bufferIndex]);

			if(fileInBuffer == 0)
			{
				break;
			}
			bufferIndex++;
        }
	
	if(strcmp(strPtr, strPtrFile) == 0 && HDFflag == PGS_FALSE)
	{
	   if(fileInBuffer != 0)
	   {
	   	retVal = PGS_MET_HDFToODL(fileAttr, "locAggr", hdfAttrName, &aggNode);

	   	if(retVal != PGS_S_SUCCESS)
	   	{
	      		/* error message is
                	"Unable to convert <filename> into an ODL format */
	      		errInserts[0] = "HDF attribute";

              		(void) PGS_MET_ErrorMsg(PGSMET_E_FILETOODL_ERR,
                                      funcName, 1, errInserts);
              		return(PGSMET_E_FILETOODL_ERR);
	   	}
	   }
	   else
	   {
		aggNode = PGSg_MET_AggList[bufferIndex];
	   }
        }

        /* set &aggNode specially for retrieving the archive metadata from the HDF file when
         * the user sets up the first parameter "fileId", file id for the file containing
         * parameter data is the ASCII metadata file .met file
         */

	else if(HDFflag == PGS_TRUE && hdfattrnameflag == PGS_FALSE && metflag
		== PGS_FALSE)
	{
       	   if(fileInBuffer != 0)
	   {
	   	retVal = PGS_MET_HDFToODL(fileName, "locAggr", hdfAttrName, &aggNode);

	   	if(retVal != PGS_S_SUCCESS)
	   	{
	      		/* error message is
                	"Unable to convert <filename> into an ODL format */
	      		errInserts[0] = "HDF attribute";

              		(void) PGS_MET_ErrorMsg(PGSMET_E_FILETOODL_ERR,
                                      funcName, 1, errInserts);
              		return(PGSMET_E_FILETOODL_ERR);
	   	}
	   }
	   else
	   {
		aggNode = PGSg_MET_AggList[bufferIndex];
	   }
        }
	else /* attributes are contained in a separate file */
	{
	   (void) PGS_MET_NameAndClass(parmName, name, metClass);
	   if(fileInBuffer != 0)
	   {
	   	aggNode = NewAggregate(aggNode, KA_GROUP, "locAggr", "");
           	if (aggNode == NULL)
           	{
              		errInserts[0] = "";
              		/* error message is:
              		"Unable to create odl aggregate <aggregate name>" */
 
              		(void) PGS_MET_ErrorMsg(PGSMET_E_AGGREGATE_ERR, funcName,
                                     1, errInserts);
              		return(PGSMET_E_AGGREGATE_ERR);
           	}
	   	attrFile = fopen(fileAttr, "r");
	   	if(attrFile == NULL)
	   	{
              		/* error message is:
              		"Unable to open pc attribute file" */

              		(void) PGS_MET_ErrorMsg(PGSMET_E_SYS_OPEN_ERR, funcName,
                                   0, errInserts);
              		return(PGSMET_E_SYS_OPEN_ERR);
		}
	   	odlRetVal = ReadLabel(attrFile, aggNode);
	   	if(odlRetVal == 0)
           	{
              		/* error message is:
              		"Unable to convert <filename> into an odl structure" */
	      		errInserts[0] = strPtr;

              		(void) PGS_MET_ErrorMsg(PGSMET_E_FILETOODL_ERR, funcName,
                                   1, errInserts);
	      		fclose(attrFile);
              		return(PGSMET_E_FILETOODL_ERR);
		}
                /* need to set the class attribute */
 
                objectNode = aggNode;
                do
                {
                   objectNode = NextObject(objectNode);
                   if(objectNode != NULL)
                   {
                        classParmNode = FindParameter(objectNode, PGSd_MET_CLASS_STR);
                        if(classParmNode != NULL) /* object is a multiiple */
                                {
                                        classValueNode = FirstValue(classParmNode);
                                        if(classValueNode->item.type == TV_STRING ||
                                        classValueNode->item.type == TV_SYMBOL)
                                        {
                                                if(objectNode->objClass != NULL)
                                                {
                                                        free(objectNode->objClass);
                                                        objectNode->objClass = NULL;
                                                objectNode->objClass = (char *) malloc(strlen(classValueNode->item.value.string)+ 1);
                                                }
                                                strcpy(objectNode->objClass, classValueNode->item.value.string);
                                        }
                                }
                   }
                }
                while(objectNode != NULL);
           }     
	   else 
           {
                aggNode = PGSg_MET_AggList[bufferIndex];
           }

	   /* This section is included for the landsat 7 file to locate the group
            * name name in the LANDSAT7 metadata
            */

	   if(hdfAttrName != NULL && *hdfAttrName != '\0')
	   {
		if(strlen(hdfAttrName) > (strlen(PGSd_MET_LSAT_GRP_STR) + 1))
		{
			if(strncmp(hdfAttrName, PGSd_MET_LSAT_GRP_STR, strlen(PGSd_MET_LSAT_GRP_STR)) == 0)
			{
                                charPtr = strchr(hdfAttrName, (int)'=');
                                charPtr++;
                                landsatFlag = PGS_TRUE;
                                landsatNode = CopyAggregate(aggNode);

				aggNode = FindGroup(aggNode, charPtr);
				if(aggNode == NULL)
				{
                                         /* error message is:
                                            "No group called <name> found in the MCF" */
   
                                         (void) PGS_MET_ErrorMsg(PGSMET_E_GROUP_NOT_FOUND,
                                                                 funcName, 1, errInserts);
                                         landsatNode = RemoveAggregate(landsatNode);
                                         fclose(attrFile);
                                         return(PGSMET_E_GROUP_NOT_FOUND);
				}
			}
		}
	   }

	   /* extract the values and dump in the buffer provided */
	   parmNode = FindParameter(aggNode, name); 
           if(parmNode == NULL)
           {
			if(attrFile != NULL)
			{
				fclose(attrFile);
			}
           }
	   else
	   {
	   	valueNode = FirstValue(parmNode);
 
           	/* copy the value string(s) into user provided string */
           	if(valueNode->item.type == TV_STRING  || valueNode->item.type == TV_SYMBOL)
           	{
                	strPtr1 = (char **) parmValue;
                	while(valueNode != NULL)
                	{
                        	strcpy(*strPtr1, valueNode->item.value.string);
                        	strPtr1++;
                        	valueNode = NextValue(valueNode);
                	}
           	}   

                /* This section is included for retrieving the LANDSAT7 data value that
                 *  that is belong to the type of datetime
                 */

                else if(valueNode->item.type == TV_DATE || valueNode->
item.type == TV_TIME || valueNode->item.type == TV_DATE_TIME || valueNode->item.type == TV_SYMBOL)
                {
                        datetimePtr = (char **) parmValue; 

                        date_time_Ptr = (struct ODLDate *) malloc ( sizeof(short) +
                                                 sizeof(short) +
                                                 sizeof(char) +
                                                 sizeof(char) +
                                                 sizeof(short) +
                                                 sizeof(char) +
                                                 sizeof(char) +
                                                 sizeof(char) +
                                                 sizeof(char) +
                                                 sizeof(long));

                        while(valueNode != NULL)
                        {
                                date_time_Ptr->year = valueNode->item.value.date_time.year; 
                                iyear = (long) (date_time_Ptr->year);

                                date_time_Ptr->month = valueNode->item.value.date_time.month; 
                                imonth = (long) (date_time_Ptr->month);

                                if ((imonth / 10) < 1) sprintf(cmonth,"0%ld",imonth);
                                else sprintf(cmonth,"%ld",imonth);

                                date_time_Ptr->doy = valueNode->item.value.date_time.doy;
                                iday = (long) (date_time_Ptr->doy);

                                date_time_Ptr->day = valueNode->item.value.date_time.day;
                                nday = (long) (date_time_Ptr->day);

                                if(nday == 0 || imonth == 0) yearday = PGS_TRUE;

                                if (yearday == PGS_TRUE) 
                                {
                                    if ((iday / 100) >= 1) sprintf(cday,"%ld",iday);
                                    else
                                    {
                                       if ((iday / 10) >= 1 && (iday / 100) < 1) sprintf(cday,"0%ld",iday);
                                       else sprintf(cday,"00%ld",iday);
                                    }
                                }
                                else 
                                {
                                    if ((nday / 10) < 1) sprintf(cday,"0%ld",nday);
                                    else sprintf(cday,"%ld",nday);
                                }
 
                                /* check if year is a leap year or not */
                                if ((iyear%4 == 0 && iyear%100 != 0) 
                                   || iyear%400 == 0)
                                {
                                    leapyear = PGS_TRUE;
                                }

                                for (i=0; i<12; i++)
                                {
                                     if(leapyear == PGS_TRUE)
                                     {
                                        if(iday > month2[i]) iday -= month2[i];
                                        else break;
                                     }
                                     else
                                     {
                                         if(iday > month1[i]) iday -= month1[i];
                                         else break; 
                                     }
                                }
          
                                date_time_Ptr->zone_hours = valueNode->item.value.date_time.zone_hours; 
                                izonehours = (long) (date_time_Ptr->zone_hours);

                                date_time_Ptr->zone_minutes = valueNode->item.value.date_time.zone_minutes;
                                izoneminutes = (long) (date_time_Ptr->zone_minutes);

                                if(valueNode->item.precision == -99) Zchar = PGS_TRUE;
                                if(izonehours == 0) zonehoursiszero = PGS_TRUE;
                                if(izonehours > 0) sprintf(czonehours, "+%ld",izonehours);
 
                                if(izonehours < 0) sprintf(czonehours, "%ld",izonehours);
                                if((izoneminutes / 10) < 1) sprintf(czoneminutes, ":0%ld",izoneminutes);
                                else sprintf(czoneminutes, ":%ld",izoneminutes);

                                date_time_Ptr->hours = valueNode->item.value.date_time.hours; 
                                ihours = (long) (date_time_Ptr->hours);
                                if ((ihours /10) < 1) sprintf(chours,"%0ld",ihours);
                                else sprintf(chours,"%ld",ihours);

                                date_time_Ptr->minutes = valueNode->item.value.date_time.minutes; 
                                iminutes = (long) (date_time_Ptr->minutes);
                                if((iminutes / 10) < 1) sprintf(cminutes,"0%ld",iminutes);
                                else sprintf(cminutes,"%ld",iminutes);

                                date_time_Ptr->seconds = valueNode->item.value.date_time.seconds; 
                                iseconds = (long) (date_time_Ptr->seconds);

                                date_time_Ptr->nanoseconds = valueNode->item.value.date_time.nanoseconds; 
                                inanoseconds = (double) (date_time_Ptr->nanoseconds) / 1.0E9;
                                if(iseconds == 0.0 && inanoseconds == 0.0) secondiszero = PGS_TRUE;
                                if(secondiszero == PGS_FALSE) 
                                {
                                   if((iseconds / 10) < 1) sprintf(cseconds,"0%ld",iseconds);
                                   else sprintf(cseconds,"%ld",iseconds);
                                   sprintf(cinanoseconds,"%f",inanoseconds);
                                   ccinanoseconds = strtok(cinanoseconds,".");
                                   ccinanoseconds = strtok(NULL,".");
                                }
                                else 
                                {
                                   sprintf(cseconds,"0%ld",iseconds);
                                   sprintf(cinanoseconds,"%f",inanoseconds);
                                   ccinanoseconds = strtok(cinanoseconds,".");
                                   ccinanoseconds = strtok(NULL,".");
                                }

                                if((yearday == PGS_TRUE && secondiszero == PGS_TRUE) && zonehoursiszero == PGS_TRUE )
                                {
                                   if(Zchar == PGS_TRUE) sprintf(date_time_name, "%d-%sT%s:%s:%s.%s%s%sZ",date_time_Ptr->year,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                   else sprintf(date_time_name, "%d-%sT%s:%s:%s.%s%s%s",date_time_Ptr->year,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                }
                                else if(yearday == PGS_TRUE && zonehoursiszero == PGS_FALSE)
                                {
                                   if(Zchar == PGS_TRUE) sprintf(date_time_name, "%d-%sT%s:%s:%s.%s%s%sZ",date_time_Ptr->year,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                   else sprintf(date_time_name, "%d-%sT%s:%s:%s.%s%s%s",date_time_Ptr->year,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                }
                                else if(yearday == PGS_TRUE)
                                {
                                   if(Zchar == PGS_TRUE) sprintf(date_time_name, "%d-%sT%s:%s:%s.%s%s%sZ",date_time_Ptr->year,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                   else sprintf(date_time_name, "%d-%sT%s:%s:%s.%s%s%s",date_time_Ptr->year,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                }
                                else
                                {
                                   if(Zchar == PGS_TRUE) sprintf(date_time_name, "%d-%s-%sT%s:%s:%s.%s%s%sZ",date_time_Ptr->year,cmonth,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                   else sprintf(date_time_name, "%d-%s-%sT%s:%s:%s.%s%s%s",date_time_Ptr->year,cmonth,cday,chours,cminutes,cseconds,ccinanoseconds,czonehours,czoneminutes);
                                }
                                /* now fill with the value string untill end of string character
                                or the input str length is exhausted */
                                strcpy(*datetimePtr, date_time_name);

                                free(date_time_Ptr);
                                valueNode = NextValue(valueNode);
                        }

                }

	   	else if(valueNode->item.type == TV_INTEGER)
	   	{
                	intPtr = (PGSt_integer*) parmValue;
                	while(valueNode != NULL)
                	{
                        	*intPtr = (PGSt_integer)valueNode->item.value.integer.number; 
                        	intPtr++;
                        	valueNode = NextValue(valueNode);
                	}
           	}
	   	else 
	   	{    
                	dblPtr = (PGSt_double*) parmValue;
                	while(valueNode != NULL)
                	{
                        	*dblPtr = (PGSt_double)valueNode->item.value.real.number; 
                        	dblPtr++;
                        	valueNode = NextValue(valueNode);
                	}
           	}

	   	if(attrFile != NULL)
           	{
           		fclose(attrFile);
           	}
	   	if(fileInBuffer != 0) /* its a new file or attribute */
           	{
                	strcpy(PGSg_MET_AttrHandle[newFilePosition], signature);
			PGSg_MET_AggList[newFilePosition] = RemoveAggregate(PGSg_MET_AggList[newFilePosition]);
                        if(landsatFlag == PGS_TRUE)
                        {
			        PGSg_MET_AggList[newFilePosition] = landsatNode;
                        }
                        else
                        {
                                PGSg_MET_AggList[newFilePosition] = aggNode;
                        }

                	newFilePosition++;
			if(newFilePosition == PGSd_MET_NUM_OF_SIG)
             		{  
                		newFilePosition = 0;
             		}
           	}
		else
        	{
                        if(landsatFlag == PGS_TRUE)
                        {
                                landsatNode = RemoveAggregate(landsatNode);
                        }
                        else
                        {
                	       ; 
                        }
        	}	
	   	return(PGS_S_SUCCESS);
	    }
	} /* end else */
	
		/* MasterNode could be null, therfore just create a dummy one .
	 	* Its important to initialize masternode because GetSetAttr() 
	 	* only recognizes the master node and is used here to 
	 	* actually read the values in.
	 	*/
		mdFlag = PGS_FALSE;
		if(PGSg_MET_MasterNode[0] == NULL)
		{
	   		PGSg_MET_MasterNode[0] = NewAggregate(PGSg_MET_MasterNode[0], KA_GROUP, "MCF", "");	
	   		mdFlag = PGS_TRUE;
		}
		/* attach the new node to the master node and the value of the parameter */

		aggNode = PasteAggregate(PGSg_MET_MasterNode[0], aggNode);

		/* This section of code is to resolve the the Aster problem 
		   so that different groups in an ascii file can be read */

		strcpy(locAggrName, "locAggr#0");
		if(hdfAttrName != NULL && *hdfAttrName !='\0')
		{
		  if(strlen(hdfAttrName) > (strlen(PGSd_MET_GROUP_STR) + 1))
                  {
                        if(strncmp(hdfAttrName, PGSd_MET_GROUP_STR, strlen(PGSd_MET_GROUP_STR)) == 0)
			/* hdf attr name contains the name of the master group in the file */
			{
				charPtr = strchr(hdfAttrName, (int)'=');
				charPtr++;
				sprintf(locAggrName, "%s#0", charPtr);
			}
           	  }
		}
		
		retVal = PGS_MET_GetSetAttr(locAggrName, parmName, parmValue);

                /* a return status of PGSMET_E_NULL_PARAMETER will be set up if the requested
                 * parameter is a NULL value, and a return status of PGSMET_W_METADATA_NOT_SET
                 * will be set up if the requested parameter is not set yet
                 */
 
                /* error message is:
                   "the requested parameter <parameter name> could not be found in <agg node>" */

                if(retVal == PGSMET_E_DD_UNKNOWN_PARM)
                {
                   errInserts[0] = parmName;
                   /* error message is :
                      "The requested Parameter is a NULL value" */
                   (void) PGS_MET_ErrorMsg(PGSMET_E_NULL_PARAMETER,
                                           funcName, 1, errInserts);
                   retVal = PGSMET_E_NULL_PARAMETER;
                 }
                 else
                 {
                      if(retVal == PGSMET_W_METADATA_NOT_SET)
                      {
                         errInserts[0] = parmName;
                         /* error message is :
                            "The requested Parameter is not set yet" */
                         (void) PGS_MET_ErrorMsg(PGSMET_E_PARAMETER_NOT_SET,
                                                 funcName, 1, errInserts);
                          retVal = PGSMET_E_PARAMETER_NOT_SET;
                      }
                 }
 
	/* clean up */

	aggNode = CutAggregate(aggNode);
	if(fileInBuffer != 0) /* its a new file or attribute */
        {
             strcpy(PGSg_MET_AttrHandle[newFilePosition], signature);
             PGSg_MET_AggList[newFilePosition] = RemoveAggregate(PGSg_MET_AggList[newFilePosition]);
             PGSg_MET_AggList[newFilePosition] = aggNode;
             newFilePosition++;
	     if(newFilePosition == PGSd_MET_NUM_OF_SIG)
	     {
		newFilePosition = 0;
	     }
        }
	else
	{
		;
	}
	if(mdFlag == PGS_TRUE)
	{
	   PGSg_MET_MasterNode[0] = RemoveAggregate(PGSg_MET_MasterNode[0]);
	   PGSg_MET_MasterNode[0] = NULL;
	}
	return(retVal);
}
