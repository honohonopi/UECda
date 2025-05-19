#include<stdio.h>
#include<string.h>
#include<strings.h>
#include"common.h"

void search_low_card(int out_cards[8][15],int my_cards[8][15],int use_joker_flag){
  /*
    低い方から探して,最初に見つけたカードを一枚out_cardsにのせる。
    use_joker_flagが1のとき,カードが見つからなければ,jokerを一枚out_cardsにのせる。
  */
  int i,j,find_flag=0;

  clear_table(out_cards);                  //テーブルをクリア
  for(j=1;j<14&&find_flag==0;j++){        //低い方からさがし
    for(i=0;i<4&&find_flag==0;i++){
      if(my_cards[i][j]==1){              //カードを見つけたら               
        find_flag=1;                      //フラグを立て
        out_cards[i][j]=my_cards[i][j];   //out_cardsにのせ,ループを抜ける。
      }
    }
  }
  if(find_flag==0&&use_joker_flag==1){       //見つからなかったとき
    out_cards[0][14]=2;                  //ジョーカーをのせる
  }
}

void search_low_pair(int out_cards[8][15],int my_cards[8][15],int use_joker_flag){
  /*
    低い方から探して,最初に見つけたカードを一枚out_cardsにのせる。
    use_joker_flagが1のとき,カードが見つからなければ,jokerを一枚out_cardsにのせる。
  */
  int i,j,find_flag=0;
  clear_table(out_cards); // カード選択用の配列を初期化
  for (j = 1; j < 14; j++){ // ペア出し
    int count = 0;
    for (i = 0; i < 4; i++){ // 全スートについて
      if (my_cards[i][j] == 1){
        count++;
      }
    }
    if (count >= 2){ // ペアが見つかった場合
      int put = 0;
      for (i = 0; i < 4 && put < 2; i++){
        if (my_cards[i][j] == 1){
          out_cards[i][j] = 1;
          put++;
        }
      }
      return;
    }
  }
}

void search_low_sequence(int out_cards[8][15],int my_cards[8][15],int use_joker_flag){
  /*
    低い方から探して,最初に見つけたカードを一枚out_cardsにのせる。
    use_joker_flagが1のとき,カードが見つからなければ,jokerを一枚out_cardsにのせる。
  */
  int i,j,find_flag=0;
  clear_table(out_cards); // カード選択用の配列を初期化
  for (i = 1; i < 4; i++){ // 階段出し
    int count = 0;
    for (j = 0; j < 14; j++){ // 全数字について
      if (my_cards[i][j] == 1){
        count++;
      }
    }
    if (count >= 3){ // 階段が見つかった場合
      int put = 0;
      for (j = 0; j < 14; j++){
        if (my_cards[i][j] == 1){
          out_cards[i][j] = 1;
          put++;
        }
      }
      return;
    }
  }
}

void search_low_pair_restrict(int out_cards[8][15],int my_cards[8][15],int use_joker_flag, int pair){ // ペア出し,指定した枚数のペアをdst_cardsに乗せる


}