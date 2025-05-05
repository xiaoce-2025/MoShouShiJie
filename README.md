# MoShouShiJie
北京大学程序设计实习2025春魔兽世界大作业
## 题目
[魔兽世界终极版](http://cxsjsx.openjudge.cn/hw202515/A/)

[魔兽世界一(备战)](http://cxsjsx.openjudge.cn/hw202502/E/)

[魔兽世界终(装备)](http://cxsjsx.openjudge.cn/hw202504/C/)

[魔兽世界三(开战)](http://cxsjsx.openjudge.cn/hw202505/E/)
## 关于魔兽世界终极版一些比较容易忽视的内容（？

1. 关于dragon士气取小数点后两位的问题

这个我自己也没有研究明白他是一个什么机制，但是将士气用double类型替换float类型后是可以ac的。（详见代码中实现）

2. sword生成时即有可能攻击力为0，要在生成时进行检验

3. 魔兽世界终极版测试数据量较大，如何快速发现wrong answer的点？

首先，在代码main函数开头添加以下片段将输出重定向到文件中（记得include fstream）
```c++
streambuf *orig_buf = std::cout.rdbuf();
ofstream out("output.txt");
if (out){
	std::cout.rdbuf(out.rdbuf());
}
```

接着便可以通过文本比对网站（[推荐这个网站](https://www.qianbo.com.cn/Tool/File-Difference/)）来快速查看标准输出与你的输出的区别
