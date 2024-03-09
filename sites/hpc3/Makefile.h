#----------------------------------------------------------------------------
# Flash-X Makefile definitions for (x86-64 Ubuntu)
#----------------------------------------------------------------------------

#----------------------------------------------------------------------------
# Set the HDF5/MPI library paths -- managed by loading with Spack 
#----------------------------------------------------------------------------
HDF5_PATH    = $(HDF5_HOME)
HYPRE_PATH   = $(HYPRE_HOME)
MPI_PATH     = $(MPI_HOME)
ZLIB_PATH    =
PAPI_PATH    =
NCMPI_PATH   =
AMREX_PATH   = $(AMREX$(NDIM)D_HOME)
ANN_PATH     = $(ANN_HOME)

#----------------------------------------------------------------------------
# Compiler and linker commands
#
#   Use the parallel HDF5 wrappers which use the mpiXX compiler wrappers 
#   -- these will automatically load the proper libraries and include files.
#--------------I${subst :, -I,$(CPATH)}--------------------------------------------------------------
FCOMP   = $(HDF5_PATH)/bin/h5pfc
CCOMP   = $(HDF5_PATH)/bin/h5pcc
CPPCOMP = $(MPI_PATH)/bin/mpicxx
LINK    = $(HDF5_PATH)/bin/h5pfc -std=c++14

# pre-processor flag
PP      = -D

#----------------------------------------------------------------------------
# Compilation flags
#
#  Three sets of compilation/linking flags are defined: one for optimized
#  code, one for testing, and one for debugging.  The default is to use the
#  _OPT version.  Specifying -debug to setup will pick the _DEBUG version,
#  these should enable bounds checking.  Specifying _TEST is used for
#  flash_test, and is set for quick code generation, and (sometimes)
#  profiling.  The Makefile generated by setup will assign the generic token
#  (ex. FFLAGS) to the proper set of flags (ex. FFLAGS_OPT).
#----------------------------------------------------------------------------
FFLAGS_OPT   = -c -O2 -fdefault-real-8 -fdefault-double-8 -fallow-argument-mismatch -Wuninitialized #\
               #-Wno-argument-mismatch -ftree-vectorize -funroll-loops -fprefetch-loop-arrays


FFLAGS_DEBUG = -ggdb -c -O0 -fdefault-real-8 -fdefault-double-8 \
	       -pedantic -Wall -Wextra -Wno-do-subscript -Wno-unused -Waliasing \
	       -Wsurprising -Wconversion -Wunderflow \
	       -ffpe-trap=invalid,zero,overflow -fbounds-check \
	       -fimplicit-none -fstack-protector-all \
	       -fbacktrace -fbounds-check

FFLAGS_TEST  = -ggdb -c -fdefault-real-8 -fdefault-double-8 \
	       -ffree-line-length-none

FFLAGS_HYPRE = -I${HYPRE_PATH}/include
FFLAGS_AMREX = -I${AMREX_PATH}/include
FFLAGS_ANN   = -I${ANN_PATH}/include
FFLAGS_HDF5  = -DH5_USE_18_API
F90FLAGS     =

#------------------------------------------------------------------------------
# The macro _FORTIFY_SOURCE adds some lightweight checks for buffer
# overflows at both compile time and run time (only active at -O1 or higher)
# http://gcc.gnu.org/ml/gcc-patches/2004-09/msg02055.html
#-------------------------------------------------------------------------------
CFLAGS_OPT   = -c -O2 -Wuninitialized -D_FORTIFY_SOURCE=2

CFLAGS_DEBUG = -ggdb -c -O0 -Wno-div-by-zero -Wundef \
	       -Wconversion -Wstrict-prototypes -Wunreachable-code \
	       -pedantic -Wall -Wextra -Winit-self -ftree-vrp -Wfloat-equal \
	       -Wunsafe-loop-optimizations -Wpadded -fstack-protector-all

CFLAGS_TEST  = -c

CFLAGS_HDF5  = -DH5_USE_18_API
CFLAGS_AMREX = -I${AMREX_PATH}/include
CFLAGS_ANN   = -I${ANN_PATH}/include
CFLAGS_HYPRE = -I${HYPRE_PATH}/include
PAPI_FLAGS   = 

#----------------------------------------------------------------------------
# Linker flags
#
#  There is a seperate version of the linker flags for each of the _OPT,
#  _DEBUG, and _TEST cases.
#----------------------------------------------------------------------------

LFLAGS_OPT   = -o
LFLAGS_DEBUG = -g -O0 -o
LFLAGS_TEST  = -o

#----------------------------------------------------------------------------
# Library specific linking
#
#  If a FLASH module has a 'LIBRARY xxx' line in its Config file, we need to
#  create a macro in this Makefile.h for LIB_xxx, which will be added to the
#  link line when FLASH is built.  This allows us to switch between different
#  (incompatible) libraries.  We also create a _OPT, _DEBUG, and _TEST
#------------------------------------------------------------------------------

LIB_OPT    =
LIB_DEBUG  =
LIB_TEST   =

LIB_HDF5   =
LIB_PAPI   =
LIB_MATH   =
LIB_MPI    = 
LIB_MPE    =
LIB_NCMPI  =
LIB_HYPRE  = -L${HYPRE_PATH}/lib -lHYPRE
LIB_AMREX  = -L${AMREX_PATH}/lib -lamrex -lpthread
LIB_BITTREE = 
LIB_ANN    = -L${ANN_PATH}/lib -lANN
LIB_STDCXX = -lstdc++
LIB_LAPACK = -llapack -lblas

# Uncomment the following line to use electic fence memory debugger.
# Need the following environmental variable (see env.sh):
# export EF_ALLOW_MALLOC_0=1
#CONFIG_LIB = -L/usr/lib64 -lefence

#----------------------------------------------------------------------------
# Additional machine-dependent object files
#
#  Add any machine specific files here -- they will be compiled and linked
#  when FLASH is built.
#----------------------------------------------------------------------------

MACHOBJ =

#----------------------------------------------------------------------------
# Additional commands
#----------------------------------------------------------------------------

MV = mv -f
AR = ar -r
RM = rm -f
CD = cd
RL = ranlib
ECHO = echo

