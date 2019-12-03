/* Grading Multiple Choice Tests
Tony Griffin & Treston Tedilla
December 2, 2019 */

#include <iostream>
#include <iomanip>
#include <fstream>                                                  //Allows file stream
#include <string>                                                   //Allows strings and string manipulation

using namespace std;

ifstream fteach("testKey.txt");                                     //Input file of the answer key
ifstream fstud("studentAns.txt");                                   //Input file of student's answers
fstream fout("gradeReport.txt");                                    //Final grade of each student

void title();
void students(float &, float &, float &, char);                      //Find individual student grades
void overall(float, float, float &, char);                           //Find overalls
char letterGrade(float, char &);                                     //Find letter grade

string teachName, testInfo, schoolName, correctAns;                 //Declares strings
string lastName, firstName, studAns;

int main() {
    float totalStudents, totalScore, percent; char letter;                 //Declare variables

    title();
    fteach.close();                                                              //Close teacher file
    students(totalStudents, totalScore, percent, letter);                        //Output student's names, answers, and results
    overall(totalStudents, totalScore, percent, letter);                         //Output overall score and results
    fstud.close();                                              //Close student file

    return 0;
}

void title() {
    getline(fteach, teachName); getline(fteach, testInfo); getline(fteach, schoolName); getline(fteach, correctAns);        //Get inputs as lines

    cout << "Page No. 1" << endl; cout << "12/02/2019" << endl << endl;     //Display to console
    cout << setw(38) << "Grades for: " << testInfo << endl;                //getline takes whole line for each string
    cout << setw(38) << "Teacher: " << teachName << endl;
    cout << setw(38) << "School: " << schoolName << endl << endl;

    cout << "STUDENT NAME    | - - - - Q U E S T I O N    N U M B E R - - - - |  R   %   L" << endl;
    cout << setw(26) << "1" << setw(10) << "2" << setw(10) << "3" << setw(10) << "4" << setw(10) << "5" << setw(11) << "A  cor. T" << endl;
    cout << setw(66) << "12345678901234567890123456789012345678901234567890" << setw(3) << "W" << setw(8) << "R" << endl;
    cout << "=============================================================================" << endl;

    cout << "ANSWER KEY" << setw(50) << correctAns << setw(17) << "44 100.0 A" << endl << endl;         //Displays Key

    fout << "Page No. 1" << endl; fout << "12/02/2019" << endl << endl;     //Display to file
    fout << setw(38) << "Grades for: " << testInfo << endl;                //getline takes whole line for each string
    fout << setw(38) << "Teacher: " << teachName << endl;
    fout << setw(38) << "School: " << schoolName << endl << endl;

    fout << "STUDENT NAME    | - - - - Q U E S T I O N    N U M B E R - - - - |  R   %   L" << endl;
    fout << setw(26) << "1" << setw(10) << "2" << setw(10) << "3" << setw(10) << "4" << setw(10) << "5" << setw(11) << "A  cor. T" << endl;
    fout << setw(66) << "12345678901234567890123456789012345678901234567890" << setw(3) << "W" << setw(8) << "R" << endl;
    fout << "=============================================================================" << endl;

    fout << "ANSWER KEY" << setw(50) << correctAns << setw(17) << "44 100.0 A" << endl << endl;         //Displays Key
}

void students(float & totalStudents, float & totalScore, float & percent, char letter) {
    totalScore = 0;                         //Start at 0
    totalStudents = 0;                        //Start at 0

    fstud >> lastName >> firstName >> studAns;              //Input from file

    while (!fstud.eof()) {                          //eof = end of file
        float rawScore = 0;                           //Start at 0

        for(int num = 0; num < correctAns.length(); num++) {            //num = which question you're on
            if(correctAns[num] == studAns[num])                         //Compare student and key answers
                rawScore++;                                             //Add one for every correct answer
        }
        percent = (rawScore / correctAns.length() * 100);               //Find percent score
        letterGrade(percent, letter);                                   //Call letterGrade function
        totalScore = totalScore + rawScore;                             //Find total score of all scores added
        totalStudents++;                                                  //Total amount of questions

        cout << lastName << setw(4) << firstName << "\t" << studAns << setw(9) << fixed << setprecision(0) << rawScore <<        //Outputs
        setw(6) << setprecision(1) << percent << setw(2) << letter << endl;

        fout << lastName << setw(4) << firstName << "\t" << studAns << setw(9) << fixed << setprecision(0) << rawScore <<        //Outputs
        setw(6) << setprecision(1) << percent << setw(2) << letter << endl;

        fstud >> lastName >> firstName >> studAns;                  //Check for more lines, end if eof
    }
    cout << "=============================================================================" << endl;                            //Dividers
    fout << "=============================================================================" << endl;
}

void overall(float totalStudents, float totalScore, float & percent, char letter) {
    float averageRaw = totalScore / totalStudents;                    //Find average of all test scores
    percent = (averageRaw / correctAns.length() * 100);             //Find percent average of all test scores
    letterGrade(percent, letter);                                   //Find letter grade average of all test scores

    cout << "Overall Averages: " << setw(51) << fixed << setprecision(0) << averageRaw <<           //Output to console
    setw(6) << fixed << setprecision(1) << percent << setw(2) << letter << endl;

    fout << "Overall Averages: " << setw(51) << fixed << setprecision(0) << averageRaw <<           //Output to file
    setw(6) << fixed << setprecision(1) << percent << setw(2) << letter << endl;
}

char letterGrade(float percent, char & letter) {	if(percent >= 90.0000)                                                      //Set letter grade based on the TCC grading scale		letter = 'A';        else if(percent >= 80.0000)            letter = 'B';        else if(percent >= 70.0000)            letter = 'C';        else if(percent >= 60.0000)            letter = 'D';
        else if(percent < 60.0000)
            letter = 'F';
}
