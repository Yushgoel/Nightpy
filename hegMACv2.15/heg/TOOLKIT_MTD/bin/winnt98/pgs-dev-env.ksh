# pgs-dev-env.ksh
# Clear all conditional flags
sgi_mode=""
pgs_daac=""
pgs_f90_comp=""
pgs_nag_flag=""
# set the toolkit home directory environment variable
# Toolkit installation done on Wed Jul 10 10:37:46  2002 
# 
 
PGSHOME=/home/ataaheri/New_TOOLKIT_MTD/TOOLKIT_MTD	# set the toolkit home directory
 
#-----------------------------------------------------------------------------
# file:	
# 	pgs-dev-env.ksh
#
# description:
# 	This file defines environment variables used by SDP (PGS) Toolkit.
# 	This version is for use under the Korn shell (ksh).
#
# usage:
# 	This file should be called from your .profile file with the line:
#
# 	    . <toolkit-home-dir>/bin/pgs-dev-env.ksh
#	
# 	where <toolkit-home-dir> is the full path of the toolkit home directory.
#
# author:
# 	Mike Sucher / A.R.C.
#       Guru Tej S. Khalsa / Applied Research Corporation
#
# notes:
# 	1) This file is compatible with the following platforms:
# 	   Sun, SGI, HP-9000, IBM RS-6000, DEC Alpha and Cray.
# 	   It automatically figures out which platform you are on,
# 	   and sets environment variables accordingly.
# 	2) (OPTIONAL) if HDF is installed on your system, you may 
# 	   wish to edit the line near the end of this file that sets
# 	   up the environment variable HDFHOME.
# 	3) This file adds the PGS bin (and optionally the HDF bin) 
#	   directory to the 'path'  environment variable.
# 	4) This file defines a variable called pgs_path which contains
# 	   all the directories likely to be needed on a given machine
# 	   type, including the PGS (and HDF) bin directories.  Users 
# 	   may choose to set their path variable with:
# 	   
# 	           PATH=<user-path-additions>:$pgs_path
# 	           export PATH
#
# 	   where <user-path-additions> is an optional list of other
# 	   directories added to the search path.
#
# history:
#	03-May-1995 MES  Initial version for TK5 - adapted from pgs-dev-env.csh
# 	09-May-1995 MES  Updated compiler flags for Release 5:
# 			   hp:                        ibm:
# 			   C_CFH:   remove -Dextname  C_CFH:   remove -Dextname
# 			   F77_CFH: remove +ppu       F77_CFH: remove -qextname
# 			 Note: this change was made to facilitate binding with
# 			 heritage code libraries.  Caution:  the cfortran.h 
# 			 bindings can ONLY be used with mixed-case C function
# 			 names.  Otherwise the bindings will not work.
#	15-Jun-1995 GTSK Added support for IRIX64, the sgi 64 bit O/S.
#			 This script will install the toolkit in 32 bit mode.
#	10-Jul-1995 MES  Removed flags "-h stdc" from Cray CFLAGS.
#	18-Aug-1995 MES  Revised environment for formal track directory
# 			 structure used by the DAAC version Toolkit for IR-1.
# 	31-Aug-1995 MES  Updated IRIX64 OS support to recognize both 32 and 64
# 			 bit modes.  Default is is 32-bit.  New BRAND setting
# 			 sgi64 supports the SGI 64 bit mode.
# 	30-Oct-1995 MES  Updates for IR-1 release:
# 			 - add support for SGI compiled -n32 ($BRAND = sgi32)
# 			 - formal directory structure is now set by pgs_formal
# 			 - revise PGSRUN: no longer architecture-specific
#  			 - set PGS_PC_INFO_FILE to $PGSRUN/$BRAND/PCF.ir1
# 	21-Nov-1995 MES  Handle the DAAC toolkit compilation.
# 	22-Nov-1995 MES  Add code to handle FORTRAN-90 compiler.
# 	15-Apr-1996 MES  Updates for Release A
#  			 - clear DAAC version env variables, if not used
#  			 - set PGS_PC_INFO_FILE to $PGSRUN/$BRAND/PCF.relA
# 	26-Aug-1996 MES  Updates for Release A
#  			 - update DAAC version logic
#  			 - update HDF environment variables setup
#
#-----------------------------------------------------------------------------

: ${sgi_mode:=32}	# by default, SGI mode is standard 32-bit

: ${pgs_daac:=0}	# by default, DAAC toolkit version disabled

: ${pgs_f90_comp:=""}	# by default, no FORTRAN-90 compiler

: ${pgs_nag_flag:=0}	# by default, not using NAG FORTRAN-90

: ${use_flavor:=0}	# by default, do not use "flavors"


user_path=$PATH		# save user path

# set path to a base subset of directories, allowing startup on unknown host
# note: once the host has been determined the path is appropriately customized

PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/etc:/usr/ucb:/usr/bin/X11
export PATH

# get operating system type, login name
# special cases: SCO and Cray  - uname works differently,

MACHINE="`uname -m | awk '{print $1}'`"	# needed on Cray & SCO

case "$MACHINE" in

    i386)        			# SCO box
        OSTYPE=sco386 
        ;;

    i686)        			# SCO box
        OSTYPE=sco686 
        ;;

    CRAY) 				# CRAY
        OSTYPE=UNICOS 
        ;;

    *)     				# everybody else
        OSTYPE="`uname`"
        ;;

esac

user=`id | cut -d\( -f2 | cut -d\) -f1`
LOGNAME=$user				# make sure $LOGNAME is defined
USER=$LOGNAME				# make sure $USER is defined
export USER LOGNAME

# set machine-dependent environment variables:
# 	HOST   the host name of this machine
# 	BRAND  used by other achitecture-specific code
# 	PATH   the execution search path 

case "$OSTYPE" in

  AIX) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/etc:/usr/ucb:/usr/bin/X11:/usr/sbin
    HOST="`hostname`"
    BRAND="ibm"
    ;;

  HP-UX) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/bin/X11
    HOST="`hostname`"
    BRAND="hp"
    ;;

  IRIX) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/etc:/usr/bsd:/usr/sbin
    HOST="`hostname`"
    BRAND="sgi"
    ;;

  IRIX64) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/etc:/usr/bsd:/usr/sbin
    HOST="`hostname`"
    case $sgi_mode in
      64 ) BRAND=sgi64 ;;
      n32) BRAND=sgi32 ;;
      32 ) BRAND=sgi ;;
      *  ) BRAND=sgi ;;  # just in case
    esac
    ;;

  Linux) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/X11/bin
    HOST="`hostname`"
    BRAND="linux"
    ;;

  OSF1) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/etc:/usr/ucb:/usr/bin/X11:/usr/sbin
    HOST="`hostname -s`"
    BRAND="dec"
    ;;

  sco386) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/bin/X11
    HOST="`hostname -s`"
    BRAND="sco"
    ;;

  sco686) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/bin/X11
    HOST="`hostname -s`"
    BRAND="winnt98"
    ;;

  SunOS) 
    # distinguish between SunOS 5.x and 4.x versions
    if [ `uname -r | awk -F. '{print $1}'` = "5" ] ; then 
        BRAND="sun5"			# release V5.x SunOS
        PATH=/usr/local/bin:/opt/SUNWspro/bin:/bin:/usr/bin:/etc:/usr/etc:/usr/ucb:/usr/openwin/bin:/usr/openwin/demo:/usr/sbin
    else                                
        BRAND="sun4"			# release V4.x SunOS
        PATH=/usr/local/bin:/usr/local/lang:/usr/lang:/bin:/usr/bin:/etc:/usr/etc:/usr/ucb:/usr/openwin/demo
    fi
    HOST="`hostname`"
    ;;

  UNICOS) 
    PATH=/usr/local/bin:/bin:/usr/bin:/etc:/usr/bin/X11
    HOST="`hostname`"
    BRAND="cray"
    ;;

  *)	
    echo "Operating system: $OSTYPE not supported"
    echo "This release of the PGS Toolkit supports: "
    echo "   Sun, SGI HP-9000 IBM-6000 DEC-Alpha and Cray/Unicos "
    ;;

esac

export PATH HOST BRAND


# set machine-dependent compilers and compilation switches:
#
#

case "$BRAND" in

    cray)
	CC=cc 			# C compiler
	CFLAGS="-O" 		# default C flags (optimize, ansi)
	C_CFH="-DCRAYFortran"   # C/cfortran.h called from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=cf77		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main 
	HDFSYS=UNICOS		# system type as defined by HDF
	;;

    dec)
	CC=cc 			# C compiler
	CFLAGS="-O -std"	# default C flags (optimize, ansi)
	C_CFH="-DDECFortran"	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=f77 		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""            # calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=DEC_ALPHA	# system type as defined by HDF
	;;

    hp)
	CC=cc 			# C compiler
	CFLAGS="-O -Ae" 	# default C flags (optimize, ansi)
	C_CFH="" 		# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=fort77		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=HP9000		# system type as defined by HDF
	;;

    ibm)
	CC=cc 			# C compiler
	CFLAGS="-O -qlanglvl=ansi" # default C flags (optimize, ansi)
	C_CFH="" 		# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=xlf 		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=IBM6000		# system type as defined by HDF
	;;

    linux)
	CC=gcc 			# C compiler
	CFLAGS="-O -ansi"	# default C flags (optimize, ansi)
	C_CFH="-Df2cFortran"	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=f77			# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=LINUX		# system type as defined by HDF
	;;

    sco)
	CC=cc 			# C compiler
	CFLAGS="-O -posix"	# default C flags (optimize, ansi)
	C_CFH="-Df2cFortran"	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=""			# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=SCO		# system type as defined by HDF
	;;

    winnt98 )

	CC=gcc 			# C compiler
	CFLAGS="-O3 -Wall -W -Wundef -Wno-switch"	# default C flags (optimize, ansi)
	C_CFH="-Df2cFortran"	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	HDFSYS=CYGWIN		# system type as defined by HDF
	;;

    sgi)
	if [ $OSTYPE = "IRIX64" ] ; then
		CC="cc -32"	# C compiler (32 bit)
		F77="f77 -32"	# FORTRAN compiler (32 bit)
        else
		CC=cc		# C compiler
		F77=f77		# FORTRAN compiler
    fi
	CFLAGS="-O -xansi -D_POSIX_SOURCE"	# default C flags (optimize, ansi)
	C_CFH=""	 	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=IRIX		# system type as defined by HDF
	;;

    sgi32)
	CC="cc -n32"		# C compiler (new-style 32 bit)
	F77="f77 -n32"		# FORTRAN compiler (new-style 32 bit)
	CFLAGS="-O -xansi -D_POSIX_SOURCE"	# default C flags (optimize, ansi)
	C_CFH=""	 	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=IRIX		# system type as defined by HDF
	;;

    sgi64)
	cpu_type=`hinv | fgrep CPU | head -1 | cut -d' ' -f3 | cut -b2`
	if [ "$cpu_type" = "4" ] ; then
	    CC="cc -64 -mips3"		# C compiler (R4?00 chip)
	    F77="f77 -64 -mips3"	# FORTRAN compiler (R4?00 chip)
        else
            CC="cc -64"      	# C compiler
            F77="f77 -64"    	# FORTRAN compiler
        fi
	CFLAGS="-O -xansi -D_POSIX_SOURCE"	# default C flags (optimize, ansi)
	C_CFH=""	 	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""          	# calling C w/ cfortran.h
	F77_C_LIB=""		# C lib called by FORTRAN main
	HDFSYS=IRIX		# system type as defined by HDF
	;;

    sun4)
	CC=acc			# C compiler
	CFLAGS="-O -Xa" 	# default C flags (optimize, ansi)
	C_CFH="-DsunFortran"	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=f77 		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""           	# calling C w/ cfortran.h
	F77_C_LIB="-lm" 	# C lib called by FORTRAN main
	HDFSYS=SUN		# system type as defined by HDF
	;;

    sun5)
	CC=cc			# C compiler
	CFLAGS="-O -Xa" 	# default C flags (optimize, ansi)
	C_CFH="-DsunFortran"	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=f77 		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""           	# calling C w/ cfortran.h
	F77_C_LIB="-lm" 	# C lib called by FORTRAN main
	HDFSYS=SUN		# system type as defined by HDF
	;;

    *)
	CC=cc			# C compiler
	CFLAGS="-O" 		# default C flags (optimize)
	C_CFH=""	# C w/ cfortran.h callable from FORTRAN
	CFHFLAGS="$CFLAGS $C_CFH" # CFLAGS + C_CFH
	F77=f77 		# FORTRAN compiler
	F77FLAGS="-O" 		# common FORTRAN flags
        F77_CFH=""              # FORTRAN callable from C w/ cfortran.h
	F77_C_CFH=""           	# calling C w/ cfortran.h
	F77_C_LIB="-lm" 	# C lib called by FORTRAN main
	HDFSYS=unknown		# system type as defined by HDF
	;;
esac

export CC CFLAGS C_CFH CFHFLAGS F77
export F77FLAGS F77_CFH F77_C_CFH F77_C_LIB HDFSYS


# 
# set up environment to handle FORTRAN-90 compiler
#

if [ "$pgs_f90_comp" != "" ] ; then		# using FORTRAN-90

    F77="$pgs_f90_comp"

    if [ "$pgs_nag_flag" = "1" ] ; then		# using NAG f90
        C_CFH="$C_CFH -DNAGf90F"
        CFHFLAGS="$CFLAGS $C_CFH"
    fi

    export CFHFLAGS C_CFH F77

fi


# copy the machine-specific path to variable pgs_path

pgs_path=$PATH

# set PGS-related environment variables
# these may be referred to in makefiles and on compiler command lines

if [ "$PGSHOME" != "" ] ; then

# set up base set of PGS Toolkit directory variables.

    PGSBIN=$PGSHOME/bin/$BRAND		# executable files
    PGSDAT=$PGSHOME/database/$BRAND	# database files
    PGSINC=$PGSHOME/include		# include header files
    PGSLIB=$PGSHOME/lib/$BRAND 		# library files
    PGSMSG=$PGSHOME/message		# SMF message files
    PGSOBJ=$PGSHOME/obj/$BRAND		# object files
    PGSRUN=$PGSHOME/runtime		# runtime work files
    PGSSRC=$PGSHOME/src			# toolkit source files
    PGSTST=$PGSHOME/test		# test source files

    if [ "$use_flavor" = 1 ] ; then
        PGSBIN=${PGSBIN}_${flavor}		# executable files
        PGSLIB=${PGSLIB}_${flavor}  		# library files
        PGSOBJ=${PGSOBJ}_${flavor}		# object files

    fi


    export PGSHOME PGSBIN PGSDAT PGSINC PGSLIB 
    export PGSMSG  PGSOBJ PGSRUN PGSSRC PGSTST

# update path variables

    PATH=$PATH:$PGSBIN; export PATH		# add PGSBIN to path
    pgs_path=$pgs_path:$PGSBIN			# add PGSBIN to pgs  path
    user_path=$user_path:$PGSBIN		# add PGSBIN to user path

# set up variables needed by Process Control (PC) tools. 
# user may customize these in their private .cshrc file

#    PGS_PC_INFO_FILE=$PGSRUN/$BRAND/PCF.relB0 

#    export PGS_PC_INFO_FILE 



else

    echo "You must first set the environment variable PGSHOME"

fi


# set HDF-related environment variables
# these may be referred to in makefiles and on compiler command lines
# use the command 'sethdf <hdf-home-directory> to override the default

####
#
#
# if your site has HDF installed:
#    uncomment the next line and edit it to properly 
#    set your HDF home directory
#
####

HDFHOME=/home/ataaheri/New_TOOLKIT_MTD/TOOLKIT_MTD/hdf/winnt98/HDF4.1r5	# set HDF home directory

if [ $use_flavor = 1 ] ; then
    case $flavor in
	*debug)
	    hdfhome=`echo $HDFHOME | sed "s/${BRAND}/${BRAND}_debug/"`
	    if [ -d $hdfhome ] ; then
		HDFHOME=$hdfhome
	    fi
	;;
    esac
fi

#
# Set HDF directories:
#
# - first look in $HDFHOME
# - if not found, default to $HDFHOME/hdf
#

if [ "$HDFHOME" != "" ] ; then

    if [ -d $HDFHOME/bin ] ; then	# HDF utilities
        HDFBIN=$HDFHOME/bin
    else
        HDFBIN=$HDFHOME/hdf/bin
    fi

    if [ -d $HDFHOME/include ] ; then	# HDF header files
        HDFINC=$HDFHOME/include
    else
        HDFINC=$HDFHOME/hdf/include
    fi

    if [ -d $HDFHOME/lib ] ; then	# HDF libraries
        HDFLIB=$HDFHOME/lib
    else
        HDFLIB=$HDFHOME/hdf/lib
    fi
		
    export HDFBIN HDFINC HDFLIB

    pgs_path=$pgs_path:$HDFBIN		# add HDFBIN to pgs  path
    user_path=$user_path:$HDFBIN	# add HDFBIN to user path

fi


####
#
#
# if your site has HDF-EOS installed:
#    uncomment the next line and edit it to properly 
#    set your HDF-EOS home directory
#
####

HDFEOS_HOME=/home/ataaheri/New_TOOLKIT_MTD/TOOLKIT_MTD/hdfeos	# set HDF-EOS home directory

#
# Set HDF-EOS directories:
#

if [ "$HDFEOS_HOME" != "" ] ; then

    HDFEOS_INC=$HDFEOS_HOME/include
    HDFEOS_LIB=$HDFEOS_HOME/lib/$BRAND
    HDFEOS_BIN=$HDFEOS_HOME/bin/$BRAND

    if [ $use_flavor = 1 ] ; then
	case $flavor in
	    *debug)
		if [ -d ${HDFEOS_LIB}_debug ] ; then
		    HDFEOS_LIB=${HDFEOS_LIB}_debug
		    HDFEOS_BIN=${HDFEOS_BIN}_debug
		fi
	    ;;
	esac
    fi
    export HDFEOS_HOME HDFEOS_INC HDFEOS_LIB HDFEOS_BIN
fi

#
# check to see if DAAC version of the toolkit was installed
#

ADD_IFLAGS="" ; export ADD_IFLAGS 	# make sure old values are gone
ADD_LFLAGS="" ; export ADD_LFLAGS 	# make sure old values are gone
ADD_LIBS=""   ; export ADD_LIBS 	# make sure old values are gone

if [ "$pgs_daac" = "1" ] ; then 	# yes, modify build flags

    CFLAGS="$CFLAGS -DPGS_DAAC"
    CFHFLAGS="$CFHFLAGS -DPGS_DAAC"
    export CFLAGS CFHFLAGS

fi


if [ "$ECS_VERSION" != "" ] ; then

    VFLAG="'-DPGSd_ECS_VERSION="'"${ECS_VERSION}"'"'"
    export VFLAG

fi

#
# restore augmented user path
#
PATH=$user_path ; export PATH

PGSLIB=$HOME/heg/lib/cygwin
PGSINC=$HOME/heg/TOOLKIT_MTD/include
#HDFINC=$HOME/heg/TOOLKIT_MTD/hdf/include
HDFINC=$HOME/heg/resample/include
#HDFEOS_INC=$HOME/heg/TOOLKIT_MTD/hdfeos/include
HDFEOS_INC=$HOME/heg/resample/include

MRTDATADIR=C:\\cygwin\\home\\cpradera\\heg\\data
MRTBINDIR=C:\\cygwin\\home\\cpradera\\heg\\bin
PGSHOME=C:\\cygwin\\home\\cpradera\\heg\\TOOLKIT_MTD

export PGSLIB PGSINC HDFINC HDFEOS_INC MRTDATADIR MRTBINDIR PGSHOME


# done

