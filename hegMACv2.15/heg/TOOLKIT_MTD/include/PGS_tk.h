/*---------------------------------------------------------------------------*/
/*									     */
/*	COPYRIGHT	1994, 1995, 1996     Applied Research Corporation    */
/*									     */
/*			1997, 1998	     Space Applications Corporation  */
/*									     */
/*			ALL RIGHTS RESERVED				     */
/*									     */
/*---------------------------------------------------------------------------*/
/****************************************************************************
 * Portions developed at the National Center for Supercomputing Applications*
 * at the University of Illinois at Urbana-Champaign.                       *

 * UI MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR ANY
 * PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.  THE
 * UI SHALL NOT BE LIABLE FOR ANY DAMAGES SUFFERED BY THE USER OF THIS
 * SOFTWARE.  The software may have been developed under agreements between
 * the UI and the Federal Government which entitle the Government to certain
 * rights.
 *                                                                          *
 ****************************************************************************/

/* herr.h,v 1.36 1996/08/27 15:05:59 sxu Exp */

/*+ herr.h
   ***  header file for using error routines
   *** to be included by all ".c" files
   + */
#include <hdf.h>
#include <PGS_AUX.h>

#ifndef _PGS_MET_NEW_H
#define _PGS_MET_NEW_H
#define MAX_NUM_FILES 256
#define FILE_ID_BASE 10001
#define PGSd_MET_PATH_LENGTH_MAX 768
#define PGSd_MET_TEMP_ENVIRONMENT "PGS_TEMPORARY_IO"
#define PGSd_MET_INTER_OUTPUT_ENVIRONMENT "PGS_INTERMEDIATE_OUTPUT"
#define PGSd_MET_INFO_FILE_ENVIRONMENT "PGS_PC_INFO_FILE"
typedef PGSt_integer PGSt_MET_Long_Int;  /* for backwards compatibility */
typedef PGSt_Logical  PGSt_MET_Logical;
#define PGSd_MET_FILE_NAME_MAX 256
#define PGSd_MET_FILE_PATH_MAX 1025
#define PGSd_MET_UREF_LENGTH_MAX 255
#define PGSd_MET_INTERMEDIATE_OUTPUT 5500
#define PGSd_MET_INTERMEDIATE_INPUT 5400
#define PGSd_MET_TEMPORARY_FILE 5300
#define PGSd_MET_INPUT_FILE_NAME 5600 
#define PGSd_MET_OUTPUT_FILE_NAME 5700
#define PGSd_MET_SUPPORT_IN_NAME 5800
#define PGSd_MET_SUPPORT_OUT_NAME 5900
#define PGSd_MET_VALUE_LENGTH_MAX 200
#define PGSd_MET_LINE_LENGTH_MAX 2000
#define PGSd_MET_CONFIGURATION 5000
#define PGSd_MET_INPUT_FILE_ATTRIBUTE 5110
#define PGSd_MET_OUTPUT_FILE_ATTRIBUTE 5210
#define PGSd_MET_SUPPORT_IN_ATTR 5610
#define PGSd_MET_SUPPORT_OUT_ATTR 5710
#define PGSd_MET_ATTRIBUTE_STRING 2
#define PGSd_MET_PRODUCTION_RUN_ID 1
#define PGSd_MET_ATTRIBUTE_LOCATION 1

#define PGSd_PC_PATH_LENGTH_MAX 768
#define PGSd_PC_TEMP_ENVIRONMENT "PGS_TEMPORARY_IO"
#define PGSd_PC_INTER_OUTPUT_ENVIRONMENT "PGS_INTERMEDIATE_OUTPUT"
#define PGSd_PC_INFO_FILE_ENVIRONMENT "PGS_PC_INFO_FILE"
typedef PGSt_integer PGSt_PC_Long_Int;  /* for backwards compatibility */
typedef PGSt_Logical  PGSt_PC_Logical;
#define PGSd_PC_FILE_NAME_MAX 256
#define PGSd_PC_FILE_PATH_MAX 1025
#define PGSd_PC_UREF_LENGTH_MAX 255
#define PGSd_PC_INTERMEDIATE_OUTPUT 5500
#define PGSd_PC_INTERMEDIATE_INPUT 5400
#define PGSd_PC_TEMPORARY_FILE 5300
#define PGSd_PC_INPUT_FILE_NAME 5600 
#define PGSd_PC_OUTPUT_FILE_NAME 5700
#define PGSd_PC_SUPPORT_IN_NAME 5800
#define PGSd_PC_SUPPORT_OUT_NAME 5900
#define PGSd_PC_VALUE_LENGTH_MAX 200
#define PGSd_PC_LINE_LENGTH_MAX 2000
#define PGSd_PC_CONFIGURATION 5000
#define PGSd_PC_INPUT_FILE_ATTRIBUTE 5110
#define PGSd_PC_OUTPUT_FILE_ATTRIBUTE 5210
#define PGSd_PC_SUPPORT_IN_ATTR 5610
#define PGSd_PC_SUPPORT_OUT_ATTR 5710
#define PGSd_PC_ATTRIBUTE_STRING 2
#define PGSd_PC_PRODUCTION_RUN_ID 1
#define PGSd_PC_ATTRIBUTE_LOCATION 1
#define PGSd_PC_CONFIG_COUNT 6
#define PGSd_PC_DIVIDER '?'
#define PGSd_PC_COMMENT '#'
#define PGSd_PC_DELIMITER '|'
#define PGSd_PC_NEWLINE '\n'
#define USER_SETS_HDFID 100 /* if user wants the PGS_MET_Write to output
			       metadata to a file other than hdf and AsciiDump
			       file */
typedef struct {
     PGSt_MET_Logical    index;
     PGSt_uinteger	size;
     PGSt_uinteger	entries;
     char	        universalRef[PGSd_MET_UREF_LENGTH_MAX];
     char		attributeLoc[PGSd_MET_FILE_NAME_MAX];
     char               fileName[PGSd_MET_FILE_NAME_MAX];
     char               path[PGSd_MET_PATH_LENGTH_MAX];
    }PGSt_PC_File_Struct;

PGSt_PC_File_Struct fileinfo;   /* data for Process Control file mapping */

#endif /* end _PGS_MET_NEW_H */

#define ERROR_CODE_BASE 10000

#ifndef __HERR_H_tk
#define __HERR_H_tk

/* if these symbols are not provided by the compiler, we'll have to
   fake them.  These are used in HERROR for recording location of
   error in code. */

#ifndef __FILE__
#   define __FILE__ "File name not supported"
#endif
#ifndef __LINE__
#   define __LINE__ 0
#endif

/* HERROR macro, used to facilitate error reporting.  Assumes that
   there's a variable called FUNC which holds the function name.
   Assume that func and file are both stored in static space, or at
   least be not corrupted in the meanwhile. */

#define tk_HERROR(e) tk_HEpush(e, FUNC, __FILE__, __LINE__)

/* HRETURN_ERROR macro, used to facilitate error reporting.  Makes
   same assumptions as HERROR.  IN ADDITION, this macro causes
   a return from the calling routine */

#define tk_HRETURN_ERROR(err, ret_val) {tk_HERROR(err); return(ret_val);}

/* HCLOSE_RETURN_ERROR macro, used to facilitate error reporting.  Makes
   same assumptions as HRETURN_ERROR.  IN ADDITION, this macro causes
   the file specified by the id "fid" to be closed */

#define tk_HCLOSE_RETURN_ERROR(hfid, err, ret_val) {tk_HERROR(err); tk_Hclose(hfid); \
                                                return(ret_val);}

/* HGOTO_ERROR macro, used to facilitate error reporting.  Makes
   same assumptions as HERROR.  IN ADDITION, this macro causes
   a jump to the label 'done' which should be in every fucntion
   Also there is an assumption of a variable 'ret_value' */

#define tk_HGOTO_ERROR(err, ret_val) {tk_HERROR(err); ret_value = ret_val; \
                                   goto done;}

/* HCLOSE_RETURN_ERROR macro, used to facilitate error reporting.  Makes
   same assumptions as HRETURN_ERROR.  IN ADDITION, this macro causes
   the file specified by the id "fid" to be closed 
   Also , this macro causes a jump to the label 'done' which should 
   be in every fucntion. There is an assumption of a variable 'ret_value' */

#define tk_HCLOSE_GOTO_ERROR(hfid, err, ret_val) {tk_HERROR(err); tk_Hclose(hfid); \
                                            ret_value = ret_val; goto done;}

/* HGOTO_DONE macro, used to facilitate the new error reporting model.  
   This macro is just a wrapper to set the return value and jump to the 'done'
   label.  Also assumption of a variable 'ret_value' */

#define tk_HGOTO_DONE(ret_val) {ret_value = ret_val; goto done;}

/* For further error reporting */
#define TK_HE_REPORT(msg) tk_HEreport(msg)
#define TK_HE_REPORT_RETURN(msg, ret_val) { tk_HEreport(msg); return(ret_val); }
#define TK_HE_CLOSE_REPORT_RETURN(hfid,msg, ret_val) { tk_HEreport(msg); \
                                                    tk_Hclose(hfid); \
                                                    return(ret_val);}

#define TK_HE_REPORT_GOTO(msg, ret_val) { tk_HEreport(msg); ret_value = ret_val; \
                                       goto done;}
#define TK_HE_CLOSE_REPORT_GOTO(hfid,msg, ret_val) { tk_HEreport(msg); \
                                                  tk_Hclose(hfid); \
                                                  ret_value = ret_val; \
                                                  goto done;}


/* always points to the next available slot; the last error record is in slot (top-1) */
#ifndef _H_ERR_MASTER_TK_
extern
#endif
int32       error_top_tk
#ifdef _H_ERR_MASTER_TK_
= 0
#endif
; 

/* Macro to wrap around calls to HEPclear, so it doesn't get called zillions of times */
#define tk_HEclear() {if(error_top_tk!=0) HEPclear(); }

/*
   ======================================================================
   Error codes

   NOTE: Remember to update the error_messages[] structure in herr.c
   whenever errors are added/deleted from this list.
   ======================================================================
 */
/* Declare an enumerated type which holds all the valid HDF error codes */
typedef enum
  {
/* MET tool errors */
    PGSMET_E_NONE = ERROR_CODE_BASE,       /* No Error messsage */ 
    PGSMET_E_NO_INITIALIZATION,            /*Metadata control file is
					     not yet loaded using
					     PGS_MET_Init() */
    PGSMET_E_AGGREGATE_ERR,                /* Unable to create odl aggregate
					      %s */
    PGSMET_E_OPEN_ERR,                     /* Unable to open %s file with
					      file id %s */
    PGSMET_E_ODL_READ_ERR,                 /* Unable to create ODL tree %s
					      with file id %s */
    PGSMET_E_LOAD_ERR,                     /* Unable to load %s information */
    PGSMET_E_DD_UNKNOWN_PARM,              /* The requested parameter %s could
					      not be found in %s */
    PGSMET_E_UNKNOWN_PARM_ATTR,            /* Attribute %s is not defined for 
					      parameter %s */
    PGSMET_E_CORRUPT_MCF,                  /* Unable to find %s definition in
					      the %s */
    PGSMET_E_PARM_NOT_SET,                 /* Mandatory Parameter %s not set
					      in %s */
    PGSMET_W_NO_MAND_PARM,                 /* No Mandatory Parameter found in
					      %s */
    PGSMET_E_INV_ODL_TYPE,                 /* Input odl type is invalid */
    PGSMET_E_OUTOFRANGE,                   /* Value of metadata %s at
					      position %s is out of range */
    PGSMET_E_DD_ERR,                       /* Unable to access the data
					      dictionary to obtain %s of
					      parameter %s */
    PGSMET_E_MCF_DD_CONFLICT,              /* Conflict with data dictionary
					      for Meta data %s, The data
					      dictionary definition of %s is
					      %s */
    PGSMET_E_PCS_OPEN_ERR,		   /* Unable to open PCS file */
    
    PGSMET_E_LABEL_NOT_FOUND,              /* Unable to find %s  in file %s */
    PGSMET_E_CONFIG_VAL_STR_ERR,           /* Unable to obtain the value of
					      configuration parameter %s from
					      the config file */
    PGSMET_E_CONFIG_CONV_ERR,              /* Unable to convert the value of
					      configuration parameter %sfrom
					      the config file into an ODL format
				           */
    PGSMET_E_INCORRECT_VAL,                /* Illegal value of the parameter
					      %s defined in the PC table */
    PGSMET_E_NO_INVENT_DATA,               /* Granule data section not in the
					      MCF */
    PGSMET_E_CONFIG_DATA_ERR,              /* Unable to retrieve data from
					      the config file table */
    PGSMET_E_CONFIRM_ERR,                  /* Unable to confirm %s's value
					      against DD */
    PGSMET_E_LOCATION_ERR,                 /* In object %s value %s for
					      parameter DATA_LOCATION is
					      invalid */
    PGSMET_E_NEW_ODL_DATA_ERR,             /* Unable to create a new odl %s ,
					      probably due to lack of memeory
					   */
    PGSMET_E_INVALID_DATATYPE,             /* Invalid data type definition in
					      DD for parameter %s */
    PGSMET_E_CHECK_RANGE_ERR,              /* Unable to check the range for
					      metaData %s */
    PGSMET_E_PCREAD_ERR,                   /* Unable to obtain %s from the PC
					      table */
    PGSMET_E_FILETOODL_ERR,                /* Unable to convert %s into an
					      ODL format */
    PGSMET_E_SYS_OPEN_ERR,                 /* Unable to open pc attribute
					      file */
    PGSMET_E_ODLTOVAL_ERR,                 /* Unable to convert attribute
					      values from the odl format */
    PGSMET_E_SD_START,                     /* Unable to open the HDF file */
    PGSMET_E_SD_FINDATTR,                  /* Unable to get the attr index */
    PGSMET_E_SD_INFO,                      /* Unable to retrieve sd attribute
					      information */
    PGSMET_E_MALLOC_ERR,                   /* Unable to allocate memory for
					      the hdf attribute */
    PGSMET_E_SD_READ,                      /* Unable to read hdf attribute */
    PGSMET_W_CLASS_TYPE,                   /* Illegal class type for
					      parameter %s */
    PGSMET_E_SD_SETATTR,                   /* Unable to set the HDF file
					      attribute */
    PGSMET_E_GROUP_NOT_FOUND,              /* No group called %s found in the
					      MCF */
    PGSMET_E_INCOMP_GROUP,                 /* Some of the mandatory
					      parameters are not set */
    PGSMET_E_ODL_ERROR,                    /* "%s:%s" */
    PGSMET_W_ODL_WARNING,                  /* "%s:%s" */
    PGSMET_M_ODL_INFO,                     /* "%s:%s" */
    PGSMET_E_MINMAX_ERR,                   /* Minimum value is greater than
					      the maximum value of parameter
					      %s in %s */
    PGSMET_E_MCF_TYPE_CONFLICT,            /* Value type in PCF does not
					      match the type given for
					      metadata %s in MCF */
    PGSMET_E_MCF_NUMVAL_CONFLICT,          /* Number of values in PCF does
					      not match the number defined
					      for metadata %s in MCF */
    PGSMET_E_NESTED_OBJECTS,               /* Object descriptions enclosing
					      related objects must not be
					      enclosed themselves by other
					      objects */
    PGSMET_E_ODL_MEM_ALLOC,                /* ODL routine failed to allocate
					      memory */
    PGSMET_E_CLASS_PARAMETER,              /* Container object must also have
					      class parameter defined */
    PGSMET_E_METADATA_CHILD,               /* MetaData Objects are not
					      allowed to enclose other
					      objects */
    PGSMET_W_NOT_MULTIPLE,                 /* Object is not supposed to be
					      multiple therefore resetting
					      the value */
    PGSMET_E_NO_DEFINITION,                /* Unable to obtain %s of metadata
					      %s */
    PGSMET_E_ILLEGAL_NUMVAL,               /* Illegal NUMVAL definition for
					      metadata %s . It should be an
					      integer */
    PGSMET_E_ILLEGAL_TYPE,                 /* Illegal type definition for
					      metadata %s . It should bea
					      string */
    PGSMET_E_INV_DATATYPE,                 /* Invalid data type definition in
					      MCF for parameter %s */
    PGSMET_E_PARENT_GROUP,                 /* Multiple objects must have
					      enclosing groups around them */
    PGSMET_E_MANDATORY_FIELD,              /* Mandatory fiesld is not defined
					      for %s */
    PGSMET_E_MANDATORY_DEF,                /* MANDATORY field type is not
					      correct for metadata %s. It
					      should be a STRING */
    PGSMET_E_MANDATORY_VALUE,              /* MANDATORY field value is not
					      correct for metadata %s. It
					      should be a TRUE or FALSE */
    PGSMET_E_LOC_FIELD,                    /* Data Locationis not defined 
					      for %s */
    PGSMET_E_LOC_DEF,                      /* Data Location field type is not
					      correct for metadata %s. It
					      should be a STRING */
    
    PGSMET_E_LOC_VALUE,                    /* Data Location value is not
					      correct for metadata %s. It
					      should be a PCF, MCF, PGE, or
					      NONE */
    PGSMET_E_CONTAINER_LEVELS,             /* Metadata objects can only be
					      enclosed by one level of
					      Container objects. The
					      offending object is %s */
    PGSMET_E_DUPLICATE_ERR,                /* There is a another object with
					      the same name for object %s */
    PGSMET_E_CLASS,                        /* Illegal class definition for
					      metadata %s. It should be
					      always be M */
    PGSMET_E_CLASS_STATEMENTS,             /* Class statements should be
					      defined for all the sister
					      objects as well as thecontainer
					      objects.The offending object is
					      %s */
    PGSMET_E_INV_NUMVAL,                   /* Illegal NUMVAL value for
					      metadata %s. It should be
					      greater than or equal to 1 */
    PGSMET_E_CLASS_DEF,                    /* Illegal class definition for
					      metadata <metedata name>. It
					      shoualways be
					      PGSd_MET_MULTIPLE_FLAG */
    PGSMET_E_CLASS_TYPE,                   /* Illegal class type for metadata
					      %s */
    PGSMET_E_MAND_NOT_SET,                 /* Some of the Mandatory metadata
					      were not set */
    PGSMET_W_META_NOT_SET,                 /* Some of the metadata
					      descriptions were not set */
    PGSMET_W_METADATA_NOT_SET,             /* The metadata %s is not yet set */
    PGSMET_E_FGDC_ERR,                     /* Unable to convert UTC to FGDC
					      format for metadata %s */
    PGSMET_E_OUTFILE_ERR,                  /* Unable to open output file */
    PGSMET_E_PCF_VALUE_ERR,                /* Metadata %s could not be set
					      from a value in PCF file */
    PGSMET_E_GRP_ERR,                      /* Master groups are not supposed
					      to be enclosed under any other
					      group or object.The offending
					      group is %s */
    PGSMET_E_HDFNOTSET,                    /* The value was originally not
					      set in the hdf header */
    PGSMET_E_HDFFILENAME_ERR,              /* Unable to obtain hdf filename */
    PGSMET_E_MET_ASCII_ERR,                /* Unable to open MET ascii file */
    PGSMET_E_ILLEGAL_HANDLE,               /* Handle is illegal. Check that
					      initialization has taken place
					   */
    PGSMET_E_NUMOFMCF_ERR,                 /* Unable to load. The number of
					      MCFs allowed has exceeded */
    PGSMET_E_GRP_NAME_ERR,                 /* Group Name length should not
					      exceed %s */
    PGSMET_E_INVALID_LOCATION,             /* Invalid data location for
					      setting attribute value %s */
    PGSMET_E_NULL_PARAMETER,               /* The requested Parameter %s is a
					      NULL value */
    PGSMET_E_PARAMETER_NOT_SET,            /* The requested Parameter %s is
					      not set yet */
    PGSMET_E_SET_ATTRIBUTE_ERROR,          /* Unable to set attribute for
					      ProductionDateTime */
    PGSMET_E_SEARCH_FAILED,                /* The requested parameter could
					      not be found after searching
					      the file listing */
    PGSMET_E_GROUP_NOT_FOUND_IN_L7,        /* No group called %s found in the
					      LANDSAT7 Metadata */
    PGSMET_W_OBJECT_NOT_SET,               /* Object for data location of PGE
					      is not set */
    PGSMET_E_CONVERT_ERR,                  /* unable to convert HDF-EOS/non
					      HDF-EOS metadata product file,
					      in which unset attributes were
					      defined as NOT SET for Data
					      Location PGE, NOT SUPPLIED for
					      Data Location MCF, or NOT FOUND
					      for Data Location NONE, to a
					      .MCF file */
    PGSMET_E_TYPE_ERR,                     /* Unable to obtain data type for
					      the unset attribute */
    PGSMET_E_SET_ERR,                      /* Attribute value set up in the
					      data locateion MCF is not
					      allowable to be written over */
    PGSMET_E_ILLEGAL_LENGTH,               /* The length of character string
					      assigned to be the value of the
					      attribute name %s can not
					      exceed
					      PGSd_MET_MAX_STRING_SET_L(255)
					   */
    PGSMET_E_ARRAY_ELEMENT_SIZE,           /* The size of array element of
					      the attribute value assigned
					      for the attribute name %s can
					      not exceed
				      PGSd_MET_MAX_ARRAY_ELEMENT_SIZE(1000) */
    PGS_E_UNIX,                            /* a UNIX system error occured */
    PGSSMF_M_UNIX,                            /* a UNIX error occured */
    PGSIO_E_FILEMAP,	             /* Attempt to map logical to 
					physical file failed.*/
    
    PGSIO_E_GEN_OPEN,	             /*Generic IO - Attempt to open file 
				       failed. */
    PGSIO_E_GEN_OPENMODE,	     /*Generic IO - Invalid mode for file 
				       open. */ 
    PGSIO_E_GEN_FILE_NOEXIST,	     /*File does not exist, or cannot be 
				       created. */     
    PGSIO_E_GEN_NO_TEMP_NAME,        /*New name could not be generated for 
				       this temporary file */
    PGSIO_E_GEN_REFERENCE_FAILURE,   /*File reference could not be achieved */
    PGSIO_E_GEN_CREATE_FAILURE,	     /*File creation could not be achieved */
    PGSIO_E_GEN_BAD_FILE_DURATION,   /*An invalid file duration setting was 
				       requested */
    PGSIO_W_GEN_ACCESS_MODIFIED,     /*File exists! resetting access mode to 
				       PGSd_IO_Gen_Append Update */
    PGSIO_W_GEN_DURATION_NOMOD,	     /*Intermediate file duration may not be 
				       modified in this access mode */ 
    PGSIO_W_GEN_NEW_FILE,	     /*New file was created eventhough access 
				       mode was not explicit write */
    PGSIO_E_PARTIAL_NAME,	     /*Generated temporary file name missing 
				       key component */
    PGSIO_E_GEN_NO_FREE_LUN,         /*No free logical unit number available 
				       to allocate */
    PGSIO_E_GEN_ILLEGAL_LUN,         /*Illegal value for logical unit number:
				       can't deallocate */
    PGSIO_W_GEN_UNUSED_LUN,          /*The LUN marked for deallocation was not
				       allocated */
    PGSIO_W_GEN_OLD_FILE,            /*File exists! Changing access mode from 
				       Write to Update */
    PGSIO_E_GEN_OPEN_OLD,            /*Attempt to do FORTRAN Open with
				       STATUS=OLD failed! */
    PGSIO_E_GEN_OPEN_NEW,            /*Attempt to do FORTRAN Open with 
				       STATUS=NEW failed! */
    PGSIO_E_GEN_OPEN_UNKNOWN,        /* Attempt to do FORTRAN Open with 
					STATUS=UNKNOWN failed! */
    PGSIO_E_GEN_OPEN_RECL,           /*Illegal value for record length */
    PGSIO_E_GEN_FILE_NODEL,          /*File does not exist, or cannot be 
				       deleted */
    PGSIO_W_GEN_FILE_NOT_FOUND,	     /*File could not be located on disk */
    PGSIO_E_GEN_CLOSE,       	     /*Generic IO - Attempt to close file 
				       failed. */
    PGSIO_E_GEN_BAD_ENVIRONMENT,     /*Bad default setting detected for I/O 
				       path */
    PGSIO_E_L0_BAD_BUF_SIZ,          /*Buffer size must be a positive 
				       integer */
    PGSIO_E_L0_BAD_SPACECRAFT_TAG,   /*Illegal spacecraft tag */
    PGSIO_E_L0_FSEEK,                /* Failed to locate requested byte in 
					file */
    PGSIO_E_L0_MANAGE_TABLE,         /*Error accessing internal virtual file 
				       table */
    PGSIO_E_L0_PHYSICAL_OPEN,        /*Unable to open physical file */
    PGSIO_E_L0_UNEXPECTED_EOF,       /*Encountered unexpected end-of-file */
    PGSIO_E_L0_VIRTUAL_DS_NOT_OPEN,  /*Virtual data set is not open */
    PGSIO_M_L0_HEADER_CHANGED,       /* New physical file open - file header 
					has changed */
    PGSIO_W_L0_PKT_BUF_TRUNCATE,     /*Insufficient packet buffer size - data 
				       truncated */
    PGSIO_W_L0_PHYSICAL_CLOSE,       /*Failed to close physical file */
    PGSIO_E_L0_INIT_FILE_TABLE,      /*Error during read of physical file 
				       header for initialization */
    PGSIO_E_L0_INVALID_FILE_LOGICAL, /*Failed to process this file logical in 
				       process control file */
    PGSIO_E_L0_MAP_VERSIONS,         /* Failed to initialize internal physical
					file table */
    PGSIO_E_L0_SEEK_1ST_PACKET,      /*Can't find 1st packet in dataset */
    PGSIO_W_L0_TIME_NOT_FOUND,       /*Requested start time not found; file 
				       pointer position was unchanged */ 
    PGSIO_E_L0_SEEK_PACKET,          /*Unable to find requested packet */
    PGSIO_E_L0_PHYSICAL_NOT_OPEN,    /* No physical file currently open for 
					this virtual data set */
    PGSIO_E_L0_PKT_BUF_OVERFLOW,     /*Packet buffer too small; no data was 
				       read */
    PGSIO_W_L0_END_OF_VIRTUAL_DS,    /*Reached end of the current data set */
    PGSIO_E_L0_NEXT_PHYSICAL,        /*Error opening next physical file */
    PGSIO_E_L0_ILLEGAL_COMMAND,      /*Specified command code is illegal */
    PGSIO_E_L0_ILLEGAL_PACKET_NUM,   /*Illegal packet number  */
    PGSIO_E_L0_INDEX_OUT_OF_RANGE,   /*File table lookup index is out of 
				       range */
    PGSIO_E_L0_MAX_OPEN_EXCEEDED,    /*Max no. of open Level 0 data sets 
				       exceeded */
    PGSIO_E_L0_MEM_ALLOC,            /*Error occurred during memory allocation
				      */
    PGSIO_E_L0_UNUSED_TABLE_ENTRY,   /*File table lookup index points to 
				       unused table entry */
    PGSIO_E_L0_VERSION_COUNT,        /*Unable to read no. of file versions 
				       from process control file */
    PGSIO_E_L0_VERSION_INFO,         /*Error occurred attempting to get 
				       physical file header information */
    PGSIO_E_L0_PACKET_NOT_FOUND,     /*Packet not found in current physical 
				       file */
    PGSIO_E_L0_TIME_CONVERSION,      /*Error occurred during time conversion */
    PGSIO_E_L0_BAD_FILEINFO,         /*Error occurred determining file 
				       information */
    PGSIO_E_L0_BAD_NUM_PKTS,         /*Illegal number of packets */
    PGSIO_E_L0_BAD_APP_ID,           /*At least 1 packet had a bad Application
				       ID */
    PGSIO_E_L0_BAD_FIRST_PKTNUM,     /*Illegal first packet number */
    PGSIO_E_L0_BAD_DATA_LENGTH,      /*At least 1 packet had a bad data 
				       length */
    PGSIO_E_L0_BAD_NUM_APP_IDS,      /*Illegal number of differing Application
				       IDs */
    PGSIO_W_L0_HDR_BUF_TRUNCATE,     /*Insufficient header buffer size - data 
				       truncated */
    PGSIO_W_L0_FTR_BUF_TRUNCATE,     /*Insufficient footer buffer size - data 
				       truncated */
    PGSIO_W_L0_ALL_BUF_TRUNCATE,     /*Insufficient header buffer AND footer 
				       buffer sizes - data truncated */
    PGSIO_W_L0_BUFTRUNC_END_DS,      /*Insufficient packet buffer size - data 
				       truncated, reached end of the current 
				       data set */
    PGSIO_W_L0_BUFTRUNC_HDR_CHG,     /*Insufficient packet buffer size - data 
				       truncated, new physical file open - 
				       file header has changed */
    PGSIO_E_L0_BUFTRUNC_NXTFILE,     /*Insufficient packet buffer size - data 
				       truncated, error opening next physical 
				       file in sequence */
    PGSIO_W_L0_HDR_TIME_ORDER,       /*Time of last packet is earlier than 
				       time of first packet in file header */
    PGSIO_E_L0_BAD_VAR_HDR_SIZE,     /*The size of the variable header as 
				       indicated in the fixed header is 
				       invalid */
    PGSIO_W_L0_BAD_PKT_DATA_SIZE,    /*The total size of the packet data as 
				       indicated in the file header is 
				       invalid */
    PGSIO_W_L0_BAD_PACKET_COUNT,     /*The total number of packets as 
				       indicated in the file header is invalid
				     */
    PGSIO_W_L0_BAD_FOOTER_SIZE,      /*The size of the file footer as 
				       indicated in the file header is invalid
				     */
    PGSIO_W_L0_ZERO_PACKET_COUNT,    /*The total number of packets as 
				       indicated in the file header is zero */
    PGSIO_W_L0_CORRUPT_FILE_HDR,     /*An error was found in the file header*/
    PGSPC_E_FILE_OPEN_ERROR,     /*Error opening file:  %s*/
    PGSPC_E_INVALID_MODE,        /*Mode value not defined:  %d*/
    PGSPC_W_NO_FILES_EXIST,      /*File not found in product group:  %d*/
    PGSPC_W_NO_CONFIG_VALUE,     /*No configuration value exists for logical*/
    PGSPC_E_FILE_READ_ERROR,     /*Error while reading from Process Control 
				   file:  %s*/
    PGSPC_E_LINE_FORMAT_ERROR,   /*Incorrect format in line of file:  %s*/
    PGSPC_E_ENVIRONMENT_ERROR,   /*Environment variable not set:  %s*/
    PGSPC_W_NO_DATA_PRESENT,     /*The data requested is not in the line 
				   found.*/
    PGSPC_E_DATA_ACCESS_ERROR,   /*Error accessing Process Control Status 
				   data.*/
    PGSPC_W_NO_REFERENCE_FOUND,  /*No reference was found matching Product 
				   ID (%d) and Version number (%d).*/
    PGSPC_W_NO_CONFIG_FOR_ID,    /*The Product ID does not contain a 
				   configuration value.*/
    PGSPC_W_NO_FILES_FOR_ID,     /*The Product ID does not contain a 
				   physical reference.*/
    PGSPC_W_NO_ATTR_FOR_ID,      /*The reference does not contain an 
				   attribute.*/
    PGSPC_W_TRUNCATED,           /*The value was truncated.*/
    PGSPC_W_ATTR_TRUNCATED,      /*The attribute was truncated due to 
				   maxSize being exceeded.*/
    PGSPC_W_NO_ATTR_MATCH,       /*No attribute was found that matches the 
				   attribute passed in.*/
    PGSPC_W_INVALID_VERSION,     /*Version number must be greater than or 
				   equal to one (1).*/
    PGSPC_W_FILE_NOT_ON_DISK,    /*The file requested to be removed was not 
				   on disk:  %s*/
    PGSPC_W_NULL_DATA_SHM,       /*Data field is NULL.*/
    PGSPC_E_INV_DIVPOINTER_SHM,  /*Division pointer not pointing to divider 
				   symbol.*/
    PGSPC_E_EXCEEDED_SHM,        /*Exceeded amount of shared memory 
				   requested - write failed.*/
    PGSPC_E_NO_DEFAULT_LOC,      /*Default file location not specified.*/
    PGSPC_E_ENV_NOT_PC,          /*Environment not defined by Process Control 
				   Tools:  %s*/
    PGSPC_C_PGSINFO_PGE_START,   /*PGE Processing starting up.*/
    PGSPC_C_PGSINFO_PGE_STOP,    /*PGE Processing will NOT be performed.*/
    PGSPC_C_PGSINFO_TERM_START,  /*Toolkit Termination Procedure is underway.*/
    PGSPC_M_TOOLKIT_INIT_PASS,   /*Toolkit Initialization Procedure has 
				   succeeded! ::PGSPC_C_PGSINFO_PGE_START*/
    PGSPC_E_TOOLKIT_INIT_FAIL,   /*Toolkit Initialization Procedure has 
				   failed! ::PGSPC_C_PGSINFO_PGE_STOP*/
    PGSPC_M_TOOLKIT_TERM_BEGIN,  /*Initialization or PGE Processing has 
				   completed. ::PGSPC_C_PGSINFO_TERM_START*/
    PGSPC_W_NO_UREF_DATA,        /*The Product ID contains no Universal
				   Reference.*/
    PGSMEM_E_MAXSIZE,           /* Maximum memory size reached: %d in bytes*/
    PGSMEM_E_NO_MEMORY,         /* No memory space available for current 
				   process*/ 
    PGSMEM_E_ADDR_NOTALLOC,     /* Address %d is not allocated previously */
    PGSMEM_W_MEMORY_USED,       /* Memory address has been allocated 
				   previously*/
    PGSMEM_E_SHM,               /* ERRNO %d, %s*/
    PGSMEM_E_SHM_NOTCREATE,     /* Shared-memory has not been created*/
    PGSMEM_E_SHM_MULTICREATE,   /* More than one shared-memory is created for 
				   a given PGE script*/
    PGSMEM_E_SHM_MULTIATTACH,   /* Multiply attached shared-memory in a 
				   process*/
    PGSMEM_E_SHM_NOTATTACH,     /* Shared-memory has not been attached to the 
				   process*/
    PGSMEM_E_SHM_MAXSIZE,       /* Maximum system-imposed shared memory 
				   exceeded*/
    PGSMEM_E_SHM_ENV,           /* Environment variable "PGSMEM_SHM_SYSKEY" is 
				   not set*/
    PGSMEM_E_SHM_INVALIDKEY,    /* Invalid system keyPGSMEM_E_SHM_ENV*/
    PGSTD_M_ASCII_TIME_FMT_B,   /* the time string passed in is in proper 
				   CCSDS ASCII Time Format B*/
    PGSTD_M_LEAP_SEC_IGNORED,   /* the input time string seconds field has 
				   been reduced from 60 to 59*/
    PGSTD_M_TIME_TRUNCATED,     /* the input time has been truncated to 
				   match the resolution of the output time 
				   format*/
    PGSTD_W_DATA_FILE_MISSING,  /* an open file call failed*/
    PGSTD_W_JD_OUT_OF_RANGE,    /* input julian day out of range for 
				   tabulated corrections*/
    PGSTD_W_PRED_LEAPS,         /* predicted value of TAI-UTC used 
				   (actual value unavailable)*/
    PGSTD_W_BAD_SC_TIME,        /* one or more spacecraft times in the 
				   input array (other than the 1st) could not
				   be deciphered*/
    PGSTD_E_BAD_P_FIELD,        /* the first 9 bits of the P-field 
				   (which are constant for EOS PM) differ 
				   from the expected state*/
    PGSTD_E_DATE_OUT_OF_RANGE,  /* the input time is outside the range of 
				   allowable values for the spacecraft clock*/
    PGSTD_E_MICSEC_TOO_BIG,     /* microsecond field too large, should 
				   be < 1000 */
    PGSTD_E_MILSEC_TOO_BIG,     /* millisecond field too large, should 
				   be < 86401000*/
    PGSTD_E_NO_LEAP_SECS,       /* no leap second correction available*/
    PGSTD_E_SC_TAG_UNKNOWN,     /* spacecraft tag is unknown or not 
				   currently supported*/
    PGSTD_E_TIME_FMT_ERROR,     /* error in ascii time string format 
				   (generic format: 
				   YYYY-MM-DDThh:mm:ss.ddddddZ)*/
    PGSTD_E_TIME_VALUE_ERROR,   /* error in ascii time string value 
				   (e.g. hours > 23)*/
    PGSTD_E_UNIX_ERROR,         /* some sort of unix error occured*/
    PGSTD_E_NO_UT1_VALUE,       /* no UT1 value available  */              
    PGSTD_E_BAD_2ND_HDR_FLAG,   /* the secondary header ID flag 
				   (one bit value) is set to 1 
				   (should be set to 0)*/
    PGSTD_E_BAD_INITIAL_TIME,   /* the initial spacecraft time in the 
				   input array cannot be deciphered*/
    PGSTD_E_BAD_ARRAY_SIZE,     /* incorrect array size (e.g. negative) 
				   specified*/
    PGSTD_E_SECONDS_TOO_BIG,    /* seconds field to large, should be < 86401*/
    PGSTD_E_UTCF_UNINITIALIZED, /* the TRMM UTCF value has not been 
				   initialized*/
    PGSTD_E_TMDF_UNINITIALIZED, /* the ADEOS-II TMDF values (period, s/c 
				   reference and ground reference) have not
				   been initialized*/
    PGSCBP_E_NO_EPHEMERIS_DATA,      /*Ephemeris data (file) is unavailable.*/
    PGSCBP_E_BAD_ARRAY_SIZE,         /*Invalid arrays size*/
    PGSCBP_E_BAD_TIME_FORMAT,        /*Invalid time format*/
    PGSCBP_E_NO_MEMORY,              /*Memory allocation failed, array may be 
				       to large*/
    PGSCBP_E_BAD_CB_ID,              /*Invalid celestian body identifier*/
    PGSCBP_E_TIME_OUT_OF_RANGE,      /*There is NO data for time specified.*/
    PGSCBP_W_EPHEMERIS_ERROR,        /*Error occured in JPL Ephemeris 
				       software function PLEPH*/
    PGSCBP_E_UNABLE_TO_READ_FILE,    /*Input file can't be open*/
    PGSCBP_E_UNABLE_TO_OPEN_FILE,    /*Output file can't be open*/
    PGSCBP_W_NOT_HEADER,             /*Header not found*/
    PGSCBP_E_INVALID_NCOEFF,         /*NCOEFF is invalid*/
    PGSCBP_E_NO_OVERLAP,             /*Records do not overlap or abut*/
    PGSCBP_W_NO_RECORD_WRITTEN,      /*Records not written*/
    PGSCBP_E_INVALID_CB_ID,          /*Invalid cb_id*/
    PGSCBP_E_NO_LIBRATIONS,          /*No librations*/
    PGSCBP_E_TARG_EQUAL_CENTER,      /*Target equal to center*/
    PGSCBP_E_INVALID_FILE_POS,       /*File not positioned*/
    PGSCBP_E_READ_RECORD_ERROR,      /*Read error record*/
    PGSCBP_E_INVALID_INT_FLAG,       /*Invalid flag*/
    PGSCBP_E_EPOCH_OUT_OF_SPAN,      /*Ephemeris out of span*/
    PGSCBP_E_NO_NUTATIONS,           /*No nutations*/
    PGSCBP_E_INVALID_BODY,           /*Invalid requested body*/
    PGSCBP_E_BAD_INITIAL_TIME,       /*initial time incorrect*/
    PGSCBP_W_EARTH_CB_ID,            /*cbId of Earth*/
    PGSCBP_W_BAD_CB_VECTOR,          /*one or more bad vectors for requested
				       times*/ 
    PGSCBP_W_ERROR_IN_BODYINFOV,     /*an error occurred in determining if the
				       CB was in the FOV for at least one case
				     */
    PGSCSC_W_JD_OUT_OF_RANGE,       /*input julian day out of range for
				      tabulated corrections*/
    PGSCSC_W_DATA_FILE_MISSING,     /*an open file call failed*/ 
    PGSCSC_E_BAD_DIRECTION_FLAG,    /*the TRUE/FALSE flag has invalid value*/
    PGSCSC_E_JD_WRONG_EPOCH,        /*indicates input date not = to J2000 as
				      required*/ 
    PGSCSC_E_ZERO_INPUT_VECTOR,     /*input vector with zero length when
				      direction is required*/
    PGSCSC_E_BAD_FLAT,              /*error in flattening value used, 
				      flattening must be < 1*/
    PGSCSC_E_NEG_OR_ZERO_RAD,       /*radius must be greater than 0.0*/
    PGSCSC_E_BAD_LAT,               /*bad value for latitude*/
    PGSCSC_E_BAD_LON,               /*bad value for longitude*/
    PGSCSC_W_PROLATE_BODY,          /*prolate body assumed*/
    PGSCSC_W_SPHERE_BODY,           /*perfectly spherical body assumed*/
    PGSCSC_W_BELOW_SURFACE,         /*location is below surface*/
    PGSCSC_E_BAD_ROT_AXIS_INDEX,    /*value of rotation axis index invalid*/
    PGSCSC_E_SC_TAG_UNKNOWN,        /*unknown/unsupported spacecraft tag*/ 
    PGSCSC_E_TRANS_FLAG_ERR,        /*coordinate system transformation 
				      flag not recognized/supported*/
    PGSCSC_E_INVALID_VECTAG,        /*invalid tag for vector whose zenith 
				      and azimuth are sought*/
    PGSCSC_W_BELOW_HORIZON,         /*vector whose zenith angle is sought 
				      is below horizon*/
    PGSCSC_E_LOOK_PT_ALTIT_RANGE,   /*look point altitude unreasonably low 
				      or high*/
    PGSCSC_W_UNDEFINED_AZIMUTH,     /*azimuth worthless because ray is at 
				      zenith*/    
    PGSCSC_W_SUBTERRANEAN,          /*below the ground*/ 
    PGSCSC_W_TOO_MANY_ITERS,        /*poor convergence - suggests bad Earth 
				      model or bad data*/
    PGSCSC_W_ZERO_JACOBIAN_DET,     /*Singularity at N or S pole - or bad 
				      data*/
    PGSCSC_W_DEFAULT_EARTH_MODEL,   /*Default Earth model used*/
    PGSCSC_W_MISS_EARTH,            /*look vector does not intersect Earth*/
    PGSCSC_W_INSTRUMENT_OFF_BOARD,  /*user-provided instrument offset exceeds 
				      120 meters*/
    PGSCSC_W_ZERO_PIXEL_VECTOR,     /*user-provided pixel unit vector has 
				      zero length*/
    PGSCSC_W_BAD_ACCURACY_FLAG,     /*Value other than PGS_TRUE or PGS_FALSE 
				      detected*/
    PGSCSC_W_BAD_EPH_FOR_PIXEL,     /*Bad SC ephemeris values encountered for 
				      some pixels*/
    PGSCSC_E_INACCURATE_UTCPOLE,    /*status of data should be one of 'f' for 
				      final, 'p' for predicted or 'i' for 
				      interim */
    PGSCSC_W_INTERIM_UT1,           /*status of data used is interim*/
    PGSCSC_W_PREDICTED_UT1,         /*status of data used is predicted*/
    PGSCSC_E_BAD_QUATERNION,        /*the input quaternion is invalid, the 
				      sum of the squares of the components of
				      a quaternion must = 1*/
    PGSCSC_W_ERRORS_IN_GHA,         /*error computing Greenwich Hour angle 
				      from either getting UTC time, Julian 
				      date, polar motion correction, or GMST 
				      time*/
    PGSCSC_W_ERROR_IN_DAYNIGHT,     /*an error occurred in computing at least 
				      one after dark value*/
    PGSCSC_W_BAD_TRANSFORM_VALUE,   /*an error occurred in at least one of the 
				      transformations*/
    PGSCSC_E_INVALID_LIMITTAG,      /*invalid sun zenith limit tag*/
    PGSCSC_E_BAD_ARRAY_SIZE,        /*incorrect array size*/
    PGSCSC_W_INVALID_ALTITUDE,      /*invalid altitude - probably indicates 
				      bad input data*/
    PGSCSC_W_LARGE_FLATTENING,      /*flattening should be about 1/300 for 
				      Earth*/
    PGSCSC_W_ERROR_IN_SUBSATPT,     /*an error occurred in computing at least 
				      one subsatellite point value*/
    PGSCSC_W_NO_REFRACTION,         /*unable to perform refraction 
				      calculation*/
    PGSCSC_E_EULER_REP_INVALID,     /*invalid euler angle representation*/
    PGSCSC_E_EULER_INDEX_ERROR,     /*euler angle index is out of range - 
				      should be one of 1, 2 or 3*/
    PGSCSC_W_ACCURACY_SUSPECT,      /*accuracy of the output is suspect*/
    PGSCSC_E_QUAT_NOT_FOUND,        /*the rotation could not be determined*/
    PGSCSC_E_INVALID_FOV_DATA,      /*FOV perimeter vectors are invalid*/
    PGSCSC_E_FOV_TOO_LARGE,         /*FOV specification outside algorithmic 
				      limits*/
    PGSCSC_E_INVALID_EARTH_PT,      /*one of the Earth point vectors was zero*/
    PGSCSC_M_EARTH_BLOCKS_CB,       /*Earth blocks the celestial body*/ 
    PGSCSC_M_EARTH_BLOCKS_FOV,      /*Earth blocks the FOV*/
    PGSCSC_M_CHECK_EARTH_BULGE,     /*check to see if the Earth's bulge 
				      occults the CB*/
    PGSCSC_E_BAD_EARTH_MODEL,       /*bad Earth model specified (e.g. negative
				      or zero Earth radii or prolate Earth)*/ 
    PGSCSC_W_ERROR_IN_EARTHPTFOV,   /*an error occurred in determining if 
				      point was in the FOV for at least one 
				      case*/ 
    PGSCSC_E_INVALID_ZENITH,        /*invalid zenith angle specified*/ 
    PGSCSC_E_BELOW_SURFACE,         /* altitude specified is more than 50,000 
				       km below surface of Earth*/ 
    PGSCSC_E_ABORT_UTCPOLE_UPDATE,  /*error condition in updating - see 
				      LogStatus file*/ 
    PGSCSC_W_ERROR_IN_GRAZINGRAY,   /*an error occurred in a function called 
				      by this one*/ 
    PGSCSC_W_HIT_EARTH,             /*line of sight intended to miss the 
				      horizon (i.e. limb sounder) hits Earth*/ 
    PGSCSC_W_LOOK_AWAY,             /*line of sight of instrument points above 
				      the horizontal*/
    PGSEPH_E_SIMULATOR_ERROR,    /*orbit/attitude simulator error*/
    PGSEPH_W_BAD_EPHEM_VALUE,    /*one or more of the requested values could 
				   not be det
				   ermined, undetermined values set to 1.0E50*/
    PGSEPH_E_BAD_ARRAY_SIZE,     /*incorrect array size (i.e. < 0) specified*/
    PGSEPH_E_NO_SC_EPHEM_FILE,   /*error in accessing spacecraft ephemeris 
				   and/or attitude file*/
    PGSEPH_E_BAD_EPHEM_FILE_HDR, /*error in file header of spacecraft 
				   ephemeris and/or attitude file*/
    PGSEPH_E_BAD_TIME_ORDER,     /*bad ordering of input times (start 
				   time <= desired time <= stop time)*/
    PGSEPH_E_NO_DATA_REQUESTED,  /*no data has been requested (i.e. all 
				   data flags set to PGS_FALSE)*/
    PGSEPH_M_SHORT_ARRAY,        /*not all elements of input array have 
				   been initialize with data*/
    PGSCUC_E_CANT_GET_FILE_ID,               /*No matching filepath to input 
					       fileid*/
    PGSCUC_E_CANT_OPEN_INPUT_FILE,           /*Cant open input file*/
    PGSCUC_E_AGG_CANT_BE_INSERTED,           /*Base node, aggregate cannot 
					       be formed*/
    PGSCUC_E_READLABEL_PARSE_ERROR,          /*Pointer to aggregate label 
					       parsing error*/
    PGSCUC_E_PARAMETER_INVALID,              /*Parameter not found within 
					       input file*/
    PGSCUC_E_FIRST_NODE_NOT_FOUND,           /*Parameter node not found*/
    PGSCUC_E__ERROR,                         /*CUC runtime error*/
    PGSCUC_E_COULDNT_INIT_UDUNITS3,          /*Couldnt initialise Data file*/
    PGSCUC_E_DONT_KNOW_INP_UNIT,             /*Input unit is not known*/
    PGSCUC_E_DONT_KNOW_OUTP_UNIT,            /*Output unit is not known*/
    PGSCUC_E_UNITS_ARE_INCOMPATIBLE,         /*No conversion between units*/
    PGSCUC_E_A_UNIT_IS_CORRUPTED,            /*A unit in the data file is 
					      corrupted*/
    PGSTD_M_HEADER_UPDATED,                  /*the leap seconds file header 
					       was updated to show USNO 
					       listed no new leap second*/
    PGS_E_TOOLKIT,                            /* TOOLKIT Error occured */
    PGSMET_E_GETSET_ATTRIBUTE_ERROR,          /* Unable to get attribute for 
						 ProductionDateTime */
    PGSMET_M_METADATA_NOT_SET_TK,             /* Metadata has not been set, 
						 TOOLKIT may set it */
    PGSMET_M_METADATA_NOT_SET_PGE             /* Metadata has not been set, 
						 TOOLKIT will not set it */
  }tk_hdf_err_code_t;

#ifdef _H_ERR_MASTER_TK_

/* error_messages is the list of error messages in the system, kept as
   error_code-message pairs.  To look up a message, a linear search is
   required but efficiency should be okay. */

typedef struct tk_error_messages_t
  {
      tk_hdf_err_code_t error_code;
      const char *str;
  }
tk_error_messages_t;

PRIVATE const struct tk_error_messages_t tk_error_messages[] =
{
/* MET tool errors */
    {PGSMET_E_NONE,          "No error"},
    {PGSMET_E_NO_INITIALIZATION,	
     "Metadata control file is not yet loaded using PGS_MET_Init()"},
    {PGSMET_E_AGGREGATE_ERR,		
     "Unable to create odl aggregate %s"},
    {PGSMET_E_OPEN_ERR,	        	
     "Unable to open %s file with file id %s"},
    {PGSMET_E_ODL_READ_ERR,		
     "Unable to create ODL tree %s with file id %s"},
    {PGSMET_E_LOAD_ERR,		        
     "Unable to load %s information"},
    {PGSMET_E_DD_UNKNOWN_PARM,   	
     "The requested parameter %s could not be found in %s"},
    {PGSMET_E_UNKNOWN_PARM_ATTR,	
     "Attribute %s is not defined for parameter %s"},
    {PGSMET_E_CORRUPT_MCF,	
     "Unable to find %s definition in the %s"},
    {PGSMET_E_PARM_NOT_SET,		
     "Mandatory Parameter %s not set in %s"},
    {PGSMET_W_NO_MAND_PARM,		
     "No Mandatory Parameter found in %s"},
    {PGSMET_E_INV_ODL_TYPE,		
     "Input odl type is invalid"},
    {PGSMET_E_OUTOFRANGE,		
     "Value of metadata %s at position %s is out of range"},
    {PGSMET_E_DD_ERR,			
     "Unable to access the data dictionary to obtain %s of parameter %s"},
    {PGSMET_E_MCF_DD_CONFLICT,	
     "Conflict with data dictionary for Meta data %s, The data dictionary definition of %s is %s"},
    {PGSMET_E_PCS_OPEN_ERR,	        	
     "Unable to open PCS file"},
    {PGSMET_E_LABEL_NOT_FOUND,	        
     "Unable to find %s  in file %s"},
    {PGSMET_E_CONFIG_VAL_STR_ERR,	       
     "Unable to obtain the value of configuration parameter %s from the config file"},
    {PGSMET_E_CONFIG_CONV_ERR,              
     "Unable to convert the value of configuration parameter %sfrom the config file into an ODL format"},
    {PGSMET_E_INCORRECT_VAL,	
     "Illegal value of the parameter %s defined in the PC table"},
    {PGSMET_E_NO_INVENT_DATA,		
     "Granule data section not in the MCF"},
    {PGSMET_E_CONFIG_DATA_ERR,	
     "Unable to retrieve data from the config file table"},
    {PGSMET_E_CONFIRM_ERR,		
     "Unable to confirm %s's value against DD"},
    {PGSMET_E_LOCATION_ERR,		
     "In object %s value %s for parameter DATA_LOCATION is invalid"},
    {PGSMET_E_NEW_ODL_DATA_ERR,	
     "Unable to create a new odl %s , probably due to lack of memeory"},
    {PGSMET_E_INVALID_DATATYPE,	
     "Invalid data type definition in DD for parameter %s"},
    {PGSMET_E_CHECK_RANGE_ERR,	
     "Unable to check the range for metaData %s"},
    {PGSMET_E_PCREAD_ERR,		
     "Unable to obtain %s from the PC table"},
    {PGSMET_E_FILETOODL_ERR,		
     "Unable to convert %s into an ODL format"},
    {PGSMET_E_SYS_OPEN_ERR,		
     "Unable to open pc attribute file"},
    {PGSMET_E_ODLTOVAL_ERR,	
     "Unable to convert attribute values from the odl format"},
    {PGSMET_E_SD_START,		
     "Unable to open the HDF file"},
    {PGSMET_E_SD_FINDATTR,		
     "Unable to get the attr index"},
    {PGSMET_E_SD_INFO,		
     "Unable to retrieve sd attribute information"},
    {PGSMET_E_MALLOC_ERR,		
     "Unable to allocate memory for the hdf attribute"},
    {PGSMET_E_SD_READ,		
     "Unable to read hdf attribute"},
    {PGSMET_W_CLASS_TYPE,		
     "Illegal class type for parameter %s"},
    {PGSMET_E_SD_SETATTR,		
     "Unable to set the HDF file attribute"},
    {PGSMET_E_GROUP_NOT_FOUND,	
     "No group called %s found in the MCF"},
    {PGSMET_E_INCOMP_GROUP,	
     "Some of the mandatory parameters are not set"},
    {PGSMET_E_ODL_ERROR,	
     "%s:%s"},
    {PGSMET_W_ODL_WARNING,	
     " %s:%s "},
    {PGSMET_M_ODL_INFO,	
     "%s:%s"},
    {PGSMET_E_MINMAX_ERR,		
     "Minimum value is greater than the maximum value of parameter %s in %s"}, 
    {PGSMET_E_MCF_TYPE_CONFLICT,	
     "Value type in PCF does not match the type given for metadata %s in MCF"},
    {PGSMET_E_MCF_NUMVAL_CONFLICT,	
     "Number of values in PCF does not match the number defined for metadata %s in MCF"},
    {PGSMET_E_NESTED_OBJECTS,		
     "Object descriptions enclosing related objects must not be enclosed themselves by other objects"},
    {PGSMET_E_ODL_MEM_ALLOC,		
     "ODL routine failed to allocate memory"},
    {PGSMET_E_CLASS_PARAMETER,
     "Container object must also have class parameter defined"},
    {PGSMET_E_METADATA_CHILD,		
     "MetaData Objects are not allowed to enclose other objects"},
    {PGSMET_W_NOT_MULTIPLE,		
     "Object is not supposed to be multiple therefore resetting the value"},
    {PGSMET_E_NO_DEFINITION,	
     "Unable to obtain %s of metadata %s"},
    {PGSMET_E_ILLEGAL_NUMVAL,		
     "Illegal NUMVAL definition for metadata %s . It should be an integer"},
    {PGSMET_E_ILLEGAL_TYPE,		
     "Illegal type definition for metadata %s . It should bea string"},
    {PGSMET_E_INV_DATATYPE,		
     "Invalid data type definition in MCF for parameter %s"},
    {PGSMET_E_PARENT_GROUP,		
     "Multiple objects must have enclosing groups around them"},
    {PGSMET_E_MANDATORY_FIELD,
     "Mandatory fiesld is not defined for %s"},
    {PGSMET_E_MANDATORY_DEF,	
     "MANDATORY field type is not correct for metadata %s. It should be a STRING"},
    {PGSMET_E_MANDATORY_VALUE,	
     "MANDATORY field value is not correct for metadata %s. It should be a TRUE or FALSE"},
    {PGSMET_E_LOC_FIELD,		
     "Data Locationis not defined for %s"},
    {PGSMET_E_LOC_DEF,		
     "Data Location field type is not correct for metadata %s. It should be a STRING"},
    {PGSMET_E_LOC_VALUE,	
     "Data Location value is not correct for metadata %s. It should be a PCF, MCF, PGE, or NONE"},
    {PGSMET_E_CONTAINER_LEVELS,	
     "Metadata objects can only be enclosed by one level of Container objects. The offending object is %s"},
    {PGSMET_E_DUPLICATE_ERR,		
     "There is a another object with the same name for object %s"},
    {PGSMET_E_CLASS,			
     "Illegal class definition for metadata %s. It should be always be M"},
    {PGSMET_E_CLASS_STATEMENTS,	
     "Class statements should be defined for all the sister objects as well as thecontainer objects.The offending object is %s"},
    {PGSMET_E_INV_NUMVAL,		
     "Illegal NUMVAL value for metadata %s. It should be greater than or equal to 1"},
    {PGSMET_E_CLASS_DEF,		
     "Illegal class definition for metadata <metedata name>. It shoualways be PGSd_MET_MULTIPLE_FLAG"},
    {PGSMET_E_CLASS_TYPE,		
     "Illegal class type for metadata %s"},
    {PGSMET_E_MAND_NOT_SET,		
     "Some of the Mandatory metadata were not set"},
    {PGSMET_W_META_NOT_SET,       
     "Some of the metadata descriptions were not set "},
    {PGSMET_W_METADATA_NOT_SET,	
     "The metadata %s is not yet set"},
    {PGSMET_E_FGDC_ERR,		
     "Unable to convert UTC to FGDC format for metadata %s"},
    {PGSMET_E_OUTFILE_ERR,		
     "Unable to open output file"},
    {PGSMET_E_PCF_VALUE_ERR,		
     "Metadata %s could not be set from a value in PCF file"},
    {PGSMET_E_GRP_ERR,		
     "Master groups are not supposed to be enclosed under any other group or object.The offending group is %s"},
    {PGSMET_E_HDFNOTSET,		
     "The value was originally not set in the hdf header"},
    {PGSMET_E_HDFFILENAME_ERR,	
     "Unable to obtain hdf filename"},
    {PGSMET_E_MET_ASCII_ERR,		
     "Unable to open MET ascii file"},
    {PGSMET_E_ILLEGAL_HANDLE,		
     "Handle is illegal. Check that initialization has taken place"},
    {PGSMET_E_NUMOFMCF_ERR,		
     "Unable to load. The number of MCFs allowed has exceeded"},
    {PGSMET_E_GRP_NAME_ERR,		
     "Group Name length should not exceed %s"},
    {PGSMET_E_INVALID_LOCATION,       
     "Invalid data location for setting attribute value %s"},
    {PGSMET_E_NULL_PARAMETER,         
     "The requested Parameter %s is a NULL value "},
    {PGSMET_E_PARAMETER_NOT_SET,      
     "The requested Parameter %s is not set yet "},
    {PGSMET_E_SET_ATTRIBUTE_ERROR,    
     "Unable to set attribute for ProductionDateTime"},
    {PGSMET_E_SEARCH_FAILED,          
     "The requested parameter could not be found after searching the file listing"},
    {PGSMET_E_GROUP_NOT_FOUND_IN_L7,  
     "No group called %s found in the LANDSAT7 Metadata"},
    {PGSMET_W_OBJECT_NOT_SET,        
     " Object for data location of PGE is not set "},
    {PGSMET_E_CONVERT_ERR,            
     "unable to convert HDF-EOS/non HDF-EOS metadata product file, in which unset attributes were defined as NOT SET for Data Location PGE, NOT SUPPLIED for Data Location MCF, or NOT FOUND for Data Location NONE, to a .MCF file "},
    {PGSMET_E_TYPE_ERR,              
     " Unable to obtain data type for the unset attribute "},
    {PGSMET_E_SET_ERR,                
     "Attribute value set up in the data locateion MCF is not allowable to be written over "},
    {PGSMET_E_ILLEGAL_LENGTH,        
     "The length of character string assigned to be the value of the attribute name %s can not exceed PGSd_MET_MAX_STRING_SET_L(255) "},
    {PGSMET_E_ARRAY_ELEMENT_SIZE,     
     "The size of array element of the attribute value assigned for the \
attribute name %s can not exceed PGSd_MET_MAX_ARRAY_ELEMENT_SIZE(1000) "},
    {PGS_E_UNIX,                    
     "a UNIX system error occured"},
    {PGSSMF_M_UNIX,                    
     "a UNIX error occured"},
    {PGSIO_E_FILEMAP,	
     "Attempt to map logical to physical file failed."},
    {PGSIO_E_GEN_OPEN,	
     "Generic IO - Attempt to open file failed. "},
    {PGSIO_E_GEN_OPENMODE,	
     "Generic IO - Invalid mode for file open. "}, 
    {PGSIO_E_GEN_FILE_NOEXIST,	
     "File does not exist, or cannot be created. "},     
    {PGSIO_E_GEN_NO_TEMP_NAME,     	
     "New name could not be generated for this temporary file "},
    {PGSIO_E_GEN_REFERENCE_FAILURE,
     "File reference could not be achieved "},
    {PGSIO_E_GEN_CREATE_FAILURE,	
     "File creation could not be achieved "},
    {PGSIO_E_GEN_BAD_FILE_DURATION,   
     "An invalid file duration setting was requested "},
    {PGSIO_W_GEN_ACCESS_MODIFIED, 	
     "File exists! resetting access mode to PGSd_IO_Gen_Append Update "},
    {PGSIO_W_GEN_DURATION_NOMOD,	
     "Intermediate file duration may not be modified in this access mode "}, 
    {PGSIO_W_GEN_NEW_FILE,		
     "New file was created eventhough access mode was not explicit write "},
    {PGSIO_E_PARTIAL_NAME,	
     "Generated temporary file name missing key component "},
    {PGSIO_E_GEN_NO_FREE_LUN,         
     "No free logical unit number available to allocate "},
    {PGSIO_E_GEN_ILLEGAL_LUN,        
     "Illegal value for logical unit number: can't deallocate "},
    {PGSIO_W_GEN_UNUSED_LUN,         
     "The LUN marked for deallocation was not allocated "},
    {PGSIO_W_GEN_OLD_FILE,            
     "File exists! Changing access mode from Write to Update "},
    {PGSIO_E_GEN_OPEN_OLD,            
     "Attempt to do FORTRAN Open with STATUS=OLD failed! "},
    {PGSIO_E_GEN_OPEN_NEW,           
     "Attempt to do FORTRAN Open with STATUS=NEW failed! "},
    {PGSIO_E_GEN_OPEN_UNKNOWN,      
     " Attempt to do FORTRAN Open with STATUS=UNKNOWN failed! "},
    {PGSIO_E_GEN_OPEN_RECL,          
     "Illegal value for record length "},
    {PGSIO_E_GEN_FILE_NODEL,		
     "File does not exist, or cannot be deleted "},
    {PGSIO_W_GEN_FILE_NOT_FOUND,
     "File could not be located on disk "},
    {PGSIO_E_GEN_CLOSE,       
     "Generic IO - Attempt to close file failed. "},
    {PGSIO_E_GEN_BAD_ENVIRONMENT,	
     "Bad default setting detected for I/O path "},
    {PGSIO_E_L0_BAD_BUF_SIZ,              
     "Buffer size must be a positive integer "},
    {PGSIO_E_L0_BAD_SPACECRAFT_TAG,      
     "Illegal spacecraft tag "},
    {PGSIO_E_L0_FSEEK,                   
     " Failed to locate requested byte in file "},
    {PGSIO_E_L0_MANAGE_TABLE,             
     "Error accessing internal virtual file table "},
    {PGSIO_E_L0_PHYSICAL_OPEN,            
     "Unable to open physical file "},
    {PGSIO_E_L0_UNEXPECTED_EOF,           
     "Encountered unexpected end-of-file "},
    {PGSIO_E_L0_VIRTUAL_DS_NOT_OPEN,      
     "Virtual data set is not open "},
    {PGSIO_M_L0_HEADER_CHANGED,          
     " New physical file open - file header has changed "},
    {PGSIO_W_L0_PKT_BUF_TRUNCATE,         
     "Insufficient packet buffer size - data truncated "},
    {PGSIO_W_L0_PHYSICAL_CLOSE,           
     "Failed to close physical file "},
    {PGSIO_E_L0_INIT_FILE_TABLE,          
     "Error during read of physical file header for initialization "},
    {PGSIO_E_L0_INVALID_FILE_LOGICAL,     
     "Failed to process this file logical in process control file "},
    {PGSIO_E_L0_MAP_VERSIONS,            
     " Failed to initialize internal physical file table "},
    {PGSIO_E_L0_SEEK_1ST_PACKET,          
     "Can't find 1st packet in dataset "},
    {PGSIO_W_L0_TIME_NOT_FOUND,           
     "Requested start time not found; file pointer position was unchanged "}, 
    {PGSIO_E_L0_SEEK_PACKET,              
     "Unable to find requested packet "},
    {PGSIO_E_L0_PHYSICAL_NOT_OPEN,       
     " No physical file currently open for this virtual data set "},
    {PGSIO_E_L0_PKT_BUF_OVERFLOW,         
     "Packet buffer too small; no data was read "},
    {PGSIO_W_L0_END_OF_VIRTUAL_DS,        
     "Reached end of the current data set "},
    {PGSIO_E_L0_NEXT_PHYSICAL,            
     "Error opening next physical file "},
    {PGSIO_E_L0_ILLEGAL_COMMAND,          
     "Specified command code is illegal "},
    {PGSIO_E_L0_ILLEGAL_PACKET_NUM,       
     "Illegal packet number  "},
    {PGSIO_E_L0_INDEX_OUT_OF_RANGE,       
     "File table lookup index is out of range "},
    {PGSIO_E_L0_MAX_OPEN_EXCEEDED,        
     "Max no. of open Level 0 data sets exceeded "},
    {PGSIO_E_L0_MEM_ALLOC,                
     "Error occurred during memory allocation "},
    {PGSIO_E_L0_UNUSED_TABLE_ENTRY,       
     "File table lookup index points to unused table entry "},
    {PGSIO_E_L0_VERSION_COUNT,            
     "Unable to read no. of file versions from process control file "},
    {PGSIO_E_L0_VERSION_INFO,             
     "Error occurred attempting to get physical file header information "},
    {PGSIO_E_L0_PACKET_NOT_FOUND,        
     "Packet not found in current physical file "},
    {PGSIO_E_L0_TIME_CONVERSION,          
     "Error occurred during time conversion "},
    {PGSIO_E_L0_BAD_FILEINFO,             
     "Error occurred determining file information "},
    {PGSIO_E_L0_BAD_NUM_PKTS,             
     "Illegal number of packets "},
    {PGSIO_E_L0_BAD_APP_ID,               
     "At least 1 packet had a bad Application ID "},
    {PGSIO_E_L0_BAD_FIRST_PKTNUM,         
     "Illegal first packet number "},
    {PGSIO_E_L0_BAD_DATA_LENGTH,          
     "At least 1 packet had a bad data length "},
    {PGSIO_E_L0_BAD_NUM_APP_IDS,          
     "Illegal number of differing Application IDs "},
    {PGSIO_W_L0_HDR_BUF_TRUNCATE,         
     "Insufficient header buffer size - data truncated "},
    {PGSIO_W_L0_FTR_BUF_TRUNCATE,         
     "Insufficient footer buffer size - data truncated "},
    {PGSIO_W_L0_ALL_BUF_TRUNCATE,         
     "Insufficient header buffer AND footer buffer sizes - data truncated "},
    {PGSIO_W_L0_BUFTRUNC_END_DS,          
     "Insufficient packet buffer size - data truncated, reached end of the current data set "},
    {PGSIO_W_L0_BUFTRUNC_HDR_CHG,         
     "Insufficient packet buffer size - data truncated, new physical file open - file header has changed "},
    {PGSIO_E_L0_BUFTRUNC_NXTFILE,        
     "Insufficient packet buffer size - data truncated, error opening next physical file in sequence "},
    {PGSIO_W_L0_HDR_TIME_ORDER,          
     "Time of last packet is earlier than time of first packet in file header "},
    {PGSIO_E_L0_BAD_VAR_HDR_SIZE,         
     "The size of the variable header as indicated in the fixed header is invalid "},
    {PGSIO_W_L0_BAD_PKT_DATA_SIZE,        
     "The total size of the packet data as indicated in the file header is invalid "},
    {PGSIO_W_L0_BAD_PACKET_COUNT,         
     "The total number of packets as indicated in the file header is invalid "},
    {PGSIO_W_L0_BAD_FOOTER_SIZE,          
     "The size of the file footer as indicated in the file header is invalid "},
    {PGSIO_W_L0_ZERO_PACKET_COUNT,       
     "The total number of packets as indicated in the file header is zero "},
    {PGSIO_W_L0_CORRUPT_FILE_HDR,       
     "An error was found in the file header "},
    {PGSPC_E_FILE_OPEN_ERROR,     
     "Error opening file:  %s"},
    {PGSPC_E_INVALID_MODE,        
     "Mode value not defined:  %d"},
    {PGSPC_W_NO_FILES_EXIST,     
     "File not found in product group:  %d"},
    {PGSPC_W_NO_CONFIG_VALUE,    
     "No configuration value exists for logical"},
    {PGSPC_E_FILE_READ_ERROR,    
     "Error while reading from Process Control file:  %s"},
    {PGSPC_E_LINE_FORMAT_ERROR,  
     "Incorrect format in line of file:  %s"},
    {PGSPC_E_ENVIRONMENT_ERROR,   
     "Environment variable not set:  %s"},
    {PGSPC_W_NO_DATA_PRESENT,     
     "The data requested is not in the line found."},
    {PGSPC_E_DATA_ACCESS_ERROR,   
     "Error accessing Process Control Status data."},
    {PGSPC_W_NO_REFERENCE_FOUND, 
     "No reference was found matching Product ID (%d) and Version number (%d)."},
    {PGSPC_W_NO_CONFIG_FOR_ID,   
     "The Product ID does not contain a configuration value."},
    {PGSPC_W_NO_FILES_FOR_ID,    
     " The Product ID does not contain a physical reference."},
    {PGSPC_W_NO_ATTR_FOR_ID,     
     "The reference does not contain an attribute."},
    {PGSPC_W_TRUNCATED,           
     "The value was truncated."},
    {PGSPC_W_ATTR_TRUNCATED,      
     "The attribute was truncated due to maxSize being exceeded."},
    {PGSPC_W_NO_ATTR_MATCH,      
     "No attribute was found that matches the attribute passed in."},
    {PGSPC_W_INVALID_VERSION,     
     "Version number must be greater than or equal to one (1)."},
    {PGSPC_W_FILE_NOT_ON_DISK,    
     "The file requested to be removed was not on disk:  %s"},
    {PGSPC_W_NULL_DATA_SHM,       
     "Data field is NULL."},
    {PGSPC_E_INV_DIVPOINTER_SHM,  
     "Division pointer not pointing to divider symbol."},
    {PGSPC_E_EXCEEDED_SHM,        
     "Exceeded amount of shared memory requested - write failed."},
    {PGSPC_E_NO_DEFAULT_LOC,     
     "Default file location not specified."},
    {PGSPC_E_ENV_NOT_PC,          
     "Environment not defined by Process Control Tools:  %s"},
    {PGSPC_C_PGSINFO_PGE_START,   
     "PGE Processing starting up."},
    {PGSPC_C_PGSINFO_PGE_STOP,    
     "PGE Processing will NOT be performed."},
    {PGSPC_C_PGSINFO_TERM_START,  
     "Toolkit Termination Procedure is underway."},
    {PGSPC_M_TOOLKIT_INIT_PASS,   
     "Toolkit Initialization Procedure has succeeded! ::PGSPC_C_PGSINFO_PGE_START"},
    {PGSPC_E_TOOLKIT_INIT_FAIL,   
     "Toolkit Initialization Procedure has failed! ::PGSPC_C_PGSINFO_PGE_STOP"},
    {PGSPC_M_TOOLKIT_TERM_BEGIN,  
     "Initialization or PGE Processing has completed.::PGSPC_C_PGSINFO_TERM_START"},
    {PGSPC_W_NO_UREF_DATA,        
     "The Product ID contains no Universal Reference."},
    {PGSMEM_E_MAXSIZE,           
     " Maximum memory size reached: %d in bytes"},
    {PGSMEM_E_NO_MEMORY,         
     " No memory space available for current process"}, 
    {PGSMEM_E_ADDR_NOTALLOC,     
     " Address %d is not allocated previously"}, 
    {PGSMEM_W_MEMORY_USED,       
     " Memory address has been allocated previously"},
    {PGSMEM_E_SHM,               
     " ERRNO %d, %s"},
    {PGSMEM_E_SHM_NOTCREATE,      
     "Shared-memory has not been created"},
    {PGSMEM_E_SHM_MULTICREATE,    
     "More than one shared-memory is created for a given PGE script"},
    {PGSMEM_E_SHM_MULTIATTACH,    
     "Multiply attached shared-memory in a process"},
    {PGSMEM_E_SHM_NOTATTACH,      
     "Shared-memory has not been attached to the process"},
    {PGSMEM_E_SHM_MAXSIZE,       
     "Maximum system-imposed shared memory exceeded"},
    {PGSMEM_E_SHM_ENV,            
     "Environment variable PGSMEM_SHM_SYSKEY is not set"},
    {PGSMEM_E_SHM_INVALIDKEY,    
     "Invalid system keyPGSMEM_E_SHM_ENV"}, 
    {PGSTD_M_ASCII_TIME_FMT_B,     
     "the time string passed in is in proper CCSDS ASCII Time Format B"},
    {PGSTD_M_LEAP_SEC_IGNORED,    
     "the input time string seconds field has been reduced from 60 to 59"},
    {PGSTD_M_TIME_TRUNCATED,       
     "the input time has been truncated to match the resolution of the output time format"},
    {PGSTD_W_DATA_FILE_MISSING,    
     "an open file call failed"},
    {PGSTD_W_JD_OUT_OF_RANGE,      
     "input julian day out of range for tabulated corrections"},
    {PGSTD_W_PRED_LEAPS,          
     "predicted value of TAI-UTC used (actual value unavailable)"},
    {PGSTD_W_BAD_SC_TIME,          
     "one or more spacecraft times in the input array (other than the 1st)could not be deciphered"},
    {PGSTD_E_BAD_P_FIELD,          
     "the first 9 bits of the P-field (which are constant for EOS PM) differ from the expected state"},
    {PGSTD_E_DATE_OUT_OF_RANGE,    
     "the input time is outside the range of allowable values for the spacecraft clock"},
    {PGSTD_E_MICSEC_TOO_BIG,      
     "microsecond field too large, should be < 1000 "},
    {PGSTD_E_MILSEC_TOO_BIG,      
     "millisecond field too large, should be < 86401000"},
    {PGSTD_E_NO_LEAP_SECS,        
     "no leap second correction available"},
    {PGSTD_E_SC_TAG_UNKNOWN,       
     "spacecraft tag is unknown or not currently supported"},
    {PGSTD_E_TIME_FMT_ERROR,      
     "error in ascii time string format (generic format: YYYY-MM-DDThh:mm:ss.ddddddZ)"},
    {PGSTD_E_TIME_VALUE_ERROR,    
     "error in ascii time string value (e.g. hours > 23)"},
    {PGSTD_E_UNIX_ERROR,          
     "some sort of unix error occured"},
    {PGSTD_E_NO_UT1_VALUE, 
     "no UT1 value available  "},              
    {PGSTD_E_BAD_2ND_HDR_FLAG,     
     "the secondary header ID flag (one bit value) is set to 1(should be set to 0)"},
    {PGSTD_E_BAD_INITIAL_TIME,    
     "the initial spacecraft time in the input array cannot be deciphered"},
    {PGSTD_E_BAD_ARRAY_SIZE,      
     "incorrect array size (e.g. negative) specified"},
    {PGSTD_E_SECONDS_TOO_BIG,     
     "seconds field to large, should be < 86401"},
    {PGSTD_E_UTCF_UNINITIALIZED,   
     "the TRMM UTCF value has not been initialized"},
    {PGSTD_E_TMDF_UNINITIALIZED,   
     "the ADEOS-II TMDF values (period, s/c reference and ground reference)have not been initialized"},
    {PGSCBP_E_NO_EPHEMERIS_DATA,    
     "Ephemeris data (file) is unavailable."},
    {PGSCBP_E_BAD_ARRAY_SIZE,       
     "Invalid arrays size"},
    {PGSCBP_E_BAD_TIME_FORMAT,      
     "Invalid time format"},
    {PGSCBP_E_NO_MEMORY,            
     "Memory allocation failed, array may be to large"},
    {PGSCBP_E_BAD_CB_ID,            
     "Invalid celestian body identifier"},
    {PGSCBP_E_TIME_OUT_OF_RANGE,    
     "There is NO data for time specified."},
    {PGSCBP_W_EPHEMERIS_ERROR,      
     "Error occured in JPL Ephemeris software function PLEPH"},
    {PGSCBP_E_UNABLE_TO_READ_FILE,  
     "Input file can't be open"},
    {PGSCBP_E_UNABLE_TO_OPEN_FILE,  
     "Output file can't be open"},
    {PGSCBP_W_NOT_HEADER,           
     "Header not found"},
    {PGSCBP_E_INVALID_NCOEFF,       
     "NCOEFF is invalid"},
    {PGSCBP_E_NO_OVERLAP,           
     "Records do not overlap or abut"},
    {PGSCBP_W_NO_RECORD_WRITTEN,    
     "Records not written"},
    {PGSCBP_E_INVALID_CB_ID,        
     "Invalid cb_id"},
    {PGSCBP_E_NO_LIBRATIONS,        
     "No librations"},
    {PGSCBP_E_TARG_EQUAL_CENTER,    
     "Target equal to center"},
    {PGSCBP_E_INVALID_FILE_POS,     
     "File not positioned"},
    {PGSCBP_E_READ_RECORD_ERROR,    
     "Read error record"},
    {PGSCBP_E_INVALID_INT_FLAG,     
     "Invalid flag"},
    {PGSCBP_E_EPOCH_OUT_OF_SPAN,    
     "Ephemeris out of span"},
    {PGSCBP_E_NO_NUTATIONS,
     "No nutations"},
    {PGSCBP_E_INVALID_BODY,
     "Invalid requested body"},
    {PGSCBP_E_BAD_INITIAL_TIME,
     "initial time incorrect"},
    {PGSCBP_W_EARTH_CB_ID,        
     "cbId of Earth"},
    {PGSCBP_W_BAD_CB_VECTOR,
     "one or more bad vectors for requested times"},
    {PGSCBP_W_ERROR_IN_BODYINFOV,
     "an error occured in determining if the CB was in the FOV for at least one case."},
    {PGSCSC_W_JD_OUT_OF_RANGE,     
     "input julian day out of range for tabulated corrections"},
    {PGSCSC_W_DATA_FILE_MISSING,   
     "an open file call failed"}, 
    {PGSCSC_E_BAD_DIRECTION_FLAG,  
     "the TRUE/FALSE flag has invalid value"},
    {PGSCSC_E_JD_WRONG_EPOCH,      
     "indicates input date not = to J2000 as required" },
    {PGSCSC_E_ZERO_INPUT_VECTOR,   
     "input vector with zero length when direction is required"},
    {PGSCSC_E_BAD_FLAT,            
     "error in flattening value used, flattening must be < 1"},
    {PGSCSC_E_NEG_OR_ZERO_RAD,     
     "radius must be greater than 0.0"},
    {PGSCSC_E_BAD_LAT,             
     "bad value for latitude"},
    {PGSCSC_E_BAD_LON,             
     "bad value for longitude"},
    {PGSCSC_W_PROLATE_BODY,        
     "prolate body assumed"},
    {PGSCSC_W_SPHERE_BODY,         
     "perfectly spherical body assumed"},
    {PGSCSC_W_BELOW_SURFACE,       
     "location is below surface"},
    {PGSCSC_E_BAD_ROT_AXIS_INDEX,  
     "value of rotation axis index invalid"},
    {PGSCSC_E_SC_TAG_UNKNOWN,      
     "unknown/unsupported spacecraft tag" },
    {PGSCSC_E_TRANS_FLAG_ERR,      
     "coordinate system transformation flag not recognized/supported"},
    {PGSCSC_E_INVALID_VECTAG,      
     "invalid tag for vector whose zenith and azimuth are sought"},
    {PGSCSC_W_BELOW_HORIZON,       
     "vector whose zenith angle is sought is below horizon"},
    {PGSCSC_E_LOOK_PT_ALTIT_RANGE, 
     "look point altitude unreasonably low or high"},
    {PGSCSC_W_UNDEFINED_AZIMUTH,   
     "azimuth worthless because ray is at zenith"  },  
    {PGSCSC_W_SUBTERRANEAN,        
     "below the ground"}, 
    {PGSCSC_W_TOO_MANY_ITERS,      
     "poor convergence - suggests bad Earth model or bad data"},
    {PGSCSC_W_ZERO_JACOBIAN_DET,   
     "Singularity at N or S pole - or bad data"},
    {PGSCSC_W_DEFAULT_EARTH_MODEL, 
     "Default Earth model used"},
    {PGSCSC_W_MISS_EARTH,          
     "look vector does not intersect Earth"},
    {PGSCSC_W_INSTRUMENT_OFF_BOARD,
     "user-provided instrument offset exceeds 120 meters"},
    {PGSCSC_W_ZERO_PIXEL_VECTOR,   
     "user-provided pixel unit vector has zero length"},
    {PGSCSC_W_BAD_ACCURACY_FLAG,   
     "Value other than PGS_TRUE or PGS_FALSE detected"},
    {PGSCSC_W_BAD_EPH_FOR_PIXEL,   
     "Bad SC ephemeris values encountered for some pixels"},
    {PGSCSC_E_INACCURATE_UTCPOLE,  
     "status of data should be one of 'f' for final, 'p' for predicted or 'i' for interim"},
    {PGSCSC_W_INTERIM_UT1,         
     "status of data used is interim"},
    {PGSCSC_W_PREDICTED_UT1,       
     "status of data used is predicted"},
    {PGSCSC_E_BAD_QUATERNION,      
     "the input quaternion is invalid, the sum of the squares of the components of a quaternion must = 1"},
    {PGSCSC_W_ERRORS_IN_GHA,       
     "error computing Greenwich Hour angle from either getting UTC time, Julian date, polar motion correction, or GMST time"},
    {PGSCSC_W_ERROR_IN_DAYNIGHT,   
     "an error occurred in computing at least one after dark value"},
    {PGSCSC_W_BAD_TRANSFORM_VALUE, 
     "an error occurred in at least one of the transformations"},
    {PGSCSC_E_INVALID_LIMITTAG,    
     "invalid sun zenith limit tag"},
    {PGSCSC_E_BAD_ARRAY_SIZE,      
     "incorrect array size"},
    {PGSCSC_W_INVALID_ALTITUDE,    
     "invalid altitude - probably indicates bad input data"},
    {PGSCSC_W_LARGE_FLATTENING,    
     "flattening should be about 1/300 for Earth"},
    {PGSCSC_W_ERROR_IN_SUBSATPT,   
     "an error occurred in computing at least one subsatellite point value"},
    {PGSCSC_W_NO_REFRACTION,       
     "unable to perform refraction calculation"},
    {PGSCSC_E_EULER_REP_INVALID,   
     "invalid euler angle representation"},
    {PGSCSC_E_EULER_INDEX_ERROR,   
     "euler angle index is out of range - should be one of 1, 2 or 3"},
    {PGSCSC_W_ACCURACY_SUSPECT,    
     "accuracy of the output is suspect"},
    {PGSCSC_E_QUAT_NOT_FOUND,      
     "the rotation could not be determined"},
    {PGSCSC_E_INVALID_FOV_DATA,    
     "FOV perimeter vectors are invalid"},
    {PGSCSC_E_FOV_TOO_LARGE,       
     "FOV specification outside algorithmic limits"},
    {PGSCSC_E_INVALID_EARTH_PT,    
     "one of the Earth point vectors was zero"},
    {PGSCSC_M_EARTH_BLOCKS_CB,     
     "Earth blocks the celestial body" },
    {PGSCSC_M_EARTH_BLOCKS_FOV,    
     "Earth blocks the FOV"},
    {PGSCSC_M_CHECK_EARTH_BULGE,  
     "check to see if the Earth's bulge occults the CB"},
    {PGSCSC_E_BAD_EARTH_MODEL,     
     "bad Earth model specified(e.g. negativ or zero Earth radii or prolate Earth)"}, 
    {PGSCSC_W_ERROR_IN_EARTHPTFOV, 
     "an error occurred in determining if point was in the FOV for at least one case."},
    {PGSCSC_E_INVALID_ZENITH,      
     "invalid zenith angle specified"}, 
    {PGSCSC_E_BELOW_SURFACE,       
     " altitude specified is more than 50,000 km below surface of Earth" },
    {PGSCSC_E_ABORT_UTCPOLE_UPDATE,
     "error condition in updating - see LogStatus file" },
    {PGSCSC_W_ERROR_IN_GRAZINGRAY, 
     "an error occurred in a function called by this one"}, 
    {PGSCSC_W_HIT_EARTH,           
     "line of sight intended to miss the horizon(i.e. limb sounder)hits Earth"}, 
    {PGSCSC_W_LOOK_AWAY,            
     "line of sight of instrument points above the horizontal"},
    {PGSEPH_E_SIMULATOR_ERROR,    
     "orbit/attitude simulator error"},
    {PGSEPH_W_BAD_EPHEM_VALUE,    
     "one or more of the requested values could not be determined, undetermined values set to 1.0E50"},
    {PGSEPH_E_BAD_ARRAY_SIZE,     
     "incorrect array size (i.e. < 0) specified"},
    {PGSEPH_E_NO_SC_EPHEM_FILE,   
     "error in accessing spacecraft ephemeris and/or attitude file"},
    {PGSEPH_E_BAD_EPHEM_FILE_HDR, 
     "error in file header of spacecraft ephemeris and/or attitude file"},
    {PGSEPH_E_BAD_TIME_ORDER,     
     "bad ordering of input times (start time <= desired time <= stop time)"},
    {PGSEPH_E_NO_DATA_REQUESTED,  
     "no data has been requested (i.e. all data flags set to PGS_FALSE)"},
    {PGSEPH_M_SHORT_ARRAY,        
     "not all elements of input array have been initialize with data"},
    {PGSCUC_E_CANT_GET_FILE_ID,               
     "No matching filepath to input fileid"},
    {PGSCUC_E_CANT_OPEN_INPUT_FILE,           
     "Cant open input file"},
    {PGSCUC_E_AGG_CANT_BE_INSERTED,           
     "Base node, aggregate cannot be formed"},
    {PGSCUC_E_READLABEL_PARSE_ERROR,          
     "Pointer to aggregate label parsing error"},
    {PGSCUC_E_PARAMETER_INVALID,              
     "Parameter not found within input file"},
    {PGSCUC_E_FIRST_NODE_NOT_FOUND,           
     "Parameter node not found"},
    {PGSCUC_E__ERROR,                         
     "CUC runtime error"},
    {PGSCUC_E_COULDNT_INIT_UDUNITS3,          
     "Couldnt initialise Data file"},
    {PGSCUC_E_DONT_KNOW_INP_UNIT,             
     "Input unit is not known"},
    {PGSCUC_E_DONT_KNOW_OUTP_UNIT,            
     "Output unit is not known"},
    {PGSCUC_E_UNITS_ARE_INCOMPATIBLE,         
     "No conversion between units"},
    {PGSCUC_E_A_UNIT_IS_CORRUPTED,            
     "A unit in the data file is corrupted"},
    {PGSTD_M_HEADER_UPDATED,
     "the leap seconds file header was updated to show USNO listed no new leap second"},
    {PGS_E_TOOLKIT,
     "TOOLKIT Error occured"},
    {PGSMET_E_GETSET_ATTRIBUTE_ERROR,
     "Unable to get attribute for ProductionDateTime"},
    {PGSMET_M_METADATA_NOT_SET_TK,
     "Metadata has not been set, TOOLKIT may set it"},
    {PGSMET_M_METADATA_NOT_SET_PGE,
     "Metadata has not been set, TOOLKIT will not set it"}

};

char codes_names[][40] =
{    
    "PGSMET_E_NONE",
    "PGSMET_E_NO_INITIALIZATION", 
    "PGSMET_E_AGGREGATE_ERR",     				
    "PGSMET_E_OPEN_ERR",  
    "PGSMET_E_ODL_READ_ERR",  				
    "PGSMET_E_LOAD_ERR",          
    "PGSMET_E_DD_UNKNOWN_PARM",   				
    "PGSMET_E_UNKNOWN_PARM_ATTR", 				
    "PGSMET_E_CORRUPT_MCF",       				
    "PGSMET_E_PARM_NOT_SET",      				
    "PGSMET_W_NO_MAND_PARM",      				
    "PGSMET_E_INV_ODL_TYPE",      
    "PGSMET_E_OUTOFRANGE",        
    "PGSMET_E_DD_ERR",            				
    "PGSMET_E_MCF_DD_CONFLICT",   
    "PGSMET_E_PCS_OPEN_ERR",	
    "PGSMET_E_LABEL_NOT_FOUND", 
    "PGSMET_E_CONFIG_VAL_STR_ERR", 
    "PGSMET_E_CONFIG_CONV_ERR",           
    "PGSMET_E_INCORRECT_VAL",             
    "PGSMET_E_NO_INVENT_DATA",            
    "PGSMET_E_CONFIG_DATA_ERR",           
    "PGSMET_E_CONFIRM_ERR",               
    "PGSMET_E_LOCATION_ERR",              
    "PGSMET_E_NEW_ODL_DATA_ERR",          
    "PGSMET_E_INVALID_DATATYPE",          
    "PGSMET_E_CHECK_RANGE_ERR",           
    "PGSMET_E_PCREAD_ERR",                
    "PGSMET_E_FILETOODL_ERR",             
    "PGSMET_E_SYS_OPEN_ERR",              
    "PGSMET_E_ODLTOVAL_ERR",              				       
    "PGSMET_E_SD_START",                  
    "PGSMET_E_SD_FINDATTR",               
    "PGSMET_E_SD_INFO",                   
    "PGSMET_E_MALLOC_ERR",                
    "PGSMET_E_SD_READ",                   
    "PGSMET_W_CLASS_TYPE",           
    "PGSMET_E_SD_SETATTR",           
    "PGSMET_E_GROUP_NOT_FOUND",      
    "PGSMET_E_INCOMP_GROUP",              
    "PGSMET_E_ODL_ERROR",                 
    "PGSMET_W_ODL_WARNING",          
    "PGSMET_M_ODL_INFO",             
    "PGSMET_E_MINMAX_ERR",           
    "PGSMET_E_MCF_TYPE_CONFLICT",    
    "PGSMET_E_MCF_NUMVAL_CONFLICT",       
    "PGSMET_E_NESTED_OBJECTS",            
    "PGSMET_E_ODL_MEM_ALLOC",             
    "PGSMET_E_CLASS_PARAMETER",           
    "PGSMET_E_METADATA_CHILD",            
    "PGSMET_W_NOT_MULTIPLE",          
    "PGSMET_E_NO_DEFINITION",        
    "PGSMET_E_ILLEGAL_NUMVAL",       
    "PGSMET_E_ILLEGAL_TYPE",              
    "PGSMET_E_INV_DATATYPE",              
    "PGSMET_E_PARENT_GROUP",              
    "PGSMET_E_MANDATORY_FIELD",           
    "PGSMET_E_MANDATORY_DEF",             
    "PGSMET_E_MANDATORY_VALUE",           
    "PGSMET_E_LOC_FIELD",                 
    "PGSMET_E_LOC_DEF",                   
    "PGSMET_E_LOC_VALUE",                 
    "PGSMET_E_CONTAINER_LEVELS",          
    "PGSMET_E_DUPLICATE_ERR",             
    "PGSMET_E_CLASS",                     
    "PGSMET_E_CLASS_STATEMENTS",          
    "PGSMET_E_INV_NUMVAL",                
    "PGSMET_E_CLASS_DEF",                 
    "PGSMET_E_CLASS_TYPE",                
    "PGSMET_E_MAND_NOT_SET",              
    "PGSMET_W_META_NOT_SET",         
    "PGSMET_W_METADATA_NOT_SET",     
    "PGSMET_E_FGDC_ERR",             
    "PGSMET_E_OUTFILE_ERR",          
    "PGSMET_E_PCF_VALUE_ERR",        
    "PGSMET_E_GRP_ERR",                   
    "PGSMET_E_HDFNOTSET",                 
    "PGSMET_E_HDFFILENAME_ERR",           
    "PGSMET_E_MET_ASCII_ERR",             
    "PGSMET_E_ILLEGAL_HANDLE",            
    "PGSMET_E_NUMOFMCF_ERR",              
    "PGSMET_E_GRP_NAME_ERR",              
    "PGSMET_E_INVALID_LOCATION",          
    "PGSMET_E_NULL_PARAMETER",            
    "PGSMET_E_PARAMETER_NOT_SET",         
    "PGSMET_E_SET_ATTRIBUTE_ERROR",       
    "PGSMET_E_SEARCH_FAILED",             
    "PGSMET_E_GROUP_NOT_FOUND_IN_L7",     
    "PGSMET_W_OBJECT_NOT_SET",       
    "PGSMET_E_CONVERT_ERR",          
    "PGSMET_E_TYPE_ERR",            
    "PGSMET_E_SET_ERR",                   
    "PGSMET_E_ILLEGAL_LENGTH",           
    "PGSMET_E_ARRAY_ELEMENT_SIZE",
    "PGS_E_UNIX",
    "PGSSMF_M_UNIX",
    "PGSIO_E_FILEMAP",	
    "PGSIO_E_GEN_OPEN",	
    "PGSIO_E_GEN_OPENMODE",	
    "PGSIO_E_GEN_FILE_NOEXIST",	
    "PGSIO_E_GEN_NO_TEMP_NAME",     	
    "PGSIO_E_GEN_REFERENCE_FAILURE",
    "PGSIO_E_GEN_CREATE_FAILURE",	
    "PGSIO_E_GEN_BAD_FILE_DURATION",   
    "PGSIO_W_GEN_ACCESS_MODIFIED", 	
    "PGSIO_W_GEN_DURATION_NOMOD",	
    "PGSIO_W_GEN_NEW_FILE",		
    "PGSIO_E_PARTIAL_NAME",	
    "PGSIO_E_GEN_NO_FREE_LUN",         
    "PGSIO_E_GEN_ILLEGAL_LUN",        
    "PGSIO_W_GEN_UNUSED_LUN",         
    "PGSIO_W_GEN_OLD_FILE",            
    "PGSIO_E_GEN_OPEN_OLD",            
    "PGSIO_E_GEN_OPEN_NEW",           
    "PGSIO_E_GEN_OPEN_UNKNOWN",      
    "PGSIO_E_GEN_OPEN_RECL",          
    "PGSIO_E_GEN_FILE_NODEL",		
    "PGSIO_W_GEN_FILE_NOT_FOUND",
    "PGSIO_E_GEN_CLOSE",       
    "PGSIO_E_GEN_BAD_ENVIRONMENT",	
    "PGSIO_E_L0_BAD_BUF_SIZ",              
    "PGSIO_E_L0_BAD_SPACECRAFT_TAG",      
    "PGSIO_E_L0_FSEEK",                   
    "PGSIO_E_L0_MANAGE_TABLE",             
    "PGSIO_E_L0_PHYSICAL_OPEN",            
    "PGSIO_E_L0_UNEXPECTED_EOF",           
    "PGSIO_E_L0_VIRTUAL_DS_NOT_OPEN",      
    "PGSIO_M_L0_HEADER_CHANGED",          
    "PGSIO_W_L0_PKT_BUF_TRUNCATE",         
    "PGSIO_W_L0_PHYSICAL_CLOSE",           
    "PGSIO_E_L0_INIT_FILE_TABLE",          
    "PGSIO_E_L0_INVALID_FILE_LOGICAL",     
    "PGSIO_E_L0_MAP_VERSIONS",            
    "PGSIO_E_L0_SEEK_1ST_PACKET",          
    "PGSIO_W_L0_TIME_NOT_FOUND",           
    "PGSIO_E_L0_SEEK_PACKET",              
    "PGSIO_E_L0_PHYSICAL_NOT_OPEN",       
    "PGSIO_E_L0_PKT_BUF_OVERFLOW",         
    "PGSIO_W_L0_END_OF_VIRTUAL_DS",        
    "PGSIO_E_L0_NEXT_PHYSICAL",            
    "PGSIO_E_L0_ILLEGAL_COMMAND",          
    "PGSIO_E_L0_ILLEGAL_PACKET_NUM",       
    "PGSIO_E_L0_INDEX_OUT_OF_RANGE",       
    "PGSIO_E_L0_MAX_OPEN_EXCEEDED",        
    "PGSIO_E_L0_MEM_ALLOC",                
    "PGSIO_E_L0_UNUSED_TABLE_ENTRY",       
    "PGSIO_E_L0_VERSION_COUNT",            
    "PGSIO_E_L0_VERSION_INFO",             
    "PGSIO_E_L0_PACKET_NOT_FOUND",        
    "PGSIO_E_L0_TIME_CONVERSION",          
    "PGSIO_E_L0_BAD_FILEINFO",             
    "PGSIO_E_L0_BAD_NUM_PKTS",             
    "PGSIO_E_L0_BAD_APP_ID",               
    "PGSIO_E_L0_BAD_FIRST_PKTNUM",         
    "PGSIO_E_L0_BAD_DATA_LENGTH",          
    "PGSIO_E_L0_BAD_NUM_APP_IDS",          
    "PGSIO_W_L0_HDR_BUF_TRUNCATE",         
    "PGSIO_W_L0_FTR_BUF_TRUNCATE",         
    "PGSIO_W_L0_ALL_BUF_TRUNCATE",         
    "PGSIO_W_L0_BUFTRUNC_END_DS",          
    "PGSIO_W_L0_BUFTRUNC_HDR_CHG",         
    "PGSIO_E_L0_BUFTRUNC_NXTFILE",        
    "PGSIO_W_L0_HDR_TIME_ORDER",          
    "PGSIO_E_L0_BAD_VAR_HDR_SIZE",         
    "PGSIO_W_L0_BAD_PKT_DATA_SIZE",        
    "PGSIO_W_L0_BAD_PACKET_COUNT",         
    "PGSIO_W_L0_BAD_FOOTER_SIZE",          
    "PGSIO_W_L0_ZERO_PACKET_COUNT",       
    "PGSIO_W_L0_CORRUPT_FILE_HDR",
    "PGSPC_E_FILE_OPEN_ERROR",
    "PGSPC_E_INVALID_MODE",
    "PGSPC_W_NO_FILES_EXIST",
    "PGSPC_W_NO_CONFIG_VALUE",
    "PGSPC_E_FILE_READ_ERROR",
    "PGSPC_E_LINE_FORMAT_ERROR", 
    "PGSPC_E_ENVIRONMENT_ERROR", 
    "PGSPC_W_NO_DATA_PRESENT",   
    "PGSPC_E_DATA_ACCESS_ERROR", 
    "PGSPC_W_NO_REFERENCE_FOUND",
    "PGSPC_W_NO_CONFIG_FOR_ID",  
    "PGSPC_W_NO_FILES_FOR_ID",   
    "PGSPC_W_NO_ATTR_FOR_ID",    
    "PGSPC_W_TRUNCATED",         
    "PGSPC_W_ATTR_TRUNCATED",    
    "PGSPC_W_NO_ATTR_MATCH",     
    "PGSPC_W_INVALID_VERSION",   
    "PGSPC_W_FILE_NOT_ON_DISK",  
    "PGSPC_W_NULL_DATA_SHM",     
    "PGSPC_E_INV_DIVPOINTER_SHM",
    "PGSPC_E_EXCEEDED_SHM",      
    "PGSPC_E_NO_DEFAULT_LOC",    
    "PGSPC_E_ENV_NOT_PC",        
    "PGSPC_C_PGSINFO_PGE_START", 
    "PGSPC_C_PGSINFO_PGE_STOP", 
    "PGSPC_C_PGSINFO_TERM_START",
    "PGSPC_M_TOOLKIT_INIT_PASS", 
    "PGSPC_E_TOOLKIT_INIT_FAIL", 
    "PGSPC_M_TOOLKIT_TERM_BEGIN",
    "PGSPC_W_NO_UREF_DATA",
    "PGSMEM_E_MAXSIZE",
    "PGSMEM_E_NO_MEMORY",
    "PGSMEM_E_ADDR_NOTALLOC",
    "PGSMEM_W_MEMORY_USED",  
    "PGSMEM_E_SHM",     
    "PGSMEM_E_SHM_NOTCREATE",
    "PGSMEM_E_SHM_MULTICREATE",
    "PGSMEM_E_SHM_MULTIATTACH",
    "PGSMEM_E_SHM_NOTATTACH",
    "PGSMEM_E_SHM_MAXSIZE",
    "PGSMEM_E_SHM_ENV",
    "PGSMEM_E_SHM_INVALIDKEY",
    "PGSTD_M_ASCII_TIME_FMT_B",
    "PGSTD_M_LEAP_SEC_IGNORED",    
    "PGSTD_M_TIME_TRUNCATED",       
    "PGSTD_W_DATA_FILE_MISSING",    
    "PGSTD_W_JD_OUT_OF_RANGE",      
    "PGSTD_W_PRED_LEAPS",          
    "PGSTD_W_BAD_SC_TIME",          
    "PGSTD_E_BAD_P_FIELD",          
    "PGSTD_E_DATE_OUT_OF_RANGE",    
    "PGSTD_E_MICSEC_TOO_BIG",      
    "PGSTD_E_MILSEC_TOO_BIG",      
    "PGSTD_E_NO_LEAP_SECS",        
    "PGSTD_E_SC_TAG_UNKNOWN",       
    "PGSTD_E_TIME_FMT_ERROR",      
    "PGSTD_E_TIME_VALUE_ERROR",    
    "PGSTD_E_UNIX_ERROR",          
    "PGSTD_E_NO_UT1_VALUE", 
    "PGSTD_E_BAD_2ND_HDR_FLAG",     
    "PGSTD_E_BAD_INITIAL_TIME",    
    "PGSTD_E_BAD_ARRAY_SIZE",      
    "PGSTD_E_SECONDS_TOO_BIG",     
    "PGSTD_E_UTCF_UNINITIALIZED",   
    "PGSTD_E_TMDF_UNINITIALIZED",
    "PGSCBP_E_NO_EPHEMERIS_DATA",    
    "PGSCBP_E_BAD_ARRAY_SIZE",       
    "PGSCBP_E_BAD_TIME_FORMAT",      
    "PGSCBP_E_NO_MEMORY",           
    "PGSCBP_E_BAD_CB_ID",           
    "PGSCBP_E_TIME_OUT_OF_RANGE",    
    "PGSCBP_W_EPHEMERIS_ERROR",      
    "PGSCBP_E_UNABLE_TO_READ_FILE",  
    "PGSCBP_E_UNABLE_TO_OPEN_FILE",  
    "PGSCBP_W_NOT_HEADER",           
    "PGSCBP_E_INVALID_NCOEFF",       
    "PGSCBP_E_NO_OVERLAP",           
    "PGSCBP_W_NO_RECORD_WRITTEN",    
    "PGSCBP_E_INVALID_CB_ID",        
    "PGSCBP_E_NO_LIBRATIONS",        
    "PGSCBP_E_TARG_EQUAL_CENTER",    
    "PGSCBP_E_INVALID_FILE_POS",     
    "PGSCBP_E_READ_RECORD_ERROR",    
    "PGSCBP_E_INVALID_INT_FLAG",     
    "PGSCBP_E_EPOCH_OUT_OF_SPAN",    
    "PGSCBP_E_NO_NUTATIONS",
    "PGSCBP_E_INVALID_BODY",
    "PGSCBP_E_BAD_INITIAL_TIME",
    "PGSCBP_W_EARTH_CB_ID",        
    "PGSCBP_W_BAD_CB_VECTOR",
    "PGSCBP_W_ERROR_IN_BODYINFOV",
    "PGSCSC_W_JD_OUT_OF_RANGE",     
    "PGSCSC_W_DATA_FILE_MISSING",   
    "PGSCSC_E_BAD_DIRECTION_FLAG",  
    "PGSCSC_E_JD_WRONG_EPOCH",      
    "PGSCSC_E_ZERO_INPUT_VECTOR",   
    "PGSCSC_E_BAD_FLAT",            
    "PGSCSC_E_NEG_OR_ZERO_RAD",     
    "PGSCSC_E_BAD_LAT",             
    "PGSCSC_E_BAD_LON",             
    "PGSCSC_W_PROLATE_BODY",        
    "PGSCSC_W_SPHERE_BODY",         
    "PGSCSC_W_BELOW_SURFACE",       
    "PGSCSC_E_BAD_ROT_AXIS_INDEX",  
    "PGSCSC_E_SC_TAG_UNKNOWN",      
    "PGSCSC_E_TRANS_FLAG_ERR",      
    "PGSCSC_E_INVALID_VECTAG",      
    "PGSCSC_W_BELOW_HORIZON",       
    "PGSCSC_E_LOOK_PT_ALTIT_RANGE", 
    "PGSCSC_W_UNDEFINED_AZIMUTH",   
    "PGSCSC_W_SUBTERRANEAN",        
    "PGSCSC_W_TOO_MANY_ITERS",      
    "PGSCSC_W_ZERO_JACOBIAN_DET",   
    "PGSCSC_W_DEFAULT_EARTH_MODEL", 
    "PGSCSC_W_MISS_EARTH",          
    "PGSCSC_W_INSTRUMENT_OFF_BOARD",
    "PGSCSC_W_ZERO_PIXEL_VECTOR",   
    "PGSCSC_W_BAD_ACCURACY_FLAG",   
    "PGSCSC_W_BAD_EPH_FOR_PIXEL",   
    "PGSCSC_E_INACCURATE_UTCPOLE",  
    "PGSCSC_W_INTERIM_UT1",         
    "PGSCSC_W_PREDICTED_UT1",       
    "PGSCSC_E_BAD_QUATERNION",      
    "PGSCSC_W_ERRORS_IN_GHA",       
    "PGSCSC_W_ERROR_IN_DAYNIGHT",   
    "PGSCSC_W_BAD_TRANSFORM_VALUE", 
    "PGSCSC_E_INVALID_LIMITTAG",    
    "PGSCSC_E_BAD_ARRAY_SIZE",      
    "PGSCSC_W_INVALID_ALTITUDE",    
    "PGSCSC_W_LARGE_FLATTENING",    
    "PGSCSC_W_ERROR_IN_SUBSATPT",   
    "PGSCSC_W_NO_REFRACTION",       
    "PGSCSC_E_EULER_REP_INVALID",   
    "PGSCSC_E_EULER_INDEX_ERROR",   
    "PGSCSC_W_ACCURACY_SUSPECT",    
    "PGSCSC_E_QUAT_NOT_FOUND",      
    "PGSCSC_E_INVALID_FOV_DATA",    
    "PGSCSC_E_FOV_TOO_LARGE",       
    "PGSCSC_E_INVALID_EARTH_PT",    
    "PGSCSC_M_EARTH_BLOCKS_CB",     
    "PGSCSC_M_EARTH_BLOCKS_FOV",    
    "PGSCSC_M_CHECK_EARTH_BULGE",  
    "PGSCSC_E_BAD_EARTH_MODEL",     
    "PGSCSC_W_ERROR_IN_EARTHPTFOV", 
    "PGSCSC_E_INVALID_ZENITH",      
    "PGSCSC_E_BELOW_SURFACE",       
    "PGSCSC_E_ABORT_UTCPOLE_UPDATE",
    "PGSCSC_W_ERROR_IN_GRAZINGRAY", 
    "PGSCSC_W_HIT_EARTH",           
    "PGSCSC_W_LOOK_AWAY",
    "PGSEPH_E_SIMULATOR_ERROR",    
    "PGSEPH_W_BAD_EPHEM_VALUE",    
    "PGSEPH_E_BAD_ARRAY_SIZE",     
    "PGSEPH_E_NO_SC_EPHEM_FILE",   
    "PGSEPH_E_BAD_EPHEM_FILE_HDR", 
    "PGSEPH_E_BAD_TIME_ORDER",     
    "PGSEPH_E_NO_DATA_REQUESTED",  
    "PGSEPH_M_SHORT_ARRAY",
    "PGSCUC_E_CANT_GET_FILE_ID",               
    "PGSCUC_E_CANT_OPEN_INPUT_FILE",          
    "PGSCUC_E_AGG_CANT_BE_INSERTED",          
    "PGSCUC_E_READLABEL_PARSE_ERROR",         
    "PGSCUC_E_PARAMETER_INVALID",             
    "PGSCUC_E_FIRST_NODE_NOT_FOUND",          
    "PGSCUC_E__ERROR",                        
    "PGSCUC_E_COULDNT_INIT_UDUNITS3",         
    "PGSCUC_E_DONT_KNOW_INP_UNIT",            
    "PGSCUC_E_DONT_KNOW_OUTP_UNIT",           
    "PGSCUC_E_UNITS_ARE_INCOMPATIBLE",        
    "PGSCUC_E_A_UNIT_IS_CORRUPTED",
    "PGSTD_M_HEADER_UPDATED",
    "PGS_E_TOOLKIT",
    "PGSMET_E_GETSET_ATTRIBUTE_ERROR",
    "PGSMET_M_METADATA_NOT_SET_TK",
    "PGSMET_M_METADATA_NOT_SET_PGE"
};



#endif /* _H_ERR_MASTER_TK_ */

#endif /* __HERR_H_tk */
