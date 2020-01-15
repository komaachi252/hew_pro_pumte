//UIの表示
//制作者　安保圭一郎
//
//デフォルトでは、仮の画像を元に作られており、左上に表示している　本画像が来た場合調整必須
//ナンバー表示のポジションのマジックナンバーはご容赦ください　（defineするにも何だかなぁ）
//タイム表示の部分は小数点はないが、デフォルトの下2桁は小数となっている
//例：ゲーム画面で「Time:11451」の場合　「114.51秒」となる

#ifndef UI_H_
#define UI_H_

void UI_Init(void);
void UI_Uninit(void);
void UI_Update(void);
void UI_Draw(void);



#endif //UI_H_
