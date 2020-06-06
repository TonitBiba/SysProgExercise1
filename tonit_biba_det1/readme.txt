#Covid application to manage list of patients infected with Covid-19.

## Requirements
    In order to use this application you must install:
        1. GCC compiler (sudo apt-get install gcc);
        2. Doxygen (sudo apt-get install doxygen);
        3. Splint for static check (sudo apt-get install splint);
        4. Valgrind for checking memory leaks (sudo apt-get install valgrind).

## Installation
    sudo make all    (this command will compile and generate executable application);

## Usage
    In order to use and test application you must follow list of commands below:
        1) ./output/exe/covid -h  (to see synopsis for this application);
        2) ./output/exe/covid -f patient.db -a  (this command will execute application, will create new file with name patient.db (if not exist) in application root directory.
                                             . The application will ask you to write personal number, name, surname, address, age and test date.);
        3) ./output/exe/covid -f patient.db -l  (this command will list all patients that are registered in patient.db file.);
        4)  sudo valgrind --track-origins=yes ./output/exe/covid -f patient.db -a -l 2>&1 | sudo tee ./output/ml_report.txt  (will test for memory leaks.);

## Optionally:
    5) ./output/exe/covid -f patient.db -a -p 1234567890 -n Tonit -s Biba -m 23 -c Kosove -d 12/12/2020./output/exe/covid -f patient.db -l  (You can specifi patient data using options and arguments.)

Tonit Biba
06.06.2020