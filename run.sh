clear
rm -fr build
mkdir build
cd build
cmake ..
make
# ls
clear
# export OMP_NUM_THREADS=4
./exercice_3
cd ..