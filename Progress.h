//進捗バーの表示
//制作者　安保圭一郎
//
//デフォルトでは、仮の画像を元に作られており、画面の中央の上側に表示している
//赤い三角形が、進捗を示すアイコン

#ifndef PROGRESS_H_
#define PROGRESS_H_

void Progress_Init(void);
void Progress_Uninit(void);
void Progress_Update(void);
void Progress_Draw(void);

#endif //PROGRESS_H_