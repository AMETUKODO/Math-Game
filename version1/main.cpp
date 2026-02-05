#include <iostream> 
#include<cstdlib>
#include <string.h>
#include <ctime>
using namespace std; 
enum enQuestionsLevel { easy=1, med=2,hard=3,Mix=4};
enum enOperationType { add =1 ,sub=2,mul=3,div=4,mix=5};
enum enRightOrWrongAnswer { Right=1 , wrong=2 };
struct strGameResult {
   short RoundQuestions=0;
   string Level ;
   string OpType ;
   short NumberOfRightAnswers ;
  short  NumberOfWrongAnswers ;
};
struct strRoundInfo{
   short QuestionRound=0;
   short NumberOfLevel1;
  short NumberOfLevel2;
    short ResultChoice ;
  short  ResultOperation;
    enRightOrWrongAnswer ResultAnswer;
};
short RandomNumber(int From, int To) 
{ 
 //Function to generate a random number
 short randNum = rand() % (To - From + 1) + From; 
 return randNum; 
} 
short QuestionsRound () {
   short QuestionsRound =0;
   cout <<"How many questions do you want to answer ?";
   cin >> QuestionsRound;
   return QuestionsRound;
}
enQuestionsLevel ChoiceLevel () {
    short Level ; 
   do{
      cout<<"Enter your questions level : [1]easy [2]med [3]Hard [4] Mix ?";
    cin>>Level;
   }while (Level < 1 || Level > 4 );
    
    return (enQuestionsLevel)Level ;
}
enOperationType ChoiceOperationType () {
    short OpType=0;
    do {
       cout<<"Enter operation type : [1]add [2]sub [3]mul [4]Div [5]mix ?";
       cin>>OpType;
    }while (OpType < 1 || OpType > 5 ); 
   
    return (enOperationType)OpType ;
}
short ChoiceResult () {
   short choiceResult;
   cout<<"\t";
   cin>>choiceResult;
   return choiceResult;
}
short EasyLevel () {
   return RandomNumber(1,10);
}
short MedLevel () {
   return RandomNumber(10,30);
}
short HardLevel () {
   return RandomNumber(30,50);
}
short MixLevel () {
   return RandomNumber(1,50);
}
short Add (short a , short b){
   return a+b;
}
short Sub (short a , short b){
   return a-b;
}
short Mul (short a , short b){
   return a*b;
}
short Div (short a , short b){
   if(b!=0) return a/b;
   else
   return 0;
}
short OperationType (strRoundInfo RoundInfo,enOperationType OpType, enOperationType mix ){
   short result=0;
   if(OpType==1 || mix==1 )
      result=Add(RoundInfo.NumberOfLevel1,RoundInfo.NumberOfLevel2);
   else if (OpType==2 || mix==2)
    result= Sub(RoundInfo.NumberOfLevel1,RoundInfo.NumberOfLevel2);
   else if (OpType==3 || mix==3)
    result= Mul(RoundInfo.NumberOfLevel1,RoundInfo.NumberOfLevel2);
   else
     result= Div(RoundInfo.NumberOfLevel1,RoundInfo.NumberOfLevel2);
   
   
   return result;
}
short QuestionsLevel (enQuestionsLevel Level){
   
   if(Level ==1 )
   return EasyLevel();
   else if (Level==2)
   return MedLevel();
   else if (Level==3)
   return HardLevel();
   else 
   return MixLevel();
}
enRightOrWrongAnswer CheckAnswer( short ResultChoice , short ResultOperation){
   short Answer=0;
   if (ResultChoice == ResultOperation)
      Answer=1;
   else 
      Answer=2;
   
   
    return (enRightOrWrongAnswer)Answer;
}
string NameOperType (enOperationType OpType )
{
    string ArrOpTypeChoice[5] = { " add " , " sub " , " mul " , "div" , "mix"} ;
    return ArrOpTypeChoice[OpType-1];
}
string NameLevel(enQuestionsLevel Level){
   
    string ArrLevelChoice[4] = { " easy " , " med " , " hard ", "Mix"} ;
    return ArrLevelChoice[Level-1];
}
string NameResultAnswer(enRightOrWrongAnswer Answer){
   
    string ArrAnswer[2] = { " Right Answer :) " , "Wrong Answer :( " } ;
    return ArrAnswer[Answer-1];
}
void PrintChoiceOperationType(enOperationType OpType,enOperationType mix){
    
   if(OpType==1 || mix==1)
    cout<<"   +";
   else if (OpType==2 || mix==2)
    cout<<"   -";
   else if (OpType==3 || mix==3)
    cout<<"   *";
   else if (OpType==4 || mix==4)
    cout<<"   /";
   else 
    return ;
}
enOperationType MixOperation(){
   short mix=RandomNumber(1,4);
   return (enOperationType)mix;
}
short PrintRoundResults(strRoundInfo Info , short GameRound,enOperationType OpType,enOperationType mix){
   cout<<"\nQuestion ["<<GameRound<<"/"<<Info.QuestionRound<<"]"<<endl;
   cout<<"\t"<<Info.NumberOfLevel1<<endl;
   
   PrintChoiceOperationType(OpType,mix);
   cout<<"\n";
   cout<<"\t"<<Info.NumberOfLevel2<<endl;
   cout<<"  __________\n";
   Info.ResultChoice=ChoiceResult();
   Info.ResultAnswer=CheckAnswer(Info.ResultChoice,Info.ResultOperation);
   cout<<NameResultAnswer(Info.ResultAnswer);
   
   return (short)Info.ResultAnswer;
}

strGameResult GameRound (){
   short NumberOfRightAnswer=0 ;
   short NumberOfWrongAnswer=0;
   strRoundInfo RoundInfo;
   RoundInfo.QuestionRound=QuestionsRound();
   enQuestionsLevel Level=ChoiceLevel();
   enOperationType OpType=ChoiceOperationType();
   short i;
   for(i =1 ;i<=RoundInfo.QuestionRound;i++){
  
      RoundInfo.NumberOfLevel1=QuestionsLevel(Level);
   RoundInfo.NumberOfLevel2=QuestionsLevel(Level);
      enOperationType mix = MixOperation();
      RoundInfo.ResultOperation=OperationType(RoundInfo,OpType,mix);
      //cout<<RoundInfo.ResultOperation;
      
   //RoundInfo.ResultAnswer=CheckAnswer(RoundInfo.ResultChoice,RoundInfo.ResultOperation);
      
 short Result = PrintRoundResults(RoundInfo,i,OpType,mix);
      
   if(Result == 1)
      NumberOfRightAnswer++;
   else
       NumberOfWrongAnswer++;
      
      
      
   }
   cout<<"\nThe right Answer is : "<<NumberOfRightAnswer;
   string LevelName=NameLevel(Level);
   string OpName=NameOperType(OpType);
    return { 
       RoundInfo.QuestionRound,
        LevelName ,
       OpName ,
       NumberOfRightAnswer, 
       NumberOfWrongAnswer 
    };
}
void PassOrFill (strGameResult GameResult){
   if(GameResult.NumberOfRightAnswers==GameResult.NumberOfWrongAnswers){
     cout<<"\n____________________________________\n";
      cout<<"       Final Results is Eqaul :|       ";
      cout<<"\n___________________________________\n";}
   else if (GameResult.NumberOfRightAnswers > GameResult.NumberOfWrongAnswers){
      cout<<"\n___________________________________\n";
      cout<<"       Final Results is Pass :)      ";
      cout<<"\n___________________________________\n";}
   else {
     cout<<"\n______________________________________\n";
     cout<<"        Final Results is Fill :(      ";
     cout<<"\n______________________________________\n"; }
}

void FinalResults(strGameResult GameResult){
   PassOrFill(GameResult);
   cout<<"\nNumberOfQuetions : "<<GameResult.RoundQuestions<<endl;
   cout<<"\nQuetions Level : "<<GameResult.Level<<endl;
   cout<<"\nOperation Type : "<<GameResult.OpType<<endl;
   cout<<"\nNumber Of Right Answers : "<<GameResult.NumberOfRightAnswers<<endl;
   cout<<"\nNumber Of Wrong Answers : "<<GameResult.NumberOfWrongAnswers<<endl;
   cout<<"______________________________________\n";
   
}
void GameOverResults(){
   char Playagain = 'y' ;
  do
  {
   
   strGameResult GameResults = GameRound();
   FinalResults(GameResults);

       cout<<"Do you want to play again ? (Y/N) ?  "  ;
       cin>>Playagain ;
       cout<<"\n";

  } while (Playagain =='y' || Playagain =='Y');
  
 }
int main() {
   srand((unsigned)time(NULL));
   GameOverResults();
    return 0;
}
