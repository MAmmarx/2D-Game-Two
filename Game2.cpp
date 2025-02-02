
//************************************************************************
//**                    PROGRAMMING II PROJECT                          **
//**                GAME MADE BY -- MOHAMMED AMMAR                      **
//************************************************************************




#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>

using namespace std;

void Clear_and_Draw_Map(char Map[][400])
{

    //CLEAR THE SCREEN
    for (int r = 0; r < 400; r++)
    {
        for (int c = 0; c < 400; c++)
        {
            Map[r][c] = ' ';
        }
    }
}
void Cout_Map_to_Screen(char Map[][400], char& UserMove, int& RBorderStart, int& RBorderEnd, int& colMapBorderStart, int& colMapBorderEnd, int IndR, int IndC)
{
    int ViewportHeight = RBorderEnd - RBorderStart; // The visible vertical slice of the map
    int ViewportWidth = colMapBorderEnd - colMapBorderStart; // The visible horizontal slice of the map
    int ScrollThreshold = ViewportHeight / 3; // Threshold for scrolling, adjust as needed
    int ScrollAmount = 1; // Amount to scroll for smoother movement

    system("cls");
    for (int rowMap = RBorderStart; rowMap < RBorderEnd; rowMap++) {
        for (int columnMap = colMapBorderStart; columnMap < colMapBorderEnd; columnMap++) {
            cout << Map[rowMap][columnMap];
        }
        cout << endl;
    }

    // Update for dynamic vertical scrolling based on hero's position
    // If the hero is close to the bottom of the viewport, scroll down
    if (IndR - RBorderStart >= ViewportHeight - ScrollThreshold)
    {
        if (RBorderEnd < 400) { // Ensure we don't scroll past the map boundary
            RBorderStart += ScrollAmount;
            RBorderEnd += ScrollAmount;
        }
    }
    // If the hero is close to the top of the viewport, scroll up
    if (RBorderStart > 0 && IndR - RBorderStart <= ScrollThreshold)
    {
        if (RBorderStart > 0) { // Ensure we don't scroll past the map boundary
            RBorderStart -= ScrollAmount;
            RBorderEnd -= ScrollAmount;
        }
    }

    // Recenter the viewport vertically after the hero falls
    if (IndR - RBorderStart >= ViewportHeight - ScrollThreshold || IndR - RBorderStart <= ScrollThreshold)
    {
        RBorderStart = IndR - (ViewportHeight / 2);
        RBorderEnd = RBorderStart + ViewportHeight;

        // Ensure we don't scroll past the map boundary
        if (RBorderStart < 0) {
            RBorderStart = 0;
            RBorderEnd = ViewportHeight;
        } 
        else if (RBorderEnd > 400) {
            RBorderEnd = 400;
            RBorderStart = 400 - ViewportHeight;
        }
    }

    // Horizontal scrolling using user input
    if (UserMove == 'p' && colMapBorderEnd < 400) {
        colMapBorderStart += ScrollAmount;
        colMapBorderEnd += ScrollAmount;
    }
    if (UserMove == 'o' && colMapBorderStart > 0) {
        colMapBorderStart -= ScrollAmount;
        colMapBorderEnd -= ScrollAmount;
    }

    // Ensure horizontal boundaries are maintained
    if (colMapBorderEnd > 400) {
        colMapBorderEnd = 400;
        colMapBorderStart = 400 - ViewportWidth;
    }
    if (colMapBorderStart < 0) {
        colMapBorderStart = 0;
        colMapBorderEnd = ViewportWidth;
    }

    UserMove = 'G'; // Reset the user move command after processing
    cout.flush();
}

//HERO ||||TASK: CHANGE HERO LOOKS|||||
void HeroDraw(char Map[][400], int rHero, int cHero, int& IndexRHero, int& IndexCHero, char UserMove) {

    int HeroColumn = cHero;

    // Drawing the hero's upper body
    Map[rHero][HeroColumn++] = ' ';
    Map[rHero][HeroColumn++] = '/';
    Map[rHero][HeroColumn++] = '\\';
    Map[rHero][HeroColumn++] = '_';
    Map[rHero][HeroColumn++] = '/';
    Map[rHero][HeroColumn++] = '\\';

    HeroColumn = cHero;

    // Drawing the hero's middle body
    Map[rHero + 1][HeroColumn++] = '(';
    Map[rHero + 1][HeroColumn++] = ' ';
    Map[rHero + 1][HeroColumn++] = 'o';
    Map[rHero + 1][HeroColumn++] = '.'; // INDEX

    IndexRHero = rHero + 1;
    IndexCHero = HeroColumn - 1;

    Map[rHero + 1][HeroColumn++] = 'o';
    Map[rHero + 1][HeroColumn++] = ' ';
    Map[rHero + 1][HeroColumn++] = ')';

    HeroColumn = cHero;

    // Drawing the hero's lower body
    Map[rHero + 2][HeroColumn++] = '>';
    Map[rHero + 2][HeroColumn++] = ' ';
    Map[rHero + 2][HeroColumn++] = '^';
    Map[rHero + 2][HeroColumn++] = ' ';
    Map[rHero + 2][HeroColumn++] = '<';
}
void Move_Hero(char Map[][400], int& rHero, int& cHero, char UserMove, int &flagBarrierAtLevel1, int &IndR, int &IndC, int&flagJump, int &LevelCount, int &FlagPistol, int &colMapBorderStart, int &colMapBorderEnd, int &Game, int &rowMapS, int &rowMapE)
{
    int Constant = 4;
    int Constant2 = 5;

    if (UserMove == ' ')
    {
        flagJump = 1;
    }

    if (UserMove == 'a' && Map[IndR][IndC - Constant] == ' ' && Map[IndR][IndC - Constant2] == ' ' && Map[IndR + 1][IndC - Constant] == ' ' && Map[IndR + 1][IndC - Constant2] == ' ' )
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'd' && Map[IndR][IndC + Constant] == ' ' && Map[IndR][IndC + Constant2] == ' ' && Map[IndR + 1][IndC + Constant] == ' ' && Map[IndR + 1][IndC + Constant2] == ' ' )
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    // EXCEPTION FOR LADDER LEVEL 2
    if (UserMove == 'd' && IndC > 380-7 && IndC < 380+14)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (UserMove == 'a' && IndC > 380-7)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'w' && IndC > 380-7 && IndC < 385+4)
    {
        IndR -= 2;
        rHero -= 2;

        rowMapS -= 2;
        rowMapE -= 2;
    }

    // EXCEPTION FOR LADDER LEVEL 3
    if (UserMove == 'd' && IndC > 344 && IndC < 370)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (UserMove == 'a' && IndC > 344)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'w' && IndC > 344 && IndC < 360)
    {
        IndR -= 2;
        rHero -= 2;

        rowMapS -= 2;
        rowMapE -= 2;
    }

    // LEVEL 2 MOVEMENTS

    // TO TAKE PISTOL
    int FlagPos = 0;
    if (IndC < 370 && IndC > 355)
    {
        FlagPos = 1;
    }
    else
    {
        FlagPos = 0;
    }

    if (UserMove == 'a' && Map[IndR][IndC - Constant] == ' ' && Map[IndR][IndC - Constant2] == ' ' && Map[IndR + 1][IndC - Constant] == ' ' && Map[IndR + 1][IndC - Constant2] == ' ' && FlagPos == 0 && LevelCount == 2 && FlagPistol == 0)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'd' && Map[IndR][IndC + Constant] == ' ' && Map[IndR][IndC + Constant2] == ' ' && Map[IndR + 1][IndC + Constant] == ' ' && Map[IndR + 1][IndC + Constant2] == ' ' && LevelCount == 2 && FlagPistol == 0)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (FlagPos == 1 && UserMove == 'a')
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (FlagPos == 1 && UserMove == 'd')
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (UserMove == 'a' && Map[IndR][IndC - 10] == ' ' && Map[IndR][IndC - 11] == ' ' && Map[IndR + 1][IndC - 10] == ' ' && Map[IndR + 1][IndC - 11] == ' ' && FlagPos == 0 && LevelCount == 2 && FlagPistol == 1)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'd' && Map[IndR][IndC + 10] == ' ' && Map[IndR][IndC + 11] == ' ' && Map[IndR + 1][IndC + 10] == ' ' && Map[IndR + 1][IndC + 11] == ' ' && LevelCount == 2 && FlagPistol == 1)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    // LEVEL 3 MOVEMENTS

    if (UserMove == 'a' && Map[IndR][IndC - Constant] == ' ' && Map[IndR][IndC - Constant2] == ' ' && Map[IndR + 1][IndC - Constant] == ' ' && Map[IndR + 1][IndC - Constant2] == ' ' && FlagPos == 0 && LevelCount == 3 && FlagPistol == 0 && IndC >= 60)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'a' && FlagPos == 0 && LevelCount == 3 && FlagPistol == 0 && IndC < 60)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'd' && Map[IndR][IndC + Constant] == ' ' && Map[IndR][IndC + Constant2] == ' ' && Map[IndR + 1][IndC + Constant] == ' ' && Map[IndR + 1][IndC + Constant2] == ' ' && LevelCount == 3 && FlagPistol == 0 && IndR >= 60)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (UserMove == 'd' && Map[IndR][IndC + Constant] == ' ' && Map[IndR][IndC + Constant2] == ' ' && Map[IndR + 1][IndC + Constant] == ' ' && Map[IndR + 1][IndC + Constant2] == ' ' && LevelCount == 3 && FlagPistol == 1 && IndR >= 60)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (UserMove == 'd' && FlagPos == 0 && LevelCount == 3 && FlagPistol == 0 && IndC < 60)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }

    if (UserMove == 'a' && Map[IndR][IndC - 10] == ' ' && Map[IndR][IndC- 11] == ' ' && Map[IndR + 1][IndC - 10] == ' ' && Map[IndR + 1][IndC - 11] == ' ' && FlagPos == 0 && LevelCount == 3 && FlagPistol == 1)
    {
        IndC -= 2;
        cHero -= 2;

        if (colMapBorderStart > 0)
        {
            colMapBorderStart -= 2;
            colMapBorderEnd -= 2;
        }
    }

    if (UserMove == 'd' && Map[IndR][IndC + 10] == ' ' && Map[IndR][IndC + 11] == ' ' && Map[IndR + 1][IndC + 10] == ' ' && Map[IndR + 1][IndC + 11] == ' ' && LevelCount == 3 && FlagPistol == 1)
    {
        IndC += 2;
        cHero += 2;

        if (colMapBorderEnd < 400)
        {
            colMapBorderStart += 2;
            colMapBorderEnd += 2;
        }
    }
}

//JUMP AND GRAVITY
void ApplyGravity(char Map[][400], int& rHero, int& cHero, int& JumpCT, int& RBorderStart, int& RBorderEnd, int& Againjump, int& IndR, int& IndC, int FlagLadder) {

    if ((JumpCT == 7 || JumpCT == 0) && Map[IndR + 2][IndC] == ' ' && Map[IndR + 2][IndC + 1] == ' ' && Map[IndR + 2][IndC + 2] == ' ' &&
        Map[IndR + 2][IndC + 3] == ' ' && Map[IndR + 2][IndC - 1] == ' ' && Map[IndR + 2][IndC - 2] == ' ' && Map[IndR + 2][IndC - 3] == ' ') {

        rHero++;
        Againjump++;

        if (rHero % 2 == 1) {

            RBorderStart++;
            RBorderEnd++;
        }
   }

    if (Map[IndR + 2][cHero] != ' ' || Map[IndR + 2][cHero + 1] != ' ' || Map[IndR + 2][cHero + 2] != ' ' || Map[IndR + 2][cHero + 3] != ' ' ||
        Map[IndR + 2][cHero + 4] != ' ' || Map[IndR + 2][cHero + 5] != ' ' || Map[IndR + 2][cHero + 6] != ' ') {

        JumpCT = 0;
        Againjump = 0;
    }
}

void ApplyJump(char Map[][400], int& rHero, int& cHero, int& JumpCT, int& jumpflag, int& RBorderStart, int& RBorderEnd, int Againjump, int IndR, int IndC, int JJ) {

    if (jumpflag == 1 && Againjump == 0) {

        int canJump = 1; // 1 represents true, 0 represents false

        for (int i = 0; i < 7 && canJump; ++i) {

            if (Map[rHero - 1][cHero + i] != ' ') {

                canJump = 0;
            }
        }

        if (canJump) {

            rHero--;
            JumpCT++;

            if (rHero % 2 == 0) {

                RBorderStart--;
                RBorderEnd--;
            }
        }
    }

    if (JumpCT >= 7) {

        jumpflag = 0;
    }

    int obstacleAbove = 0; // 1 represents true, 0 represents false

    for (int i = -3; i <= 3 && !obstacleAbove; ++i) {

        if (Map[IndR - 2][IndC + i] != ' ') {

            obstacleAbove = 1;
        }
    }

    if (obstacleAbove) {

        JumpCT = 7;
    }
}

void DrawLvl1(char Map[][400]) {

    for (int ColumnFirstFlood = 0; ColumnFirstFlood < 335; ColumnFirstFlood++) {

        Map[191][ColumnFirstFlood] = 219;
    }

    for (int ColumnFirstFlood = 370; ColumnFirstFlood < 400; ColumnFirstFlood++) {

        Map[191][ColumnFirstFlood] = 219;
    }

    //right cell wall
    int WallR = 185;

    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;
    Map[WallR--][100] = 222;

    //Left cell wall
    int WallL = 190;

    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;
    Map[WallL--][1] = 222;

    //seats and table
    Map[190][29] = 196;
    Map[190][30] = 196;
    Map[190][31] = 196;
    Map[190][32] = 196;
    Map[190][33] = 196;
    Map[190][34] = 196;
    Map[189][30] = 179;
    Map[189][33] = 179;
    Map[188][29] = 196;
    Map[188][30] = 196;
    Map[188][31] = 196;
    Map[188][32] = 196;
    Map[188][33] = 196;
    Map[188][34] = 196;
    Map[187][29] = 179;
    Map[186][29] = 179;

    Map[190][39 + 5] = 196;
    Map[190][40 + 5] = 196;
    Map[190][41 + 5] = 196;
    Map[190][42 + 5] = 196;
    Map[190][43 + 5] = 196;
    Map[190][44 + 5] = 196;
    Map[189][40 + 5] = 179;
    Map[189][43 + 5] = 179;
    Map[188][39 + 5] = 196;
    Map[188][40 + 5] = 196;
    Map[188][41 + 5] = 196;
    Map[188][42 + 5] = 196;
    Map[188][43 + 5] = 196;
    Map[188][44 + 5] = 196;
    Map[187][44 + 5] = 179;
    Map[186][44 + 5] = 179;

    Map[190][29 + 8] = 196;
    Map[190][30 + 8] = 196;
    Map[190][31 + 8] = 196;
    Map[190][32 + 8] = 196;
    Map[190][33 + 8] = 196;
    Map[189][31 + 8] = 179;
    Map[188][31 + 8] = 179;
    Map[187][29 + 8] = 196;
    Map[187][30 + 8] = 196;
    Map[187][31 + 8] = 196;
    Map[187][32 + 8] = 196;
    Map[187][33 + 8] = 196;


    Map[180 - 5][40 - 4] = '|';
    Map[180 - 5][40 - 3] = 'P';
    Map[180 - 5][41 - 3] = 'R';
    Map[180 - 5][41 - 3] = 'R';
    Map[180 - 5][42 - 3] = 'I';
    Map[180 - 5][43 - 3] = 'S';
    Map[180 - 5][44 - 3] = 'O';
    Map[180 - 5][45 - 3] = 'N';
    Map[180 - 5][46 - 3] = ' ';
    Map[180 - 5][46 + 1 - 3] = 'E';
    Map[180 - 5][47 + 1 - 3] = 'S';
    Map[180 - 5][48 + 1 - 3] = 'C';
    Map[180 - 5][49 + 1 - 3] = 'A';
    Map[180 - 5][50 + 1 - 3] = 'P';
    Map[180 - 5][51 + 1 - 3] = 'E';
    Map[180 - 5][52 + 1 - 3] = '|';

    //frame to jump on
    Map[175 + 8][65] = 192;
    Map[175 + 8][66] = 196;
    Map[175 + 8][67] = 196;
    Map[175 + 8][68] = 196;
    Map[175 + 8][68 + 1] = 217;
    Map[174 + 8][65] = 179;
    Map[173 + 8][65] = 218;
    Map[173 + 8][66] = 196;
    Map[173 + 8][67] = 196;
    Map[173 + 8][68] = 196;
    Map[173 + 8][68 + 1] = 191;
    Map[174 + 8][68 + 1] = 179;
    Map[174 + 8][67] = 'O';

    //platform of key
    Map[178][83] = 220;
    Map[178][84] = 220;
    Map[178][85] = 220;
    Map[178][86] = 220;
    Map[178][87] = 220;

    Map[174][83] = 'K';
    Map[174][84] = '-';
    Map[174][85] = 'E';
    Map[174][86] = '-';
    Map[174][87] = 'Y';

    //gun table
    Map[190][120] = 196;
    Map[190][121] = 196;
    Map[190][122] = 196;
    Map[190][123] = 196;
    Map[190][124] = 196;
    Map[189][122] = 179;
    Map[188][122] = 179;
    Map[187][120] = 196;
    Map[187][121] = 196;
    Map[187][122] = 196;
    Map[187][123] = 196;
    Map[187][124] = 196;

    Map[183][120] = 'G';
    Map[183][121] = '-';
    Map[183][122] = 'U';
    Map[183][123] = '-';
    Map[183][124] = 'N';

    //key two table
    Map[190][290] = 196;
    Map[190][291] = 196;
    Map[190][292] = 196;
    Map[190][293] = 196;
    Map[190][294] = 196;
    Map[189][292] = 179;
    Map[188][292] = 179;
    Map[187][290] = 196;
    Map[187][291] = 196;
    Map[187][292] = 196;
    Map[187][293] = 196;
    Map[187][294] = 196;

    Map[183][290] = 'K';
    Map[183][291] = '-';
    Map[183][292] = 'E';
    Map[183][293] = '-';
    Map[183][294] = 'Y';

    for(int r = 190; r > 172; r--){

        Map[r][297] = 222;
    }

    int Wallr = 186;

    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;
    Map[Wallr--][280] = 222;

    
    //Laser walls
    Map[172][206] = 222;
    Map[173][206] = 222;
    Map[174][206] = 222;

    Map[172][210] = 222;
    Map[173][210] = 222;
    Map[174][210] = 222;

    Map[172][219] = 222;
    Map[173][219] = 222;
    Map[174][219] = 222;

    Map[172][223] = 222;
    Map[173][223] = 222;
    Map[174][223] = 222;

    Map[172][232] = 222;
    Map[173][232] = 222;
    Map[174][232] = 222;

    Map[172][236] = 222;
    Map[173][236] = 222;
    Map[174][236] = 222;

    Map[172][245] = 222;
    Map[173][245] = 222;
    Map[174][245] = 222;

    Map[172][249] = 222;
    Map[173][249] = 222;
    Map[174][249] = 222;

    Map[172][258] = 222;
    Map[173][258] = 222;
    Map[174][258] = 222;

    Map[172][262] = 222;
    Map[173][262] = 222;
    Map[174][262] = 222;
}
void DrawRoof(char Map[][400])
{
    //FLOOR

    for (int ColumnSecondFloor = 0; ColumnSecondFloor < 300; ColumnSecondFloor++)
    {
        //if(ColumnSecondFloor != 275 && ColumnSecondFloor != 276 && ColumnSecondFloor != 277 && ColumnSecondFloor != 278&& ColumnSecondFloor != 279&& ColumnSecondFloor != 280&& ColumnSecondFloor != 281&& ColumnSecondFloor != 274)
        Map[171][ColumnSecondFloor] = 219;
    }
}
void DrawLevel2(char Map[][400], int& z, int &Health, int &rHero, int &cHero)
{

    for (int rowWallR = 192; rowWallR < 212; rowWallR++) {

        Map[rowWallR][1] = 221;
    }

    for (int rowWallL = 192; rowWallL < 205; rowWallL++) {

        Map[rowWallL][15] = 222;
    }

    for (int ColumnSecondFloor = 0; ColumnSecondFloor < 30; ColumnSecondFloor++)
    {
        Map[212][ColumnSecondFloor] = 219;
    }

    for (int ColumnSecondFloor = 30; ColumnSecondFloor < 90; ColumnSecondFloor++)
    {
        Map[219][ColumnSecondFloor] = '~';
        Map[220][ColumnSecondFloor] = '~';
        Map[221][ColumnSecondFloor] = '~';
        Map[222][ColumnSecondFloor] = '~';
        Map[223][ColumnSecondFloor] = '~';
        Map[224][ColumnSecondFloor] = '~';
        Map[225][ColumnSecondFloor] = '~';
        Map[226][ColumnSecondFloor] = '~';
        Map[227][ColumnSecondFloor] = '~';

    }

    for (int row = 213; row < 233; row++) {

        Map[row][29] = 221;
    }

    for (int cow = 213; cow < 233; cow++) {

        Map[cow][90] = 221;
    }

    for (int ColumnSecondFloor = 90; ColumnSecondFloor < 231; ColumnSecondFloor++)
    {
        Map[212][ColumnSecondFloor] = 219;
    }

    for (int rowWallR = 213; rowWallR < 262; rowWallR++) {

        Map[rowWallR][230] = 221;
    }

    for (int ColumnSecondFloor = 230; ColumnSecondFloor < 245; ColumnSecondFloor++)
    {
        Map[262][ColumnSecondFloor] = 219;
    }

    for (int r = 262; r > 252; r--) {

        Map[r][245] = 222;
    }

    for (int c = 245; c < 255; c++) {

        Map[252][c] = 220;
    }

    for (int r = 252; r > 242; r--) {

        Map[r][255] = 222;
    }

    for (int c = 255; c < 265; c++) {

        Map[242][c] = 220;
    }

    for (int r = 242; r > 232; r--) {

        Map[r][265] = 222;
    }

    for (int c = 265; c < 390; c++) {

        Map[232][c] = 219;
    }

    for (int c = 260; c < 380; c++) {

        Map[222][c] = 219;
    }

    Map[222][386] = 219;
    Map[222][387] = 219;
    Map[222][388] = 219;
    Map[222][389] = 219;

    for(int r = 232; r > 191 ; r--){

        Map[r][390] = 222;
    }

    for(int r = 221; r > 191; r--){

        Map[r][330] = 222;
    }

    for(int r = 221; r > 191; r--){

        Map[r][260] = 222;
    }

        for(int r = 190; r > 170; r--){

        Map[r][395] = 222;
    }

    int con = 289;
    int ron = 218;
    Map[ron][con] = '|';
    Map[ron][con+1] = 'T';
    Map[ron][con+2] = 'O';
    Map[ron][con+3] = '-';
    Map[ron][con+4] = 'E';
    Map[ron][con+5] = 'S';
    Map[ron][con+6] = 'C';
    Map[ron][con+7] = 'A';
    Map[ron][con+8] = 'P';
    Map[ron][con+9] = 'E';
    Map[ron][con+10] = '|';
    Map[ron+1][con+3] = '|';
    Map[ron+1][con+4] = '-';
    Map[ron+1][con+5] = '-';
    Map[ron+1][con+6] = '-';
    Map[ron+1][con+7] = '>';
    Map[ron+1][con+8] = '|';

    Map[204][21] = '|';
    Map[204][22] = 'C';
    Map[204][23] = '-';
    Map[204][24] = 'P';
    Map[204][25] = '-';
    Map[204][26] = '2';
    Map[204][27] = '|';


    Map[216][370] = '|';
    Map[216][371] = 'C';
    Map[216][372] = '-';
    Map[216][373] = 'P';
    Map[216][374] = '-';
    Map[216][375] = '3';
    Map[216][376] = '|';

    //ladder

    int Clol = 380;
    Map[231][Clol+0] = 'o';
    Map[231][Clol+1] = ' ';
    Map[231][Clol+2] = ' ';
    Map[231][Clol+3] = ' ';
    Map[231][Clol+4] = ' ';
    Map[231][Clol+5] = 'o';

    Map[230][Clol+0] = '|';
    Map[230][Clol+1] = ' ';
    Map[230][Clol+2] = ' ';
    Map[230][Clol+3] = ' ';
    Map[230][Clol+4] = ' ';
    Map[230][Clol+5] = '|';

    Map[229][Clol+0] = '+';
    Map[229][Clol+1] = '-';
    Map[229][Clol+2] = '-';
    Map[229][Clol+3] = '-';
    Map[229][Clol+4] = '-';
    Map[229][Clol+5] = '+';

    Map[228][Clol+0] = '+';
    Map[228][Clol+1] = '-';
    Map[228][Clol+2] = '-';
    Map[228][Clol+3] = '-';
    Map[228][Clol+4] = '-';
    Map[228][Clol+5] = '+';

    Map[227][Clol+0] = '|';
    Map[227][Clol+1] = ' ';
    Map[227][Clol+2] = ' ';
    Map[227][Clol+3] = ' ';
    Map[227][Clol+4] = ' ';
    Map[227][Clol+5] = '|';

    Map[226][Clol+0] = '+';
    Map[226][Clol+1] = '-';
    Map[226][Clol+2] = '-';
    Map[226][Clol+3] = '-';
    Map[226][Clol+4] = '-';
    Map[226][Clol+5] = '+';

    Map[225][Clol+0] = '|';
    Map[225][Clol+1] = ' ';
    Map[225][Clol+2] = ' ';
    Map[225][Clol+3] = ' ';
    Map[225][Clol+4] = ' ';
    Map[225][Clol+5] = '|';

    Map[224][Clol+0] = '+';
    Map[224][Clol+1] = '-';
    Map[224][Clol+2] = '-';
    Map[224][Clol+3] = '-';
    Map[224][Clol+4] = '-';
    Map[224][Clol+5] = '+';

    Map[223][Clol+0] = '|';
    Map[223][Clol+1] = ' ';
    Map[223][Clol+2] = ' ';
    Map[223][Clol+3] = ' ';
    Map[223][Clol+4] = ' ';
    Map[223][Clol+5] = '|';

    Map[222][Clol+0] = 'o';
    Map[222][Clol+1] = '-';
    Map[222][Clol+2] = '-';
    Map[222][Clol+3] = '-';
    Map[222][Clol+4] = '-';
    Map[222][Clol+5] = 'o';

    //clouds
    int constant = 1;
    int C = 170;
    Map[193 - constant][C++] = '.';
    Map[193 - constant][C++] = '-';
    Map[193 - constant][C++] = '~';
    Map[193 - constant][C++] = '~';
    Map[193 - constant][C++] = '-';
    Map[193 - constant][C++] = '.';
    C = 169;
    Map[194 - constant][C--] = '-';
    Map[194 - constant][C--] = '~';
    Map[194 - constant][C--] = ' ';
    Map[194 - constant][C--] = '~';
    Map[194 - constant][C--] = ' ';
    Map[194 - constant][C--] = '-';
    Map[194 - constant][C--] = '.';
    Map[194 - constant][C] = ' ';
    Map[195 - constant][C--] = '/';
    Map[196 - constant][C++] = '|';
    Map[197 - constant][C] = '\\';
    C += 2;
    Map[198 - constant][C++] = '~';
    Map[198 - constant][C++] = '-';
    Map[198 - constant][C++] = ' ';
    Map[198 - constant][C++] = '.';
    Map[198 - constant][C++] = '_';
    Map[198 - constant][C++] = ' ';
    Map[198 - constant][C++] = ',';
    Map[198 - constant][C++] = '.';
    Map[198 - constant][C++] = ' ';
    Map[198 - constant][C++] = ',';
    Map[198 - constant][C++] = '.';
    Map[198 - constant][C++] = ',';
    Map[198 - constant][C++] = '.';
    Map[198 - constant][C++] = ',';
    Map[198 - constant][C++] = ' ';
    Map[198 - constant][C++] = ',';
    Map[198 - constant][C++] = '.';
    Map[198 - constant][C++] = '.';
    Map[198 - constant][C++] = ' ';
    Map[198 - constant][C++] = '-';
    Map[198 - constant][C++] = '~';
    Map[195 - constant][181] = '~';
    Map[195 - constant][182] = ' ';
    Map[195 - constant][183] = '-';
    Map[195 - constant][184] = '.';
    Map[196 - constant][186] = '"';
    Map[196 - constant][187] = ',';
    Map[197 - constant][186] = '.';
    Map[197 - constant][187] = '"';
    C = 169;
    Map[194 - constant][C++] = '(';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = ')';
    Map[194 - constant][C++] = '_';
    Map[194 - constant][C++] = ' ';
    Map[194 - constant][C++] = '_';


    int constant1 = 1;
    int C1 = 190;
    Map[193 - constant1][C1++] = '.';
    Map[193 - constant1][C1++] = '-';
    Map[193 - constant1][C1++] = '~';
    Map[193 - constant1][C1++] = '~';
    Map[193 - constant1][C1++] = '-';
    Map[193 - constant1][C1++] = '.';
    C1 = 189;
    Map[194 - constant1][C1--] = '-';
    Map[194 - constant1][C1--] = '~';
    Map[194 - constant1][C1--] = ' ';
    Map[194 - constant1][C1--] = '~';
    Map[194 - constant1][C1--] = ' ';
    Map[194 - constant1][C1--] = '-';
    Map[194 - constant1][C1--] = '.';
    Map[194 - constant1][C1] = ' ';
    Map[195 - constant1][C1--] = '/';
    Map[196 - constant1][C1++] = '|';
    Map[197 - constant1][C1] = '\\';
    C1 += 2;
    Map[198 - constant1][C1++] = '~';
    Map[198 - constant1][C1++] = '-';
    Map[198 - constant1][C1++] = ' ';
    Map[198 - constant1][C1++] = '.';
    Map[198 - constant1][C1++] = '_';
    Map[198 - constant1][C1++] = ' ';
    Map[198 - constant1][C1++] = ',';
    Map[198 - constant1][C1++] = '.';
    Map[198 - constant1][C1++] = ' ';
    Map[198 - constant1][C1++] = ',';
    Map[198 - constant1][C1++] = '.';
    Map[198 - constant1][C1++] = ',';
    Map[198 - constant1][C1++] = '.';
    Map[198 - constant1][C1++] = ',';
    Map[198 - constant1][C1++] = ' ';
    Map[198 - constant1][C1++] = ',';
    Map[198 - constant1][C1++] = '.';
    Map[198 - constant1][C1++] = '.';
    Map[198 - constant1][C1++] = ' ';
    Map[198 - constant1][C1++] = '-';
    Map[198 - constant1][C1++] = '~';
    Map[195 - constant1][181 + 20] = '~';
    Map[195 - constant1][182 + 20] = ' ';
    Map[195 - constant1][183 + 20] = '-';
    Map[195 - constant1][184 + 20] = '.';
    Map[196 - constant1][186 + 20] = '"';
    Map[196 - constant1][187 + 20] = ',';
    Map[197 - constant1][186 + 20] = '.';
    Map[197 - constant1][187 + 20] = '"';
    C1 = 189;
    Map[194 - constant1][C1++] = '(';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = ')';
    Map[194 - constant1][C1++] = '_';
    Map[194 - constant1][C1++] = ' ';
    Map[194 - constant1][C1++] = '_';
    
    Map[199][189 - 5] = '/';
    Map[198][189 - 5] = '\\';

    Map[199][183 - 15] = '/';
    Map[198][183 - 15] = '\\';

    Map[199][195 + 8] = '/';
    Map[198][195 + 8] = '\\';


    if (z <= 4)
    {
        Map[200][189 - 5] = '/';
    }
    if (z <= 2)
    {
        Map[201][189 - 5] = '\\';
    }
    if (z <= 0)
    {
        Map[202][189 - 5] = '/';
    }
    if (z <= -2)
    {
        Map[203][189 - 5] = '\\';
    }
    if (z <= -4)
    {
        Map[204][189 - 5] = '/';
    }
    if (z <= -6)
    {
        Map[205][189 - 5] = '\\';
    }
    if (z <= -8)
    {
        Map[206][189 - 5] = '/';
    }
    if (z <= -10)
    {
        Map[207][189 - 5] = '\\';
    }
    if (z <= -12)
    {
        Map[208][189 - 5] = '/';
    }
    if (z <= -14)
    {
        Map[209][189 - 5] = '\\';
    }
    if (z == -16)
    {
        z = 4;
    }
    z--;
   
    //
    if (z <= 4)
    {
        Map[200][183 - 15] = '/';
    }
    if (z <= 2)
    {
        Map[201][183 - 15] = '\\';
    }
    if (z <= 0)
    {
        Map[202][183 - 15] = '/';
    }
    if (z <= -2)
    {
        Map[203][183 - 15] = '\\';
    }
    if (z <= -4)
    {
        Map[204][183 - 15] = '/';
    }
    if (z <= -6)
    {
        Map[205][183 - 15] = '\\';
    }
    if (z <= -8)
    {
        Map[206][183 - 15] = '/';
    }
    if (z <= -10)
    {
        Map[207][183 - 15] = '\\';
    }
    if (z <= -12)
    {
        Map[208][183 - 15] = '/';
    }
    if (z <= -14)
    {
        Map[209][183 - 15] = '\\';
    }

    //
    if (z <= 4)
    {
        Map[200][195 + 8] = '/';
    }
    if (z <= 2)
    {
        Map[201][195 + 8] = '\\';
    }
    if (z <= 0)
    {
        Map[202][195 + 8] = '/';
    }
    if (z <= -2)
    {
        Map[203][195 + 8] = '\\';
    }
    if (z <= -4)
    {
        Map[204][195 + 8] = '/';
    }
    if (z <= -6)
    {
        Map[205][195 + 8] = '\\';
    }
    if (z <= -8)
    {
        Map[206][195 + 8] = '/';
    }
    if (z <= -10)
    {
        Map[207][195 + 8] = '\\';
    }
    if (z <= -12)
    {
        Map[208][195 + 8] = '/';
    }
    if (z <= -14)
    {
        Map[209][195 + 8] = '\\';
    }
    //

    if ((rHero+2 == 208 && (cHero == 189 - 5 || cHero == 189 - 4 || cHero == 189 - 6) && Map[208][189 - 5] == '/') || (rHero+2 == 208 && (cHero == 183 - 15 || cHero == 183 - 14 || cHero == 183 - 16) && Map[208][183 - 15] == '/') || (rHero == 208+2 && (cHero == 195 + 8 || cHero == 195 + 9 || cHero == 195 + 7)&& Map[208][195 + 8] == '/')){

        Health = 0;
    }

}

void DrawElevator(char x[][400], int rElevator, int cElevator, int rElevator2) { // drawing the elevator
    
    
    for (int c = cElevator; c < 42; c++) {
        x[rElevator][c] = 219;
    }
    for (int c = cElevator + 14; c < 56; c++) {
        x[rElevator2][c] = 219;
    }
    for (int c = cElevator + 28; c < 70; c++) {
        x[rElevator][c] = 219;
    }
    for (int c = cElevator + 42; c < 84; c++) {
        x[rElevator2][c] = 219;
    }
    
}
void MoveElevator(int& rElevator, int& dirElevator, int& stopelevator, int& rHero, int cHero, int&rElevator2 , int CheckPoint) {
    
    if (rElevator == 212) {
        dirElevator = -1;
    }
    if (rElevator == 197) { 
        dirElevator = 1; 
    }

    
    if (dirElevator == 1)
    {
        rElevator ++; 
        rElevator2--;
    }
    if (dirElevator == -1)
    {
        rElevator--; 
        rElevator2++;
    }

    //Add Num
    int Num;

    if(CheckPoint == 1){

        Num = 100;
    }

    if(CheckPoint == 2){

        Num = 0;
    }

    if (cHero < 42 && cHero > 32 && rHero+Num < rElevator) {

        rHero = rElevator - 3;
    }
    if (cHero < 56 && cHero > 46 && rHero+Num< rElevator2) {

        rHero = rElevator2 - 3;
    }
    if (cHero < 70 && cHero > 60 && rHero+Num < rElevator) {

        rHero = rElevator - 3;
    }
    if (cHero < 84 && cHero > 74 && rHero+Num < rElevator2) {

        rHero = rElevator2 - 3;
    }

}

void DrawAndRemoveBarrierAndLaserAtLevel1(char Map[][400], int rHero, int cHero, int& flagBarrier, int& flagBarrier2, int IndR, int IndC, int& laser, int& Fcheck, int& FlagLaser, int FlagDeadEnemy2, int &FlagFall, int &Health)
{

    if ((IndR == 176 && IndC == 83) || (IndR == 176 && IndC == 84) || (IndR == 176 && IndC == 85) || (IndR == 176 && IndC == 86))
    {
        flagBarrier = 1;
    }

    if ((IndR == 231 && IndC == 240) || (IndR == 210 && IndC == 241) || (IndR == 210 && IndC == 242) || (IndR == 210 && IndC == 243))
    {
        FlagFall = 1;
    }

    if (FlagFall == 0) {

        for (int c = 231; c < 246; c++) {

            Map[212][c] = 219; 
        }

    }

    if (FlagFall == 0) {

        for (int r = 212; r > 192; r--) {

            Map[r][246] = 221;
        }
    }

    if (FlagFall == 1) {

        Map[209][240] = 'T';
        Map[209][241] = '-';
        Map[209][242] = 'R';
        Map[209][243] = '-';
        Map[209][244] = 'A';
        Map[209][245] = '-';
        Map[209][246] = 'P';
        
    }




    if (FlagFall == 1) {

        for (int c = 231; c < 241; c++) {

            Map[212][c] = ' ';
        }
    }

    if (FlagFall == 1) {

        for (int r = 211; r < 190; r++) {

            Map[r][241] = ' ';
        }
    }

    if (FlagLaser == 1 && FlagDeadEnemy2 == 1)
    {
        flagBarrier2 = 1;
    }

    if (flagBarrier == 0)
    {
        for (int RowBarrier = 190; RowBarrier > 185; RowBarrier--)
        {
            Map[RowBarrier][100] = 222;
        }
    }

    if (flagBarrier == 1)
    {
        for (int RowBarrier = 190; RowBarrier > 186; RowBarrier--)
        {
            Map[RowBarrier][100] = ' ';
        }

    }

    if ((IndR == 189 && IndC == 102) || (IndR == 189 && IndC == 103) || (IndR == 189 && IndC == 104) && Fcheck == 0)
    {
        flagBarrier = 0;
        Fcheck = 1;
    }

    if ((IndR == 185 && IndC == 290) || (IndR == 185 && IndC == 291) || (IndR == 185 && IndC == 292) || (IndR == 185 && IndC == 293))
    {
        flagBarrier = 1;
    }

    if (flagBarrier2 == 0) {

        for (int Rbarrier = 190; Rbarrier > 185; Rbarrier--) {

            Map[Rbarrier][280] = 222;
        }
    }

    if (flagBarrier2 == 1)
    {
        for (int RowBarrier = 190; RowBarrier > 186; RowBarrier--)
        {
            Map[RowBarrier][280] = ' ';
        }

    }

    if ((IndR == 189 && IndC == 275) || (IndR == 189 && IndC == 276) || (IndR == 189 && IndC == 277)) {

        FlagLaser = 1;
    }

    if (FlagLaser == 0) {

        laser++;

        if (laser <= 15)
        {
            for (int r = 172; r < 190; r++)
            {
                Map[r][260] = 176;
                Map[r][234] = 176;
                Map[r][208] = 176;
            }
        }

        if (laser >= 15)
        {
            for (int r = 172; r < 190; r++)
            {
                Map[r][247] = 176;
                Map[r][221] = 176;
            }
        }

        if (laser == 30)
        {
            laser = 0;
        }
    }
    if(flagBarrier2 == 0){
        
        if ((((cHero == 260 || cHero == 259 || cHero == 261) && rHero == 188) || ((cHero == 234 || cHero == 233 || cHero == 235) && rHero == 188) || ((cHero == 208 || cHero == 207 || cHero == 209) && rHero == 188)) && (laser <= 15)||(((cHero == 247 || cHero == 248 || cHero == 246) && rHero == 188) || ((cHero == 221 || cHero == 222 || cHero == 220) && rHero == 188)) && (laser >= 15)) {
        
            Health = 0;
        }
    }
}
void DrawAndRemovePistolLevel2(char Map[][400], int& IndR, int& IndC, int& flagPistol, int& MoveEnemyToHero, int& flagPistol2, int &FlagUp)
{
    //ROW EXCEPTION
    if ((IndR == 189 && IndC == 110) || (IndR == 189 && IndC == 111) || (IndR == 189 && IndC == 112) || (IndR == 189 && IndC == 113))
    {
        flagPistol = 1;
        MoveEnemyToHero = 1;
    }

    if ((IndR == 210 && IndC == 110) || (IndR == 210 && IndC == 111) || (IndR == 210 && IndC == 112) || (IndR == 210 && IndC == 113))
    {
        flagPistol2 = 1;
        MoveEnemyToHero = 1;
    }

    if (flagPistol == 0)
    {
        Map[186][120] = '-';
        Map[186][121] = 205;
        Map[186][122] = 209;
        Map[186][123] = 209;

        Map[190][120] = 196;
        Map[190][121] = 196;
        Map[190][122] = 196;
        Map[190][123] = 196;
        Map[190][124] = 196;
        Map[189][122] = 179;
        Map[188][122] = 179;
        Map[187][120] = 196;
        Map[187][121] = 196;
        Map[187][122] = 196;
        Map[187][123] = 196;
        Map[187][124] = 196;


    }

    if (flagPistol == 1)
    {
        Map[186][120] = ' ';
        Map[186][121] = ' ';
        Map[186][122] = ' ';
        Map[186][123] = ' ';

        Map[190][120] = ' ';
        Map[190][121] = ' ';
        Map[190][122] = ' ';
        Map[190][123] = ' ';
        Map[190][124] = ' ';
        Map[189][122] = ' ';
        Map[188][122] = ' ';
        Map[187][120] = ' ';
        Map[187][121] = ' ';
        Map[187][122] = ' ';
        Map[187][123] = ' ';
        Map[187][124] = ' ';
    }

    if (flagPistol2 == 0) {

        Map[207][110 + 5] = '-';
        Map[207][111 + 5] = 205;
        Map[207][112 + 5] = 209;
        Map[207][113 + 5] = 209;

        Map[211][110 + 5] = 196;
        Map[211][111 + 5] = 196;
        Map[211][112 + 5] = 196;
        Map[211][113 + 5] = 196;
        Map[211][114 + 5] = 196;
        Map[210][112 + 5] = 179;
        Map[209][112 + 5] = 179;
        Map[208][110 + 5] = 196;
        Map[208][111 + 5] = 196;
        Map[208][112 + 5] = 196;
        Map[208][113 + 5] = 196;
        Map[208][114 + 5] = 196;
    }

    if (flagPistol2 == 1)
    {
        Map[207][120] = ' ';
        Map[207][121] = ' ';
        Map[207][122] = ' ';
        Map[207][123] = ' ';

        Map[211][120 + 5] = ' ';
        Map[211][121 + 5] = ' ';
        Map[211][122 + 5] = ' ';
        Map[211][123 + 5] = ' ';
        Map[211][124 + 5] = ' ';
        Map[210][122 + 5] = ' ';
        Map[209][122 + 5] = ' ';
        Map[208][120 + 5] = ' ';
        Map[208][121 + 5] = ' ';
        Map[208][122 + 5] = ' ';
        Map[208][123 + 5] = ' ';
        Map[208][124 + 5] = ' ';
    }


    if((IndR == 189 && IndC == 350) || (IndR == 189 && IndC == 349) || (IndR == 189 && IndC == 348) || (IndR == 189 && IndC == 347) || (IndR == 189 && IndC == 346) || (IndR == 189 && IndC == 351) || (IndR == 189 && IndC == 353) || (IndR == 189 && IndC == 352) || (IndR == 189 && IndC == 346) || (IndR == 189 && IndC == 354) || (IndR == 189 && IndC == 355) || (IndR == 189 && IndC == 356) || (IndR == 189 && IndC == 357) || (IndR == 189 && IndC == 358) || (IndR == 189 && IndC == 359) || (IndR == 189 && IndC == 360) || (IndR == 189 && IndC == 361) || (IndR == 189 && IndC == 362) || (IndR == 189 && IndC == 363) || (IndR == 189 && IndC == 364) || (IndR == 189 && IndC == 365) || (IndR == 189 && IndC == 366) || (IndR == 189 && IndC == 367) || (IndR == 189 && IndC == 368) || (IndR == 189 && IndC == 369) || (IndR == 189 && IndC == 370)){

        FlagUp = 1;
    }

    if(FlagUp == 0){

        int ColumnFirstFlood = 335;

        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        Map[191][ColumnFirstFlood++] = ' ';
        //Map[191][ColumnFirstFlood++] = 219;
        
    }

    if(FlagUp == 1){

        int ColumnFirstFlood = 335;

        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        Map[191][ColumnFirstFlood++] = 219;
        //Map[191][ColumnFirstFlood++] = 219;
    }
}
void DrawAndRemoveToilet(char Map[][400], int& FlagBarrierAtLevel1No2) {

    if (FlagBarrierAtLevel1No2 == 0) {

        Map[190][4 + 2] = 220;
        Map[190][5 + 2] = 220;
        Map[190][6 + 2] = 220;
        Map[190][7 + 2] = 220;
        Map[190][8 + 2] = 220;
        Map[190][9 + 2] = 220;
        Map[189][5 + 2] = 222;
        Map[189][8 + 2] = 222;
        Map[188][4 + 2] = 220;
        Map[188][5 + 2] = 220;
        Map[188][6 + 2] = 220;
        Map[188][7 + 2] = 220;
        Map[188][8 + 2] = 220;
        Map[188][9 + 2] = 220;
        Map[187][4 + 2] = 222;
        Map[186][4 + 2] = 222;

    }

    if (FlagBarrierAtLevel1No2 == 1) {

        Map[190][4 + 2] = ' ';
        Map[190][5 + 2] = ' ';
        Map[190][6 + 2] = ' ';
        Map[190][7 + 2] = ' ';
        Map[190][8 + 2] = ' ';
        Map[190][9 + 2] = ' ';
        Map[189][5 + 2] = ' ';
        Map[189][8 + 2] = ' ';
        Map[188][4 + 2] = ' ';
        Map[188][5 + 2] = ' ';
        Map[188][6 + 2] = ' ';
        Map[188][7 + 2] = ' ';
        Map[188][8 + 2] = ' ';
        Map[188][9 + 2] = ' ';
        Map[187][4 + 2] = ' ';
        Map[186][4 + 2] = ' ';

        Map[191][4 + 2] = ' ';
        Map[191][5 + 2] = ' ';
        Map[191][6 + 2] = ' ';
        Map[191][7 + 2] = ' ';
        Map[191][8 + 2] = ' ';
        Map[191][9 + 2] = ' ';
        Map[191][3 + 2] = ' ';
        Map[191][10 + 2] = ' ';
        Map[191][2 + 2] = ' ';
        Map[191][11 + 2] = ' ';
        Map[191][1 + 2] = ' ';
        Map[191][12 + 2] = ' ';
        Map[191][0 + 2] = ' ';

    
    }
}

//BULLETS
void shootSingleBullet(char x[][400], int& IndR, int& IndC, int& bulletX, int& bulletY)
{

    bulletX = IndR;
    bulletY = IndC + 4;
}
void moveSingleBullet(char x[][400], int& IndR, int& IndC, int& bulletX, int& bulletY, int& FlagDeadEnemy2, int& HealthEnemy2, int& HitEnemy2L, int HitBoss, int& HPBoss , int &columnEnemy2)
{
    bulletY++;

    if (bulletY < IndC + 30)
    {
        if (x[bulletX][bulletY] == ' ')
        {
            if (bulletY > 0)
            {
                x[bulletX][bulletY - 1] = ' ';
            }
            x[bulletX][bulletY] = '*';

            if (bulletX == 189 && (bulletY == HitEnemy2L || bulletY == HitEnemy2L - 1 || bulletY == HitEnemy2L - 2 || bulletY == HitEnemy2L - 3 || bulletY == HitEnemy2L - 4) && HealthEnemy2 > 0)
            {
                HealthEnemy2--;
                bulletX = -1;
                bulletY = -1;

                if(HealthEnemy2 == 0){

                    FlagDeadEnemy2 == 1;
                }
            }

            if (bulletX == IndR && (bulletY == HitBoss || bulletY == HitBoss - 1 || bulletY == HitBoss - 2 || bulletY == HitBoss - 3 || bulletY == HitBoss - 4) && HPBoss >= 0)
            {
                HPBoss--;
                bulletX = -1;
                bulletY = -1;
            }
        }
        else
        {
            bulletX = -1;
            bulletY = -1;
        }
    }
    else
    {
        bulletX = -1;
        bulletY = -1;
    }
}

void shootMultipleBullets(char map[][400], int& heroRow, int& heroCol, int bulletRows[], int bulletCols[], int bulletActive[], int numBullets) {

    for (int i = 0; i < numBullets; i++) {

        if (bulletActive[i] == 0) {

            bulletRows[i] = heroRow;
            bulletCols[i] = heroCol + 3;
            bulletActive[i] = 1;
            //break;
        }
    }
}
void moveMultipleBullets(char map[][400], int& heroRow, int& IndR, int& heroCol, int bulletRows[], int bulletCols[], int bulletActive[], int numBullets, int height, int& enemyFlag, int& HitBoss, int& HealthBoss, int &HitEnemyLeft, int &FlagsEnemyDead, int &sEnemyHP, int &LeftIndexColumFinalBoss , int &FlagFinalBoss) {

    for (int i = 0; i < numBullets; i++) {

        if (bulletActive[i] == 1) {

            bulletCols[i]++;

            if (bulletCols[i] < heroCol + 30) {

                if (map[bulletRows[i]][bulletCols[i]] == ' ') {

                    if (bulletCols[i] > 0) {

                        //map[bulletRows[i]][bulletCols[i] - 1] = ' ';
                    }

                    map[bulletRows[i]][bulletCols[i]] = '*';

                    if (bulletRows[i] == 210 && (bulletCols[i] == HitEnemyLeft || bulletCols[i] == HitEnemyLeft - 1 || bulletCols[i] == HitEnemyLeft - 2 || bulletCols[i] == HitEnemyLeft - 3 || bulletCols[i] == HitEnemyLeft - 4) && sEnemyHP > 0)
                    {   
                        sEnemyHP--;

                        if(sEnemyHP == 0){

                            FlagsEnemyDead == 1;
                        }
                    }

                    if (bulletRows[i] == 189 && (bulletCols[i] == LeftIndexColumFinalBoss || bulletCols[i] == LeftIndexColumFinalBoss - 1 || bulletCols[i] == LeftIndexColumFinalBoss - 2 || bulletCols[i] == LeftIndexColumFinalBoss - 3 || bulletCols[i] == LeftIndexColumFinalBoss - 4) && HealthBoss > 0)
                    {   
                        HealthBoss--;

                        if(HealthBoss == 0){

                            FlagFinalBoss == 1;
                        }
                    }

                }

                else {

                    bulletActive[i] = 0;
                }
            }

            else {

                bulletActive[i] = 0;
            }
        }
    }
}

void shootMultipleBulletsLeft(char map[][400], int& heroRow, int& heroCol, int bulletRows[], int bulletCols[], int bulletActive[], int numBullets) {
    
    for (int i = 0; i < numBullets; i++) {
        
        if (bulletActive[i] == 0) {
            
            bulletRows[i] = heroRow;
            bulletCols[i] = heroCol - 3; 
            
            bulletActive[i] = 1;
            break; 
            
        }
    }
}


void moveMultipleBulletsLeft(char map[][400], int& heroRow, int& IndR, int& heroCol, int bulletRows[], int bulletCols[], int bulletActive[], int numBullets, int height, int& enemyFlag, int& HitBoss, int& HealthBoss, int& HitEnemyLeft, int& FlagsEnemyDead, int& sEnemyHP, int& RightIndexColumFinalBoss, int& FlagFinalBoss) {
    
    for (int i = 0; i < numBullets; i++) {
        
        if (bulletActive[i] == 1) {

            if (bulletCols[i] < 399) {
                
                map[bulletRows[i]][bulletCols[i] + 1] = ' ';
            }

            bulletCols[i]--;

            if (bulletCols[i] > heroCol - 30) {
               
                if (map[bulletRows[i]][bulletCols[i]] == ' ') {
                    
                    map[bulletRows[i]][bulletCols[i]] = '*';

                    if (bulletRows[i] == 189 && (bulletCols[i] == RightIndexColumFinalBoss || bulletCols[i] == RightIndexColumFinalBoss - 1 || bulletCols[i] == RightIndexColumFinalBoss - 2 || bulletCols[i] == RightIndexColumFinalBoss - 3 || bulletCols[i] == RightIndexColumFinalBoss - 4) && HealthBoss > 0) {
                        
                        HealthBoss--;
                        bulletActive[i] = 0; 
                        
                        if (HealthBoss == 0) {
                            
                            FlagFinalBoss = 1;
                        }
                    }
                } 
                
                else {
                    
                    bulletActive[i] = 0; 
                    
                }
            } 
            
            else {
                
                bulletActive[i] = 0; 
                
            }
        }
    }
}



void DrawHealthEnemy2(char Map[][400], int& Health, int& FlagDeadEnemy2, int& timer, int Move, int& flagpistol)
{

    if (Health == 5)
    {
        int col = 166;
        Map[182][col++ + Move] = 'H';
        Map[182][col++ + Move] = 'P';
        Map[182][col++ + Move] = ' ';        
        Map[182][col++ + Move] = ':';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = '5';

    }

    if (Health == 4)
    {
        int col = 165;
        Map[182][col++ + Move] = 'H';
        Map[182][col++ + Move] = 'P';
        Map[182][col++ + Move] = ' ';        
        Map[182][col++ + Move] = ':';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = '4';

    }
    if (Health == 3)
    {
        int col = 165;
        Map[182][col++ + Move] = 'H';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = ':';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = '3';

    }
    if (Health == 2)
    {
        int col = 165;
        Map[182][col++ + Move] = 'H';
        Map[182][col++ + Move] = 'P';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = ':';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = '2';

    }
    if (Health == 1)
    {
        int col = 165;
        Map[182][col++ + Move] = 'H';
        Map[182][col++ + Move] = 'P';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = ':';
        Map[182][col++ + Move] = ' ';
        Map[182][col++ + Move] = '1';

    }

    if(Health == 0)
    {
        int col = 165;
        Map[182][col++ + Move] = 'D';
        Map[182][col++ + Move] = 'E';       
        Map[182][col++ + Move] = 'A';
        Map[182][col++ + Move] = 'D';

        FlagDeadEnemy2 = 1;
    }
}
void DrawEnemy2(char Map[][400], int& Movement, int& FlagDeadOrAlive, int timer, int& IndexColumnEnemy2, int& HitEnemy, int& EnemyHitLeftSide)
{

    if (FlagDeadOrAlive == 0)
    {
        int constant = 30;
        Map[190][195 - constant + Movement] = '\\';
        Map[190][194 - constant + Movement] = '_';
        Map[190][193 - constant + Movement] = '_';
        Map[190][197 - constant + Movement] = 'd';
        Map[190][196 - constant + Movement] = '_';
        Map[190][198 - constant + Movement] = '|';
        Map[190][199 - constant + Movement] = '_';
        Map[190][200 - constant + Movement] = '|';

        Map[190][201 - constant + Movement] = 'b';


        IndexColumnEnemy2 = 201 - constant + Movement;

        Map[190][202 - constant + Movement] = '_';
        Map[190][203 - constant + Movement] = '_';

        Map[189][195 - constant + Movement] = 'Z';

        EnemyHitLeftSide = 195 - constant + Movement;
        Map[189][201 - constant + Movement] = '|';

        HitEnemy = 201 - constant + Movement;

        Map[189][200 - constant + Movement] = '|';
        Map[189][198 - constant + Movement] = '|';
        Map[189][199 - constant + Movement] = '|';

        Map[188][195 - constant + Movement] = '|';
        Map[188][203 - constant + Movement] = '0';
        Map[188][202 - constant + Movement] = '`';
        Map[188][197 - constant + Movement] = '/';
        Map[188][198 - constant + Movement] = '_';
        Map[188][199 - constant + Movement] = '^';
        Map[188][200 - constant + Movement] = '_';
        Map[188][201 - constant + Movement] = '\\';


        Map[187][199 - constant + Movement] = '+';
        Map[187][200 - constant + Movement] = '/';
        Map[187][203 - constant + Movement] = '|';
        Map[187][198 - constant + Movement] = '\\';
        Map[187][195 - constant + Movement] = '|';
        Map[187][195 - constant + Movement] = '0';
        Map[187][196 - constant + Movement] = '/';
        Map[187][198 - constant + Movement] = '\\';
        Map[187][200 - constant + Movement] = '/';
        Map[187][202 - constant + Movement] = 'o';
        Map[187][203 - constant + Movement] = '=';
        Map[187][204 - constant + Movement] = 'o';
        Map[187][201 - constant + Movement] = '/';
        Map[187][199 - constant + Movement] = '^';
        Map[187][197 - constant + Movement] = '\\';
        Map[187][196 - constant + Movement] = '/';


        Map[186][203 - constant + Movement] = '|';
        Map[186][195 - constant + Movement] = '|';
        Map[186][201 - constant + Movement] = '_';
        Map[186][200 - constant + Movement] = '>';
        Map[186][199 - constant + Movement] = '=';
        Map[186][198 - constant + Movement] = '<';
        Map[186][197 - constant + Movement] = '_';


        Map[185][199 - constant + Movement] = '+';
        Map[185][200 - constant + Movement] = '/';
        Map[185][198 - constant + Movement] = '\\';
        Map[185][195 - constant + Movement] = '|';
        Map[184][195 - constant + Movement] = '+';
    }

    if(FlagDeadOrAlive == 1){
        
        if (timer < 10)
        {
            int constant = 30;

            Map[190][199 - constant + Movement] = '*';
            Map[190][201 - constant + Movement] = '*';
            Map[190][203 - constant + Movement] = '*';

            Map[189][195 - constant + Movement] = '*';
            Map[189][200 - constant + Movement] = '*';
            Map[189][197 - constant + Movement] = '*';

            Map[188][195 - constant + Movement] = '*';
            Map[188][203 - constant + Movement] = '*';
            Map[188][197 - constant + Movement] = '*';
            Map[188][200 - constant + Movement] = '*';


            Map[187][199 - constant + Movement] = '*';
            Map[187][200 - constant + Movement] = '*';
            Map[187][203 - constant + Movement] = '*';
            Map[187][196 - constant + Movement] = '*';
            Map[187][203 - constant + Movement] = '*';
            Map[187][199 - constant + Movement] = '*';
            Map[187][196 - constant + Movement] = '*';


            Map[186][203 - constant + Movement] = '*';
            Map[186][199 - constant + Movement] = '*';
        }
    }
}
void MoveEnemy2(int& col, int& IndC, int& MoveEnemy, int& IndexColumnEnemy2, int& HeroHealth, int LevelCount, int StartMoving, int flagdead, int flagPistol)
{
    if (flagPistol == 1) {

        if (flagdead == 0)
        {
            if (IndC > IndexColumnEnemy2 && StartMoving >= 1)
            {
                MoveEnemy = 1;
            }
            if (IndC < IndexColumnEnemy2)
            {
                MoveEnemy = 2;
            }


            if ((IndexColumnEnemy2 == IndC - 3 || IndexColumnEnemy2 == IndC + 3) && StartMoving >= 1)
            {
                MoveEnemy = 3;
            }


            if (MoveEnemy == 1 && StartMoving >= 1)
            {
                col++;
            }

            if (MoveEnemy == 2 && StartMoving >= 1)
            {
                col--;
            }

            if (MoveEnemy == 3 && StartMoving >= 1)
            {
                HeroHealth--;
            }

        }
    }
}

void DrawEnenmySewerLevel2(char Map[][400], int& FlagPistol2 , int FlagsEnemyDead, int &HitEnemyLeft)
{

    if(FlagsEnemyDead == 0){

        if (FlagPistol2 == 1)
        {
            Map[211][150] = '/';
            Map[211][151] = '\\';

            Map[210][147] = '-';
            Map[210][148] = 205;
            Map[210][149] = 209;
            Map[210][150] = 209;
            Map[210][150] = '>';
            Map[210][151] = '>';
            HitEnemyLeft = 147;
            Map[209][149] = '(';
            Map[209][150] = '#';
            Map[209][151] = 'x';
            Map[209][152] = ')';

            Map[208][150] = '/';
            Map[208][152] = '\\';
        }   
    }

    if (FlagPistol2 == 0 || FlagsEnemyDead == 1) {
        
        Map[211][150] = ' ';
        Map[211][151] = ' ';

        Map[210][146] = ' ';
        Map[210][147] = ' ';
        Map[210][148] = ' ';
        Map[210][149] = ' ';
        Map[210][150] = ' ';
        Map[210][151] = ' ';
        Map[209][149] = ' ';
        Map[209][150] = ' ';
        Map[209][151] = ' ';
        Map[209][152] = ' ';

        Map[208][150] = ' ';
        Map[208][152] = ' ';
    }
    

}
void EnenmySewerLevel2Bullets(char Map[][400], int IndR, int IndC, int& FlagEnemy, int& cBullet, int FlagsEnemyDead, int& Health, int FlagPistol2)
{

    if (FlagsEnemyDead == 0)
    {
        if (FlagPistol2 == 1)
        {
            FlagEnemy = 1;
        }
        if (FlagPistol2 == 0)
        {
            FlagEnemy = 0;
        }

        if (FlagEnemy == 1)
        {
            Map[210][cBullet] = '*';
            cBullet--;
        }

        if (cBullet == 110)
        {
            Map[210][cBullet] = ' ';
            cBullet = 149;
        }

        if (IndR == 210 && cBullet == IndC + 3)
        {
            Health--;
            cBullet = 149;
        }
    }

}
void DrawHealthEnemySewer(char Map[][400], int &sEnemyHP, int &FlagsEnemyDead, int FlagStop){
    
    if(sEnemyHP == 20){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '2';
        Map[206][col++] = '0';
    }
    if(sEnemyHP == 19){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '9';
    }
    if(sEnemyHP == 18){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '8';
    }
    if(sEnemyHP == 17){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '7';
    }
    if(sEnemyHP == 16){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '6';
    }
    if(sEnemyHP == 15){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '5';
    }
    if(sEnemyHP == 14){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '4';
    }
    if(sEnemyHP == 13){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '3';
    }
    if(sEnemyHP == 12){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '2';
    }
    if(sEnemyHP == 11){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '1';
    }
    if(sEnemyHP == 10){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
        Map[206][col++] = '0';
    }
    if(sEnemyHP == 9){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '9';
    }
    if(sEnemyHP == 8){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '8';
    }
    if(sEnemyHP == 7){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '7';
    }
    if(sEnemyHP == 6){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '6';
    }
    if(sEnemyHP == 5){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '5';
    }
    if(sEnemyHP == 4){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '4';
    }

    if(sEnemyHP == 3){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '3';
    }
    
    if(sEnemyHP == 9){

        int col = 147;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '2';
    }
    
    if(sEnemyHP == 1){

        int col = 149;

        Map[206][col++] = 'H';
        Map[206][col++] = 'P';       
        Map[206][col++] = ':';
        Map[206][col++] = ' ';
        Map[206][col++] = '1';
    }

    if(sEnemyHP == 0){

        int col = 149;

        Map[206][col++] = 'D';
        Map[206][col++] = 'E';       
        Map[206][col++] = 'A';
        Map[206][col++] = 'D';

        FlagsEnemyDead = 1;
    }
}

void DrawDiagonalElevator(char x[][400], int rDElevator, int cDElevator, int FlagUp) { // drawing the elevator
    
    if(FlagUp == 0){
        for (int c = cDElevator; c < 370; c++) {
            x[rDElevator][c] = 219;
    }
    }

    if(FlagUp == 1){

        for (int c = cDElevator; c < 370; c++) {
            x[rDElevator][c] = ' ';
    }
    }
}
void MoveDiagonalElev(int& rDElevator, int& cDElevator , int& DdirElevator, int& rHero, int& cHero, char X[][400], int &FlagUp)
{
    if(FlagUp == 0){
	    if (DdirElevator == -1)
	    {
		    if (rDElevator == 185)
		    {
			    DdirElevator*= -1;

		    }
		    cDElevator-= 1;
	    }
	    else
	    {
		    if ((rDElevator ) == 220)
		    {
			    DdirElevator *= -1;

		    }
		    cDElevator += 1;
	    }

	    rDElevator += DdirElevator;
	
        if (cHero < 370 && cHero > 330 && rHero < rDElevator) {

            rHero = rDElevator - 3;
        }
    }

    if(FlagUp == 1){

        DdirElevator = 0;
    }
    
}

void DrawHelicopter(int rHeli, int cHeli, char X[][400], int FlagDeadFinalBoss)
{
    if(FlagDeadFinalBoss == 1){
	X[rHeli][cHeli + 4] = '-';
	for (int c = cHeli - 4; c < cHeli + 5; c++) {
		X[rHeli][c] = '-';
	}
	X[rHeli][cHeli + 5] = '*';
	for (int c = cHeli + 6; c < cHeli + 15; c++)
	{
		X[rHeli][c] = '-';
	}
	X[rHeli + 2][cHeli] = '_';
	X[rHeli + 2][cHeli + 1] = '_';
	X[rHeli + 2][cHeli + 2] = '_';
	X[rHeli + 2][cHeli + 3] = ' ';
	X[rHeli + 2][cHeli + 4] = '/';
	X[rHeli + 2][cHeli + 5] = '^';
	X[rHeli + 2][cHeli + 6] = '^';
	X[rHeli + 2][cHeli + 7] = '[';
	X[rHeli + 2][cHeli + 8] = '_';
	X[rHeli + 2][cHeli + 9] = '_';
	X[rHeli + 2][cHeli + 10] = '_';
	X[rHeli + 3][cHeli - 1] = '/';
	X[rHeli + 3][cHeli] = '|';
	X[rHeli + 3][cHeli + 1] = '^';
	X[rHeli + 3][cHeli + 2] = '+';
	X[rHeli + 3][cHeli + 3] = '-';
	X[rHeli + 3][cHeli + 4] = '-';
	X[rHeli + 3][cHeli + 5] = '-';
	X[rHeli + 3][cHeli + 6] = '-';
	X[rHeli + 3][cHeli + 7] = '+';
	X[rHeli + 3][cHeli + 8] = ' ';
	X[rHeli + 3][cHeli + 9] = ' ';
	X[rHeli + 3][cHeli + 10] = ' ';
	X[rHeli + 3][cHeli + 11] = '|';
	X[rHeli + 3][cHeli + 12] = '#';
	for (int c = cHeli + 13; c < cHeli + 24; c++) {
		X[rHeli + 3][c] = '_';
	}
	X[rHeli + 3][cHeli + 20] = '/';
	X[rHeli + 3][cHeli + 21] = '/';
	X[rHeli + 2][cHeli + 21] = '_';
	X[rHeli + 4][cHeli - 3] = '(';
	X[rHeli + 4][cHeli - 2] = ' ';
	X[rHeli + 4][cHeli - 1] = '-';
	X[rHeli + 4][cHeli] = '+';
	X[rHeli + 4][cHeli + 1] = ' ';
	X[rHeli + 4][cHeli + 2] = '|';
	X[rHeli + 4][cHeli + 3] = '_';
	X[rHeli + 4][cHeli + 4] = '_';
	X[rHeli + 4][cHeli + 5] = '_';
	X[rHeli + 4][cHeli + 6] = '_';
	X[rHeli + 4][cHeli + 7] = '|';
	X[rHeli + 4][cHeli + 8] = ' ';
	X[rHeli + 4][cHeli + 9] = ' ';
	X[rHeli + 4][cHeli + 10] = ' ';
	for (int c = cHeli + 11; c < cHeli + 36; c++) {
		X[rHeli + 4][c] = '_';
	}
	for (int c = cHeli + 28; c < cHeli + 33; c++) {
		X[rHeli + 4][c] = '-';
	}
	X[rHeli + 4][cHeli + 23] = '+';
	X[rHeli + 4][cHeli + 24] = '/';
	X[rHeli + 5][cHeli - 2] = '=';
	X[rHeli + 5][cHeli - 1] = '=';
	for (int c = cHeli; c < cHeli + 10; c++) {
		X[rHeli + 5][c] = '_';
	}
	X[rHeli + 5][cHeli + 10] = '-';
	X[rHeli + 5][cHeli + 11] = '-';
	X[rHeli + 5][cHeli + 12] = '`';
	X[rHeli + 6][cHeli] = '`';
	X[rHeli + 6][cHeli + 1] = '_';
	X[rHeli + 6][cHeli + 2] = '|';
	X[rHeli + 6][cHeli + 3] = '_';
	X[rHeli + 6][cHeli + 4] = '_'; //bomb loc
	X[rHeli + 6][cHeli + 5] = '_';
	X[rHeli + 6][cHeli + 6] = '|';
	//////////////////////////





	X[rHeli + 6][cHeli + 7] = '_';
	X[rHeli + 6][cHeli + 8] = '_';
	X[rHeli + 6][cHeli + 9] = ' ';
	X[rHeli + 6][cHeli + 10] = '-';
	X[rHeli + 6][cHeli + 11] = 'w';
	X[rHeli + 6][cHeli + 12] = 'h';


    //ladder to heli

    int Clol = 348+3;
    X[190][Clol+0] = 'o';
    X[190][Clol+1] = ' ';
    X[190][Clol+2] = ' ';
    X[190][Clol+3] = ' ';
    X[190][Clol+4] = ' ';
    X[190][Clol+5] = 'o';

    X[185+4][Clol+0] = '|';
    X[185+4][Clol+1] = ' ';
    X[185+4][Clol+2] = ' ';
    X[185+4][Clol+3] = ' ';
    X[185+4][Clol+4] = ' ';
    X[185+4][Clol+5] = '|';

    X[184+4][Clol+0] = '+';
    X[184+4][Clol+1] = '-';
    X[184+4][Clol+2] = '-';
    X[184+4][Clol+3] = '-';
    X[184+4][Clol+4] = '-';
    X[184+4][Clol+5] = '+';

    X[183+4][Clol+0] = '|';
    X[183+4][Clol+1] = ' ';
    X[183+4][Clol+2] = ' ';
    X[183+4][Clol+3] = ' ';
    X[183+4][Clol+4] = ' ';
    X[183+4][Clol+5] = '|';

    X[182+4][Clol+0] = '+';
    X[182+4][Clol+1] = '-';
    X[182+4][Clol+2] = '-';
    X[182+4][Clol+3] = '-';
    X[182+4][Clol+4] = '-';
    X[182+4][Clol+5] = '+';


    X[181+4][Clol+0] = '|';
    X[181+4][Clol+1] = ' ';
    X[181+4][Clol+2] = ' ';
    X[181+4][Clol+3] = ' ';
    X[181+4][Clol+4] = ' ';
    X[181+4][Clol+5] = '|';

    X[180+4][Clol+0] = '+';
    X[180+4][Clol+1] = '-';
    X[180+4][Clol+2] = '-';
    X[180+4][Clol+3] = '-';
    X[180+4][Clol+4] = '-';
    X[180+4][Clol+5] = '+';


    X[179+4][Clol+0] = '|';
    X[179+4][Clol+1] = ' ';
    X[179+4][Clol+2] = ' ';
    X[179+4][Clol+3] = ' ';
    X[179+4][Clol+4] = ' ';
    X[179+4][Clol+5] = '|';

    X[178+4][Clol+0] = '+';
    X[178+4][Clol+1] = '-';
    X[178+4][Clol+2] = '-';
    X[178+4][Clol+3] = '-';
    X[178+4][Clol+4] = '-';
    X[178+4][Clol+5] = '+';

    X[177+4][Clol+0] = '|';
    X[177+4][Clol+1] = ' ';
    X[177+4][Clol+2] = ' ';
    X[177+4][Clol+3] = ' ';
    X[177+4][Clol+4] = ' ';
    X[177+4][Clol+5] = '|';

    X[176+4][Clol+0] = '+';
    X[176+4][Clol+1] = '-';
    X[176+4][Clol+2] = '-';
    X[176+4][Clol+3] = '-';
    X[176+4][Clol+4] = '-';
    X[176+4][Clol+5] = '+';

    X[175+4][Clol+0] = '|';
    X[175+4][Clol+1] = ' ';
    X[175+4][Clol+2] = ' ';
    X[175+4][Clol+3] = ' ';
    X[175+4][Clol+4] = ' ';
    X[175+4][Clol+5] = '|';

    X[174+4][Clol+0] = '+';
    X[174+4][Clol+1] = '-';
    X[174+4][Clol+2] = '-';
    X[174+4][Clol+3] = '-';
    X[174+4][Clol+4] = '-';
    X[174+4][Clol+5] = '+';

    X[173+4][Clol+0] = '|';
    X[173+4][Clol+1] = ' ';
    X[173+4][Clol+2] = ' ';
    X[173+4][Clol+3] = ' ';
    X[173+4][Clol+4] = ' ';
    X[173+4][Clol+5] = '|';

    X[172+4][Clol+0] = 'o';
    X[172+4][Clol+1] = '-';
    X[172+4][Clol+2] = '-';
    X[172+4][Clol+3] = '-';
    X[172+4][Clol+4] = '-';
    X[172+4][Clol+5] = 'o';

    }

    if(FlagDeadFinalBoss == 0){
	X[rHeli][cHeli + 4] = ' ';
	for (int c = cHeli - 4; c < cHeli + 5; c++) {
		X[rHeli][c] = ' ';
	}
	X[rHeli][cHeli + 5] = ' ';
	for (int c = cHeli + 6; c < cHeli + 15; c++)
	{
		X[rHeli][c] = ' ';
	}
	X[rHeli + 2][cHeli] = ' ';
	X[rHeli + 2][cHeli + 1] = ' ';
	X[rHeli + 2][cHeli + 2] = ' ';
	X[rHeli + 2][cHeli + 3] = ' ';
	X[rHeli + 2][cHeli + 4] = ' ';
	X[rHeli + 2][cHeli + 5] = ' ';
	X[rHeli + 2][cHeli + 6] = ' ';
	X[rHeli + 2][cHeli + 7] = ' ';
	X[rHeli + 2][cHeli + 8] = ' ';
	X[rHeli + 2][cHeli + 9] = ' ';
	X[rHeli + 2][cHeli + 10] = ' ';
	X[rHeli + 3][cHeli - 1] = ' ';
	X[rHeli + 3][cHeli] = ' ';
	X[rHeli + 3][cHeli + 1] = ' ';
	X[rHeli + 3][cHeli + 2] = ' ';
	X[rHeli + 3][cHeli + 3] = ' ';
	X[rHeli + 3][cHeli + 4] = ' ';
	X[rHeli + 3][cHeli + 5] = ' ';
	X[rHeli + 3][cHeli + 6] = ' ';
	X[rHeli + 3][cHeli + 7] = ' ';
	X[rHeli + 3][cHeli + 8] = ' ';
	X[rHeli + 3][cHeli + 9] = ' ';
	X[rHeli + 3][cHeli + 10] = ' ';
	X[rHeli + 3][cHeli + 11] = ' ';
	X[rHeli + 3][cHeli + 12] = ' ';
	for (int c = cHeli + 13; c < cHeli + 24; c++) {
		X[rHeli + 3][c] = ' ';
	}
	X[rHeli + 3][cHeli + 20] = ' ';
	X[rHeli + 3][cHeli + 21] = ' ';
	X[rHeli + 2][cHeli + 21] = ' ';
	X[rHeli + 4][cHeli - 3] = ' ';
	X[rHeli + 4][cHeli - 2] = ' ';
	X[rHeli + 4][cHeli - 1] = ' ';
	X[rHeli + 4][cHeli] = ' ';
	X[rHeli + 4][cHeli + 1] = ' ';
	X[rHeli + 4][cHeli + 2] = ' ';
	X[rHeli + 4][cHeli + 3] = ' ';
	X[rHeli + 4][cHeli + 4] = ' ';
	X[rHeli + 4][cHeli + 5] = ' ';
	X[rHeli + 4][cHeli + 6] = ' ';
	X[rHeli + 4][cHeli + 7] = ' ';
	X[rHeli + 4][cHeli + 8] = ' ';
	X[rHeli + 4][cHeli + 9] = ' ';
	X[rHeli + 4][cHeli + 10] = ' ';
	for (int c = cHeli + 11; c < cHeli + 36; c++) {
		X[rHeli + 4][c] = ' ';
	}
	for (int c = cHeli + 28; c < cHeli + 33; c++) {
		X[rHeli + 4][c] = ' ';
	}
	X[rHeli + 4][cHeli + 23] = ' ';
	X[rHeli + 4][cHeli + 24] = ' ';
	X[rHeli + 5][cHeli - 2] = ' ';
	X[rHeli + 5][cHeli - 1] = ' ';
	for (int c = cHeli; c < cHeli + 10; c++) {
		X[rHeli + 5][c] = ' ';
	}
	X[rHeli + 5][cHeli + 10] = ' ';
	X[rHeli + 5][cHeli + 11] = ' ';
	X[rHeli + 5][cHeli + 12] = ' ';
	X[rHeli + 6][cHeli] = ' ';
	X[rHeli + 6][cHeli + 1] = ' ';
	X[rHeli + 6][cHeli + 2] = ' ';
	X[rHeli + 6][cHeli + 3] = ' ';
	X[rHeli + 6][cHeli + 4] = ' '; //bomb loc
	X[rHeli + 6][cHeli + 5] = ' ';
	X[rHeli + 6][cHeli + 6] = ' ';
	//////////////////////////





	X[rHeli + 6][cHeli + 7] = ' ';
	X[rHeli + 6][cHeli + 8] = ' ';
	X[rHeli + 6][cHeli + 9] = ' ';
	X[rHeli + 6][cHeli + 10] = ' ';
	X[rHeli + 6][cHeli + 11] = ' ';
	X[rHeli + 6][cHeli + 12] = ' ';


    //ladder to heli

    int Clol = 348+3;
    X[190][Clol+0] = ' ';
    X[190][Clol+1] = ' ';
    X[190][Clol+2] = ' ';
    X[190][Clol+3] = ' ';
    X[190][Clol+4] = ' ';
    X[190][Clol+5] = ' ';

    X[185+4][Clol+0] = ' ';
    X[185+4][Clol+1] = ' ';
    X[185+4][Clol+2] = ' ';
    X[185+4][Clol+3] = ' ';
    X[185+4][Clol+4] = ' ';
    X[185+4][Clol+5] = ' ';

    X[184+4][Clol+0] = ' ';
    X[184+4][Clol+1] = ' ';
    X[184+4][Clol+2] = ' ';
    X[184+4][Clol+3] = ' ';
    X[184+4][Clol+4] = ' ';
    X[184+4][Clol+5] = ' ';

    X[183+4][Clol+0] = ' ';
    X[183+4][Clol+1] = ' ';
    X[183+4][Clol+2] = ' ';
    X[183+4][Clol+3] = ' ';
    X[183+4][Clol+4] = ' ';
    X[183+4][Clol+5] = ' ';

    X[182+4][Clol+0] = ' ';
    X[182+4][Clol+1] = ' ';
    X[182+4][Clol+2] = ' ';
    X[182+4][Clol+3] = ' ';
    X[182+4][Clol+4] = ' ';
    X[182+4][Clol+5] = ' ';


    X[181+4][Clol+0] = ' ';
    X[181+4][Clol+1] = ' ';
    X[181+4][Clol+2] = ' ';
    X[181+4][Clol+3] = ' ';
    X[181+4][Clol+4] = ' ';
    X[181+4][Clol+5] = ' ';

    X[180+4][Clol+0] = ' ';
    X[180+4][Clol+1] = ' ';
    X[180+4][Clol+2] = ' ';
    X[180+4][Clol+3] = ' ';
    X[180+4][Clol+4] = ' ';
    X[180+4][Clol+5] = ' ';


    X[179+4][Clol+0] = ' ';
    X[179+4][Clol+1] = ' ';
    X[179+4][Clol+2] = ' ';
    X[179+4][Clol+3] = ' ';
    X[179+4][Clol+4] = ' ';
    X[179+4][Clol+5] = ' ';

    X[178+4][Clol+0] = ' ';
    X[178+4][Clol+1] = ' ';
    X[178+4][Clol+2] = ' ';
    X[178+4][Clol+3] = ' ';
    X[178+4][Clol+4] = ' ';
    X[178+4][Clol+5] = ' ';

    X[177+4][Clol+0] = ' ';
    X[177+4][Clol+1] = ' ';
    X[177+4][Clol+2] = ' ';
    X[177+4][Clol+3] = ' ';
    X[177+4][Clol+4] = ' ';
    X[177+4][Clol+5] = ' ';

    X[176+4][Clol+0] = ' ';
    X[176+4][Clol+1] = ' ';
    X[176+4][Clol+2] = ' ';
    X[176+4][Clol+3] = ' ';
    X[176+4][Clol+4] = ' ';
    X[176+4][Clol+5] = ' ';

    X[175+4][Clol+0] = ' ';
    X[175+4][Clol+1] = ' ';
    X[175+4][Clol+2] = ' ';
    X[175+4][Clol+3] = ' ';
    X[175+4][Clol+4] = ' ';
    X[175+4][Clol+5] = ' ';

    X[174+4][Clol+0] = ' ';
    X[174+4][Clol+1] = ' ';
    X[174+4][Clol+2] = ' ';
    X[174+4][Clol+3] = ' ';
    X[174+4][Clol+4] = ' ';
    X[174+4][Clol+5] = ' ';

    X[173+4][Clol+0] = ' ';
    X[173+4][Clol+1] = ' ';
    X[173+4][Clol+2] = ' ';
    X[173+4][Clol+3] = ' ';
    X[173+4][Clol+4] = ' ';
    X[173+4][Clol+5] = ' ';

    X[172+4][Clol+0] = ' ';
    X[172+4][Clol+1] = ' ';
    X[172+4][Clol+2] = ' ';
    X[172+4][Clol+3] = ' ';
    X[172+4][Clol+4] = ' ';
    X[172+4][Clol+5] = ' ';

    }
}

void DrawFinalBoss(char Map[][400] , int &Movement , int &FlagDeadOrAlive , int timer , int &IndexColFinalBoss , int& HitEnemy , int&EnemyHitLeftSide , int rBoss , int cBoss , int FlagUp, int &EnemyHitRightSide)
{
    if(FlagDeadOrAlive == 0){
    if (FlagUp == 1)
    {
    Map[rBoss][cBoss +Movement] = ' ';
	Map[rBoss][cBoss + 1 + Movement] = '|';
	Map[rBoss][cBoss - 1+ Movement] = '|';
	Map[rBoss][cBoss - 2+ Movement] = '<';
    HitEnemy = cBoss - 2 + Movement;
	Map[rBoss][cBoss + 2+ Movement] = '>';
    EnemyHitLeftSide = cBoss+2+Movement;
    EnemyHitRightSide = cBoss+2-Movement;
	Map[rBoss - 1][cBoss + Movement] = '`';
	Map[rBoss - 1][cBoss + Movement - 1] = '#';

    IndexColFinalBoss = cBoss+Movement-1;
	Map[rBoss - 1][cBoss + Movement - 2] = '(';
	Map[rBoss - 1][cBoss + Movement + 1] = '_';
	Map[rBoss - 1][cBoss + Movement + 2] = '`';
	Map[rBoss - 1][cBoss + Movement + 3] = ')';
	Map[rBoss - 2][cBoss + Movement] = '_';
	Map[rBoss - 2][cBoss + Movement + 1] = '_';
	Map[rBoss - 2][cBoss + Movement + 2] = '\\';
	Map[rBoss - 2][cBoss + Movement + 3] = '_';
	Map[rBoss - 2][cBoss + Movement - 1] = '/';
	Map[rBoss - 2][cBoss + Movement - 2] = '_';
	Map[rBoss + 1][cBoss + Movement] = ' ';
	Map[rBoss + 1][cBoss + Movement + 1] = '\\';
	Map[rBoss + 1][cBoss + Movement + 2] = '_';
	Map[rBoss + 1][cBoss + Movement - 1] = '/';
	Map[rBoss + 1][cBoss + Movement - 2] = '_';
    }
    }

    if (FlagDeadOrAlive == 1 && timer < 15)
    {
    Map[rBoss - 1][cBoss + Movement - 2] = '*';
	Map[rBoss - 1][cBoss + Movement + 2] = '*';
	Map[rBoss - 2][cBoss + Movement] = '*';
	Map[rBoss - 2][cBoss + Movement + 2] = '*';
	Map[rBoss - 2][cBoss + Movement - 1] = '*';
	Map[rBoss + 1][cBoss + Movement] = '*';
	Map[rBoss + 1][cBoss + Movement + 2] = '*';
	Map[rBoss + 1][cBoss + Movement - 2] = '*';

    }


}
void MoveFinalBoss(int & col , int &IndC , int &IndR , int &MoveBoss , int &IndexColumnFinalBoss , int&HeroHealth , int LevelCount , int StartMoving , int FlagDead , int FlagUp)
{
    if(FlagDead == 0){
    if (FlagUp == 1)
    {
    if (IndC > 330)
    {
        StartMoving++;
    }

    if(StartMoving > 0)
    {
    if (IndC > IndexColumnFinalBoss && StartMoving >= 1)
    {
        MoveBoss = 1;
    }
    if (IndC < IndexColumnFinalBoss)
    {
        MoveBoss = 2;
    }

    
    if ((IndexColumnFinalBoss == IndC - 2 || IndexColumnFinalBoss == IndC + 2)&& StartMoving >= 1)
    {
        MoveBoss = 3;
    }


    if (MoveBoss == 1 && StartMoving >= 1)
    {
        col++;
    }

    if (MoveBoss == 2 && StartMoving >= 1)
    {
        col--;
    }

    if (MoveBoss == 3 && IndR == 189 && StartMoving >= 1)
    {
        HeroHealth-=1;
    }
    }
    }
    }
}
void HealthFinalBoss(char Map[][400] , int &Health , int &FlagDeadFinalBoss , int& timer , int Move , int LevelCount , int &FlagPistol)
{

    if (Health > 35 && Health <= 40)
    {
        
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '1';
        Map[rowFinalBoss][col++ + Move] = '0';
        Map[rowFinalBoss][col++ + Move] = '0';
 
    }

    if (Health > 32 && Health <= 35)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '9';
        Map[rowFinalBoss][col++ + Move] = '3';

    }

    if (Health > 29 && Health <= 32)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '8';
        Map[rowFinalBoss][col++ + Move] = '7';

    }

    if (Health > 26 && Health <= 29)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '8';
        Map[rowFinalBoss][col++ + Move] = '1';

    }

    if (Health > 23 && Health <= 26)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '7';
        Map[rowFinalBoss][col++ + Move] = '4';

    }

    if (Health > 21 && Health <= 23)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '6';
        Map[rowFinalBoss][col++ + Move] = '9';

    }

    if (Health > 19 && Health <= 21)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '6';
        Map[rowFinalBoss][col++ + Move] = '2';

    }
    if (Health > 16 && Health <= 19)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '5';
        Map[rowFinalBoss][col++ + Move] = '6';

    }
    if (Health > 13 && Health <= 16)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '4';
        Map[rowFinalBoss][col++ + Move] = '8';
 
    }
    if (Health > 10 && Health <= 13)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '4';
        Map[rowFinalBoss][col++ + Move] = '0';
 
    }

     if (Health > 7 && Health <= 10)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '3';
        Map[rowFinalBoss][col++ + Move] = '1';
 
    }

     if (Health > 4 && Health <= 7)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '2';
        Map[rowFinalBoss][col++ + Move] = '2';

    }

     if (Health > 0 && Health <= 4)
    {
        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'H';
        Map[rowFinalBoss][col++ + Move] = 'P';
        Map[rowFinalBoss][col++ + Move] = ' ';        
        Map[rowFinalBoss][col++ + Move] = ':';
        Map[rowFinalBoss][col++ + Move] = ' ';
        Map[rowFinalBoss][col++ + Move] = '1';
        Map[rowFinalBoss][col++ + Move] = '3';

    }


    if (Health == 0 && timer != 0)
    {
        FlagDeadFinalBoss = 1;

        int rowFinalBoss= 187-2;
        int col = 370-3;
        Map[rowFinalBoss][col++ + Move] = 'D';
        Map[rowFinalBoss][col++ + Move] = '-';
        Map[rowFinalBoss][col++ + Move] = 'E';        
        Map[rowFinalBoss][col++ + Move] = '-';
        Map[rowFinalBoss][col++ + Move] = 'A';
        Map[rowFinalBoss][col++ + Move] = '-';
        Map[rowFinalBoss][col++ + Move] = 'D';

    }

    
}
void FinalBossBullet(char Map[][400], int IndR, int IndC, int &cBullet, int FlagDeadOrAlive, int &Health, int LevelCount, int HitEnemy, int &Move, int FlagUp) {
    if(FlagUp == 1){
    if (FlagDeadOrAlive == 0) {
        
        if (cBullet - 1 - Move >= 0) {
            Map[188][cBullet - 1 - Move] = ' ';
        }

        
        if (cBullet - 2 - Move >= 0) {
            Map[188][cBullet - 2 - Move] = '*';
        }

        cBullet--;

        
        if (cBullet == IndC) {
            Health--;
        }

        
        if (cBullet < 300) {
            cBullet = 368;
        }

        Map[190][369+1] = '|';
        Map[189][369+1] = '|';
        Map[188][369+1] = 191;
        Map[188][369] = 196;
    }
    }
}


//CHECKPOINTS
void CheckPoints(char Map[][400] , int &rHero , int &cHero , int &IndR , int &IndC , int &mapRowStart , int &mapRowEnd , int &mapColS , int &mapColE , int &CheckPointFlag , int &Health , int&FlagAK)
{
    // VOID TRAP
    if (Map[IndR + 2][IndC] == '~')
    {
        Health = 0;

    }
    if ((IndR == 210 && IndC == 23) || (IndR == 210 && IndC == 24 ) || (IndR == 210 && IndC == 25))
    {
        CheckPointFlag = 2;
    }
    
 
    if ((IndR == 220 && IndC == 372 ) || (IndR == 220 && IndC == 373) || (IndR == 220 && IndC == 371))
    {
        CheckPointFlag = 3;
    }

}
void DrawGameOver(char Map[][400] , int flaggameover , int FlagWin)
{
if (flaggameover == 1)
{
    for (int r = 0 ; r < 30 ; r++)
    {
        for (int c = 0 ; c < 90 ; c++)
        {
            Map[r][c] = ' ';
        }
    }
}
                              
    if (flaggameover == 1)
    {
    cout << endl << endl << endl << endl<< endl << endl << endl << endl<< endl << endl << endl << endl;
    cout << "                       ____                         ___                 \n";
    cout << "                      / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ \n";
    cout << "                     | |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|\n";
    cout << "                     | |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   \n";
    cout << "                      \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   \n";
    cout << "                                                  \n";
    }
}
void CreateStatus(char Map[][400], int &Health, int &flagGameOver, int row, int column , int &IndR , int &IndC , int CheckPointRow , int CheckPointCol , int &rHero , int &cHero , int CheckPointFlag , int &mapRowStart , int &mapRowEnd , int &mapColS , int &mapColE ,int &Lives)
{

    if (Health == 6)
    {

        Map[row+3-1][column + 1] = 'H'; 
        Map[row+3-1][column + 2] = 'E'; 
        Map[row+3-1][column + 3] = 'R'; 
        Map[row+3-1][column + 4] = 'O'; 
        Map[row+3-1][column + 5] = ' '; 
        Map[row+3-1][column + 6] = 'H'; 
        Map[row+3-1][column + 7] = 'E'; 
        Map[row+3-1][column + 8] = 'A'; 
        Map[row+3-1][column + 9] = 'L';
        Map[row+3-1][column + 10] = 'T'; 
        Map[row+3-1][column + 11] = 'H';
        Map[row+3-1][column + 12] = ' '; 
        Map[row+3-1][column + 13] = ':'; 
        Map[row+3-1][column + 14] = ' '; 
        Map[row+3-1][column + 15] = '5'; 
        Map[row+3-1][column + 16] = '0';  

 
 
    }
    if (Health == 5)
    {
 
        Map[row+3-1][column + 1] = 'H'; 
        Map[row+3-1][column + 2] = 'E'; 
        Map[row+3-1][column + 3] = 'R'; 
        Map[row+3-1][column + 4] = 'O'; 
        Map[row+3-1][column + 5] = ' '; 
        Map[row+3-1][column + 6] = 'H'; 
        Map[row+3-1][column + 7] = 'E'; 
        Map[row+3-1][column + 8] = 'A'; 
        Map[row+3-1][column + 9] = 'L';
        Map[row+3-1][column + 10] = 'T'; 
        Map[row+3-1][column + 11] = 'H';
        Map[row+3-1][column + 12] = ' '; 
        Map[row+3-1][column + 13] = ':'; 
        Map[row+3-1][column + 14] = ' '; 
        Map[row+3-1][column + 15] = '4'; 
        Map[row+3-1][column + 16] = '2';  
    }
    if (Health == 4)
    {   
        Map[row+3-1][column + 1] = 'H'; 
        Map[row+3-1][column + 2] = 'E'; 
        Map[row+3-1][column + 3] = 'R'; 
        Map[row+3-1][column + 4] = 'O'; 
        Map[row+3-1][column + 5] = ' '; 
        Map[row+3-1][column + 6] = 'H'; 
        Map[row+3-1][column + 7] = 'E'; 
        Map[row+3-1][column + 8] = 'A'; 
        Map[row+3-1][column + 9] = 'L';
        Map[row+3-1][column + 10] = 'T'; 
        Map[row+3-1][column + 11] = 'H';
        Map[row+3-1][column + 12] = ' '; 
        Map[row+3-1][column + 13] = ':'; 
        Map[row+3-1][column + 14] = ' '; 
        Map[row+3-1][column + 15] = '3'; 
        Map[row+3-1][column + 16] = '5';  
    }
    if (Health == 3)
    {
        Map[row+3-1][column + 1] = 'H'; 
        Map[row+3-1][column + 2] = 'E'; 
        Map[row+3-1][column + 3] = 'R'; 
        Map[row+3-1][column + 4] = 'O'; 
        Map[row+3-1][column + 5] = ' '; 
        Map[row+3-1][column + 6] = 'H'; 
        Map[row+3-1][column + 7] = 'E'; 
        Map[row+3-1][column + 8] = 'A'; 
        Map[row+3-1][column + 9] = 'L';
        Map[row+3-1][column + 10] = 'T'; 
        Map[row+3-1][column + 11] = 'H';
        Map[row+3-1][column + 12] = ' '; 
        Map[row+3-1][column + 13] = ':'; 
        Map[row+3-1][column + 14] = ' '; 
        Map[row+3-1][column + 15] = '2'; 
        Map[row+3-1][column + 16] = '7';  
    }
    if (Health == 2)
    {
        Map[row+3-1][column + 1] = 'H'; 
        Map[row+3-1][column + 2] = 'E'; 
        Map[row+3-1][column + 3] = 'R'; 
        Map[row+3-1][column + 4] = 'O'; 
        Map[row+3-1][column + 5] = ' '; 
        Map[row+3-1][column + 6] = 'H'; 
        Map[row+3-1][column + 7] = 'E'; 
        Map[row+3-1][column + 8] = 'A'; 
        Map[row+3-1][column + 9] = 'L';
        Map[row+3-1][column + 10] = 'T'; 
        Map[row+3-1][column + 11] = 'H';
        Map[row+3-1][column + 12] = ' '; 
        Map[row+3-1][column + 13] = ':'; 
        Map[row+3-1][column + 14] = ' '; 
        Map[row+3-1][column + 15] = '1'; 
        Map[row+3-1][column + 16] = '9';  
    }
    if (Health == 1)
    {
        Map[row+3-1][column + 1] = 'H'; 
        Map[row+3-1][column + 2] = 'E'; 
        Map[row+3-1][column + 3] = 'R'; 
        Map[row+3-1][column + 4] = 'O'; 
        Map[row+3-1][column + 5] = ' '; 
        Map[row+3-1][column + 6] = 'H'; 
        Map[row+3-1][column + 7] = 'E'; 
        Map[row+3-1][column + 8] = 'A'; 
        Map[row+3-1][column + 9] = 'L';
        Map[row+3-1][column + 10] = 'T'; 
        Map[row+3-1][column + 11] = 'H';
        Map[row+3-1][column + 12] = ' '; 
        Map[row+3-1][column + 13] = ':'; 
        Map[row+3-1][column + 14] = ' '; 
        Map[row+3-1][column + 15] = '7'; 
        Map[row+3-1][column + 16] = ' ';  
    }

    if (Lives == 3)
    {
        Map[row+4-1][column+1] = 'L';
        Map[row+4-1][column+2] = 'I';
        Map[row+4-1][column+3] = 'V';
        Map[row+4-1][column+4] = 'E';
        Map[row+4-1][column+5] = 'S';
        Map[row+4-1][column+6] = ' ';
        Map[row+4-1][column+7] = ':';
        Map[row+4-1][column+8] = ' ';
        Map[row+4-1][column+9] = '3';
    }

    if (Lives == 2)
    {
        Map[row+4-1][column+1] = 'L';
        Map[row+4-1][column+2] = 'I';
        Map[row+4-1][column+3] = 'V';
        Map[row+4-1][column+4] = 'E';
        Map[row+4-1][column+5] = 'S';
        Map[row+4-1][column+6] = ' ';
        Map[row+4-1][column+7] = ':';
        Map[row+4-1][column+8] = ' ';
        Map[row+4-1][column+9] = '2';
    }

    if (Lives == 1)
    {
        Map[row+4-1][column+1] = 'L';
        Map[row+4-1][column+2] = 'I';
        Map[row+4-1][column+3] = 'V';
        Map[row+4-1][column+4] = 'E';
        Map[row+4-1][column+5] = 'S';
        Map[row+4-1][column+6] = ' ';
        Map[row+4-1][column+7] = ':';
        Map[row+4-1][column+8] = ' ';
        Map[row+4-1][column+9] = '1';
    }

    if (CheckPointFlag == 1)
    {
        Map[row+5-1][column+1] = 'C';
        Map[row+5-1][column+2] = 'H';
        Map[row+5-1][column+3] = 'E';
        Map[row+5-1][column+4] = 'C';
        Map[row+5-1][column+5] = 'K';
        Map[row+5-1][column+6] = ' ';
        Map[row+5-1][column+7] = 'P';
        Map[row+5-1][column+8] = 'O';
        Map[row+5-1][column+9] = 'I';
        Map[row+5-1][column+10] = 'N';
        Map[row+5-1][column+11] = 'T';
        Map[row+5-1][column+12] = ' ';
        Map[row+5-1][column+13] = ':';
        Map[row+5-1][column+14] = ' ';
        Map[row+5-1][column+15] = '1';
    }

    if (CheckPointFlag == 2)
    {
        Map[row+5-1][column+1] = 'C';
        Map[row+5-1][column+2] = 'H';
        Map[row+5-1][column+3] = 'E';
        Map[row+5-1][column+4] = 'C';
        Map[row+5-1][column+5] = 'K';
        Map[row+5-1][column+6] = ' ';
        Map[row+5-1][column+7] = 'P';
        Map[row+5-1][column+8] = 'O';
        Map[row+5-1][column+9] = 'I';
        Map[row+5-1][column+10] = 'N';
        Map[row+5-1][column+11] = 'T';
        Map[row+5-1][column+12] = ' ';
        Map[row+5-1][column+13] = ':';
        Map[row+5-1][column+14] = ' ';
        Map[row+5-1][column+15] = '2';
    }

    if (CheckPointFlag == 3)
    {
        Map[row+5-1][column+1] = 'C';
        Map[row+5-1][column+2] = 'H';
        Map[row+5-1][column+3] = 'E';
        Map[row+5-1][column+4] = 'C';
        Map[row+5-1][column+5] = 'K';
        Map[row+5-1][column+6] = ' ';
        Map[row+5-1][column+7] = 'P';
        Map[row+5-1][column+8] = 'O';
        Map[row+5-1][column+9] = 'I';
        Map[row+5-1][column+10] = 'N';
        Map[row+5-1][column+11] = 'T';
        Map[row+5-1][column+12] = ' ';
        Map[row+5-1][column+13] = ':';
        Map[row+5-1][column+14] = ' ';
        Map[row+5-1][column+15] = '3';
    }

    if (Lives == 0)
    {
        flagGameOver = 1;
    }
    if (Health == 0 && CheckPointFlag == 1)
    {   
        rHero = IndR;
        IndR = 188 ;
        rHero = IndR;
        IndC = 18 ;
        cHero = IndC;
        mapRowStart = 190;
        mapRowEnd = 220 ;
        mapColS = 0-2;
        mapColE = 88;
        Health = 6;

        Lives --;
 
    }

    if (Health == 0 && CheckPointFlag == 2)
    {   

        rHero = IndR;
        IndR = 208 ;
        rHero = IndR;
        IndC = 21 ;
        cHero = IndC;
        mapRowStart = 190;
        mapRowEnd = 220 ;
        mapColS = 1;
        mapColE = 91;
        Health = 6;

        Lives--;
    }

    if (Health == 0 && CheckPointFlag == 3)
    {
        rHero = IndR;
        IndR = 218 ;
        rHero = IndR;
        IndC = 372 ;
        cHero = IndC;
        mapRowStart = 190;
        mapRowEnd = 220 ;
        mapColS = 352;
        mapColE = 442;
        Health = 6;

        Lives--;   
    }

    
}
void ExitDoor(char Map[][400] , int IndR , int IndC , int &FlagGameOver, int FlagDead, int FlagWin)
{
    if(FlagDead == 1){

        int c = 350-9;
        Map[185-1][c++] = 'C';
        Map[185-1][c++] = 'L';
        Map[185-1][c++] = 'I';
        Map[185-1][c++] = 'M';
        Map[185-1][c++] = 'B';
        int r = 350-9;
        Map[185+1-1][r++] = 'T';
        Map[185+1-1][r++] = 'O';
        int f = 350-9;
        Map[185+2-1][f++] = 'W';
        Map[185+2-1][f++] = 'I';
        Map[185+2-1][f++] = 'N';
        int g = 349-1;
        Map[185+2-1][g] = '|';
        Map[185+1-1][g] = '|';
        Map[185+0-1][g+1] = '\\';
        Map[185+0-1][g-1] = '/';


    }

    Map[175][353] = 219;

    
    if ((IndR == 175 && IndC == 353) || (IndR == 175 && IndC == 354) || (IndR == 175 && IndC == 355) || (IndR == 175 && IndC == 356))
    {
        FlagWin = 1;
    }

}
void WinGame(char Map[][400], int FlagWin){

    if (FlagWin == 1)
    {
    for (int r = 0 ; r < 30 ; r++)
    {
        for (int c = 0 ; c < 90 ; c++)
        {
            Map[r][c] = ' ';
        }
    }
    }

    if (FlagWin == 1) {
    cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
    cout << "                                      __        ___                      \n";
    cout << "                                      \\ \\      / (_)_ __                 \n";
    cout << "                                       \\ \\ /\\ / /| | '_ \\               \n";
    cout << "                                        \\ V  V / | | | | |               \n";
    cout << "                                         \\_/\\_/  |_|_| |_|               \n";
    cout << "                                                                       \n";
    }
}
int main()
{
    char Map[400][400];
    int rowElevatorAboveWater = 182, columnElevatorAboveWater = 191, DirectionElevatorAboveWater = 1;
    char UserMove = 'G';
    int rowMapBorderStart = 190, rowMapBorderEnd = 220, colMapBorderStart = 0, colMapBorderEnd = 90;
    int FlagBarrierAtLevel1 = 0;
    int FlagBarrierAtLevel1No2 = 0;
    int rowElevatorToLevel3 = 212, columnElevatorToLevel3 = 32, DirectionElevatorToLevel3 = 1;
    int rHero = 188, cHero = 20, flagHeroElevatorAboveWater = 0;
    int IndexRowHero, IndexColumnHero;
    int ctJump = 0, flagJump = 0, JumpAgain = 0, JJ = 0;
    int MidPointRowElev, MidPointColElev;
    int IndexRLvl3, IndexCLvl3;
    int flagHeroElevatorLvl3 = 0;
    int SingleBulletRow = -1, SingleBulletCol = -1;
    int LevelCount = 1;
    int FlagLadder = 0;
    int FlagPistol = 0;
    int FlagEnemy1 = 0, cBulletEnemy1 = 149;
    int ctActivateLaser = 0;
    int flagGameOver = 0;
    int CloudRainCol1, CloudRainRow1 = 194, flagrain1 = 0;
    int CloudRainCol2, CloudRainRow2 = 204, flagrain2 = 0;
    int CloudRainCol3, CloudRainRow3 = 201, flagrain3 = 0;
    int CloudRainCol4, CloudRainRow4 = 199, flagrain4 = 0;
    int z = 4;
    int ctcloud = 0;
    int GameOver = 0, Health = 6;
    int CheckPointFlag = 1;
    int CheckPointRow = 185;
    int CheckPointCol = 5;
    int constantrainrow = 179;
    int FlagLaserLevel3 = 0;
    int countGameOver = 0;
    //s
    int columnEnemy2 = 0;
    //s
    int columnBoss = 0;
    int bulletX = -1, bulletY = -1;
    int bulletXR = -1, bulletYR = -1;
    int FlagDeadEnemy1 = 0;
    int HeroLives = 3;
    //s
    int HealthEnemy2 = 5, FlagDeadEnemy2 = 0, TimerEnemy2 = 1, MoveEnemyToHero = 0, IndexColumnEnemy2, HitEnemy2, HitEnemy2L;
    //s
    int HPFinalBoss = 40, FlagFinalBoss = 0, TimerFinalBoss = 1, MoveBossToHero = 0, LeftIndexColumFinalBoss,RIghtIndexColumFinalBoss, HitBoss, HitBossL;
    int FinalBossBullets = 368;
    int rBoss =189, cBoss = 370;
    int width = 400;
    int height = 400;
    int numBullets = 0;
    int bulletRows[100];
    int bulletCols[100];
    int bulletActive[100];

    int bulletRowsL[100];
    int bulletColsL[100];
    int bulletActiveL[100];
    int numBulletsL = 0;

    int enemyFlag = 0;
    int flagAK = 0;
    int laser = 0;
    int Fcheck = 0;
    int FlagLaser = 0;
    int rowElevatorToLevel31 = 212;
    int rowElevatorToLevel32 = 212;
    int rowElevatorToLevel33 = 212;
    int columnElevatorToLevel31 = 52;
    int columnElevatorToLevel32 = 72;
    int columnElevatorToLevel33 = 92;
    int FlagPistol2 = 0;
    int rElevator = 212, cElevator = 32, direlevator = 1, rElevator2 = 197;
    int stopelevator = 0;
    int FlagFall = 0;
    int rDElevator = 210;
    int cDElevator = 350;
    int Ddirelevator = 1;
    int Dstopelevator = 0;
    int Clol = 380;
    int FlagUp = 0;
    int rHeli = 170;
    int cHeli = 348;
    int sEnemyHP = 20;
    int FlagsEnemyDead = 0;
    int FlagStop = 0;
    int FlagNum = 0;
    int HitEnemyLeft;
    int FlagWin = 0;
    int Win = 0;
    int countWin = 0;


    for (;;)
    {
        for (; !_kbhit();)
        {
            if( GameOver == 0 && Win == 0){
                
                Clear_and_Draw_Map(Map);
                DrawLvl1(Map);
                DrawRoof(Map);

                if(FlagBarrierAtLevel1No2 == 1){
                
                    DrawLevel2(Map, z, Health, rHero, cHero);

                }
                DrawAndRemoveToilet(Map, FlagBarrierAtLevel1No2);
                DrawAndRemovePistolLevel2(Map, IndexRowHero, IndexColumnHero, FlagPistol, MoveEnemyToHero, FlagPistol2, FlagUp);
                DrawAndRemoveBarrierAndLaserAtLevel1(Map, rHero, cHero, FlagBarrierAtLevel1, FlagBarrierAtLevel1No2, IndexRowHero, IndexColumnHero, laser, Fcheck, FlagLaser, FlagDeadEnemy2, FlagFall, Health);
            
                HeroDraw(Map, rHero, cHero, IndexRowHero, IndexColumnHero, UserMove);
            
                ApplyJump(Map, rHero, cHero, ctJump, flagJump, rowMapBorderStart, rowMapBorderEnd, JumpAgain, IndexRowHero, IndexColumnHero, JJ);
                ApplyGravity(Map, rHero, cHero, ctJump, rowMapBorderStart, rowMapBorderEnd, JumpAgain, IndexRowHero, IndexColumnHero, FlagLadder);
                TimerEnemy2++;

                MoveEnemy2(columnEnemy2, IndexColumnHero, MoveEnemyToHero, IndexColumnEnemy2, Health, LevelCount, MoveEnemyToHero, FlagDeadEnemy2, FlagPistol);
                DrawEnemy2(Map, columnEnemy2, FlagDeadEnemy2, TimerEnemy2, IndexColumnEnemy2, HitEnemy2, HitEnemy2L);
                DrawHealthEnemy2(Map, HealthEnemy2, FlagDeadEnemy2, TimerEnemy2, columnEnemy2, FlagPistol);
            
                DrawElevator(Map, rElevator, cElevator, rElevator2);
                MoveElevator(rElevator, direlevator, stopelevator, rHero, cHero, rElevator2, CheckPointFlag);
            
                DrawDiagonalElevator(Map , rDElevator, cDElevator, FlagUp);
                MoveDiagonalElev(rDElevator, cDElevator , Ddirelevator, rHero , cHero , Map , FlagUp);
            
            
                DrawEnenmySewerLevel2(Map, FlagPistol2, FlagsEnemyDead, HitEnemyLeft);
                EnenmySewerLevel2Bullets(Map, IndexRowHero, IndexColumnHero, FlagEnemy1, cBulletEnemy1, FlagsEnemyDead, Health, FlagPistol2);
                DrawHealthEnemySewer(Map, sEnemyHP, FlagsEnemyDead, FlagStop);

                DrawHelicopter(rHeli , cHeli , Map, FlagFinalBoss);

                MoveFinalBoss (columnBoss , IndexColumnHero ,IndexRowHero, MoveBossToHero , LeftIndexColumFinalBoss , Health , LevelCount , MoveBossToHero ,FlagFinalBoss , FlagUp);
                DrawFinalBoss(Map , columnBoss , FlagFinalBoss , TimerFinalBoss , LeftIndexColumFinalBoss , HitBoss , HitBossL , rBoss , cBoss , FlagUp, RIghtIndexColumFinalBoss);
                HealthFinalBoss(Map , HPFinalBoss , FlagFinalBoss , TimerFinalBoss , columnBoss , LevelCount , FlagPistol);
                FinalBossBullet(Map , IndexRowHero , IndexColumnHero , FinalBossBullets , FlagFinalBoss , Health , LevelCount , HitBoss, MoveBossToHero, FlagUp);

                CheckPoints (Map , rHero , cHero , IndexRowHero , IndexColumnHero , rowMapBorderStart , rowMapBorderEnd , colMapBorderStart , colMapBorderEnd , CheckPointFlag , Health , flagAK);
                CreateStatus(Map, Health,  flagGameOver, rowMapBorderStart, colMapBorderStart , IndexRowHero , IndexColumnHero , CheckPointRow , CheckPointCol , rHero , cHero , CheckPointFlag , rowMapBorderStart , rowMapBorderEnd , colMapBorderStart , colMapBorderEnd , HeroLives);
                ExitDoor(Map , IndexRowHero , IndexColumnHero , flagGameOver, FlagFinalBoss, FlagWin);

                if ((UserMove == 'Y' || UserMove == 'y') && bulletX == -1 && bulletY == -1 && FlagPistol == 1)
                {
                    shootSingleBullet(Map, IndexRowHero, IndexColumnHero, bulletX, bulletY);
                }

                if (UserMove == 'y', bulletX != -1 && bulletY != -1 && FlagPistol == 1)
                {
                    moveSingleBullet(Map, IndexRowHero, IndexColumnHero, bulletX, bulletY, FlagDeadEnemy2, HealthEnemy2, HitEnemy2L, HitBossL, HPFinalBoss, columnEnemy2);
                }

                if (((UserMove == 'l' || UserMove == 'L') && FlagPistol2 == 1) || ((UserMove == 'l' || UserMove == 'L') && CheckPointFlag == 3)) {

                    numBullets++;
                    shootMultipleBullets(Map, IndexRowHero, IndexColumnHero, bulletRows, bulletCols, bulletActive, numBullets);
                }

                if (FlagPistol2 == 1 || CheckPointFlag == 3)
                {

                    moveMultipleBullets(Map, IndexRowHero, IndexRowHero, IndexColumnHero, bulletRows, bulletCols, bulletActive, numBullets, height, enemyFlag, HitBoss, HPFinalBoss , HitEnemyLeft , FlagsEnemyDead, sEnemyHP, LeftIndexColumFinalBoss , FlagFinalBoss);
                }

                if ((UserMove == 'k' || UserMove == 'K') && CheckPointFlag == 3) {

                    numBulletsL++;
                    shootMultipleBulletsLeft(Map, IndexRowHero, IndexColumnHero, bulletRowsL, bulletColsL, bulletActiveL, numBulletsL);
                }   

                if (CheckPointFlag == 3)
                {

                    moveMultipleBulletsLeft(Map, IndexRowHero, IndexRowHero, IndexColumnHero, bulletRowsL, bulletColsL, bulletActiveL, numBulletsL, height, enemyFlag, HitBoss, HPFinalBoss , HitEnemyLeft , FlagsEnemyDead, sEnemyHP, RIghtIndexColumFinalBoss , FlagFinalBoss);
                }
            
                Cout_Map_to_Screen(Map, UserMove, rowMapBorderStart, rowMapBorderEnd, colMapBorderStart, colMapBorderEnd, IndexRowHero, IndexColumnHero);
            

                if (flagGameOver == 1)
                {
                    GameOver = 1;
                }

                if(FlagWin == 1){

                    Win = 1;
                }
            }

            if (flagGameOver == 1)
            {
                GameOver = 1;
                countGameOver++;
            }

            if(FlagWin == 1){
                
                Win = 1;
                countWin++;
            }

            if (GameOver == 1 && countGameOver == 1)
            {
                system("cls");
                for (int row = 0; row < 400; row++)
                {
                    for (int col = 0; col < 400; col++)
                    {
                        Map[row][col] = ' ';
                    }
                }

                DrawGameOver(Map , flagGameOver , FlagWin);
            }

            if (Win == 1 && countWin == 1)
            {
                system("cls");
                for (int row = 0; row < 400; row++)
                {
                    for (int col = 0; col < 400; col++)
                    {
                        Map[row][col] = ' ';
                    }
                }

                WinGame(Map , FlagWin);
            }
        }

        UserMove = _getch();
        Move_Hero(Map, rHero, cHero, UserMove, FlagBarrierAtLevel1, IndexRowHero, IndexColumnHero, flagJump, LevelCount, FlagPistol, colMapBorderStart, colMapBorderEnd, GameOver, rowMapBorderStart, rowMapBorderEnd);
    }
}