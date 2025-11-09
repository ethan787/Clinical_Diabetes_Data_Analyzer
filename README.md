In order to run our project you have to donwload the following:
-> Install Qt Creator
-> Have a Github Account
-> install the CSV file and insert it into the program's build folder if it isn't there already
Once everything is set you have to clone the repository by clicking new project in Qt Creator and then cloning from the Github Repository.
After doing so, you can run the program but cannot access the graphs since the data is not inserted. 
Therefore, downlaod the CSV file from https://www.kaggle.com/datasets/ziya07/diabetes-clinical-dataset100k-rows and insert it into the build folder of the project in your files.
After doing so, the project should run fine and be able to be launched properly.

If you get an error here are some fixes:
->Delete the build folder 
->Delete the CMakeLists.txt.user file
->Rebuild the project with ctrl + b, and insert the CSV file again
