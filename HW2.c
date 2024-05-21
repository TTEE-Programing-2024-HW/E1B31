#include <stdio.h>
#include <stdlib.h>

int main() {
    // 定義變數
    int password = 2024;
    int input_password;
    char menu_choice;
    int n;

    // 顯示個人風格畫面
    printf("-------\n");
    printf("---------\n");
    printf("-----------\n");
    printf("-------------\n");
    printf("---------------\n");
    printf("-----------------\n");
    printf("-------------------\n");
    printf("---------------------\n");
    printf("-----------------------\n");
    printf("-------------------------\n");
    printf("-------------------------\n");
    printf("-----------------------\n");
    printf("---------------------\n");
    printf("-------------------\n");
    printf("-----------------\n");
    printf("---------------\n");
    printf("-------------\n");
    printf("-----------\n");
    printf("---------\n");
    printf("-------\n");
    printf("Please enter the 4-digit password: ");
    
    // 密碼驗證
    int x = 0;
    do {
        scanf("%d", &input_password);
        if (input_password == password) {
            break;
        } else {
            x++;
            printf("Incorrect password. x left: %d\n", 3 - x);
            if (x == 3) {
                printf("Too many incorrect x. Exiting program.\n");
                return 0;
            }
            printf("Please try again: ");
        }
    } while (x < 3);
    
    // 清除畫面，顯示主選單
    system("cls");
    printf("Main Menu:\n");
    printf("--------------------------\n");
    printf("| a. Draw Right Triangle |\n");
    printf("| b. Show Multiplication Table |\n");
    printf("| c. Exit |\n");
    printf("--------------------------\n");
    printf("Please select an option: ");
    scanf(" %c", &menu_choice);
    
    // 主選單選項處理
    switch (menu_choice) {
        case 'a':
        case 'A':{
            // 畫出直角三角形
            char triangle_char;
            printf("Enter a character from 'a' to 'n': ");
            scanf(" %c", &triangle_char);
            // 檢查輸入是否在合法範圍內
            if (triangle_char < 'a' || triangle_char > 'n') {
                printf("Invalid character. Please enter a character from 'a' to 'n'.\n");
                break;
            }
            // 繪製直角三角形
            // 這裡放繪製直角三角形的程式碼
            printf("Drawing right triangle with character '%c'.\n", triangle_char);
            break;
            }
        case 'b':
        case 'B':{
            // 顯示乘法表
            printf("Enter a number from 1 to 9: ");
            scanf("%d", &n);
            // 檢查輸入是否在合法範圍內
            if (n < 1 || n > 9) {
                printf("Invalid input. Please enter a number from 1 to 9.\n");
                break;
            }
            // 顯示乘法表
            printf("Multiplication Table for %d:\n", n);
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    printf("%d\t", i * j);
                }
                printf("\n");
            }
            break;
            }
        case 'c':
        case 'C':{
            // 結束程式或回到主選單
            char continue_choice;
            printf("Continue? (y/n): ");
            scanf(" %c", &continue_choice);
            if (continue_choice == 'y' || continue_choice == 'Y') {
                main(); // 回到主選單
            } else if (continue_choice == 'n' || continue_choice == 'N') {
                return 0; // 結束程式
            } else {
                printf("Invalid choice. Please enter 'y' or 'n'.\n");
            }
            break;
            }
        default:{
            printf("Invalid choice. Please select 'a', 'b', or 'c'.\n");
            break;
            }
    }

    return 0;
}
/*寫程式是一個不斷學習和成長的過程。重要的是要保持耐心和毅力，因為遇到問題是很正常的，而解決問題的過程通常是最寶貴的學習經驗之一。
在寫程式的過程中很常沒有發現自己的錯誤一直卡關就會去問懂得人，經過指導後就會猛然發現自己犯的愚蠢錯誤，也因為這些錯誤，下次就不會在
同一個點犯上同樣的錯。 


寫程式最重要的是享受過程，並不斷探索新的技術和工具，這樣才能保持創造力和熱情。
無論是解決實際問題還是創造有趣的應用程序，都讓寫程式變得有趣且有意義。
保持開放的心態，接受反饋和建議，這樣才能夠不斷地成長和提高自己寫程式的技能 
*/ 