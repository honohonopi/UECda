#include<stdio.h>
#include"common.h"
#include"daihinmin.h"
#include"select_cards.h"

void select_change_cards(int out_cards[8][15],int my_cards[8][15],int num_of_change){
  /*
   * カード交換時のアルゴリズム
   * 大富豪あるいは富豪が、大貧民あるいは貧民にカードを渡す時のカードを
   * カードテーブルmy_cardsと交換枚数num_of_changeに応じて、
   * 低いほうから選びカードテーブルout_cardsにのせる
  */
  int count=0;
  int one_card[8][15];
  
  clear_table(out_cards);
  while(count<num_of_change){
    search_low_card(one_card,my_cards,0);
    diff_cards(my_cards,one_card);
    or_cards(out_cards,one_card);
    count++;
  }
}

void select_submit_cards(int out_cards[8][15],int my_cards[8][15], state *field_status){
  int select_cards[8][15];
 
  clear_table(select_cards);

  if(field_status->is_rev==0){ // 革命中でない
    if(field_status->is_no_card==1){ // 場にカードが無いとき
      select_cards_free(select_cards, my_cards, field_status); // 通常時の提出用(自分の手持ちのカードの中で一番弱いカードを単騎で提出)
    }else{ // 場にカードがある時
      select_cards_restrict(select_cards,my_cards, field_status); // 通常時の提出用(場が単騎の時に自分の手持ちのカードのうちで一番弱いカードを単騎で提出)
    }
  }else{ // 革命中である
    if(field_status->is_no_card==1){ // 場にカードが無いとき
      select_cards_free_rev(select_cards, my_cards, field_status); // 革命時の提出用
    }else{ // 場にカードがある時
      select_cards_restrict_rev(select_cards, my_cards, field_status); // 革命時の提出用
    }
  }

  copy_table(out_cards, select_cards);
}

void select_cards_free(int select_cards[8][15], int my_cards[8][15], state *field_status){
  int info_table[8][15];
  make_info_table(info_table, my_cards);
  if (count_cards(select_cards) == 0){
    search_low_sequence(select_cards, info_table, my_cards); // 階段を探す
  }
  if (count_cards(select_cards) == 0){
    search_low_pair(select_cards, info_table, my_cards);  // 階段がなければペアを探す
  }
  if (count_cards(select_cards) == 0){
    search_low_card(select_cards, my_cards, 0); // ペアがなければ単騎を出す
  }
}

void select_cards_restrict(int select_cards[8][15], int my_cards[8][15], state *field_status){
  int tmp_cards[8][15];
 
  copy_table(tmp_cards, my_cards); 

  if(field_status->is_sequence==1){ // 場が階段のとき
    if(field_status->is_lock==1){ // 場が縛られている

    }else{ // 場が縛られていない

    }

  }else if(field_status->quantity > 1){ // 場がペアのとき
    if(field_status->is_lock==1){ // 場が縛られている

    }else{ // 場が縛られていない

    }
  }else{ // 場が単騎のとき
    if(field_status->is_lock==1){ // 場が縛られている
      remove_suit(tmp_cards, field_status->suit, 1);
      remove_low_card(tmp_cards, field_status->order, 0); 
      search_low_card(select_cards,tmp_cards,1); 
    }else{ // 場が縛られていない
      remove_low_card(tmp_cards, field_status->order, 0); 
      search_low_card(select_cards,tmp_cards,1); 
    }
  }
}

void select_cards_free_rev(int select_cards[8][15], int my_cards[8][15], state *field_status){
}

void select_cards_restrict_rev(int select_cards[8][15], int my_cards[8][15], state *field_status){
}

void operate_my_cards(int my_cards[8][15], state *field_status){
}

void operate_field_cards(int ba_cards[8][15], state *field_status){
}

