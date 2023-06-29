# Student list rating

Implement the compilation of a list of students receiving scholarships. 
The input is the name of the directory inside which all .csv text files should be read. 
The first line of each file contains an integer for the number of students in the file, all other lines have the following format:
`Surname, subject #1,#2,#3,#4,#5, contract student(TRUE/FALSE)`, for example

```csv
2
Brown,78,61,95,87,90,FALSE
Peterson,85,66,70,99,100,TRUE
```

The code parses all of the files inside the given directory (e.g. 1.csv, 2.csv), 
makes one big table, calculates the average score for each state-funded student 
and prints the top 40% of the total student rating + the minimum score to receive a scholarship. 

#### Input and output data
The program takes as input the folder name. The output is a rating.csv file with the names of the scholarship students and their grade point average (to the third decimal place). 
The minimum score for the scholarship is printed to stdout.
The output contains a single result for all files in the input directory.
