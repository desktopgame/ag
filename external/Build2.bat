msbuild freetype-2.12.1\builds\windows\vc2010\freetype.sln /t:build /p:Configuration=Release;Platform="x64" -m
msbuild FreeImage\FreeImage.2017.sln /t:build /p:Configuration=Release;Platform="x64" -m
move freetype-2.12.1\objs\x64\Release\freetype.lib freetype-2.12.1\freetype.lib
move freetype-2.12.1\objs\x64\Release\freetype.dll dll\freetype.dll
move FreeImage\Dist\x64\FreeImage.dll dll\FreeImage.dll
pause