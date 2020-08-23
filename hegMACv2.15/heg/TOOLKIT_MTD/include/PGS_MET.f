!----------------------------------------------------------------------------!
!									     !
!	COPYRIGHT	1994, 1995, 1996     Applied Research Corporation    !
!									     !
!			1997, 1998	     Space Applications Corporation  !
!									     !
!			ALL RIGHTS RESERVED				     !
!									     !
!----------------------------------------------------------------------------!
!-----------------------------------------------------------------------------
! BEGIN_FILE_PROLOG:
!
! FILENAME:
!
!       PGS_MET.f
!
! DESCRIPTION:
!
!       This file contains all the various definitions 
!       that are required by the user
!
! AUTHOR:
!       Alward Siyyid
!       Carol S. W. Tsai / Space Applications Corporation
!
! HISTORY:
!       15-Jun-95 ANS Initial version
!	18-Mar-96 ANS updated for tk5+
!       26-Nov-97 CSWT Added new ddfinition for strings "PGSd_MET_MAX_STRING_SET_L"
!                      and "PGSd_MET_MAX_ARRAY_ELEMENT_SIZE"
!
! END_FILE_PROLOG:
!-----------------------------------------------------------------------------
!       GCT toolkit definitions
!-----------------------------------------------------------------------------
        INTEGER PGSd_MET_NAME_L
        PARAMETER (PGSd_MET_NAME_L = 100)

        INTEGER PGSd_MET_MAX_STRING_SET_L 
        PARAMETER (PGSd_MET_MAX_STRING_SET_L = 255)

        INTEGER PGSd_MET_MAX_ARRAY_ELEMENT_SIZE 
        PARAMETER (PGSd_MET_MAX_ARRAY_ELEMENT_SIZE = 1000)

        INTEGER PGSd_MET_NUM_OF_GROUPS
        PARAMETER (PGSd_MET_NUM_OF_GROUPS = 20)

        INTEGER PGSd_MET_GROUP_NAME_L
        PARAMETER (PGSd_MET_GROUP_NAME_L = 104)

        INTEGER PGSd_MET_INT_MAX
        PARAMETER (PGSd_MET_INT_MAX = 2147483647)

        DOUBLE PRECISION PGSd_MET_DBL_MAX
        PARAMETER (PGSd_MET_DBL_MAX = 1.797693D308)

        INTEGER PGSd_MET_MCF_FILE
        PARAMETER (PGSd_MET_MCF_FILE = 10250)

        CHARACTER PGSd_MET_STR_END*1
        PARAMETER (PGSd_MET_STR_END = '$')
