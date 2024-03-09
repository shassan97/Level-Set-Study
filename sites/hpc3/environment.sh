echo "Loading environment.sh for sites/hpc3"

export OMP_NUM_THREADS=1
export UCX_TLS=rc,mm
export UCX_NET_DEVICES=mlx5_0:1

# Load GCC openmpi and python
module load gcc/11.2.0
module load openmpi/4.1.2/gcc.11.2.0
module load python/3.8.0
source /pub/sheikhh1/envs/flashx/bin/activate

# Set MPI_HOME by quering path loaded by site module
export MPI_HOME=$(which mpicc | sed s/'\/bin\/mpicc'//)


# Load HDF5 module in desired configuration if available. If not specified
# the HDF5 will be built when setting up software
#module load hdf5/1.10.7

# Path to parallel HDF5 installtion with fortran support
#export HDF5_HOME=$(which h5pfc | sed s/'\/bin\/h5pfc'//)

# load git-lfs
#module load git-lfs
