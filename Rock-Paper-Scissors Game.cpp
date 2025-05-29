#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib> // to intialize generater of random Numbers 
using namespace std;
enum enGameChoice { Stone = 1 , Paper = 2 , Scissor = 3 } ;
enum enWinner { Player = 1 , Computer = 2 , Draw = 3 } ;
struct stRoundInfo 
{
    short RoundNumber = 0 ;
    enGameChoice PlayerChoice ;
    enGameChoice ComputerChoice ;
    enWinner Winner ;
    string WinnerName ;
};
struct stGameResults 
{
    short GameRounds = 0 ;
    short PlayerWinTimes = 0 ;
    short ComputerWinTimes = 0 ;
    short DrawTimes = 0 ;
    enWinner GameWinner ;
    string WinnerName = "" ;
};
int RandomNumber (int From , int To)
{
    int randNum ;
    randNum = rand() % (To - From + 1) + From ;
    return randNum ;
}
string WinnerName(enWinner Winner)
{
     string arrWinnerName[3] = { "Player1","Computer","No Winner" } ;
     return arrWinnerName[Winner - 1];
}
enWinner WhoWonTheRound (stRoundInfo RoundInfo)
{
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)
    {
        return enWinner::Draw ;
    }
    switch (RoundInfo.PlayerChoice)
    {
    case enGameChoice::Stone :
        if (RoundInfo.ComputerChoice == enGameChoice::Paper)
        {
            return enWinner::Computer ;
        }
        break;
    case enGameChoice::Paper :
        if (RoundInfo.ComputerChoice == enGameChoice::Scissor)
        {
            return enWinner::Computer ;
        }
        break;
    case enGameChoice::Scissor :
        if (RoundInfo.ComputerChoice == enGameChoice::Stone)
        {
            return enWinner::Computer ;
        }
        break;
    }
    // if you reach here then player is the winner
    return enWinner::Player ;
}
string ChoiceName (enGameChoice Choice)
{
    string arrGameChoices[3] = {"Stone","Paper","Scissor"};
    return arrGameChoices[Choice - 1] ;
}
void SetWinnerScreenColor (enWinner Winner)
{
    switch (Winner)
    {
    case enWinner::Player :
        system ("color 2F"); //turn screen to Green
        break;
    
    case enWinner::Computer :
         system ("color 4F"); //turn screen to Red
         cout << "\a"; // to make a bill
         cout << endl;
         break;
    default :
         system ("color 6F"); //turn screen to Yellow
         break;
    }
}
void PrintRoundResults (stRoundInfo RoundInfo)
{
    cout << "\n ____________ Round [" << RoundInfo.RoundNumber << "] ____________ \n\n" ;
    cout << "Player Choice : " << ChoiceName (RoundInfo.PlayerChoice) << endl;
    cout << "Computer Choice : " << ChoiceName (RoundInfo.ComputerChoice) << endl;
    cout << "Round Winner : " << RoundInfo.WinnerName << endl;
    cout << "_____________________________________" << endl;

    SetWinnerScreenColor(RoundInfo.Winner);
}
enWinner WhoWonTheGame (short PlayerWinTimes , short ComputerWinTimes)
{
    if (PlayerWinTimes > ComputerWinTimes)
    return enWinner::Player ;
    else if (ComputerWinTimes > PlayerWinTimes)
    return enWinner::Computer ;
    else
    return enWinner::Draw ;
}
stGameResults FillGameResult (int GameRounds , short PlayerWinTimes , short ComputerWinTimes , short DrawTimes)
{
    stGameResults GameResults ;
    GameResults.GameRounds = GameRounds ;
    GameResults.PlayerWinTimes = PlayerWinTimes ;
    GameResults.ComputerWinTimes = ComputerWinTimes ;
    GameResults.DrawTimes = DrawTimes ;
    GameResults.GameWinner = WhoWonTheGame (PlayerWinTimes,ComputerWinTimes) ;
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults ;
}
enGameChoice ReadPlayerChoice ()
{
    short Choice = 1 ;
    do
    {
        cout << "\nYour Choice : [1]:Stone , [2]:Paper , [3]:Scissor ?";
        cin >> Choice ;
    } while (Choice < 1 || Choice > 3);
    return enGameChoice(Choice) ;
}
enGameChoice GetComputerChoice ()
{
    return (enGameChoice)RandomNumber(1,3) ;
}
stGameResults PlayGame (short HowManyRounds )
{
    stRoundInfo RoundInfo ;
    short PlayerWinTimes = 0 , ComputerWinTimes = 0 , DrawTimes = 0 ;
    for (short GameRound = 1 ; GameRound <= HowManyRounds ; GameRound++)
    {
        cout << "\nRound [" << GameRound << "] begins : " << endl;
        RoundInfo.RoundNumber = GameRound ;
        RoundInfo.PlayerChoice = ReadPlayerChoice () ;
        RoundInfo.ComputerChoice = GetComputerChoice () ;
        RoundInfo.ComputerChoice = GetComputerChoice () ;
        RoundInfo.Winner = WhoWonTheRound(RoundInfo) ;
        RoundInfo.WinnerName = WinnerName(RoundInfo.Winner);

        // Increase win , draw and lose Counters
        if (RoundInfo.Winner == enWinner::Player)
           PlayerWinTimes ++ ;
        else if (RoundInfo.Winner == enWinner::Computer)
           ComputerWinTimes ++ ;
        else
           DrawTimes ++ ;
    
        PrintRoundResults (RoundInfo);
    }
    return FillGameResult(HowManyRounds,PlayerWinTimes,ComputerWinTimes,DrawTimes) ;
}
string Tabs (short NumberOfTabes)
{
    string t = "" ;
    for (int i=1 ; i < NumberOfTabes ; i++)
    {
        t = t + "\t" ;
        cout << t ;
    }
    return t ;
}
void ShowGameOverScreen ()
{
    cout << Tabs(2) << "__________________________________________________________\n\n";
    cout << Tabs(2) << "                 +++ G a m e O v e r+++\n";
    cout << Tabs(2) << "__________________________________________________________\n\n";


}
void ShowFinalGameResults (stGameResults GameResults)
{
    cout << Tabs(2) << "_____________________ [Game Results] _____________________\n\n";
    cout << Tabs(2) << "Game Rounds :               " << GameResults.GameRounds << endl;
    cout << Tabs(2) << "Player Won times :          " << GameResults.PlayerWinTimes << endl;
    cout << Tabs(2) << "Computer won times :        " << GameResults.ComputerWinTimes << endl;
    cout << Tabs(2) << "Draw times :                " << GameResults.DrawTimes << endl;
    cout << Tabs(2) << "Final Winner :              " << GameResults.WinnerName << endl;
    cout << Tabs(2) << "___________________________________________________________\n";
    SetWinnerScreenColor(GameResults.GameWinner);
}
short ReadHowManyRounds ()
{
    short GameRounds = 1 ;
    do
    {
        cout << "How Many Rounds 1 to 10 ?" << endl;
        cin >> GameRounds ;
    } while (GameRounds < 1 || GameRounds > 10);
    return GameRounds ;
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
        ResetScreen () ;
        stGameResults GameResults = PlayGame(ReadHowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults (GameResults) ;
        cout << endl << Tabs(3) << "Do you want play again ? Y/N ?" ;
        cin >> PlayAgain ;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}
int main()
{
   //Seeds the random number generator in C++, called only once
   srand((unsigned)time(NULL));
   StartGame();
}
