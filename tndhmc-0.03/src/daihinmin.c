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

void make_info_table(int info_table[8][15], int my_cards[8][15]){
  clear_table(info_table);
  // ジョーカー無し階段情報の追加
  for (int i = 0; i < 4; i++){
    for (int j = 13; j > 0; j--){
      if (my_cards[i][j] == 1){
        info_table[i][j] = info_table[i][j+1]+1; // 連続数を更新
      }
    }
  }
  for (int i = 0; i < 4; i++){
    for (int j = 0; j < 15; j++){
      if (my_cards[i][j] == 2){
        info_table[i][j] = 1; // 2連続は階段に満たないので1とする
      }
    }
  }
  // ジョーカー無しペア情報の追加
  for(int i = 1; i <= 13; i++){
    info_table[4][i] = my_cards[0][i] + my_cards[1][i] + my_cards[2][i] + my_cards[3][i];
  }
}

int search_low_pair(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]){
  clear_table(dst_cards);
  for(int i = 1; i < 14; i++){
    if (info_table[4][i] >= 2) {
      for(int j = 0; j < 4; j++){
        dst_cards[j][i] = my_cards[j][i];
      }
      return 1;
    }
  }
  return 0;
}

int search_low_sequence(int dst_cards[8][15], int info_table[8][15], int my_cards[8][15]){
  clear_table(dst_cards);
  for (int i = 1; i < 14; i++){
    for (int j = 0; j < 4; j++){
      if (info_table[j][i] >= 3){
        for(int k = 0; k < info_table[j][i]; k++){
          dst_cards[j][i+k] = 1;
        }
        return 1;
      }
    }
  }
  return 0;
}