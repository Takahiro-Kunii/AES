//
//  main.c
//  AES
//
//  Created by Takahiro Kunii on 2015/11/03.
//  Copyright © 2015年 Takahiro Kunii. All rights reserved.
//

#include <stdio.h>
#import <CommonCrypto/CommonCrypto.h>

int main(int argc, const char * argv[]) {
    //  平文
    const char* text = "Hello cipher\n";
    
    //  キー（256ビット＝32バイト）
    int8_t key[] = {0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7};
    
    //  暗号文を格納するバッファ
    size_t cipher[100];
    //  暗号化
    size_t numBytesEncrypted;   //  暗号文のバイト数が設定される
    CCCryptorStatus cryptStatus = CCCrypt(
                                          kCCEncrypt,               //  暗号化
                                          kCCAlgorithmAES,          //  AES使用
                                          kCCOptionPKCS7Padding     //  AESは128ビットごとのブロックで暗号化する。
                                          //  そのため平文が、128ビット境界にぴったり収まらないなら
                                          //  後ろに詰め物をして128ビット境界にする必要がある。
                                          //  その詰め方としてPKCS7を指定した
                                          | kCCOptionECBMode,       //  ECBは圧縮方法のオプション。
                                          //  暗号強度は少し落ちるが初期化ベクタを必要としないので指定
                                          key, 32,                  //  キーとキーの大きさをバイト単位で指定（32=256ビット）
                                          NULL,                     //  ECBを指定したので不要。NULLを指定する。
                                          text, strlen(text),       //  平文と、その大きさをバイト単位で指定
                                          cipher, 100,              //  暗号文を入れてもらうバッファとその大きさをバイト単位で指定
                                          &numBytesEncrypted);      //  暗号文の大きさをバイト単位で受け取る
    if (cryptStatus == kCCSuccess) {    //  成功
        //  標準エラー出力への書き出し
        fwrite(cipher, sizeof(int8_t), numBytesEncrypted, stderr);
        
        //  標準出力へ結果を表示
        printf("\n\n%zuバイトの文字列を%zuバイトの暗号にした。\n", strlen(text), numBytesEncrypted);
    } else {                            //  失敗
        printf("error = %d\n", cryptStatus);
    }

    return 0;
}
