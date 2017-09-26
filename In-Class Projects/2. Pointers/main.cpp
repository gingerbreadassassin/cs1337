/*
 * Connor Ness - cdn073000
 * Kaleb  Warneke - ktw160030
 * 02/16/17
 */

#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

int getQuestionCount();
void getAnswerKey(ifstream&, char*, int);
void getTest(ifstream&, string&, char*, int);
void writeStudent(string, char*, double, int);
char calcLetter(double, int);
float gradeCalc(char*, char*, int);

int main()
{
    int questions = getQuestionCount();
    ifstream in("test.txt");

    //create dynamic arrays
    char *answerKey = new char[questions];
    char *studentAnswer = new char[questions];
    //read answer key
    getAnswerKey(in, answerKey, questions);



    //loop through file
    string studentID;
    while(!in.eof())
    {
        //read student answers on a line
        in >> studentID;
        getTest(in, studentID, studentAnswer, questions);
        double grade = gradeCalc(answerKey, studentAnswer, questions);
        //output grade
        writeStudent(studentID, studentAnswer, grade, questions);
    }
    in.close();
    delete[]answerKey;
    delete[]studentAnswer;
    return 0;
}

int getQuestionCount()
{
    ifstream in("test.txt");
    string line;
    getline(in, line);
    in.close();
    return (int)line.length();

}

void getAnswerKey(ifstream &in, char* key, int count)
{
    string line;
    for (int i=1; i <= count; i++)
    {
        in.get(*key);
        key++;
    }
    getline(in, line);  //move the file pointer to beginning of next line
    //pointer is passed by value, so I don't have to worry about moving the pointer back
}

void getTest(ifstream &in, string &ID, char* answers, int count)
{
    //get one student ID and answers
    string line;
    for (int i=1; i <= count; i++)
    {
        in.get(*answers);
        answers++;
    }
    getline(in, line);

}

void writeStudent(string ID, char* answers, double grade, int count)
{
   //write one student ID, answers and grade (letter and numeric)
    ofstream out("grades.txt", ios::app);
    out << ID << '\t';

    for(int i = 0; i<=count; i++)
    {
        out << *answers;
        answers++;
    }

    out << '\t' << grade << '\t' << calcLetter(grade, count) << '\n';
    out.close();
}

char calcLetter(double grade, int count)
{
    double percGrade = (grade/count) * 100;
    //determine letter grade
    // >90 A
    if(percGrade > 90.00)
        return 'A';
    // 80-89.99 B
    else if(percGrade >= 80.00 && grade < 90.00)
        return 'B';
    // 70-79.99 C
    else if(percGrade >= 70.00 && grade < 80.00)
        return 'C';
    // 60-69.99 D
    else if(percGrade >= 60.00 && grade < 70.00)
        return 'D';
    // <59.99 F
    else
        return 'F';
}

float gradeCalc(char* rKey, char* answers, int count)
{
    //check answers and calculate grade
    // compare each element of answers against key
    float grade = 0;
    for(int i = 0; i <= count; i++)
    {
        char answer = *answers;
        char key = *rKey;
        if(answer == key)
            grade += 2;
        else if(answer == ' ')
        {
            answers++;
            rKey++;
            continue;
        }
        else
            grade--;
        answers++;
        rKey++;
    }
    return grade;
}
