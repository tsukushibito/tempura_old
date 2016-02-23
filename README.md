# tempura
Game engine project

memo:  
・Windows環境でのGLEWのビルド手順  
１）msys2をインストール  
２）msys2にPerlとPythonをインストール（pacman -S perl、pacman -S python）  
３）third_party/glewのフォルダでmake extensions(必要なヘッダが作成されます)  
４）third_party/glew/build/vsXXのソリューションでビルド  
