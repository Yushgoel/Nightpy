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
        PGS_MET_GetSetFileId_Name
 
DESCRIPTION:
             This function sets file IDs for given file names and their
	     attribute file names. The Ids later
	     are recovered for a given file name using PGS_MET_GetFileId that
	     are required for Metadata tools.


	     Since this is the first function to be called for the stand-alone 
	     metadata tools, we redirect stderr to Logstatus file as for the
	     SDP toolkit. The file Logstatus will be opened in the current
	     working directory.



AUTHOR: 
        Abe Taaheri / Space Applications Corporation

HISTORY:
        24-Feb-1998      AT     Initial version
        18-Aug-1998    RSTX S.Zeng  modified for win95 

END_FILE_PROLOG:
******************************************************************************/

/* include files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <PGS_SMF.h>
#include <PGS_tk.h>
#include <time.h>
#include <PGS_MET.h>
#include <PGS_PC_Prototypes.h>

#ifdef VISUAL_CPLUSPLUS
#define  MAXPATHLEN   1024    /* maximum length for the full path of working directory */
#define  getcwd  _getcwd
/*#include <direct.h>*/
#endif

/* for HP version */
#ifdef __hpux
#include <sys/param.h>
#include <sys/unistd.h>
#endif    

/* for DEC ALPHA version */
#ifdef __alpha
#include <sys/param.h>
#include <unistd.h>
#endif    

extern struct config_file 
{
  char *file_name;                     /* config file name */
  PGSt_PC_Logical file_id;             /* config file ID */
} config_file;

extern PGSt_integer num_of_user_files; /* Total number of files that a 
					  logical ID is
					  assigned for them */


extern struct files                    /* structure to hold filenames 
					  and their corresponding ID */
{
  char *file_name;                     /* file name */
  PGSt_PC_Logical file_id;             /* file ID */
} cat[MAX_NUM_FILES];

extern struct attr_files               /* structure to hold filenames 
					  and their corresponding ID */
{
  char *file_name;                     /* file name */
  PGSt_PC_Logical file_id;             /* file ID */
} cat_attr[MAX_NUM_FILES];

PGSt_SMF_status
PGS_MET_SetFileId()                                      /* set file IDs */
{
    PGSt_integer j;
    PGSt_integer count = 0;
    PGSt_SMF_status toolID = PGSd_TOOLID_MET;
    char       File_Table[PGSd_PC_PATH_LENGTH_MAX]; /* File that holds the ID,
						       filename, and attribute 
						       file filename for input 
						       and output files */
    char              buf[PGS_SMF_MAX_MSG_SIZE];     /* message buffer */
    char              msg[PGS_SMF_MAX_MSGBUF_SIZE];  /* message buffer */
    char       data[PGSd_PC_LINE_LENGTH_MAX];
    char       data1[PGSd_PC_LINE_LENGTH_MAX];
    char       tempPath[PGSd_PC_PATH_LENGTH_MAX];   /* temporary path
						       variable */
    char       TempFilePath[PGSd_PC_PATH_LENGTH_MAX];   /* temporary path
						       variable */
    char       *resEnv;                             /* resolved environment 
						       from getenv() */

    char       *tempfile[MAX_NUM_FILES];            /* file names for data 
						       and config files */
    char       *tempattrfile[MAX_NUM_FILES];        /* attribute file names */


    char       Msg[PGS_SMF_MAX_MSG_SIZE];
    char       codeMsg[PGS_SMF_MAX_MSG_SIZE];
    FILE       *filetable = NULL;
    FILE       *logstatus = NULL;
    

    char       attrStr[PGSd_PC_LINE_LENGTH_MAX]=""; /* file id value as string
						     */
    PGSt_integer            delimiterNum = 0;
    PGSt_integer File_Id;
    PGSt_SMF_status  returnStatus = PGS_S_SUCCESS;  /* SDPS toolkit
						       ret value */
    PGSt_integer      numFiles; 
    PGSt_integer      filelen;
    /*char              *pstr;*/
    char              *tmpptr;
    char         LogStatusFile[PGSd_SMF_PATH_MAX];
    PGSt_integer      slashloc;
    
    PGSt_integer      newlen;

    char             *stars= "****************************************";
    char             *bgpage= "BEGIN_PGE: ";
    char             *tkversion = "TOOLKIT_VERSION: ";
    time_t  clock;          /* system clock */
    char start_time[50];	/* start time/date(ex. Mon_Jun__6_09:11:12_1994) */
    char                    pid_string[20];  /* process ID (PID) string */

#if ( defined(VISUAL_CPLUSPLUS) || defined ( __hpux) || defined(__alpha) )
	char path_buffer[MAXPATHLEN];
   
#endif

    /* set toolID for MET tools */

    PGS_SMF_SetToolID(toolID);
    

    /* --------------------------------------------------
       the file that holds the input/output file names is 
       $(PWD)/filetable.temp 
       find the file_table name and path 
       --------------------------------------------------*/

    /* first bget environment variable for TOOLKIT where the database 
       is located */
#if ( defined(VISUAL_CPLUSPLUS) || defined ( __hpux) || defined(__alpha) )
    resEnv = getcwd( path_buffer, MAXPATHLEN) ;
#else
    resEnv = getenv("PWD");
#endif    

    if (resEnv)
    {
	strcpy(tempPath,resEnv);
    }
    else
    {
	/* error getting env variable PGSHOME, report error and exit */
	(void) PGS_SMF_GetMsgByCode(PGSPC_E_ENVIRONMENT_ERROR, codeMsg);
	sprintf(Msg, codeMsg, "PGSHOME");
	strcat(Msg,"; Required for accessing filetable.temp file.");
	PGS_SMF_SetDynamicMsg(PGSPC_E_ENVIRONMENT_ERROR,Msg,"PGS_MET_SetFileId");
	
	return(PGSPC_E_ENVIRONMENT_ERROR);
    }
    
    strcpy(File_Table,tempPath);
#ifdef CYGWIN

    resEnv = getenv("MRTDATADIR");
    if (resEnv)
    {
	strcpy(tempPath,resEnv);
    }
    else
    {
	/* error getting env variable PGSHOME, report error and exit */
	(void) PGS_SMF_GetMsgByCode(PGSPC_E_ENVIRONMENT_ERROR, codeMsg);
	sprintf(Msg, codeMsg, "MRTDATADIR");
	strcat(Msg,"; Required for accessing filetable.temp file in PGS_MET_SetFileId.");
	fprintf(stderr,"%s\n",Msg);
	
	return(PGSPC_E_ENVIRONMENT_ERROR);
    }
    strcpy(File_Table,tempPath);
#endif

#ifdef VISUAL_CPLUSPLUS
    strcat(File_Table,"\\filetable.temp");
#else
	
#ifdef CYGWIN

		strcat(File_Table,"\\filetable.temp");
#else

		strcat(File_Table,"/filetable.temp");
#endif
#endif
 /* append process ID to make unique filetable.temp for concurrency processing */
     sprintf(pid_string, "%u", getpid());
     strcat(File_Table, "_");
     strcat(File_Table, pid_string);
    /* open the File_Table to read ID, filename, attribute filename */
    
    /*--------------------------------------------------------------
      Open input file, if there is a problem then just return to the 
      calling function and tell them that they are not going to get
      what they wanted due to a file problem. 
      --------------------------------------------------------------*/

    if ((filetable = fopen(File_Table,"r")) == NULL)
    {
	/* error openning File_Table */
        returnStatus = PGSPC_E_FILE_OPEN_ERROR;
        {
            PGS_SMF_GetMsgByCode(PGSPC_E_FILE_OPEN_ERROR,msg);
            sprintf(buf,msg,File_Table);
            PGS_SMF_SetDynamicMsg(PGSPC_E_FILE_OPEN_ERROR,buf,
				  "PGS_MET_SetFileId");
        }
    }
    
    /*--------------------------------------------------------------
      Set a message in the message log and leave if error occured.
      --------------------------------------------------------------*/
    switch(PGS_SMF_TestStatusLevel(returnStatus))
    {
      case PGS_SMF_MASK_LEV_E:
	{
	    return returnStatus;
	}
      default:
	{
	    PGS_SMF_SetStaticMsg(PGS_S_SUCCESS,"PGS_MET_SetFileId");
	}
	break;
    }
    
    
    /* Now read the input/output file IDs,  names, and attribute filenames */
    
    if(returnStatus == PGS_S_SUCCESS)
    {
	do
	{
	    (void) fgets(attrStr, PGSd_PC_LINE_LENGTH_MAX, filetable);
	    if(feof(filetable) == 0) /* non zero if EOF detected */
	    {
		/* check if not another section or a comment line or empty line
		 */

		if(attrStr[0] != PGSd_PC_DIVIDER &&
		   attrStr[0] != PGSd_PC_COMMENT && attrStr[0] != ' ' ) 
		{
		    /* Its a valid line and now get the ID which is
		     * before the first delimeter, file name which is after 
		     * the first delimeter, and attribute filename which is 
		     * after the second delimeter */

		    
		    /* retrieve ID */
		    delimiterNum = 0;
		    (void) PGS_PC_GetPCSDataGetRequest(delimiterNum,
						       PGSd_PC_DELIMITER, 
						       attrStr, data);
		    File_Id =atoi(data);
		    
		    /* retrieve filename */
		    delimiterNum = 1;
		    (void) PGS_PC_GetPCSDataGetRequest(delimiterNum,
						       PGSd_PC_DELIMITER, 
						       attrStr, data1);
		    /* retrieve the attribute filename */
		    
		    delimiterNum = 2;
		    returnStatus = 
		      PGS_PC_GetPCSDataGetRequest(delimiterNum,
						  PGSd_PC_NEWLINE, 
						  attrStr, data);

		    /* ----------------------------------------------------
		       extract path from attribute file name  and attach to
		       filename 
		       ---------------------------------------------------*/


		    strcpy(TempFilePath, data);
		    filelen =strlen(TempFilePath);
		    for(j=0; j<filelen; j++)
		    {

#ifdef  VISUAL_CPLUSPLUS
           /* find last '\' before file name */
			if((*(TempFilePath +j)) == '\134') 
#else				
			/* find last '/' before file name */
			if((*(TempFilePath +j)) == '/')
#endif
			{
			    slashloc = j;
			}
		    }

		    newlen=slashloc +1 ;

		    /* tmpptr is the path */
		    tmpptr= (char *)calloc(newlen+1,sizeof(char));
		    strncpy(tmpptr,TempFilePath,newlen);
		    strcpy(TempFilePath,tmpptr);
		    free(tmpptr);

		    /* TempFilePath will be path + filename */
		    strcat(TempFilePath,data1);

		    /* Now save the ID , file name and attribute file name */

		    tempfile[count] = (char *) malloc(strlen(TempFilePath)+1);
		    tempattrfile[count] = (char *) malloc(strlen(data)+1);

		    strcpy(tempfile[count], TempFilePath);
		    strcpy(tempattrfile[count], data);

		    cat[count].file_name =tempfile[count];
		    cat_attr[count].file_name = tempattrfile[count];
		    cat[count].file_id = File_Id ;
		    cat_attr[count].file_id = File_Id ;
		    count++; /* count number of input/output files */
		    
		}
	    }
	}while(attrStr[0] != PGSd_PC_DIVIDER);
    }
   
    /*total number of files in file table */
    
    num_of_user_files = count;
    
    /* Since this is the first function to be called for stand-alone metadata
       tools, it is desirable to redirect stderr to Logstatus file as for the
       SDP toolkit */
    returnStatus = tk_GetFileName(PGSd_MET_SUPPORT_OUT_NAME, 
				  PGSd_SMF_LOGICAL_LOGSTATUS,
				  LogStatusFile, &numFiles);
    if( returnStatus == PGS_S_SUCCESS)
    {
	if((logstatus = freopen(LogStatusFile, "a", stderr)) != NULL)
	{
	    /*get date/time and write it to LogStatus file */
	    fprintf(logstatus, "%s\n",stars);
	    clock = time(&clock);
	    strcpy(start_time,ctime(&clock));
	    fprintf(logstatus, "%s %s\n",bgpage,(start_time));
	    fprintf(logstatus, "%s %s\n",tkversion,PGSd_TOOLKIT_MAJOR_VERSION);
	    fprintf(logstatus, "%s\n\n",stars);
	    returnStatus = PGS_S_SUCCESS;
	
	}
	else
	{
	    returnStatus = PGSPC_E_FILE_OPEN_ERROR;
            PGS_SMF_GetMsgByCode(PGSPC_E_FILE_OPEN_ERROR,msg);
            sprintf(buf,msg,LogStatusFile);
            PGS_SMF_SetDynamicMsg(PGSPC_E_FILE_OPEN_ERROR,buf,
				  "PGS_MET_SetFileId");
	}
    }
    
    fclose(filetable);
    return(returnStatus);
}





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
        PGS_MET_GetSetFileId_Name
 
DESCRIPTION:

             The followings are the OLD scheme to set file IDs.
             The functions set file IDs for given file names and their
	     attribute file names. User provides the file names in the driver.
             The Ids later
	     are recovered for a given file name using PGS_MET_GetFileId that
	     are required for Metadata tools.


	     Since this is the first function to be called for the stand-alone 
	     metadata tools, we redirect stderr to Logstatus file as for the
	     SDP toolkit. The file Logstatus will be opened in the current
	     working directory.



AUTHOR: 
        Abe Taaheri / Space Applications Corporation

HISTORY:
        24-Feb-1998      AT     Initial version

END_FILE_PROLOG:
******************************************************************************/

PGSt_SMF_status
PGS_MET_SetFileId_OLD(PGSt_integer n, char *file_names[]) /* set file IDs */
{
    PGSt_integer i,j;
    PGSt_SMF_status toolID = PGSd_TOOLID_MET;
    /* Since this is the first function to be called for stand-alone metadata
       tools, it is desirable to redirect stderr to Logstatus file as for the
       SDP toolkit */
    
    freopen("Logstatus", "w", stderr);

    /* set toolID for MET tools */

    PGS_SMF_SetToolID(toolID);
    

    /* for each file name given by user, another file for the attribute must be
       defined right after the file name. Therfore, the number of files is 
       even. */

    /* if number of files less than 2, or not multiples of 2, return error */
    if((n <= 1) || ((n%2) != 0))
    {
	fprintf(stderr,"%s",
		"ERROR: For each file name another file for the attribute");
	fprintf(stderr,"%s",
		"       must bedefined. Number of files should be even.");
 
	return(-1);
    }
    else
    {
	for(i=0; i<n; i++)
	{
	    /* set fileid for user defined files */
	    cat[i].file_name=file_names[i];
	    cat[i].file_id = FILE_ID_BASE + i;
	}
	/* set fileid for some default files that needed by metadata tools
	   These IDs are defined in the header files, and they should not 
	   be changed to any other number */
	j=i;
	cat[i].file_name="GetAttrtemp";
	cat[i].file_id = 10252;

	j++;
	cat[j].file_name="MCFWrite.temp";
	cat[j].file_id = 10254;

	j++;
	cat[j].file_name="AsciiDump";
	cat[j].file_id = 10255;

	j++;
	cat[j].file_name="temporary.MCF";
	cat[j].file_id = 10256;

	num_of_user_files = j+1;
	return(PGS_S_SUCCESS);
    }    
}

/* PGS_MET_SetConfigFileId */


PGSt_SMF_status
PGS_MET_SetConfigFileId_OLD(char *file_name) /* set config file Id */
{
    
	config_file.file_name=file_name;
	config_file.file_id = 5000; /* This Id is defined in the header files
				       and it should not be changed to any 
				       other number */
	return(PGS_S_SUCCESS);
}


/* PGS_MET_GetFileId */

PGSt_PC_Logical
PGS_MET_GetFileId(                 /* get File Id */
    char             *file_name)   /* input File name */

{
    PGSt_integer i;
    PGSt_PC_Logical fileId = 0;
    PGSt_PC_Logical returnStatus = 0;
    
    for(i=0; i<num_of_user_files; i++)
    {
	if(strcmp(file_name, cat[i].file_name)== 0)
	
	{
	    fileId = cat[i].file_id;
	    returnStatus=fileId;
	    break;
	}
	else
	{
	    if(i < (num_of_user_files -1))
	    {
		/* more files to check out */
		continue;
	    }
	    else
	    {
		/* file does not exist */
		returnStatus=fileId;
		return(returnStatus);
	    }
	}
    }
    return(returnStatus);
}

