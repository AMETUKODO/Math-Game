
#include <iostream>
#include <string>
#include <cstdlib>
#include <cmath>
using namespace std;
enum enQuestionLevel { Easy = 1, Mid = 2, Hard = 3, MixLev = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion {
    int Number1 = 0;
    int Number2 = 0;
    enQuestionLevel QuestionLevel;
    enOperationType OpType;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerValid = false;
};
struct stQuizz {
    stQuestion QuestionList[100];
    short NumberOfQuestions;
    enQuestionLevel QuestionsLevel;
    enOperationType QuestionsOpType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool IsPass = 0;
};
int RandomNumber(int From, int To) {
    int Rand = rand() % (To - From + 1) + From;
    return Rand;
}
short ReadNumberOfQuestions() {
    short n = 0 ;
    do {
        cout << "How Many Questions Do You Want To Answer?: ";
        cin >> n;
    } while (n < 1 || n >100);
    return n;
}
enQuestionLevel ReadQuestionLevel() {
    short QuestionLevel = 0;
    do {
        cout << "Enter Questions Level: [1] Easy, [2] Mid , [3] Hard , [4] Mix: ";
        cin >> QuestionLevel;
    } while (QuestionLevel < 1 || QuestionLevel > 4);
    return enQuestionLevel(QuestionLevel);
}
enOperationType ReadQuestionsOpType() {
    short  QuestionsOpType = 0;
    do {
        cout << "Enter Operation Type: [1] Add , [2] Sub , [3] Mult , [4] Div , [5] MixOP: ";
        cin >> QuestionsOpType;
    } while (QuestionsOpType < 1 || QuestionsOpType > 5);
    return (enOperationType)QuestionsOpType;
}
int SimpleCalculator(int Number1, int Number2, enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add:
        return Number1 + Number2;
    case enOperationType::Sub:
        return Number1 - Number2;
    case enOperationType::Mult:
        return Number1 * Number2;
    case enOperationType::Div:
        return Number1 / Number2;
    }

}
int ReadPlayerAnswer() {
    int PlayerAnswer = 0;
    cin >> PlayerAnswer;
    return PlayerAnswer;
}
string GetOpTypeSymbol(enOperationType OpType) {
    switch (OpType) {
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "*";
    case enOperationType::Div:
        return "/";
    default:
        return "MixOp";
    }

}
void PrintTheQuestion(stQuizz Quizz,short QuestionNumber) {
    cout << "\nQuestion[" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]: " << endl;
    cout << "  "<<Quizz.QuestionList[QuestionNumber].Number1 << "\n";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OpType) << " ";
    cout << Quizz.QuestionList[QuestionNumber].Number2 << endl;
    cout << "\n-------------------------" << endl;
}
void SetAnswerScreenColor(bool AnswerValid) {
    if (AnswerValid)
        system("color 2F");
    else
        system("color 4F");
}
void CorrectPlayerAnswerAndPrintRightOrWrongAnswer(stQuizz& Quizz, short QuestionNumber) {

    if (Quizz.QuestionList[QuestionNumber].PlayerAnswer !=
        Quizz.QuestionList[QuestionNumber].CorrectAnswer) {

        Quizz.NumberOfWrongAnswers++;
        Quizz.QuestionList[QuestionNumber].AnswerValid = false;

        cout << "\nWrong Answer :-(" << endl;
        cout << "The Right Answer = "
            << Quizz.QuestionList[QuestionNumber].CorrectAnswer << endl;
    }
    else {
        Quizz.QuestionList[QuestionNumber].AnswerValid = true;
        Quizz.NumberOfRightAnswers++;

        cout << "\nRight Answer :-)" << endl;
    }

    
    SetAnswerScreenColor(Quizz.QuestionList[QuestionNumber].AnswerValid);
}

void AskandCorrectQuestionslistAnswer_PrintQuestions(stQuizz& Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
        PrintTheQuestion(Quizz, QuestionNumber);
        Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadPlayerAnswer();
        CorrectPlayerAnswerAndPrintRightOrWrongAnswer(Quizz,QuestionNumber);
    }
    Quizz.IsPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
stQuestion GenerateQuestion(enQuestionLevel QuestionLevel, enOperationType OpType) {
    stQuestion Question;
    if (QuestionLevel == enQuestionLevel::MixLev)
        QuestionLevel = (enQuestionLevel)RandomNumber(1, 3);
    if (OpType == enOperationType::MixOp)
        OpType = (enOperationType)RandomNumber(1, 4);
    Question.OpType = OpType;
    switch (QuestionLevel) {
    case enQuestionLevel::Easy:
        Question.Number1 = RandomNumber(1, 10);
        Question.Number2 = RandomNumber(1, 10);
        Question.QuestionLevel = QuestionLevel;
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        return Question;
    case enQuestionLevel::Mid:
        Question.Number1 = RandomNumber(11, 50);
        Question.Number2 = RandomNumber(11, 50);
        Question.QuestionLevel = QuestionLevel;
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        return Question;
    case enQuestionLevel::Hard:
        Question.Number1 = RandomNumber(51, 100);
        Question.Number2 = RandomNumber(51, 100);
        Question.QuestionLevel = QuestionLevel;
        Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OpType);
        return Question;
    }
}
string QuestionLevelName(enQuestionLevel QuestionLevel) {
    string ArrLevels[]{ "Easy","Mid","Hard","Mix" };
    return ArrLevels[QuestionLevel - 1];
}
string PassOrFail(bool IsPass) {
    if (IsPass)
        return "Pass :-)";
    else
        return "Fail :-(";
}
void PrintQuizzResults(stQuizz Quizz) {
    cout << "\n----------------------------------------------------------------\n\n";
    cout << "Final Results is " << PassOrFail(Quizz.IsPass) << "\n\n";
    cout << "-------------------------------------------------------------------\n\n";
    cout << "Number Of Questions: " << Quizz.NumberOfQuestions << endl;
    cout << "Questions Level: " << QuestionLevelName(Quizz.QuestionsLevel) << endl;
    cout << "Op Type: " << GetOpTypeSymbol(Quizz.QuestionsOpType) << endl;
    cout << "Number Of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
    cout << "Number Of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
    cout << "\n----------------------------------------------------------------\n";

}
void GenerateQuizzQuestions(stQuizz &Quizz) {
    for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++) {
        Quizz.QuestionList[QuestionNumber] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.QuestionsOpType);
    }
}
void ResetScreen() {
    system("cls");
    system("color 0F");
}
void PlayMathGame() {
    stQuizz Quizz;
    Quizz.NumberOfQuestions = ReadNumberOfQuestions();
    Quizz.QuestionsLevel = ReadQuestionLevel();
    Quizz.QuestionsOpType = ReadQuestionsOpType();
    GenerateQuizzQuestions(Quizz);
    AskandCorrectQuestionslistAnswer_PrintQuestions(Quizz);
    PrintQuizzResults(Quizz);
}
void StartMathGame() {
    char playAgain = 'y';
    do {
        ResetScreen();
        PlayMathGame();
        cout << "Do You Want PlayAgain [Y/N]: ";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartMathGame();
}
