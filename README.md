# AviUtl プラグイン - 最終フレーム自動調整

* 2.0.1 by 蛇色 - 2022/05/11 AviUtl で動画を開いたあと拡張編集で編集作業をするとフリーズする問題を修正
* 2.0.0 by 蛇色 - 2022/05/11 リファクタリング
* 1.0.3 by 蛇色 - 2022/01/23 オブジェクトの個数を取得するように修正
* 1.0.2 by 蛇色 - 2021/12/20 メイン処理を func_proc() で行うように修正
* 1.0.1 by 蛇色 - 2021/08/22 最終フレームが 0 にならないように修正
* 1.0.0 by 蛇色 - 2021/08/03 初版

タイムラインを編集したとき、最終フレームを自動的に調整します。

## ダウンロード

1. ページ右側にある [Releases](/../../releases) をクリックして移動します。
2. ダウンロードしたいバージョンをクリックして移動します。
3. Assets の下に圧縮ファイルがあるのでクリックしてダウンロードします。

## インストール

以下のファイルを AviUtl の Plugins フォルダに入れてください。
* AdjustLastFrame.auf

## 動作確認

* (必須) AviUtl 1.10 & 拡張編集 0.92 http://spring-fragrance.mints.ne.jp/aviutl/
* (共存確認) patch.aul r21 https://scrapbox.io/ePi5131/patch.aul

## クレジット

* Microsoft Research Detours Package https://github.com/microsoft/Detours
* aviutl_exedit_sdk https://github.com/ePi5131/aviutl_exedit_sdk
* Common Library https://github.com/hebiiro/Common-Library
