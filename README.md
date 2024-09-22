# 第二次任务报告

总体思路:用到什么查什么,什么不会查什么,基本就这样了,因为也没时间系统去学.
chatgpt用了但不多,只是用来看看用了哪些函数;最主要的还是在知乎和csdn上去搜索该函数怎么用的,定义是怎么样的,这个数据类型是干什么的...

### 使用网址

用了很多,好像放的这些不太全,因为当时用的时候也没想到之后还要保存网址,每次退出浏览器就清空历史了,所以就只能放最后查的一些网址(不过幸好这两天没有关电脑所以留得也不少)

- https://blog.csdn.net/Young__Fan/article/details/81866237
- https://blog.csdn.net/mars_xiaolei/article/details/93081046
- https://blog.csdn.net/qq_27278957/article/details/88864928
- https://blog.csdn.net/ZBC010/article/details/120656248
- https://blog.csdn.net/qq_40622955/article/details/119180886
- https://zhuanlan.zhihu.com/p/110330329
- https://blog.csdn.net/qq_41433002/article/details/115266567
- https://blog.csdn.net/kksc1099054857/article/details/76569718
- https://blog.csdn.net/u012566751/article/details/77046445
- https://blog.csdn.net/Ethan_Rich/article/details/140337238
- https://blog.csdn.net/ChenWenHaoHaoHao/article/details/128553725
- https://blog.csdn.net/fuxiaoxiaoyue/article/details/82747332
- https://blog.csdn.net/xddwz/article/details/110561132
- https://blog.csdn.net/qq_41204464/article/details/89736793
- https://blog.csdn.net/hjl_heart/article/details/109389619
- https://blog.csdn.net/2301_77444219/article/details/139397476
- https://blog.csdn.net/luozhichengaichenlei/article/details/104699802
- https://blog.csdn.net/luozhichengaichenlei/article/details/104699802
- https://blog.csdn.net/weixin_46196863/article/details/110520145
- https://blog.csdn.net/weixin_46196863/article/details/110520145
- https://blog.csdn.net/qq_33810188/article/details/81285867
- https://blog.csdn.net/weixin_43645790/article/details/104093174
- https://blog.csdn.net/u011775793/article/details/135068880
- https://blog.csdn.net/IYXUAN/article/details/124458001
- https://blog.csdn.net/m0_50616665/article/details/124810344

### chatgpt使用

![alt text](<截图 2024-09-22 11-26-09.png>) ![alt text](<截图 2024-09-22 11-26-34.png>) ![alt text](<截图 2024-09-22 11-27-02.png>)

### errors

中间绘制轮廓的部分曾有一个报错:(-215:Assertion failed) size.width>0 && size.height>0 in function 'cv::imshow'(可惜我当时没有截图),最后经过网上查找与不停的修改代码,终于发现是我在Mat定义变量的时候没有规定尺寸,新的图片与test_image.png的size不相符,规定size后错误解除.

