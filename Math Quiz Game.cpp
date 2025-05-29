#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // to intialize generater of random Numbers 
using namespace std;
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel =3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp= 5 };
struct stQuestions
{
    int Number1 = 0;
    int Number2 = 0;
    enOperationType OperationType ;
    enQuestionsLevel QuestionLevel ;
    int CorrectAnswer = 0;
    int PlayAnswer = 0 ;
    bool AnswerResult = false ;

};
struct stQuizz 
{
    stQuestions QuestionList[100] ;
    short NumberOfQuestions ;
    enQuestionsLevel QuestionLevel ;
    enOperationType OpType ;
    short NumberOfWrongAnswers = 0;
    short NumberOfRihtAnswers = 0;
    bool IsPass = false ;

};
string GetOpTypeSymbol (enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add :
         return "+";
    case enOperationType::Sub :
         return "-";
    case enOperationType::Mult :
         return "*";
    case enOperationType::Div :
         return "/";
    default:
        return "Mix";
    }
}
string GetQuestionLevelText (enQuestionsLevel QuestionLevel)
{
    string arrQuestionLevelText[4] = {"easy","Med","Hard","Mix"};
    return arrQuestionLevelText[QuestionLevel - 1] ;
}
short RandomNumber (short From , short To)
{
    int randNum ;
    randNum = rand() % (To - From + 1) + From ;
    return randNum ;
}
void SetScreenColor (bool Right)
{
    if (Right)
        system("color 2F") ; // turn screen to green 
    else
       {
        system("color 4F") ; // turn screen to red
        cout << "\a";
       }
}
short ReadHowManyQuestions ()
{
    short NumberOfQuestions ;
    do
    {
        cout << "How Many Questions do you want answer ?" << endl;
        cin >> NumberOfQuestions ;
    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions ;
}
enQuestionsLevel ReadQuestionsLevel ()
{
    short QuestionLevel = 0 ;
    do
    {
        cout << "Enter Questions Level [1] Easy, [2] Med, [3]Hard, [4] Mix ? " << endl;
        cin >> QuestionLevel ;

    } while (QuestionLevel < 1 || QuestionLevel > 10);
    
   return enQuestionsLevel (QuestionLevel) ;
}
enOperationType GetRandomOperationType()
{
    int OpType = RandomNumber(1,4);
    return (enOperationType)OpType ;
}
int SimpleCalculator (int Number1 , int Number2 , enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add :
        return Number1 + Number2 ;
        break;

    case enOperationType::Sub :
        return Number1 - Number2 ;
        break;

    case enOperationType::Mult :
        return Number1 * Number2 ;
        break;

    case enOperationType::Div :
        return Number1 / Number2 ;
        break;
    default :
        return Number1 + Number2 ;

    }
}
enOperationType ReadOpType ()
{
    short OpType ;
    do
    {
        cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul,[4] Div, [5] Mix ? " << endl;
        cin >> OpType ;
    } while (OpType < 1 || OpType > 5);
    return enOperationType (OpType) ;
}
stQuestions GenerateQuestion (enQuestionsLevel QuestionsLevel , enOperationType OpType)
{
    stQuestions Question ;
    if (QuestionsLevel == enQuestionsLevel::Mix)
    {
        QuestionsLevel = (enQuestionsLevel)RandomNumber(1,3);
    }
    if (OpType == enOperationType::MixOp)
    {
        OpType = GetRandomOperationType() ;
    }
   Question.OperationType = OpType ;

    switch (QuestionsLevel)
    {
    case enQuestionsLevel::EasyLevel :
        Question.Number1 = RandomNumber(1,10);
        Question.Number2 = RandomNumber(1,10);

        Question.CorrectAnswer = SimpleCalculator (Question.Number1 , Question.Number2 , Question.OperationType);
        Question.QuestionLevel = QuestionsLevel ;
        return Question ;

    case enQuestionsLevel::MedLevel:
        Question.Number1 = RandomNumber(10,50);
        Question.Number2 = RandomNumber(10,50);

        Question.CorrectAnswer = SimpleCalculator (Question.Number1 , Question.Number2 , Question.OperationType);
        Question.QuestionLevel = QuestionsLevel ;
        return Question ;

    case enQuestionsLevel::HardLevel :
        Question.Number1 = RandomNumber(50,100);
        Question.Number2 = RandomNumber(50,100);

        Question.CorrectAnswer = SimpleCalculator (Question.Number1 , Question.Number2 , Question.OperationType);
        Question.QuestionLevel = QuestionsLevel ;
        return Question ;
    }
     return Question ;
}
void GenerateQuizzQuestions (stQuizz &Quizz)
{
   for (short Question = 0 ; Question < Quizz.NumberOfQuestions ; Question++)
   {
    Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionLevel , Quizz.OpType) ;
   }
}
int ReadQuestionAnswer ()
{
    int Answer = 0 ;
    cin >> Answer ;
    return Answer ;
}
void PrintTheQuestion (stQuizz &Quizz , short QuestionNumber)
{
    cout << endl;
    cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
    cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
    cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
    cout << "\n______________" << endl;
}
void CorrectTheQuestionAnswer (stQuizz &Quizz , short QuestionNumber)
{
    if (Quizz.QuestionList[QuestionNumber].PlayAnswer != Quizz.QuestionList[QuestionNumber].CorrectAnswer)
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = false ;
        Quizz.NumberOfWrongAnswers++ ;
        
        cout << "Wrong Answer :-( \n";
        cout << "The Right Answer is : " ;
        cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer ;
        cout << endl;
    }
    else
    {
        Quizz.QuestionList[QuestionNumber].AnswerResult = true ;
        Quizz.NumberOfRihtAnswers ++ ;

        cout << "The Right Answer is :-) \n";

    }
     cout << endl;
    SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswer (stQuizz &Quizz)
{
    for ( short QuestionNumber = 0 ; QuestionNumber < Quizz.NumberOfQuestions ; QuestionNumber++)
    {
         PrintTheQuestion (Quizz , QuestionNumber) ;
         Quizz.QuestionList[QuestionNumber].PlayAnswer = ReadQuestionAnswer() ;
         CorrectTheQuestionAnswer(Quizz , QuestionNumber);
    }
    Quizz.IsPass = (Quizz.NumberOfRihtAnswers >= Quizz.NumberOfWrongAnswers);
    /*
    if (Quizz.NumberOfRihtAnswers >= Quizz.NumberOfWrongAnswers)
       Quizz.IsPass = true ;
    else
       Quizz.IsPass = false ;
    
    */
}
string GetFinalResultText (bool Pass)
{
    if (Pass)
       return "Pass :-)";
    else
       return "Pass :-(";
}
void PrintQuizzResult (stQuizz Quizz)
{
    cout << endl;
    cout << "__________________\n\n" << endl;
    cout << "Final Result is " << GetFinalResultText(Quizz.IsPass) << endl;
    cout << "\n__________________\n\n" << endl;

    cout << "Number Of Questions : " << Quizz.NumberOfQuestions << endl;
    cout << "Question Level : " << GetQuestionLevelText(Quizz.QuestionLevel) << endl;
    cout << "Operation Type : " << GetOpTypeSymbol(Quizz.OpType) << endl;
    cout << "Number of Right Question : " << Quizz.NumberOfRihtAnswers << endl;
    cout << "Number of Wrong Question : " << Quizz.NumberOfWrongAnswers << endl;
    cout << "\n__________________\n" << endl;
}
void PlayMathGame()
{
  stQuizz Quizz ;
  Quizz.NumberOfQuestions = ReadHowManyQuestions ();
  Quizz.QuestionLevel = ReadQuestionsLevel ();
  Quizz.OpType = ReadOpType () ;
  
  GenerateQuizzQuestions(Quizz);
  AskAndCorrectQuestionListAnswer(Quizz);
  PrintQuizzResult(Quizz);
}
void ResetScreen ()
{
    system ("cls");
    system ("color 0F");
}
void StartGame ()
{
    char PlayAgain = 'Y' ;
    do
    {
        ResetScreen() ;
        PlayMathGame() ;
        cout << "Do you want paly again ? Y/N ?" << endl;
        cin >> PlayAgain ;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
    
}
int main()
{
   //Seeds the random number generator in C++, called only once
   srand((unsigned)time(NULL));
   StartGame() ;
}
