# j-pet-ortho-simulations

## Author: Rafał Masełek
## Email: rafal.maselek@ncbj.gov.pl

### Requirements:
+ ROOT 6 (You may have to manually load the environment, if it is not set in *~/.bashrc* To learn how to do it see ROOT installation manual.
+ GCC > 4.9 (default version on NCBJ cluster is too old, load 4.9.4 instead)
+ Unix (tested on Kubuntu 16.04)

### Installation:
To build the application download all files from the repository into a destination folder. Cd to that folder
and type *make* in the bash console.

### Running:
To run the application type 
>./sim -i param_file -n output_subfolder_name

**param_file** is a path to a file, where simulation parameters are stored. If the flag '-i'  is not provided, the program will try to read file "simpar.par".
**output_subfolder_name** is also a name of the root file if tree output is selected. if the flag '-n' is not provided, system's date and time will be used.

### Changing the simulation parameters
For details see simpar.par file.

### Results 
By deault all results will be saved to the *results/* directory. You can change it by editing src/simulate.cpp file. There is static variable at the beginning of the file called:
_globalPrefix_, .

### Documentation
Documentation can be generated by user, see README.md in the doc/ directory. Comments inside the code are also provided for developers and advanced users. 
