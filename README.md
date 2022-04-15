# AntiAVfish_open

AntiAVfish_x64  一款简单的免杀shellcode生成器 
编译环境:VS2022   V143

这个项目是对之前发布的AntiAVfish的开源版本，优化了许多地方。 只支持x64，x86自己拿来改改就能用了

AntiAVfish_x64.cpp 是主程序，用于提取资源的PE文件并生成免杀马
CodeTemplate_x64_1.bin  免杀马的模板PE文件，原理是利用 VEH HOOK 和 EnumUILanguagesA 做到隐藏和执行shellcode的目的。 隐藏控制台我注释了，如果要用的话改掉就好。(应该也没人会用)


免杀测试:
Win10 x64    成功执行命令
![7GY8Q4$LX~GEI6ZF7PH 77D](https://user-images.githubusercontent.com/82560112/163532528-718ac8d4-50c7-4548-9abb-adc181c60c66.png)


绿熊的含金量还是很高的，WD，数字，盾牌基本没问题.  
这里只是提供一种思路，不知道哪时候就用不了了，对抗是在不断变化的，所以还得继续巩固基础和掌握更多的套路。
