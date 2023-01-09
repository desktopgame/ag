# Windows用ビルド手順
* 全てのライブラリを7zipなどで展開する。（ここに展開）
* freetype
    * `cd builds\windows\vc2010`を実行
    * `msbuild freetype.sln /t:build /p:Configuration=Release;Platform="x64"` を実行
    * `freetype.lib` が `objs` に生成されるが、これを親階層へ移動
* FreeImage
    * `WindowsTargetPlatformVersion` を正しいWindowsSDKバージョンに変更する(Windows11なら10.0.22000.0)
    * `PlatformToolset` を正しいVisualStudioバージョンに変更(2022ならv143)
    * `msbuild FreeImage.2017.sln /t:build /p:Configuration=Release;Platform="x64"` を実行
* リポジトリ直下の `readme.md` を参考に `cmake` 及び `make` を実行する