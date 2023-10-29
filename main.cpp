#include <iostream>
#include <string>


//盤面初期化関数宣言。
void initialize_board(int (&now_board)[8][8]);

//取得可能な石のリストを初期化する関数。
void initialize_getable_stones(int (&getable_stones)[8][8]);

//数値を表示用文字に置換する関数宣言。
char replace_mark(int glid_state);

//数値盤面データを読んで盤面を表示する関数宣言。
void draw_board(int (&now_board)[8][8]);

//座標が盤上かを判定する関数宣言。
bool on_the_board(int i,int j);

//入力に対して盤面を更新する関数。
void update_board(int counter,int (&now_board)[8][8],int i,int j);

//(i,j)に打った時の取得可能な石のリストを得る関数定義。
void list_up_getable_stones(int sign,int (&now_board)[8][8],int (&getable_stones)[8][8],int i,int j);

//合法手判定関数宣言。
bool legal_move(int (&getable_stones)[8][8]);

//入力受付。
void input_UI(int counter,int& i,int& j);

//手番に手があるかの局面判定関数。
bool turn_player_have_move(int (&legal_moves_list)[8][8]);

//ゲームループ。
void game_loop(int (&board)[8][8]);

//合法手座標と取得可能石のリストのバンドル生成関数宣言。
void list_up_legal_moves_and_getable_stones(int counter,int (&now_board)[8][8],int (&lmgs_list)[8][8][8][8],int (&legal_moves_list)[8][8]);

//黒石白石の総数を数える関数宣言。
void count_stones(int& black_stones,int& white_stones,int (&now_board)[8][8]);

//勝者を判定し表する関数宣言。
void winner_checker(int& black_stones,int& white_stones);

//main関数。
int main()
{
    int board[8][8] = {}; //盤の状態変数。

    initialize_board(board);//盤面の初期化実行。

    draw_board(board);//盤面の描画実行。最初の一回。

    game_loop(board);
}



//関数の定義部。



//盤面初期化関数定義。
void initialize_board(int (&now_board)[8][8])//盤面を初期化する。
{
    int ini_board[8][8]
    ={
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,1,-1,0,0,0},
        {0,0,0,-1,1,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            now_board[i][j] = ini_board[i][j];
        }
    }
}



//取得可能な石のリストを初期化する関数。
void initialize_getable_stones(int (&getable_stones)[8][8])
{
    int ini_board[8][8]
    ={
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0}
    };
    
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            getable_stones[i][j] = ini_board[i][j];
        }
    }
}



//表示記号置換関数定義。
char replace_mark(int glid_state)//数値データを表示用の文字データに変換する。
{
    if(glid_state == 0)
    {
        return '#';
    }else if (glid_state == 1)
    {
        return 'b';
    }else if(glid_state==-1)
    {
        return 'w';
    }else
    {
        return 'e';
    }
}



//盤面描画関数定義。
void draw_board(int (&now_board)[8][8])//盤面の数値データを詠みだして描画する。
{
    for(int k=-1;k<8;k++)//一行目、座標の表示。空白の為ー１から始める。
    {
        if(k==-1)
        {
            std::cout << " ";
            k++;
        }
        std::cout << k+1;
    }

    std::cout << std::endl;

    for(int i=0;i<8;i++)//描画部分。列番号をつけている。
    {
        for(int j=-1;j<8;j++)
        {
            if(j==-1)
            {
                std::cout << i+1;
                j++;
            }
            std::cout << replace_mark(now_board[i][j]);
        }
        std::cout << std::endl;
    }
}



//座標が盤に乗ってるかを判定する関数定義。
bool on_the_board(int i,int j)
{
    if(-1<i && i<8 && -1<j && j<8)
    {
        return true;
    }
    return false;
}



//入力に応じて盤面を更新する関数定義。
void update_board(int counter,int (&now_board)[8][8],int i,int j)
{
    int sign=0;//0か1を取る。

    int getable_stones[8][8]={};

    sign = counter%2;

    if(!on_the_board(i-1,j-1))
    {
        return;
    }

    //ここで取得可能な石のリストを更新する。
    list_up_getable_stones(sign,now_board,getable_stones,i-1,j-1);

    if(legal_move(getable_stones)==false)
    {
        return;
    }

    now_board[i-1][j-1] = std::pow(-1,sign);//石を置いた場所をまず更新。

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            now_board[i][j] = now_board[i][j]*(std::pow((-1),getable_stones[i][j]));//取得可能な石のある場所は１なので、ー１を掛けることになり、白と黒が反転する。
        }
    }
    return;
}



//(i,j)に打った時の取得可能な石のリストを得る関数定義。
void list_up_getable_stones(int sign,int (&now_board)[8][8],int (&getable_stones)[8][8],int i,int j)
{
    initialize_getable_stones(getable_stones);//毎回最初に取得可能な石のリストは初期化する。

    if(now_board[i][j] != 0)
    {
        initialize_getable_stones(getable_stones);
        return;
    }
    
    for(int a=-1;a<2;a++)
    {
        for(int b=-1;b<2;b++)
        {
            if(on_the_board(i+a,j+b))//(i,j)からの隣接マスが盤に入っているかを確かめる。角や辺から飛び出して盤状態変数を参照することを防ぐ。
            {
                int t=1;

                while(now_board[i+t*a][j+t*b]==std::pow(-1,sign+1))//隣接マスはwhite(-1)/blackか？
                    {
                        ++t;
                    }
                if(now_board[i+t*a][j+t*b]==std::pow(-1,sign))//ループ終了時の点がblack/whiteか？石がない可能性に注意。
                    {
                        for(int u=1;u<t;u++)
                        {
                            getable_stones[i+u*a][j+u*b] = 1;//終端に自分の石があれば、そこまでの相手の石の位置を取得していく。
                        }
                    }
            }//(i+a,j+b)が盤から出た場合、次の(a,b)を検査する。
        }
    }
    return;//何も起きなければ初期化されたままのリストが返り、取得可能な石はないと判定される。
}



//合法手判定関数。
bool legal_move(int (&getable_stones)[8][8])
{
    int total_getable_stones=0;

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            total_getable_stones += getable_stones[i][j];
        }
    }

    if(total_getable_stones>0)
    {
        return true;
    }

    return false;
}



//入力受付定義。
void input_UI(int counter,int& i,int& j)
{
   if(counter%2==0)
   {
    counter=counter+1;
        std::cout << "turn: " << counter << " :first mover: ";
        std::cin >> i;
        std::cout << ",";
        std::cin >> j;
   }else{
    counter=counter+1;
        std::cout << "turn: " << counter <<" :second mover: ";
        std::cin >> i;
        std::cout << ",";
        std::cin >> j;
   }
}



//手番に手無を判定する関数定義。trueが返る間はその手番には手がある。
bool turn_player_have_move(int (&legal_moves_list)[8][8])
{
   int total_legal_moves=0;

    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            total_legal_moves += legal_moves_list[i][j];
        }
    }

    if(total_legal_moves==0)
    {
        return false;
    }
    return true;
}



//ゲームループ定義。
void game_loop(int (&board)[8][8])
{
    int counter=0;//先手は偶数、後手は奇数。

    int judge=0;//終局判定変数。

    int i=1,j=1;//石を置く座標。１から８までにしてある。

    //int getable_stones[8][8]={};//取得可能な石の座標を動的に記録する。変数の場所は変えるかも。←より高次の配列に置換。

    int lmgs_list[8][8][8][8]={};//(i,j)座標に石をおいたとき、(k.l)座標の石が取れるかの記録のリスト。

    int legal_moves_list[8][8]={};//合法手の座標を記録するリスト。

    int black_stones=0, white_stones=0;

    int debug=0;

    while(counter<10)
    {
        list_up_legal_moves_and_getable_stones(counter,board,lmgs_list,legal_moves_list);//ここでlmsgリストと合法手リストを生成。

        if(turn_player_have_move(legal_moves_list)==true)
        {
            judge=0;//もし手があればjudge変数は初期化される。

            input_UI(counter,i,j);//参照渡し。

            if(i==11)
            {
                break;//ゲーム終了。
            }

            update_board(counter,board,i,j);//画面の状態更新。

            draw_board(board);//盤面の描画実行。

        }else{
            ++judge;//手がなければjudge変数が１になる。
        }

        if(judge>1)//終局処理。
        {
            count_stones(black_stones,white_stones,board);
            winner_checker(black_stones,white_stones);
            break;
        }

        ++counter;
    }
}




//新しい方式で合法手判定を行う。合法手リストとその手に置ける取得可能な石のリストを同時に作るぜ！
//呼び出すたびに新しくリストを初期化するのは無駄なのでゲームループ前に初期化する。中で初期化はしない。
void list_up_legal_moves_and_getable_stones(int counter,int (&now_board)[8][8],int (&lmgs_list)[8][8][8][8],int (&legal_moves_list)[8][8]) //lmgsはlegal moves and getable stonesの頭文字から。
{
    int sign=0;//0か1を取る。

    int total_getable_stones=0;

    sign = counter%2;


    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)//legal_movesの方を確かめる。
        {
                    //ここで取得可能な石のリストを更新する。
            list_up_getable_stones(sign,now_board,lmgs_list[i][j],i,j);//lmgs_list[i][j]は２次の配列のはず・・・

            total_getable_stones=0;//ループの毎回で変数初期化。

            for(int k=0;k<8;k++)
            {
                for(int l=0;l<8;l++)
                {
                    total_getable_stones += lmgs_list[i][j][k][l];
                }
            }

            if(total_getable_stones==0)
            {
                legal_moves_list[i][j]=0;
            }else
            {
                legal_moves_list[i][j]=1;
            }
        }
    }
}



//黒石白石総数を数える関数定義。
void count_stones(int& black_stones,int& white_stones,int (&now_board)[8][8])
{
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(now_board[i][j]==1)
            {
                black_stones++;
            }else if(now_board[i][j]==-1)
            {
                white_stones++;
            }
        }
    }

    std::cout << "black : white = " << black_stones << ":" << white_stones << std::endl;
}



//勝者判定判定関数定義。
void winner_checker(int& black_stones,int& white_stones)
{
    if(black_stones > white_stones)
    {
        std::cout << "first mover wins" << std::endl;
    }else if(black_stones < white_stones)
    {
        std::cout << "second mover wins" << std::endl;
    }else
    {
        std::cout << "draw!!" << std::endl;
    }
}